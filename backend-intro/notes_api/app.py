"""
Сам запуск нашего чудо-сервера.
"""
from flask import Flask, jsonify, request

app = Flask(__name__)

notes = [
    {"id": 1, "text": "First note ever.", "done": False}
]

@app.get("/")
def index():
    return {"massage": "Notes API is running"}

@app.get("/notes")
def get_notes():
    return jsonify(notes)

@app.get("/notes/<int:note_id>")
def get_note(note_id):
    note = next((n for n in notes if n["id"] == note_id), None)
    if note is None:
        return jsonify({"error": "No such note."}), 404
    return jsonify(note)

# теперь надо добавить создание заметки
@app.post("/notes")
def create_note():
    data = request.get_json()  # получаем то, что от клиента пришло
    if not data or "text" not in data:
        return jsonify({"error": "Field 'text' unfilled."}), 400
    new_id = max([n["id"] for n in notes], default=0) + 1
    new_note = {
        "id": new_id,
        "text": data["text"],
        "done": False
    }
    notes.append(new_note)
    return jsonify(notes), 201

if __name__ == "__main__":
    app.run(debug=True)
