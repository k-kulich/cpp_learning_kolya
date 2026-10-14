# Общая схема взаимодействия

```
Клиент -> HTTP-запрос -> Сервер его обрабатывает -> HTTP-ответ -> Клиент 
```

Клиент - в первую очередь браузер или другой софт, который будет на стороне пользователя (а не сам пользователь)

## HTTP-запрос

- метод: `GET, POST, PUT, PATCH, DELETE`
- url: адрес, откуда/куда что-то нужно
- заголовки: `Content-type: application/json...` - служебная информация
- тело запроса: данные, обычно json

## HTTP-ответ

- код ответа: 200 Ok, 4XX ошибки на стороне клиента, 5XX ошибки на стороне сервера
- тело ответа: данные, обычно json

## API

API - Application Programing Interface - способ взаимодействия с сервером через код.

## Самый первый простой бэк

Просто мини-сайт с заметками


---

## Базы данных

- Реляционные (SQL, табличные): PostgreSQL, MySQL, SQLite...
- Нереляционные: MongoDB, Redis...

Мы работаем на SQL (это язык запросов к базе данных по факту).

Основные команды SQL:
```sql
-- Создать таблицу
CREATE TABLE notes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    text TEXT NOT NULL,
    done INTEGER DEFAULT 0
);

-- Вставить строку (заметку)
INSERT INTO notes (text, done) VALUES ("текст заметки", 0);

-- Выбрать все
SELECT * FROM notes;

-- Выбрать одну заметку по id
SELECT * FROM notes WHERE id = 1;

-- Обновить заметку
UPDATE notes SET done = 1 WHERE id = 1;

-- Удалить
DELETE FROM notes WHERE id = 1;
```

