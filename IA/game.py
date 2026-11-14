import random
from collections import deque
import numpy as np
from config import *

class SnakeGameAI:
    def __init__(self, w=WIDTH, h=HEIGHT):
        self.w = w
        self.h = h
        self.reset()

    def reset(self):
        start_y = self.h // 2
        start_x = self.w // 2
        self.snake = deque([(start_y, start_x - i) for i in range(3)])
        self.head = self.snake[0]
        self.direction = DIRECTION_RIGHT
        self.score = 0
        self.food = None
        self._place_food()
        self.frame_iteration = 0

    def _place_food(self):
        while True:
            y = random.randint(0, self.h - 1)
            x = random.randint(0, self.w - 1)
            if (y, x) not in self.snake:
                self.food = (y, x)
                break

    def play_step(self, action):
        self.frame_iteration += 1
        directions_clockwise = [DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT]
        idx = directions_clockwise.index(self.direction)

        if np.array_equal(action, [1, 0, 0]):
            new_dir = self.direction
        elif np.array_equal(action, [0, 1, 0]):
            next_idx = (idx + 1) % 4
            new_dir = directions_clockwise[next_idx]
        else:
            next_idx = (idx - 1) % 4
            new_dir = directions_clockwise[next_idx]
        
        self.direction = new_dir
        dy, dx = self.direction
        self.head = (self.head[0] + dy, self.head[1] + dx)
        self.snake.appendleft(self.head)
        
        game_over = False
        reward = 0
        if self.is_collision() or self.frame_iteration > 100 * len(self.snake):
            game_over = True
            reward = -1
            return reward, game_over, self.score

        if self.head == self.food:
            self.score += 1
            reward = 1
            self._place_food()
        else:
            self.snake.pop()
        
        return reward, game_over, self.score

    def is_collision(self, pt=None):
        if pt is None:
            pt = self.head
        if pt[0] < 0 or pt[0] >= self.h or pt[1] < 0 or pt[1] >= self.w:
            return True
        if pt in list(self.snake)[1:]:
            return True
        return False
