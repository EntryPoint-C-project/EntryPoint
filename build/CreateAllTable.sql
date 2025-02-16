

CREATE TABLE Programs (
    program_id SERIAL PRIMARY KEY,
    program_name VARCHAR(50) UNIQUE NOT NULL
);
INSERT INTO Programs (program_name) VALUES 
    ('PMI'), 
    ('PADII'), 
    ('PHYSICS'), 
    ('KOTSYS');


CREATE TABLE People (
    person_id SERIAL PRIMARY KEY,
    first_name VARCHAR(100) NOT NULL,
    last_name VARCHAR(100) NOT NULL,
    tg_nick VARCHAR(100) UNIQUE
);


CREATE TABLE Roles (
    role_id SERIAL PRIMARY KEY,
    role_name VARCHAR(255) UNIQUE NOT NULL
);
INSERT INTO Roles (role_name) VALUES 
    ('admin'); 

CREATE TABLE Students (
    student_id SERIAL PRIMARY KEY,
    person_id INT UNIQUE REFERENCES People(person_id) ON DELETE CASCADE,
    program_id INT REFERENCES Programs(program_id) NOT NULL,
    info VARCHAR(255) NOT NULL
);

CREATE TABLE Person_Role (
    person_id INT REFERENCES People(person_id) ON DELETE CASCADE,
    role_id INT REFERENCES Roles(role_id) ON DELETE CASCADE,
    PRIMARY KEY (person_id, role_id)
);


CREATE TABLE Subjects (
    subject_id SERIAL PRIMARY KEY,
    subject_name VARCHAR(255) UNIQUE NOT NULL
);
INSERT INTO Programs (program_name) VALUES 
    ('MATH'), 
    ('ALGEBRA'), 
    ('C++'), 
    ('ALGOSY');




CREATE TABLE Teacher_Subject (
    teacher_id INT REFERENCES People(person_id) ON DELETE CASCADE,
    subject_id INT REFERENCES Subjects(subject_id) ON DELETE CASCADE,
    PRIMARY KEY (teacher_id, subject_id)
);


CREATE TABLE People_Subject (
    person_id INT REFERENCES People(person_id) ON DELETE CASCADE,
    subject_id INT REFERENCES Subjects(subject_id) ON DELETE CASCADE,
    PRIMARY KEY (person_id, subject_id)
);


CREATE TABLE Feedbacks (
    feedback_id SERIAL PRIMARY KEY,
    teacher_id INT REFERENCES People(person_id) ON DELETE CASCADE,
    subject_id INT REFERENCES Subjects(subject_id) ON DELETE CASCADE,
    name VARCHAR(255) NOT NULL
);


CREATE TABLE Feedback_Participants (
    student_id INT REFERENCES Students(student_id) ON DELETE CASCADE,
    feedback_id INT REFERENCES Feedbacks(feedback_id) ON DELETE CASCADE,
    feedback TEXT,
    PRIMARY KEY (feedback_id, student_id)
);


CREATE TABLE Tags (
    tag_id SERIAL PRIMARY KEY , 
    name VARCHAR(255) NOT NULL 

);


CREATE TABLE Subject_Tags (
    subject_id INT REFERENCES Subjects(subject_id) ON DELETE CASCADE,
    tag_id INT REFERENCES Tags(tag_id) ON DELETE CASCADE,
    PRIMARY KEY (subject_id, tag_id)
);

CREATE TABLE Filters (
    filter_id SERIAL PRIMARY KEY , 
    name VARCHAR(255) NOT NULL 
);


CREATE TABLE Filter_Includes (
    filter_id INT REFERENCES Filters(filter_id) ON DELETE CASCADE,
    tag_id INT REFERENCES Tags(tag_id) ON DELETE CASCADE,
    PRIMARY KEY (filter_id, tag_id)
);

CREATE TABLE Filter_Excludes (
    filter_id INT REFERENCES Filters(filter_id) ON DELETE CASCADE,
    tag_id INT REFERENCES Tags(tag_id) ON DELETE CASCADE,
    PRIMARY KEY (filter_id, tag_id)
);


CREATE TABLE Catagories (
    category_id SERIAL PRIMARY KEY , 
    name VARCHAR(255) NOT NULL , 
    filter_id INt REFERENCES Filters(filter_id) ON DELETE CASCADE ,
    required BOOLEAN
);


CREATE TABLE Category_Tags(
    category_id INT REFERENCES Catagories(category_id) ON DELETE CASCADE,
    tag_id INT REFERENCES Tags(tag_id) ON DELETE CASCADE,
    PRIMARY KEY (category_id, tag_id)
);

CREATE TABLE Person_Filter_Access (
    person_id INT REFERENCES People(person_id) ON DELETE CASCADE ,
    filter_id INT REFERENCES Filters(filter_id) ON DELETE CASCADE, 
    PRIMARY KEY (person_id , filter_id)
); 
