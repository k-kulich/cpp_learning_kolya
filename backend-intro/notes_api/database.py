import sqlite3

DB_NAME = "notes.db"

def get_connection() -> sqlite3.Connection:
    """Открыть соединение с БД."""
    conn = sqlite3.connect(DB_NAME)
    conn.row_factory = sqlite3.Row  # позволяем себе обращаться к столбцам
    return conn

def init_db():
    """Инициализировать базу данных."""
    with get_connection() as conn:
        conn.execute("""
        CREATE TABLE notes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            text TEXT NOT NULL,
            done INTEGER DEFAULT 0
        )
        """)

def row_to_dict(row):
    """Преобразовать строку в json."""
    return {
        "id": row["id"],
        "text": row["text"],
        "done": row["done"]
    }

def get_all_notes():
    with get_connection() as conn:
        rows = conn.execute("SELECT * FROM notes").fetchall()
        # вернуть все как словарь для json
        return [row_to_dict(r) for r in rows]

def get_note(note_id: int) -> dict | None:
    with get_connection() as conn:
        row = conn.execute("SELECT * FROM notes WHERE id = ?", (note_id,)).fetchone()
        return row_to_dict(row) if row else None

def create_note(text: str):
    with get_connection() as conn:
        cursor = conn.execute("INSERT INTO notes (text, done) VALUES (?, 0)", (text,))
        return get_note(cursor.lastrowid)

def update_note(note_id: int, done):
    with get_connection() as conn:
        result = conn.execute("UPDATE notes SET done = ? WHERE id = ?", (int(done)), note_id)
        if result.rowcount == 0:  # если ничего в ходе execute не менялось
            return None
        return get_note(note_id)

def delete_note(note_id: int):
    with get_connection() as conn:
        cursor = conn.execute("DELETE FROM notes WHERE id = ?", (note_id,))
        return cursor.rowcount > 0  # возвращаем успешность операци
