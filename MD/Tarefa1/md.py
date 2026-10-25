import numpy as np
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from sklearn.neighbors import KNeighborsClassifier

print("--- CARREGANDO A BASE IRIS ---")
iris = load_iris()
X = iris.data
y = iris.target

print("\n" + "="*60)
print("EXERCÍCIO 1: Distância Euclidiana Manual\n")

def distancia_euclidiana(instancia1, instancia2):
    return np.sqrt(np.sum((instancia1 - instancia2) ** 2))

inst_10 = X[9]
inst_100 = X[99]
dist_10_100 = distancia_euclidiana(inst_10, inst_100)
print(f"B) Distância entre a instância 10 e 100: {dist_10_100:.4f}")

distancias = []
for i, inst in enumerate(X):
    if i != 9:
        d = distancia_euclidiana(inst_10, inst)
        distancias.append((i, d))

distancias.sort(key=lambda x: x[1])

print("\nC) As 3 instâncias mais próximas da instância 10:")
for i in range(3):
    indice_vizinho = distancias[i][0]
    distancia_vizinho = distancias[i][1]
    print(f"   {i+1}º Vizinho: Instância {indice_vizinho + 1} (Índice Python {indice_vizinho}) - Distância: {distancia_vizinho:.4f}")

print("\n" + "="*60)
print("EXERCÍCIO 2: KNN e Normalização Min-Max\n")

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

scaler = MinMaxScaler()
X_train_norm = scaler.fit_transform(X_train)
X_test_norm = scaler.transform(X_test)

knn_norm = KNeighborsClassifier(n_neighbors=3)
knn_norm.fit(X_train_norm, y_train)
pred_norm = knn_norm.predict(X_test_norm[:10])

knn_k1 = KNeighborsClassifier(n_neighbors=1).fit(X_train_norm, y_train)
knn_k15 = KNeighborsClassifier(n_neighbors=15).fit(X_train_norm, y_train)

print("D) Classes das 10 primeiras instâncias de teste variando K:")
print(f"   k=1:  {knn_k1.predict(X_test_norm[:10])}")
print(f"   k=3:  {pred_norm}")
print(f"   k=15: {knn_k15.predict(X_test_norm[:10])}")

knn_sem_norm = KNeighborsClassifier(n_neighbors=3)
knn_sem_norm.fit(X_train, y_train)
pred_sem_norm = knn_sem_norm.predict(X_test[:10])

print("\nG) Comparação (com vs sem normalização nas 10 primeiras instâncias):")
print(f"   Com Normalização: {pred_norm}")
print(f"   Sem Normalização: {pred_sem_norm}")

print("\n" + "="*60)
print("EXERCÍCIO 3: Distância Manhattan vs Euclidiana\n")

knn_manhattan = KNeighborsClassifier(n_neighbors=3, metric='manhattan')
knn_manhattan.fit(X_train_norm, y_train)

knn_euclidiana = KNeighborsClassifier(n_neighbors=3, metric='euclidean')
knn_euclidiana.fit(X_train_norm, y_train)

vizinhos_manhattan = knn_manhattan.kneighbors(X_test_norm[:10], return_distance=False)
vizinhos_euclidiana = knn_euclidiana.kneighbors(X_test_norm[:10], return_distance=False)

classes_man = knn_manhattan.predict(X_test_norm[:10])
classes_euc = knn_euclidiana.predict(X_test_norm[:10])

print("B) Índices dos 3 vizinhos de treinamento mais próximos para a 1ª instância de teste:")
print(f"   Manhattan:  {vizinhos_manhattan[0]}")
print(f"   Euclidiana: {vizinhos_euclidiana[0]}")

print("\nC) Classes atribuídas às 10 primeiras instâncias de teste:")
print(f"   Manhattan:  {classes_man}")
print(f"   Euclidiana: {classes_euc}")

print("\n" + "="*60)
print("EXERCÍCIO 4: Programa Genérico de KNN\n")

def knn_generico(X_train, y_train, X_test, k=3, metrica='euclidean'):
    print(f" -> Executando KNN genérico (k={k}, distância='{metrica}')...")
    modelo = KNeighborsClassifier(n_neighbors=k, metric=metrica)
    modelo.fit(X_train, y_train)
    return modelo.predict(X_test)

resultado_generico = knn_generico(X_train_norm, y_train, X_test_norm[:10], k=5, metrica='manhattan')
print(f"   Predições geradas: {resultado_generico}")
print("="*60)
