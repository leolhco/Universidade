/**
 * @file paint.h
 * @brief Estrutura central de estado da aplicação Mini Paint (Trabalho 1).
 *
 * Declara a estrutura global @c App, que reúne TODO o estado compartilhado
 * entre o laço principal (paint.c), as ferramentas de desenho (tools.c) e
 * a interface (toolbar.c). Em vez de espalhar variáveis globais soltas, o
 * projeto centraliza em um único agregado:
 *
 * - **Três framebuffers** (matrizes de pixels manipuladas pixel a pixel):
 *   - @c screen — a janela inteira (toolbar + arte);
 *   - @c art    — a área de desenho propriamente dita ("canvas" do usuário);
 *   - @c buffer — cópia de backup da arte usada para o sistema de PREVIEW
 *     das ferramentas de "arrasto" (linha, retângulo, círculo). Sem esse
 *     terceiro buffer, o desenho durante o arrasto se acumularia sobre si
 *     mesmo a cada movimento do mouse.
 *
 * - **Coordenadas duplas** (screen_* e art_*): cada posição do mouse é
 *   armazenada tanto em coordenadas de TELA (origem no canto da janela)
 *   quanto em coordenadas de ARTE (origem no canto do canvas), evitando
 *   conversões repetidas e mantendo a aritmética de hit-testing simples.
 *
 * - **Estado ativo do usuário**: ferramenta atual, cor selecionada da
 *   paleta e espessura escolhida — exatamente os três eixos de controle
 *   exigidos no enunciado do Trabalho 1.
 *
 * @note Conforme o requisito técnico da disciplina, NENHUMA função de
 *       desenho de alto nível da SDL é usada: a SDL atua somente para
 *       criar a janela e expor a memória de pixels. Toda a rasterização
 *       é feita manualmente sobre estes @c Canvas.
 */

#ifndef PAINT_H
#define PAINT_H

#include "canvas.h"
#include "shapes.h"
#include "color.h"
#include "tools.h"

/**
 * @brief Estado global do Mini Paint.
 *
 * Agregado único compartilhado por todos os módulos da aplicação. Foi
 * desenhado para que cada ferramenta consulte aqui (a) onde o mouse
 * está, (b) qual cor/espessura usar e (c) em qual canvas desenhar —
 * eliminando a necessidade de passar dezenas de parâmetros em cada
 * callback.
 *
 * Descrição dos campos:
 *  - @c window_width / @c window_height: dimensões totais da janela.
 *  - @c art_width / @c art_height: dimensões da área de desenho
 *    (descontadas as toolbars).
 *  - @c screen: framebuffer da janela inteira (toolbar + arte).
 *  - @c art: framebuffer da área de desenho do usuário (o canvas que
 *    será exportado pelo botão SAVE).
 *  - @c buffer: snapshot do canvas tirado no início de cada arrasto,
 *    usado para restaurar o estado anterior em ferramentas com
 *    preview (linha, retângulo, círculo).
 *  - @c tool: ferramenta atualmente selecionada (ponteiro polimórfico).
 *  - @c screen_start / @c screen_prev / @c screen_curr: posições do
 *    mouse (em coordenadas de TELA) no início do arrasto, no evento
 *    anterior e no evento atual.
 *  - @c art_start / @c art_prev / @c art_curr: as mesmas três posições
 *    em coordenadas da ARTE (obtidas subtraindo @c art_offset). Manter
 *    os dois conjuntos pré-calculados poupa conversões repetidas em
 *    cada callback de ferramenta.
 *  - @c art_offset: deslocamento (x, y) do canvas de arte dentro da
 *    tela — define a região reservada às toolbars e é o vetor usado na
 *    conversão tela → arte.
 *  - @c color: cor RGBA atualmente selecionada na paleta.
 *  - @c thickness: espessura atual do traço (ver enum
 *    @c THIN / @c MEDIUM / @c THICK).
 */
struct app {
	int window_width;
	int window_height;
	int art_width;
	int art_height;
	Canvas *screen;
	Canvas *art;
	Canvas *buffer;
	Tool *tool;
	Vec2 screen_start, screen_prev, screen_curr;
	Vec2 art_start, art_prev, art_curr;
	Vec2 art_offset;
	uint32_t color;
	int thickness;
};
typedef struct app App; /**< Apelido de tipo para @ref app. */

/**
 * @brief Instância global única do estado da aplicação.
 *
 * Declarada como @c extern para que todos os módulos acessem o mesmo
 * estado sem cópias. Definida em paint.c.
 */
extern App app;

/**
 * @brief Níveis de espessura disponíveis para o usuário.
 *
 * Os três valores correspondem aos três botões de espessura exigidos no
 * enunciado ("fino, médio, grosso") e são usados diretamente como o
 * raio em pixels (caso pincel/borracha) ou a espessura do contorno
 * (linha, retângulo, círculo).
 *
 * - @c THIN   = 1  pixel — caso especial: usa draw_point/draw_line direto.
 * - @c MEDIUM = 5  pixels.
 * - @c THICK  = 15 pixels.
 *
 * @note O valor especial @c THIN == 1 é tratado como caso degenerado:
 *       em vez de chamar uma função "espessa" com raio 1 (que cairia em
 *       draw_thick_line/draw_thick_circle desnecessariamente), o código
 *       usa diretamente a primitiva de 1 pixel.
 */
enum {
	THIN =  1,
	MEDIUM = 5,
	THICK = 15
};

#endif
