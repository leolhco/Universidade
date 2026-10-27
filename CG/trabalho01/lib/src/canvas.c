/**
 * @file canvas.c
 * @brief Implementação da camada de framebuffer (matriz de pixels).
 *
 * Contém a lógica de gerenciamento direto da matriz de pixels: indexação
 * linear, recorte (clipping) por pixel, leitura/escrita de cor, limpeza e
 * cópia de blocos (blit). Nenhuma função de desenho da SDL ou de qualquer
 * biblioteca gráfica de alto nível é utilizada — toda manipulação de cor
 * ocorre por escrita direta na memória do framebuffer.
 *
 * @note Convenção de coordenadas: origem (0,0) no canto superior esquerdo,
 *       eixo x crescendo para a direita e eixo y crescendo para baixo
 *       (padrão raster), o que explica o índice `width * y + x`.
 */

#include "canvas.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Macro de indexação que traduz coordenadas 2D (x, y) para a posição
 *        correspondente no vetor linear de pixels.
 *
 * A fórmula `width * y + x` é a linearização row-major clássica de uma
 * matriz bidimensional: pular @c y linhas completas (cada uma com @c width
 * pixels) e avançar @c x colunas dentro da linha atual.
 *
 * @param canvas Ponteiro para o Canvas.
 * @param x Coordenada horizontal (coluna).
 * @param y Coordenada vertical (linha).
 *
 * @warning A macro NÃO valida limites; ela expande para um lvalue cru.
 *          A validação é responsabilidade das funções públicas que a usam
 *          (via canvas_in_bounds()).
 */
#define CANVAS_AT(canvas, x, y) \
	((canvas)->pixels[(canvas)->width * (y) + (x)])

/**
 * @brief Inicializa um Canvas associando-o a um buffer de pixels existente.
 *
 * @param canvas Estrutura a inicializar.
 * @param pixels Buffer linear de pixels (width * height posições) alocado pelo chamador.
 * @param width  Largura em pixels.
 * @param height Altura em pixels.
 * @return Nenhum.
 *
 * @note O Canvas apenas referencia o buffer; não há cópia nem alocação,
 *       mantendo o módulo desacoplado da camada de janela/SDL.
 */
void canvas_init(Canvas *canvas, uint32_t *pixels, int width, int height)
{
	canvas->pixels = pixels;
	canvas->width = width;
	canvas->height = height;
}

/**
 * @brief Testa se (x, y) está dentro da área válida do framebuffer.
 *
 * @param canvas Canvas alvo.
 * @param x Coordenada horizontal.
 * @param y Coordenada vertical.
 * @return @c true se o pixel é endereçável; @c false caso contrário.
 *
 * @note Centralizar o teste de limites aqui permite que todos os algoritmos
 *       de rasterização desenhem livremente "para fora" da tela: o recorte
 *       acontece de forma transparente no momento da escrita.
 */
bool canvas_in_bounds(Canvas *canvas, int x, int y)
{
	return 0 <= x && x < canvas->width && 0 <= y && y < canvas->height;
}

/**
 * @brief Escreve a cor @p c no pixel (x, y), com clipping automático.
 *
 * Primitiva atômica de rasterização do projeto: linhas (Bresenham),
 * círculos (ponto médio), triângulos (scanline) e texto bitmap convergem
 * todos para esta única escrita direta na matriz de pixels.
 *
 * @param canvas Canvas alvo.
 * @param x Coordenada horizontal do pixel.
 * @param y Coordenada vertical do pixel.
 * @param c Cor RGBA de 32 bits.
 * @return Nenhum.
 *
 * @note Escritas fora dos limites são descartadas silenciosamente — esse é
 *       o mecanismo de clipping por pixel de todo o sistema gráfico.
 */
void canvas_put_pixel(Canvas *canvas, int x, int y, uint32_t c)
{
	if (!canvas_in_bounds(canvas, x, y)) return;

	CANVAS_AT(canvas, x, y) = c;
}

/**
 * @brief Lê a cor do pixel (x, y).
 *
 * @param canvas Canvas alvo.
 * @param x Coordenada horizontal do pixel.
 * @param y Coordenada vertical do pixel.
 * @return Cor RGBA de 32 bits, ou 0 se (x, y) estiver fora dos limites.
 *
 * @note Usada por algoritmos que dependem do estado atual do framebuffer,
 *       como o flood fill, que precisa comparar a cor dos pixels vizinhos
 *       com a cor-alvo antes de substituí-la.
 * @warning Retorno 0 é ambíguo (fora dos limites vs. pixel com valor 0);
 *          verifique canvas_in_bounds() quando necessário.
 */
uint32_t canvas_get_pixel(Canvas *canvas, int x, int y)
{
	if (!canvas_in_bounds(canvas, x, y)) return 0;

	return CANVAS_AT(canvas, x, y);
}

/**
 * @brief Preenche todo o framebuffer com a cor @p c.
 *
 * @param canvas Canvas alvo.
 * @param c Cor RGBA de preenchimento.
 * @return Nenhum.
 *
 * @note O laço trata o framebuffer como vetor 1D de width*height posições,
 *       o que evita aritmética 2D desnecessária e maximiza a localidade de
 *       acesso à memória. Tipicamente usada para limpar a tela a cada frame.
 */
void canvas_fill(Canvas *canvas, uint32_t c)
{
	for (int p = 0; p < canvas->width * canvas->height; p++) {
		canvas->pixels[p] = c;
	}
}	

/**
 * @brief Copia uma região retangular do canvas @p src para o canvas @p dst (blit manual).
 *
 * A cópia é organizada por linhas (scanlines): como os pixels de uma mesma
 * linha são contíguos na memória (layout row-major), cada linha da região
 * pode ser transferida com um único @c memcpy de `width * sizeof(uint32_t)`
 * bytes. Isso reduz a operação de O(width*height) escritas individuais para
 * @p height cópias de bloco — a essência da técnica de "bit block transfer".
 *
 * @param dst    Canvas de destino.
 * @param x0     X do canto superior esquerdo da região no destino.
 * @param y0     Y do canto superior esquerdo da região no destino.
 * @param src    Canvas de origem.
 * @param x1     X do canto superior esquerdo da região na origem.
 * @param y1     Y do canto superior esquerdo da região na origem.
 * @param width  Largura da região, em pixels.
 * @param height Altura da região, em pixels.
 * @return Nenhum.
 *
 * @warning Não há clipping nesta rotina: regiões parcialmente fora de
 *          qualquer um dos canvases causam acesso inválido à memória.
 *          O chamador deve garantir coordenadas e dimensões válidas.
 * @warning Se @p dst e @p src referenciarem o mesmo buffer com regiões
 *          sobrepostas, o comportamento é indefinido (semântica do memcpy).
 */
void canvas_blit(
		Canvas *dst,
		int x0,
		int y0,
		Canvas *src,
		int x1,
		int y1,
		int width,
		int height
		)
{
	for (int h = 0; h < height; h++) {
		uint32_t *dst_row = &CANVAS_AT(dst, x0, y0 + h);
		uint32_t *src_row = &CANVAS_AT(src, x1, y1 + h);

		memcpy(dst_row, src_row, width * sizeof(uint32_t));
	}
}
