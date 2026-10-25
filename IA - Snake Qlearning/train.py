import numpy as np
from game import SnakeGameAI
from agent import Agent
from config import *

def train():
    record = 0
    agent = Agent()
    game = SnakeGameAI()

    print("Iniciando o treinamento... Pressione Ctrl+C para parar.")
    try:
        while True:
            state_old = agent.get_state(game)
            final_move = agent.get_action(state_old)
            reward, done, score = game.play_step(final_move)
            state_new = agent.get_state(game)
            agent.train_step(state_old, final_move, reward, state_new, done)

            if done:
                game.reset()
                agent.n_games += 1

                if score > record:
                    record = score
                    np.save(MODEL_FILE_RECORD, agent.q_table)
                    print(f"NOVO RECORDE! Modelo salvo em '{MODEL_FILE_RECORD}'")

                print(f'Jogo: {agent.n_games}, Score: {score}, Recorde: {record}')

    except KeyboardInterrupt:
        print("\nTreinamento interrompido. Salvando modelo final...")
        np.save(MODEL_FILE_FINAL, agent.q_table)
        print(f"Modelo salvo em '{MODEL_FILE_FINAL}'")

if __name__ == '__main__':
    train()
