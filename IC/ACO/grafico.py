import matplotlib.pyplot as plt

tempo_normal = [2.70, 19.35, 166.71, 205.32, 193.19]
label_normal = ['Berlin (7544.36)', 'XQF(579.4)', 'PMA (1425.55)', 'PKA (1383.47)', 'BCL (1698.9)']

tempo_suavizado = [2.42, 18.02, 161.35, 196.77, 177.51]
label_suavizado = ['Berlin (7544.36)', 'XQF(579.39)', 'PMA (1420.66)', 'PKA (1391.42)', 'BCL (1675.96)']

label = ['Berlin', 'XQF', 'PMA', 'PKA', 'BCL']


# plt.figure(figsize=(10, 6))
# plt.bar(label_normal, tempo_normal, label='Tempo Normal', color='blue')
# plt.xlabel('Problema')
# plt.ylabel('Tempo (segundos)')
# plt.title('Comparação de Tempos (Normal)')
# plt.legend()
# plt.show()

# plt.figure(figsize=(10, 6))
# plt.bar(label_suavizado, tempo_suavizado, label='Tempo Suavizado', color='orange')
# plt.xlabel('Problema')
# plt.ylabel('Tempo (segundos)')
# plt.title('Comparação de Tempos (suavizado)')
# plt.legend()
# plt.show()

plt.figure(figsize=(10, 6))
plt.plot(label, tempo_normal, label='Tempo Normal', marker='o', color='blue')
plt.plot(label_suavizado, tempo_suavizado, label='Tempo Suavizado', marker='o', color='orange')
plt.xlabel('Problema')
plt.ylabel('Tempo (segundos)')
plt.title('Comparação de Tempos (Normal vs Suavizado)')
plt.legend()
plt.show()