

CREATE TABLE Programs (
    program_id SERIAL PRIMARY KEY,
    program_name VARCHAR(50) UNIQUE NOT NULL
);
 


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
    -- TODO:

CREATE TABLE Students (
    student_id SERIAL PRIMARY KEY,
    person_id INT UNIQUE REFERENCES People(person_id) ON DELETE CASCADE NOT NULL,
    program_id INT REFERENCES Programs(program_id) NOT NULL,
    info VARCHAR(255) NOT NULL
);

CREATE TABLE Person_Role (
    person_id INT REFERENCES People(person_id) ON DELETE CASCADE NOT NULL,
    role_id INT REFERENCES Roles(role_id) ON DELETE CASCADE NOT NULL,
    PRIMARY KEY (person_id, role_id)
);


CREATE TABLE Subjects (
    subject_id SERIAL PRIMARY KEY,
    subject_name VARCHAR(255) UNIQUE NOT NULL
);



CREATE TABLE Teacher_Subject (
    teacher_id INT REFERENCES People(person_id) ON DELETE CASCADE NOT NULL,
    subject_id INT REFERENCES Subjects(subject_id) ON DELETE CASCADE NOT NULL,
    PRIMARY KEY (teacher_id, subject_id)
);


CREATE TABLE People_Subject (
    person_id INT REFERENCES People(person_id) ON DELETE CASCADE NOT NULL ,
    subject_id INT REFERENCES Subjects(subject_id) ON DELETE CASCADE NOT NULL ,
    PRIMARY KEY (person_id, subject_id)
);


CREATE TABLE Feedback_Request (
    request_id SERIAL PRIMARY KEY,
    teacher_id INT REFERENCES People(person_id) ON DELETE CASCADE NOT NULL,
    subject_id INT REFERENCES Subjects(subject_id) ON DELETE CASCADE NOT NULL,
    request_name VARCHAR(255) NOT NULL
);


CREATE TABLE Result_Request (
    result_id INT REFERENCES Feedback_URL(result_id) ON DELETE CASCADE NOT NULL,
    request_id INT REFERENCES Feedback_Request(request_id) ON DELETE CASCADE NOT NULL,
    PRIMARY KEY (result_id, request_id)
);


CREATE TABLE Feedback_URL (
    result_id SERIAL PRIMARY KEY,
    student_id INT REFERENCES Students(student_id) ON DELETE CASCADE NOT NULL,
    JSON VARCHAR(255) NOT NULL
);



CREATE TABLE Tags (
    tag_id SERIAL PRIMARY KEY , 
    tag_name VARCHAR(255) NOT NULL 

);


CREATE TABLE Subject_Tags (
    subject_id INT REFERENCES Subjects(subject_id) ON DELETE CASCADE NOT NULL ,
    tag_id INT REFERENCES Tags(tag_id) ON DELETE CASCADE NOT NULL ,
    PRIMARY KEY (subject_id, tag_id)
);

CREATE TABLE Filters (
    filter_id SERIAL PRIMARY KEY , 
    filter_name VARCHAR(255)  
);


CREATE TABLE Filter_Includes (
    filter_id INT REFERENCES Filters(filter_id) ON DELETE CASCADE NOT NULL ,
    tag_id INT REFERENCES Tags(tag_id) ON DELETE CASCADE NOT NULL ,
    PRIMARY KEY (filter_id, tag_id)
);

CREATE TABLE Filter_Excludes (
    filter_id INT REFERENCES Filters(filter_id) ON DELETE CASCADE NOT NULL,
    tag_id INT REFERENCES Tags(tag_id) ON DELETE CASCADE NOT NULL ,
    PRIMARY KEY (filter_id, tag_id)
);


CREATE TABLE Catagories (
    category_id SERIAL PRIMARY KEY , 
    category_name VARCHAR(255)  , 
    filter_id INt REFERENCES Filters(filter_id) ON DELETE CASCADE NOT NULL ,
    required BOOLEAN
);



CREATE TABLE Category_Tags(
    category_id INT REFERENCES Catagories(category_id) ON DELETE CASCADE NOT NULL,
    tag_id INT REFERENCES Tags(tag_id) ON DELETE CASCADE NOT NULL,
    PRIMARY KEY (category_id, tag_id)
);

CREATE TABLE Person_Filter_Access (
    person_id INT REFERENCES People(person_id) ON DELETE CASCADE NOT NULL,
    filter_id INT REFERENCES Filters(filter_id) ON DELETE CASCADE NOT NULL, 
    PRIMARY KEY (person_id , filter_id)
); 

CREATE TABLE