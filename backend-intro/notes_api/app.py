"""
Сам запуск нашего чудо-сервера.
"""
from flask import Flask, jsonify, request
import database

app = Flask(__name__)
database.init_db() # создаем таблицу при старте


@app.get("/")
def index():
    return {"massage": "Notes API is running"}

@app.get("/notes")
def get_notes():
    return jsonify(database.get_all_notes())

@app.get("/notes/<int:note_id>")
def get_note(note_id):
    note = database.get_note(note_id)
    if note is None:
        return jsonify({"error": "No such note."}), 404
    return jsonify(note)

# теперь надо добавить создание заметки
@app.post("/notes")
def create_note():
    data = request.get_json()  # получаем то, что от клиента пришло
    if not data or "text" not in data:
        return jsonify({"error": "Field 'text' unfilled."}), 400
    database.create_note(data["text"])
    notes = get_notes(database.get_all_notes())
    return jsonify(notes), 201

# PATCH /notes/<int:note_id>
@app.patch("/notes/<int:note_id>")
def patch_note(note_id):
    # по факту не всегда в True, мб мы наоборот хотим поменять в False
    data = request.get_json()  # получаем все данные, которые были переданы в json вместе
    # с запросом
    if not data or data.get("done", "") == "":
        return jsonify({"error": "Field 'done' is required"}), 400
    # меняем тумблер на тот, что передан
    note = database.update_note(note_id, data["done"])
    if note is None:
        return jsonify({"error": "No such note."}), 404
    return jsonify(note), 200

# DELETE /notes/<int:note_id>
@app.delete("/notes/<int:note_id>")
def delete_note(note_id):
    result = delete_note(note_id)
    if not result:
        return jsonify({"error": "No such note."}), 404
    return jsonify({"message": f"Note {note_id} has been deleted."}), 200


if __name__ == "__main__":
    app.run(debug=True)
