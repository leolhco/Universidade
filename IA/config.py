# Dimensões do jogo
WIDTH = 40
HEIGHT = 20

# Parâmetros do Agente e Q-Learning
GAMMA = 0.9         
EPSILON = 0.01

# Definição das direções (dy, dx)
DIRECTION_UP = (-1, 0)
DIRECTION_DOWN = (1, 0)
DIRECTION_LEFT = (0, -1)
DIRECTION_RIGHT = (0, 1)

# Nome do arquivo do modelo
MODEL_FILE_RECORD = 'q_table.npy'
MODEL_FILE_FINAL = 'q_table_final.npy'
