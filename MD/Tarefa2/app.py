from ucimlrepo import fetch_ucirepo
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OrdinalEncoder
from sklearn.naive_bayes import CategoricalNB
from sklearn.tree import DecisionTreeClassifier, plot_tree
import matplotlib.pyplot as plt

# Exercício 1 - Itens 1 e 2
car_evaluation = fetch_ucirepo(id=19)
X = car_evaluation.data.features
y = car_evaluation.data.targets.values.ravel() 

# Exercício 1 - Item 3
encoder = OrdinalEncoder()
X_encoded = encoder.fit_transform(X)

# Exercício 1 - Item 4
X_train, X_test, y_train, y_test = train_test_split(
    X_encoded, y, test_size=0.2, random_state=42
)

print("--- RESULTADOS EXERCÍCIO 1: NAIVE BAYES ---")

# Exercício 1 - Itens 5 e 6
nb_classifier = CategoricalNB()
nb_classifier.fit(X_train, y_train)

# Exercício 1 - Item 7
y_pred_nb = nb_classifier.predict(X_test)

# Exercício 1 - Item 8
print("Classes Reais (5 primeiros):    ", y_test[:5])
print("Classes Previstas (5 primeiros):", y_pred_nb[:5])
print("\n")


print("--- RESULTADOS EXERCÍCIO 2: ÁRVORE DE DECISÃO ---")

# Exercício 2 - Itens 1, 2, 3 e 4
dt_classifier = DecisionTreeClassifier(random_state=42)
dt_classifier.fit(X_train, y_train)

# Exercício 2 - Item 5
y_pred_dt = dt_classifier.predict(X_test)

# Exercício 2 - Item 11
print("Classes Reais (5 primeiros):    ", y_test[:5])
print("Classes Previstas (5 primeiros):", y_pred_dt[:5])

# Exercício 2 - Item 12
plt.figure(figsize=(20, 10))
plot_tree(dt_classifier, feature_names=X.columns, class_names=dt_classifier.classes_, 
          filled=True, rounded=True, max_depth=3, fontsize=10)
plt.title("Árvore de Decisão - Car Evaluation (Profundidade Parcial)")
plt.show()