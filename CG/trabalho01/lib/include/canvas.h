/**
 * @file canvas.h
 * @brief Interface da camada de framebuffer (matriz de pixels) do projeto.
 *
 * Este módulo define a abstração fundamental sobre a qual toda a
 * rasterização é construída: um framebuffer linear de pixels de 32 bits
 * (formato RGBA empacotado em um @c uint32_t). Nenhuma rotina de desenho
 * de alto nível da SDL (como SDL_RenderDrawLine ou SDL_RenderFillRect)
 * é utilizada: a SDL atua apenas como camada de exibição da matriz de
 * pixels, e toda a escrita de cor é feita manualmente, pixel a pixel,
 * pelas funções deste módulo.
 *
 * @note A matriz de pixels é armazenada em ordem linear (row-major):
 *       o pixel (x, y) ocupa a posição `width * y + x` do vetor.
 *       Essa linearização é a base do gerenciamento manual do framebuffer.
 *
 * @warning A estrutura Canvas NÃO é dona da memória de pixels; ela apenas
 *          referencia um buffer alocado externamente (ex.: a textura/surface
 *          da SDL). O chamador é responsável pelo ciclo de vida do buffer.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Representa o framebuffer raster manipulado diretamente pelo programa.
 *
 * Encapsula o ponteiro para a matriz linear de pixels e suas dimensões
 * lógicas. Todas as primitivas de rasterização (linhas, círculos,
 * triângulos, texto) escrevem cores exclusivamente através desta estrutura,
 * garantindo um único ponto de acesso à memória de vídeo simulada.
 */
struct canvas {
	uint32_t *pixels; /**< Ponteiro para a matriz linear de pixels (RGBA de 32 bits, row-major). */
	int width;        /**< Largura do framebuffer em pixels (número de colunas). */
	int height;       /**< Altura do framebuffer em pixels (número de linhas). */
};
typedef struct canvas Canvas; /**< Apelido de tipo para @ref canvas. */

/**
 * @brief Inicializa um Canvas associando-o a um buffer de pixels existente.
 *
 * @param canvas Ponteiro para a estrutura Canvas a ser inicializada.
 * @param pixels Buffer linear de pixels previamente alocado (width * height posições).
 * @param width  Largura do buffer em pixels.
 * @param height Altura do buffer em pixels.
 * @return Nenhum.
 *
 * @note Não há alocação interna: a função apenas registra o ponteiro e as
 *       dimensões, mantendo o módulo independente de qualquer gerenciador
 *       de memória ou biblioteca externa.
 * @warning O buffer @p pixels deve permanecer válido durante toda a vida
 *          útil do Canvas.
 */
void canvas_init(Canvas *canvas, uint32_t *pixels, int width, int height);

/**
 * @brief Verifica se a coordenada (x, y) pertence à área válida do framebuffer.
 *
 * @param canvas Canvas alvo.
 * @param x Coordenada horizontal (coluna), em pixels.
 * @param y Coordenada vertical (linha), em pixels.
 * @return @c true se 0 <= x < width e 0 <= y < height; @c false caso contrário.
 *
 * @note Este teste implementa o "clipping" por pixel: como os algoritmos de
 *       rasterização podem gerar coordenadas fora da tela (ex.: formas
 *       parcialmente visíveis), o recorte é resolvido aqui, no ponto único
 *       de escrita, evitando acesso inválido à memória.
 */
bool canvas_in_bounds(Canvas *canvas, int x, int y);

/**
 * @brief Escreve a cor @p c no pixel (x, y) do framebuffer (operação atômica de rasterização).
 *
 * Esta é a primitiva mais básica de todo o sistema gráfico: TODAS as demais
 * rotinas de desenho (Bresenham, círculo do ponto médio, preenchimento por
 * scanline, texto bitmap) reduzem-se, em última instância, a chamadas desta
 * função. É a materialização do conceito de rasterização "do zero".
 *
 * @param canvas Canvas alvo.
 * @param x Coordenada horizontal do pixel.
 * @param y Coordenada vertical do pixel.
 * @param c Cor RGBA empacotada em 32 bits (ver color.h).
 * @return Nenhum.
 *
 * @note Coordenadas fora dos limites são silenciosamente descartadas
 *       (clipping), tornando as primitivas de desenho robustas sem que
 *       cada algoritmo precise tratar bordas individualmente.
 */
void canvas_put_pixel(Canvas *canvas, int x, int y, uint32_t c);

/**
 * @brief Lê a cor armazenada no pixel (x, y).
 *
 * @param canvas Canvas alvo.
 * @param x Coordenada horizontal do pixel.
 * @param y Coordenada vertical do pixel.
 * @return A cor RGBA de 32 bits do pixel, ou 0 se a coordenada estiver fora dos limites.
 *
 * @note Função essencial para algoritmos que dependem de leitura do
 *       framebuffer, como o flood fill (preenchimento por inundação),
 *       que compara a cor-alvo dos vizinhos antes de pintá-los.
 * @warning O valor de retorno 0 (transparente/preto sem alfa) é ambíguo:
 *          pode indicar tanto "fora dos limites" quanto um pixel realmente
 *          com valor 0. Use canvas_in_bounds() quando a distinção importar.
 */
uint32_t canvas_get_pixel(Canvas *canvas, int x, int y);

/**
 * @brief Preenche todo o framebuffer com uma única cor (limpeza de tela).
 *
 * @param canvas Canvas alvo.
 * @param c Cor RGBA de preenchimento.
 * @return Nenhum.
 *
 * @note Percorre o buffer como vetor unidimensional (width * height
 *       iterações), explorando a linearidade da matriz para máxima
 *       simplicidade e localidade de cache.
 */
void canvas_fill(Canvas *canvas, uint32_t c);

/**
 * @brief Copia (blit) uma região retangular de um canvas de origem para um canvas de destino.
 *
 * Implementa manualmente a operação clássica de "bit block transfer":
 * a cópia é feita linha a linha com @c memcpy, pois dentro de uma mesma
 * linha os pixels são contíguos em memória — o que torna a transferência
 * de cada linha uma única cópia de bloco, muito mais eficiente do que
 * copiar pixel a pixel.
 *
 * @param dst    Canvas de destino.
 * @param x0     Coordenada x do canto superior esquerdo da região no destino.
 * @param y0     Coordenada y do canto superior esquerdo da região no destino.
 * @param src    Canvas de origem.
 * @param x1     Coordenada x do canto superior esquerdo da região na origem.
 * @param y1     Coordenada y do canto superior esquerdo da região na origem.
 * @param width  Largura da região copiada, em pixels.
 * @param height Altura da região copiada, em pixels.
 * @return Nenhum.
 *
 * @warning Esta rotina NÃO realiza clipping: o chamador deve garantir que
 *          a região [x..x+width) x [y..y+height) seja válida em ambos os
 *          canvases, sob pena de acesso fora dos limites do buffer.
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
		);

#endif
