import random
import numpy as np
from config import *

class Agent:
    def __init__(self):
        self.n_games = 0
        self.epsilon = EPSILON
        self.gamma = GAMMA
        self.q_table = {} 

    def get_state(self, game):
        head = game.head
        point_l = (head[0] + game.direction[1], head[1] - game.direction[0])
        point_r = (head[0] - game.direction[1], head[1] + game.direction[0])
        point_u = (head[0] + game.direction[0], head[1] + game.direction[1])
        dir_l = game.direction == DIRECTION_LEFT
        dir_r = game.direction == DIRECTION_RIGHT
        dir_u = game.direction == DIRECTION_UP
        dir_d = game.direction == DIRECTION_DOWN
        state = (
            game.is_collision(point_u), game.is_collision(point_r), game.is_collision(point_l),
            dir_l, dir_r, dir_u, dir_d,
            game.food[1] < game.head[1], game.food[1] > game.head[1],
            game.food[0] < game.head[0], game.food[0] > game.head[0]
        )
        return tuple(int(i) for i in state)

    def get_action(self, state):
        if random.random() < self.epsilon:
            move_idx = random.randint(0, 2)
        else:
            q_values = self.q_table.get(state, np.zeros(3))
            move_idx = np.argmax(q_values)
        final_move = [0, 0, 0]
        final_move[move_idx] = 1
        return final_move

    def train_step(self, state, action, reward, next_state, done):
        action_idx = np.argmax(action)
        old_q_values = self.q_table.get(state, np.zeros(3))
        next_q_values = self.q_table.get(next_state, np.zeros(3))
        old_value = old_q_values[action_idx]
        if done:
            new_q = reward
        else:
            new_q = reward + self.gamma * np.max(next_q_values)
        updated_q_values = old_q_values.copy()
        updated_q_values[action_idx] = new_q
        self.q_table[state] = updated_q_values
