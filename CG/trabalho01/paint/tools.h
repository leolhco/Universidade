/**
 * @file tools.h
 * @brief Interface polimórfica das ferramentas de desenho do Mini Paint.
 *
 * Define a estrutura @c Tool — uma "classe abstrata" em C, implementada
 * por meio de ponteiros de função — e os despachadores genéricos
 * on_click() / on_motion() / on_release(). Cada ferramenta (lápis,
 * borracha, linha, retângulo vazado, retângulo cheio, círculo vazado,
 * círculo cheio, balde) é definida em tools.c como uma instância de
 * @c Tool que preenche os ponteiros relevantes; os demais ficam @c NULL.
 *
 * Essa arquitetura atende diretamente o critério "Organização do código
 * (modularidade)" do Trabalho 1: adicionar uma ferramenta nova significa
 * apenas criar mais uma instância de @c Tool e adicioná-la ao vetor
 * @c tools[], sem modificar o laço principal nem o sistema de eventos.
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <stdbool.h>

/**
 * @brief Quantidade total de ferramentas registradas em @c tools[].
 *
 * Usada como tamanho do vetor de ferramentas e como número de células da
 * toolbar lateral. Aumentar este valor sem adicionar a ferramenta
 * correspondente em tools.c causaria leitura fora dos limites do vetor.
 */
#define NUM_TOOLS 8

/**
 * @brief "Classe" abstrata de uma ferramenta de desenho.
 *
 * Implementa polimorfismo em C por meio de PONTEIROS DE FUNÇÃO: cada
 * ferramenta concreta preenche apenas os callbacks que faz sentido
 * implementar (ex.: o lápis usa @c on_click e @c on_motion; a linha usa
 * @c on_motion para preview e @c on_release para confirmar; o balde usa
 * apenas @c on_click). Os demais ficam @c NULL e são silenciosamente
 * ignorados pelos despachadores.
 */
struct tool {
	Rect bounds;                  /**< Retângulo (em coordenadas de tela) do botão da ferramenta na toolbar. Usado para hit-testing do clique. */
	bool preview;                 /**< @c true se a ferramenta tem feedback de preview durante o arrasto (linha, retângulo, círculo). Controla se o sistema de buffer/snapshot é ativado. */
	void (*draw_icon)(Rect *);    /**< Callback de renderização do ícone da ferramenta dentro do botão da toolbar. */
	void (*on_click)();           /**< Callback executado no SDL_MOUSEBUTTONDOWN (uma única vez por traço). */
	void (*on_motion)();          /**< Callback executado em cada SDL_MOUSEMOTION enquanto o botão está pressionado. */
	void (*on_release)();         /**< Callback executado no SDL_MOUSEBUTTONUP (encerra o traço). */
};
typedef struct tool Tool; /**< Apelido de tipo para @ref tool. */

/**
 * @brief Vetor global com as @c NUM_TOOLS ferramentas disponíveis.
 *
 * A ordem dos elementos define a ordem em que aparecem na toolbar
 * lateral. Definido em tools.c.
 */
extern Tool *tools[];

/**
 * @brief Despachador do evento de clique para a ferramenta @p tool.
 *
 * Encapsula a verificação de NULL: se a ferramenta não definiu um
 * callback de clique, a chamada simplesmente não faz nada — evita um
 * @c if disperso em cada ponto de invocação.
 *
 * @param tool Ferramenta-alvo (pode ser @c NULL).
 * @return Nenhum.
 */
void on_click(Tool *tool);

/**
 * @brief Despachador do evento de motion (arrasto) para a ferramenta @p tool.
 * @param tool Ferramenta-alvo (pode ser @c NULL).
 * @return Nenhum.
 */
void on_motion(Tool *tool);

/**
 * @brief Despachador do evento de liberação do botão para @p tool.
 * @param tool Ferramenta-alvo (pode ser @c NULL).
 * @return Nenhum.
 */
void on_release(Tool *tool);

#endif
