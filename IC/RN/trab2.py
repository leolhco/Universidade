import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
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

y = y.map({
    "Yes": 1,
    "No": 0
})

X_train, X_test, y_train, y_test = train_test_split(
    X,
    y,
    test_size=0.2,
    random_state=42,
    stratify=y
)

scaler = StandardScaler()

X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

class_weights_array = compute_class_weight(
    class_weight="balanced",
    classes=np.unique(y_train),
    y=y_train
)

class_weights = {
    0: class_weights_array[0],
    1: class_weights_array[1]
}

n_features = X_train.shape[1]

model = Sequential([
    Input(shape=(n_features,)),
    Dense(32, activation="relu"),
    Dense(16, activation="relu"),
    Dropout(0.2),
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
    validation_split=0.2,
    epochs=100,
    batch_size=16,
    callbacks=[early_stop],
    class_weight=class_weights,
    verbose=1
)

loss, accuracy, mse = model.evaluate(X_test, y_test)

print("\nResultado no teste:")
print("Loss:", loss)
print("Acurácia:", accuracy)
print("MSE:", mse)

y_pred_prob = model.predict(X_test)

y_pred = (y_pred_prob >= 0.5).astype(int)

print("\nMatriz de confusão:")
print(confusion_matrix(y_test, y_pred))