

-- Таблица People
CREATE TABLE IF NOT EXISTS People (
    person_id SERIAL PRIMARY KEY,
    first_name VARCHAR(100) NOT NULL,
    last_name VARCHAR(100) NOT NULL,
    tg_nick VARCHAR(100) UNIQUE,
    access INT 
);

-- Таблица Role
CREATE TABLE IF NOT EXISTS Role (
    role_id SERIAL PRIMARY KEY, 
    role_name VARCHAR(100) NOT NULL
); 

-- Таблица связи Person_Role (многие-ко-многим между People и Role)
CREATE TABLE IF NOT EXISTS Person_Role (
    person_id INT REFERENCES People(person_id),
    role_id INT REFERENCES Role(role_id),
    PRIMARY KEY (person_id, role_id)
);

-- Исправленная таблица Course (была опечатка в названии Cource)
CREATE TABLE IF NOT EXISTS Course (
    course_id SERIAL PRIMARY KEY,
    course_name VARCHAR(100) NOT NULL  -- Исправлено с INT на VARCHAR
);

-- Таблица People_Group (исправлено с Group на People_Group)
CREATE TABLE IF NOT EXISTS People_Group (
    people_group_id SERIAL PRIMARY KEY,
    people_group_name VARCHAR(100) NOT NULL  -- Исправлено с INT на VARCHAR
);

-- Таблица Program
CREATE TABLE IF NOT EXISTS Program (
    program_id SERIAL PRIMARY KEY,
    program_name VARCHAR(100) NOT NULL 
);

-- Таблица Subjects (должна быть создана до Teaching_Assignment)
CREATE TABLE IF NOT EXISTS Subjects (
    subject_id SERIAL PRIMARY KEY,
    subject_name VARCHAR(100) NOT NULL
);

-- Таблица Subject_Offer (с правильными ссылками)
CREATE TABLE IF NOT EXISTS Subject_Offer (
    offer_id SERIAL PRIMARY KEY,
    people_group_id INT REFERENCES People_Group(people_group_id),
    program_id INT REFERENCES Program(program_id),
    course_id INT REFERENCES Course(course_id)
);

-- Таблица Teaching_Assignment (исправлено название с Teaching_Assingment)
CREATE TABLE IF NOT EXISTS Teaching_Assigment (
    assignment_id SERIAL PRIMARY KEY,
    person_id INT REFERENCES People(person_id),
    offer_id INT REFERENCES Subject_Offer(offer_id), 
    subject_id INT REFERENCES Subjects(subject_id)
);

-- Таблица Sop_Form с использованием созданного типа ENUM
CREATE TABLE IF NOT EXISTS Sop_Form (
    sop_id SERIAL PRIMARY KEY,
    person_id INT REFERENCES People(person_id),
    url_out_sop VARCHAR(100) NOT NULL,
    sop_status VARCHAR(100) NOT NULL,
    tg_answer TEXT,  -- Исправлено с NTEXT на TEXT
    url_answer TEXT   -- Исправлено с NTEXT на TEXT
);