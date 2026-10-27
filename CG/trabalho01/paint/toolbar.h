/**
 * @file toolbar.h
 * @brief Interface da camada de UI do Mini Paint (toolbars, paleta, hit-testing).
 *
 * Declara as rotinas responsáveis por (a) inicializar e DESENHAR a
 * interface gráfica do programa (toolbar lateral com 8 ferramentas,
 * toolbar inferior com paleta de 8 cores, seletor de 3 espessuras e os
 * botões "NEW"/"SAVE") e (b) realizar o HIT-TESTING dos cliques do
 * mouse — isto é, identificar qual elemento da UI foi clicado.
 *
 * Todo o desenho da UI passa pelas primitivas de rasterização próprias
 * do projeto (draw_fill_rect, draw_fill_circle, put_string), conforme
 * exigido pelo enunciado.
 */

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <stdint.h>

/**
 * @brief Inicializa todas as dimensões, posições e dados internos dos
 *        componentes de UI (toolbars, paleta, seletor de espessura, botões).
 *
 * As medidas são calculadas como FRAÇÕES das dimensões da janela
 * (consultadas em @c app.window_width / @c app.window_height), tornando
 * o layout responsivo a mudanças no tamanho da janela em tempo de
 * compilação. Também atualiza @c app.art_width, @c app.art_height e
 * @c app.art_offset — informando ao resto do programa qual a região da
 * tela reservada ao canvas de arte.
 *
 * @return Nenhum.
 * @note Deve ser chamada UMA ÚNICA VEZ antes de qualquer outra função
 *       deste módulo e antes da alocação dos buffers de pixels.
 */
void init_ui_components();

/**
 * @brief Redesenha a toolbar lateral (8 botões de ferramenta).
 *
 * Pintada apenas quando o usuário troca de ferramenta (não a cada
 * frame), para evitar trabalho de rasterização desnecessário.
 * @return Nenhum.
 */
void draw_toolbar_left(void);

/**
 * @brief Redesenha a toolbar inferior (paleta + espessura + botões NEW/SAVE).
 * @return Nenhum.
 */
void draw_toolbar_bottom(void);

/**
 * @brief Hit-test da toolbar lateral.
 * @return Ponteiro para a Tool clicada, ou @c NULL se o mouse não está
 *         sobre nenhum botão de ferramenta.
 */
Tool *hit_toolbar_left();

/**
 * @brief Hit-test da paleta de cores.
 * @return Ponteiro para a cor clicada (@c uint32_t da paleta), ou @c NULL.
 * @note Retorna ponteiro para permitir que o chamador faça
 *       `app.color = *hit_palette();` apenas se o retorno for não-nulo.
 */
uint32_t *hit_palette();

/**
 * @brief Verifica se o mouse está sobre a área de desenho (canvas).
 *
 * Função crítica para a lógica de eventos: o desenho só é iniciado
 * dentro da área de arte; cliques na toolbar precisam ser distinguidos
 * de cliques no canvas para evitar que o usuário "pinte" sobre a UI.
 *
 * @return @c true se o cursor está dentro do canvas.
 */
bool hit_art_area();

/**
 * @brief Hit-test do seletor de espessura.
 * @return Ponteiro para o nível clicado (1, 5 ou 15), ou @c NULL.
 */
int *hit_thickness();

/**
 * @brief Hit-test do botão "NEW" (limpar canvas).
 * @return @c true se o botão foi clicado.
 */
bool hit_new_button();

/**
 * @brief Hit-test do botão "SAVE" (exportar canvas para BMP).
 * @return @c true se o botão foi clicado.
 */
bool hit_save_button();

#endif
