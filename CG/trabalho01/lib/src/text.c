/**
 * @file text.c
 * @brief Implementação do renderizador de texto bitmap sobre o framebuffer.
 *
 * Converte strings ASCII em pixels usando a fonte 8x8 embutida: para cada
 * caractere, os 8 bytes do glifo são percorridos linha a linha e bit a
 * bit; cada bit aceso é rasterizado como um retângulo preenchido de
 * scale x scale pixels. Todo o desenho passa pelas primitivas próprias do
 * projeto (draw_fill_rect → triângulos → Bresenham → put_pixel), sem
 * nenhuma biblioteca de fontes ou de texto.
 */

#include "font8x8_basic.h"
#include "text.h"
#include <string.h>

/** @brief Largura de cada glifo da fonte embutida, em pixels (antes da escala). */
#define FONT_WIDTH 8

/** @brief Altura de cada glifo da fonte embutida, em pixels (antes da escala). */
#define FONT_HEIGHT 8

/**
 * @brief Desenha uma string no canvas a partir da posição (x, y).
 *
 * **Decodificação do glifo:** `font8x8_basic[c][h]` fornece a máscara de
 * bits da linha @c h do caractere @c c. O bit @c b é extraído com
 * `(row >> b) & 0x01`; como na fonte o bit menos significativo representa
 * o pixel mais à esquerda, varrer b de 0 a 7 percorre a linha da esquerda
 * para a direita.
 *
 * **Escala e avanço do cursor:** cada bit aceso vira um quadrado de
 * scale x scale pixels (desenhado com draw_fill_rect, ou seja, dois
 * triângulos rasterizados por scanline). O deslocamento horizontal do
 * i-ésimo caractere é `i * ((FONT_WIDTH * scale) + space)`: a largura do
 * glifo escalado mais o espaçamento entre caracteres — o "avanço de
 * cursor" de uma fonte monoespaçada.
 *
 * @param canvas Canvas alvo.
 * @param x      Coordenada x do canto superior esquerdo do primeiro caractere.
 * @param y      Coordenada y do topo da linha de texto.
 * @param str    String C terminada em '\0' (ASCII 0–127).
 * @param scale  Fator inteiro de ampliação dos glifos.
 * @param space  Espaçamento extra entre caracteres, em pixels.
 * @param color  Cor RGBA do texto.
 * @return Nenhum.
 *
 * @note Pixels apagados (bit 0) não são desenhados, de modo que o fundo
 *       permanece visível — o texto é renderizado com "fundo transparente".
 * @warning O índice `(int)str[i]` assume caracteres na faixa 0–127;
 *          bytes >= 128 (e char com sinal negativo) acessariam a tabela
 *          de fonte fora dos limites.
 */
void put_string(
		Canvas *canvas,
		int x,
		int y,
		const char *str,
		int scale,
		int space,
		uint32_t color
	       )
{
	for (int i = 0; str[i]; i++) {
		unsigned char *font = font8x8_basic[(int)str[i]];

		for (int h = 0; h < FONT_HEIGHT; h++) {
			unsigned char row = font[h];

			for (int b = 0; b < 8; b++) {
				unsigned char bit = (row >> b) & 0x01;

				if (bit) {
					Vec2 point = {
						x + i * ((FONT_WIDTH * scale) + space) + b * scale,
						y + h * scale
					};

					Rect rect = { point, { scale, scale } };

					draw_fill_rect(canvas, &rect, color);
				}
			}
		}
	}
}

/**
 * @brief Desenha uma string centralizada dentro de um retângulo.
 *
 * **Cálculo da centralização:** a largura total do texto é
 * `len * (FONT_WIDTH * scale) + space * (len - 1)` — a soma das larguras
 * dos glifos escalados mais os (len - 1) espaçamentos INTERNOS entre
 * caracteres consecutivos (não há espaçamento após o último). A altura é
 * a de uma única linha de glifos escalados. As margens mx e my distribuem
 * a folga igualmente: margem = (dimensão do retângulo - dimensão do
 * texto) / 2, posicionando o centro geométrico do texto sobre o centro do
 * retângulo.
 *
 * @param canvas Canvas alvo.
 * @param rect   Retângulo de referência da centralização.
 * @param str    String C terminada em '\0'.
 * @param scale  Fator inteiro de ampliação dos glifos.
 * @param space  Espaçamento extra entre caracteres, em pixels.
 * @param color  Cor RGBA do texto.
 * @return Nenhum.
 *
 * @note Após calcular a posição, a renderização em si é delegada a
 *       put_string() — separação entre layout (onde desenhar) e
 *       rasterização (como desenhar).
 * @warning Se o texto exceder as dimensões do retângulo, as margens ficam
 *          negativas e o texto transborda os limites de @p rect.
 */
void put_string_in_rect(
		Canvas *canvas,
		Rect *rect,
		const char *str,
		int scale,
		int space,
		uint32_t color
		)
{
	int len = strlen(str);

	float x = rect->pos.x;
	float y = rect->pos.y;
	float w = rect->size.x;
	float h = rect->size.y;

	float w_str = len * (FONT_WIDTH * scale) + space * (len - 1);
	float h_str = FONT_HEIGHT * scale;

	float mx = (w - w_str) * 0.5f;
	float my = (h - h_str) * 0.5f;

	put_string(
		canvas,
		x + mx,
		y + my,
		str,
		scale,
		space,
		color
		);
}
