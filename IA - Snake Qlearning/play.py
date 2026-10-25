import curses
import time
import numpy as np
from game import SnakeGameAI
from agent import Agent
from config import *

def draw_state(win, game):
    win.clear()
    win.border()
    win.addstr(0, 2, f' Score: {game.score} ')
    win.addch(game.food[0] + 1, game.food[1] + 1, '🍎')
    for i, (y, x) in enumerate(game.snake):
        char = 'O' if i == 0 else 'o'
        win.addch(y + 1, x + 1, char)
    win.refresh()

def play_main_loop(stdscr):
    curses.curs_set(0)
    win = curses.newwin(HEIGHT + 2, WIDTH + 2, 0, 0)
    win.keypad(True)
    win.timeout(100)

    agent = Agent()
    agent.epsilon = 0.0
    
    try:
        agent.q_table = np.load(MODEL_FILE_RECORD, allow_pickle=True).item()
        print(f"Modelo de recorde '{MODEL_FILE_RECORD}' carregado!")
    except FileNotFoundError:
        try:
            agent.q_table = np.load(MODEL_FILE_FINAL, allow_pickle=True).item()
            print(f"Modelo final '{MODEL_FILE_FINAL}' carregado!")
        except FileNotFoundError:
            print(f"ERRO: Nenhum arquivo de modelo encontrado.")
            time.sleep(3)
            return

    game = SnakeGameAI()
    done = False
    print("Iniciando visualização... Pressione Q para sair.")
    time.sleep(1)

    while not done:
        state = agent.get_state(game)
        action = agent.get_action(state)
        _, done, _ = game.play_step(action)
        draw_state(win, game)
        time.sleep(0.07)
        if win.getch() in [ord('q'), ord('Q')]:
            break
            
    win.addstr(HEIGHT // 2, (WIDTH - 10) // 2, " GAME OVER ")
    win.addstr(HEIGHT // 2 + 1, (WIDTH - 15) // 2, f" Score Final: {game.score} ")
    win.refresh()
    time.sleep(2)
    win.nodelay(0)
    win.getch()

def play():
    curses.wrapper(play_main_loop)

if __name__ == '__main__':
    play()
