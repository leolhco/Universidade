/**
 * @file text.h
 * @brief Interface do renderizador de texto bitmap.
 *
 * Declara as rotinas de escrita de texto sobre o framebuffer usando a
 * fonte monocromática 8x8 embutida (font8x8_basic.h). A rasterização dos
 * glifos é inteiramente manual — cada bit aceso do bitmap do caractere é
 * convertido em pixels via primitivas próprias — sem uso de bibliotecas
 * de fontes (SDL_ttf, FreeType etc.).
 */

#ifndef TEXT_H
#define TEXT_H

#include "canvas.h"
#include "shapes.h"

/**
 * @brief Desenha uma string no canvas a partir da posição (x, y), com
 *        escala e espaçamento configuráveis.
 *
 * @param canvas Canvas alvo.
 * @param x      Coordenada x do canto superior esquerdo do primeiro caractere.
 * @param y      Coordenada y do canto superior esquerdo da linha de texto.
 * @param str    String C terminada em '\0' (apenas caracteres ASCII 0–127).
 * @param scale  Fator de ampliação inteiro: cada bit do glifo vira um bloco
 *               scale x scale pixels.
 * @param space  Espaçamento extra entre caracteres, em pixels.
 * @param color  Cor RGBA do texto.
 * @return Nenhum.
 *
 * @warning Caracteres fora da faixa ASCII básica (>= 128, ex.: acentuação
 *          em UTF-8) indexariam a tabela de fonte fora dos limites.
 */
void put_string(
		Canvas *canvas,
		int x,
		int y,
		const char *str,
		int scale,
		int space,
		uint32_t color
	       );

/**
 * @brief Desenha uma string centralizada (horizontal e verticalmente)
 *        dentro de um retângulo.
 *
 * @param canvas Canvas alvo.
 * @param rect   Retângulo de referência para a centralização.
 * @param str    String C terminada em '\0'.
 * @param scale  Fator de ampliação inteiro dos glifos.
 * @param space  Espaçamento extra entre caracteres, em pixels.
 * @param color  Cor RGBA do texto.
 * @return Nenhum.
 *
 * @note A centralização calcula as dimensões totais do texto renderizado e
 *       distribui a folga igualmente como margens — útil para rótulos de
 *       botões e títulos de interface.
 * @warning Se o texto for maior que o retângulo, as margens tornam-se
 *          negativas e o texto extrapola os limites do retângulo.
 */
void put_string_in_rect(
		Canvas *canvas,
		Rect *rect,
		const char *str,
		int scale,
		int space,
		uint32_t color
		);

#endif
