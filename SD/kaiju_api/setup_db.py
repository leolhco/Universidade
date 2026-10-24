import sqlite3

conn = sqlite3.connect("kaiju.db")

columns = [
    "id INTEGER PRIMARY KEY",
    "name VARCHAR UNIQUE",
    "power VARCHAR",
    "timestamp DATETIME",
]
create_table_cmd = f"CREATE TABLE kaiju ({','.join(columns)})"
conn.execute(create_table_cmd)

kaijus = [
    "1, 'Godzilla', 'Raio Atômico', '2026-06-18 10:00:00'",
    "2, 'Mothra', 'Raios de Seda', '2026-06-18 10:05:00'",
    "3, 'King Ghidorah', 'Raios Gravitacionais', '2026-06-18 10:10:00'",
]

for kaiju_data in kaijus:
    insert_cmd = f"INSERT INTO kaiju VALUES ({kaiju_data})"
    conn.execute(insert_cmd)

conn.commit()
print("Banco de dados 'kaiju.db' criado e populado com sucesso!")