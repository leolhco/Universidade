/**
 * @file shapes.h
 * @brief Interface das primitivas geométricas, algoritmos de rasterização e testes de colisão.
 *
 * Declara as estruturas geométricas fundamentais (vetor 2D, triângulo,
 * retângulo e círculo) e duas famílias de funções:
 *
 * 1. **Rasterização manual** — implementações "do zero" dos algoritmos
 *    clássicos de Computação Gráfica: traçado de linhas pelo algoritmo de
 *    Bresenham, círculos pelo algoritmo do ponto médio com simetria de
 *    8 octantes, e preenchimento de triângulos por varredura (scanline).
 *    Nenhuma rotina de desenho da SDL ou de bibliotecas de alto nível é
 *    utilizada: todo pixel é decidido pela matemática destes algoritmos.
 *
 * 2. **Detecção de colisão matemática** — testes analíticos de
 *    pertencimento e interseção (ponto-retângulo, ponto-círculo,
 *    círculo-retângulo e círculo-círculo) usados pela lógica de jogo,
 *    independentes da camada de renderização.
 *
 * @note Todas as figuras compostas (retângulos, polígonos, linhas espessas)
 *       são decompostas em triângulos ou linhas, mantendo o núcleo de
 *       rasterização mínimo e verificável.
 */

#ifndef SHAPES_H
#define SHAPES_H

#include "canvas.h"
#include <stdbool.h>

/**
 * @brief Vetor/ponto bidimensional em coordenadas de tela.
 *
 * Usa componentes em ponto flutuante para suportar transformações
 * geométricas contínuas (rotação, escala) sem perda acumulada de precisão;
 * a conversão para a grade discreta de pixels só ocorre no momento da
 * rasterização.
 */
struct vec2 {
	float x; /**< Componente horizontal. */
	float y; /**< Componente vertical (cresce para baixo, convenção raster). */
};
typedef struct vec2 Vec2; /**< Apelido de tipo para @ref vec2. */

/**
 * @brief Triângulo definido por três vértices.
 *
 * É a primitiva de preenchimento fundamental do sistema: retângulos
 * preenchidos, polígonos e linhas espessas são todos convertidos em
 * triângulos antes da rasterização.
 */
struct triangle {
	Vec2 a; /**< Primeiro vértice. */
	Vec2 b; /**< Segundo vértice. */
	Vec2 c; /**< Terceiro vértice. */
};
typedef struct triangle Triangle; /**< Apelido de tipo para @ref triangle. */

/**
 * @brief Retângulo alinhado aos eixos (AABB — Axis-Aligned Bounding Box).
 *
 * Representado por posição (canto superior esquerdo) e tamanho. Além do
 * desenho, serve como volume envolvente nos testes de colisão.
 */
struct rect {
	Vec2 pos;  /**< Canto superior esquerdo do retângulo. */
	Vec2 size; /**< Dimensões (x = largura, y = altura). */
};
typedef struct rect Rect; /**< Apelido de tipo para @ref rect. */

/**
 * @brief Círculo definido por centro e raio.
 */
struct circle {
	Vec2 center;  /**< Centro do círculo. */
	float radius; /**< Raio em pixels. */
};
typedef struct circle Circle; /**< Apelido de tipo para @ref circle. */

/**
 * @brief Desenha um único ponto (pixel) no canvas.
 * @param canvas Canvas alvo.
 * @param point  Coordenadas do ponto.
 * @param color  Cor RGBA de 32 bits.
 * @return Nenhum.
 */
void draw_point(Canvas *canvas, Vec2 *point, uint32_t color);

/**
 * @brief Traça um segmento de reta entre @p a e @p b usando o algoritmo de
 *        Bresenham generalizado (apenas aritmética inteira).
 * @param canvas Canvas alvo.
 * @param a      Ponto inicial.
 * @param b      Ponto final.
 * @param color  Cor RGBA do traço.
 * @return Nenhum.
 * @note Ver a implementação em shapes.c para a explicação do termo de erro
 *       incremental e da generalização para todos os octantes.
 */
void draw_line(Canvas *canvas, Vec2 *a, Vec2 *b, uint32_t color);

/**
 * @brief Desenha o contorno de um triângulo (três chamadas a draw_line()).
 * @param canvas   Canvas alvo.
 * @param triangle Triângulo a contornar.
 * @param color    Cor RGBA do contorno.
 * @return Nenhum.
 */
void draw_triangle(Canvas *canvas, Triangle *triangle, uint32_t color);

/**
 * @brief Preenche um triângulo pelo algoritmo de varredura (scanline).
 * @param canvas   Canvas alvo.
 * @param triangle Triângulo a preencher.
 * @param color    Cor RGBA de preenchimento.
 * @return Nenhum.
 * @note Os vértices são ordenados por y e o triângulo é varrido linha a
 *       linha, interpolando as bordas esquerda e direita por incrementos
 *       de inclinação (dx/dy). Detalhes na implementação.
 */
void draw_fill_triangle(Canvas *canvas, Triangle *triangle, uint32_t color);

/**
 * @brief Desenha um segmento com espessura arbitrária como um quadrilátero
 *        orientado, decomposto em dois triângulos preenchidos.
 * @param canvas Canvas alvo.
 * @param a      Ponto inicial do eixo da linha.
 * @param b      Ponto final do eixo da linha.
 * @param thick  Espessura total da linha, em pixels.
 * @param color  Cor RGBA.
 * @return Nenhum.
 * @warning Comportamento indefinido se @p a == @p b (vetor direção nulo
 *          gera divisão por zero na normalização).
 */
void draw_thick_line(Canvas *canvas, Vec2 *a, Vec2 *b, float thick, uint32_t color);

/**
 * @brief Desenha a circunferência pelo algoritmo do ponto médio
 *        (variante de Bresenham para círculos), com simetria de 8 octantes.
 * @param canvas Canvas alvo.
 * @param circle Círculo a desenhar.
 * @param color  Cor RGBA do contorno.
 * @return Nenhum.
 */
void draw_circle(Canvas *canvas, Circle *circle, uint32_t color);

/**
 * @brief Desenha uma circunferência com espessura, como anéis concêntricos.
 * @param canvas Canvas alvo.
 * @param circle Círculo de referência (borda externa).
 * @param thick  Espessura do anel, em pixels.
 * @param color  Cor RGBA.
 * @return Nenhum.
 */
void draw_thick_circle(Canvas *canvas, Circle *circle, float thick, uint32_t color);

/**
 * @brief Preenche um disco usando o gerador de pontos do ponto médio para
 *        emitir cordas horizontais/verticais entre pontos simétricos.
 * @param canvas Canvas alvo.
 * @param circle Círculo a preencher.
 * @param color  Cor RGBA de preenchimento.
 * @return Nenhum.
 */
void draw_fill_circle(Canvas *canvas, Circle *circle, uint32_t color);

/**
 * @brief Desenha o contorno de um retângulo (espessura mínima).
 * @param canvas Canvas alvo.
 * @param rect   Retângulo a contornar.
 * @param color  Cor RGBA.
 * @return Nenhum.
 */
void draw_rect(Canvas *canvas, Rect *rect, uint32_t color);

/**
 * @brief Desenha o contorno de um retângulo com espessura configurável.
 * @param canvas Canvas alvo.
 * @param rect   Retângulo a contornar.
 * @param thick  Espessura do traço, em pixels.
 * @param color  Cor RGBA.
 * @return Nenhum.
 * @note As quatro arestas são estendidas em meia espessura para que os
 *       cantos fiquem fechados, sem "buracos" na junção dos traços.
 */
void draw_thick_rect(Canvas *canvas, Rect *rect, float thick, uint32_t color);

/**
 * @brief Preenche um retângulo decompondo-o em dois triângulos.
 * @param canvas Canvas alvo.
 * @param rect   Retângulo a preencher.
 * @param color  Cor RGBA.
 * @return Nenhum.
 */
void draw_fill_rect(Canvas *canvas, Rect *rect, uint32_t color);

/**
 * @brief Desenha o contorno de um polígono fechado ligando vértices consecutivos.
 * @param canvas     Canvas alvo.
 * @param points     Vetor de vértices em ordem.
 * @param num_points Número de vértices.
 * @param color      Cor RGBA.
 * @return Nenhum.
 * @note O fechamento é garantido pelo índice modular (i+1) % num_points,
 *       que liga o último vértice de volta ao primeiro.
 */
void draw_polygon(Canvas *canvas, Vec2 *points, int num_points, uint32_t color);

/**
 * @brief Preenche um polígono por triangulação em leque (fan triangulation).
 * @param canvas     Canvas alvo.
 * @param points     Vetor de vértices em ordem.
 * @param num_points Número de vértices.
 * @param color      Cor RGBA.
 * @return Nenhum.
 * @warning A triangulação em leque a partir do vértice 0 só é correta para
 *          polígonos CONVEXOS; polígonos côncavos produzem preenchimento
 *          fora da área real.
 */
void draw_fill_polygon(Canvas *canvas, Vec2 *points, int num_points, uint32_t color);

/**
 * @brief Teste de colisão ponto-retângulo (pertencimento a um AABB).
 * @param point Ponto a testar.
 * @param rect  Retângulo alinhado aos eixos.
 * @return @c true se o ponto está dentro do retângulo.
 * @note Intervalo semiaberto: a borda esquerda/superior é inclusiva e a
 *       direita/inferior é exclusiva, evitando que um ponto pertença a
 *       dois retângulos adjacentes simultaneamente.
 */
bool point_in_rect(Vec2 *point, Rect *rect);

/**
 * @brief Teste de colisão ponto-círculo via distância euclidiana ao quadrado.
 * @param point  Ponto a testar.
 * @param circle Círculo de referência.
 * @return @c true se o ponto está dentro (ou na borda) do círculo.
 * @note Compara dx² + dy² <= r², evitando a raiz quadrada — otimização
 *       clássica de colisão, pois a comparação de quadrados preserva a
 *       ordem das distâncias (a função x² é monótona para x >= 0).
 */
bool point_in_circle(Vec2 *point, Circle *circle);

/**
 * @brief Testa se um círculo está COMPLETAMENTE FORA de um retângulo
 *        (teste de separação por eixos sobre o AABB do círculo).
 * @param circle Círculo a testar.
 * @param rect   Retângulo de referência.
 * @return @c true se não há sobreposição possível entre o AABB do círculo e o retângulo.
 * @note Útil como teste rápido de rejeição (ex.: detectar saída da tela ou
 *       de uma área de jogo) antes de verificações mais caras.
 */
bool circle_out_rect(Circle *circle, Rect *rect);

/**
 * @brief Teste de colisão círculo-círculo.
 * @param c1 Primeiro círculo.
 * @param c2 Segundo círculo.
 * @return @c true se os círculos se tocam ou se sobrepõem.
 * @note Dois círculos colidem se a distância entre centros é menor ou igual
 *       à soma dos raios; a comparação é feita ao quadrado para eliminar a
 *       raiz quadrada (dx² + dy² <= (r1 + r2)²).
 */
bool circle_in_circle(Circle *c1, Circle *c2);

#endif
