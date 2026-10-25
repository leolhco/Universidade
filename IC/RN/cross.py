import pandas as pd
import numpy as np

from sklearn.model_selection import StratifiedKFold
from sklearn.preprocessing import StandardScaler
from sklearn.utils.class_weight import compute_class_weight
from sklearn.metrics import confusion_matrix, classification_report

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, Input
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import EarlyStopping

df = pd.read_csv("heart_disease.csv")
df = df.dropna()

X = df.drop("Heart Disease Status", axis=1)
y = df["Heart Disease Status"]

X = pd.get_dummies(X, drop_first=True)
y = y.map({"Yes": 1, "No": 0})

X_array = X.values
y_array = y.values

k = 5
skf = StratifiedKFold(n_splits=k, shuffle=True, random_state=42)

fold_losses = []
fold_accuracies = []
fold_mses = []
all_y_true = []
all_y_pred = []

fold_no = 1
for train_index, val_index in skf.split(X_array, y_array):

    X_train, X_val = X_array[train_index], X_array[val_index]
    y_train, y_val = y_array[train_index], y_array[val_index]


    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    X_val = scaler.transform(X_val)


    class_weights_array = compute_class_weight(
        class_weight="balanced",
        classes=np.unique(y_train),
        y=y_train
    )
    class_weights = {0: class_weights_array[0], 1: class_weights_array[1]}


    n_features = X_train.shape[1]
    
    model = Sequential([
        Input(shape=(n_features,)),
        Dense(128, activation="relu"),
        Dense(64, activation="relu"),
        Dense(32, activation="relu"),
        Dropout(0.5),
        Dense(1, activation="sigmoid")
    ])

    model.compile(
        optimizer=Adam(learning_rate=0.001),
        loss="binary_crossentropy",
        metrics=["accuracy", "MSE"]
    )

    early_stop = EarlyStopping(
        patience=10,
        restore_best_weights=True
    )



    history = model.fit(
        X_train,
        y_train,
        validation_data=(X_val, y_val),
        epochs=100,
        batch_size=16,
        callbacks=[early_stop],
        class_weight=class_weights,
    )


    loss, accuracy, mse = model.evaluate(X_val, y_val, verbose=0)
    print(f"{fold_no}\nLoss: {loss:.4f} \n Acurácia: {accuracy:.4f} \n MSE: {mse:.4f}\n")

    fold_losses.append(loss)
    fold_accuracies.append(accuracy)
    fold_mses.append(mse)


    y_pred_prob = model.predict(X_val, verbose=0)
    y_pred = (y_pred_prob >= 0.5).astype(int).flatten()
    
    all_y_true.extend(y_val)
    all_y_pred.extend(y_pred)

    fold_no += 1

print("========================================")
print(f"Resultados Médios (k={k}):")
print(f"Loss Média: {np.mean(fold_losses):.4f}")
print(f"Acurácia Média: {np.mean(fold_accuracies):.4f} ")
print(f"MSE Médio: {np.mean(fold_mses):.4f}")

print("\nMatriz de Confusão (Acumulada de todos os k's):")
print(confusion_matrix(all_y_true, all_y_pred))