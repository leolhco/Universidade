/**
 * @file color.h
 * @brief Definição do formato de cor RGBA de 32 bits e paleta de cores nomeadas.
 *
 * Cada cor é um único @c uint32_t com os canais empacotados na ordem
 * R-G-B-A (8 bits por canal). O empacotamento manual via deslocamento de
 * bits dispensa qualquer estrutura ou utilitário de cor de biblioteca
 * externa e casa diretamente com o formato de pixel do framebuffer
 * (ver canvas.h).
 *
 * @note Layout do inteiro resultante (do bit mais significativo para o
 *       menos significativo): RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA.
 */

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

/**
 * @brief Empacota quatro canais de 8 bits (R, G, B, A) em um único pixel de 32 bits.
 *
 * O deslocamento posiciona cada canal em seu byte: R no byte mais
 * significativo (<< 24), seguido de G (<< 16), B (<< 8) e A no byte menos
 * significativo. O OU bit a bit combina os quatro bytes sem perda, pois os
 * intervalos de bits não se sobrepõem.
 *
 * @param r Canal vermelho (0–255).
 * @param g Canal verde (0–255).
 * @param b Canal azul (0–255).
 * @param a Canal alfa/opacidade (0–255).
 * @return (Valor da expressão) Cor RGBA empacotada em @c uint32_t.
 *
 * @warning Valores fora do intervalo 0–255 não são saturados: bits
 *          excedentes "vazam" para o canal vizinho. O chamador deve
 *          fornecer componentes já normalizados.
 */
#define COLOR(r, g, b, a) (((uint32_t)(r) << 24) | ((uint32_t)(g) << 16) | ((uint32_t)(b) << 8) | (uint32_t)(a))

/** @name Cores primárias e secundárias básicas
 *  Paleta mínima totalmente opaca (alfa = 255). @{ */
#define BLACK       COLOR(0,   0,   0,   255) /**< Preto. */
#define WHITE       COLOR(255, 255, 255, 255) /**< Branco. */
#define RED         COLOR(255, 0,   0,   255) /**< Vermelho puro. */
#define GREEN       COLOR(0,   255, 0,   255) /**< Verde puro. */
#define BLUE        COLOR(0,   0,   255, 255) /**< Azul puro. */
#define YELLOW      COLOR(255, 255, 0,   255) /**< Amarelo (R+G). */
#define CYAN        COLOR(0,   255, 255, 255) /**< Ciano (G+B). */
#define MAGENTA     COLOR(255, 0,   255, 255) /**< Magenta (R+B). */
/** @} */

/** @name Tons de cinza
 *  Canais R=G=B produzem tons acromáticos. @{ */
#define DARKGREY    COLOR(64,  64,  64,  255) /**< Cinza escuro. */
#define GREY        COLOR(128, 128, 128, 255) /**< Cinza médio. */
#define LIGHTGREY   COLOR(192, 192, 192, 255) /**< Cinza claro. */
#define DIMGREY     COLOR(105, 105, 105, 255) /**< Cinza "dim" (padrão web). */
#define SLATEGREY   COLOR(112, 128, 144, 255) /**< Cinza-ardósia (levemente azulado). */
/** @} */

/** @name Tons terrosos @{ */
#define TAN         COLOR(210, 180, 140, 255) /**< Bege/castanho claro. */
#define BROWN       COLOR(165, 42,  42,  255) /**< Marrom. */
#define SIENNA      COLOR(160, 82,  45,  255) /**< Terra de Siena. */
/** @} */

/** @name Tons quentes (dourado/laranja) @{ */
#define GOLD        COLOR(255, 215, 0,   255) /**< Dourado. */
#define ORANGE      COLOR(255, 165, 0,   255) /**< Laranja. */
#define DARKORANGE  COLOR(255, 140, 0,   255) /**< Laranja escuro. */
/** @} */

/** @name Tons de rosa @{ */
#define LIGHTPINK   COLOR(255, 182, 193, 255) /**< Rosa claro. */
#define HOTPINK     COLOR(255, 105, 180, 255) /**< Rosa choque. */
#define PINK        COLOR(255, 192, 203, 255) /**< Rosa. */
#define DEEPPINK    COLOR(255, 20,  147, 255) /**< Rosa profundo. */
/** @} */

/** @name Tons de azul @{ */
#define DARKBLUE    COLOR(0,   0,   139, 255) /**< Azul escuro. */
#define SKYBLUE     COLOR(135, 206, 235, 255) /**< Azul céu. */
#define STEELBLUE   COLOR(70,  130, 180, 255) /**< Azul aço. */
#define ROYALBLUE   COLOR(65,  105, 225, 255) /**< Azul real. */
/** @} */

/** @name Tons de verde @{ */
#define DARKGREEN   COLOR(0,   100, 0,   255) /**< Verde escuro. */
#define LIMEGREEN   COLOR(50,  205, 50,  255) /**< Verde limão. */
#define FORESTGREEN COLOR(34,  139, 34,  255) /**< Verde floresta. */
/** @} */

/** @name Tons de roxo/violeta @{ */
#define PURPLE      COLOR(128, 0,   128, 255) /**< Roxo. */
#define DARKPURPLE  COLOR(106, 31,  126, 255) /**< Roxo escuro. */
#define VIOLET      COLOR(238, 130, 238, 255) /**< Violeta. */
/** @} */

/** @name Cores web clássicas adicionais @{ */
#define MAROON      COLOR(128, 0,   0,   255) /**< Bordô. */
#define OLIVE       COLOR(128, 128, 0,   255) /**< Oliva. */
#define NAVY        COLOR(0,   0,   128, 255) /**< Azul-marinho. */
#define TEAL        COLOR(0,   128, 128, 255) /**< Azul-petróleo. */
#define SILVER      COLOR(192, 192, 192, 255) /**< Prata. */
/** @} */

#endif
