#include <gtest/gtest.h>
#include <pqxx/pqxx>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../inc/manageSOP.hpp"
#include "../include/DOP_Functions.hpp"

using json = nlohmann::json;
using namespace std;

class DatabaseTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        conn = make_shared<pqxx::connection>("dbname=test user=postgres password=postgres host=localhost");
        pqxx::work txn(*conn);
        InitializeDB(txn);
        txn.commit();
    }

    static void TearDownTestSuite() {
        conn->disconnect();
    }

    void SetUp() override {
        txn = make_unique<pqxx::work>(*conn);
    }

    void TearDown() override {
        txn->abort();
    }

    static shared_ptr<pqxx::connection> conn;
    unique_ptr<pqxx::work> txn;
};

shared_ptr<pqxx::connection> DatabaseTest::conn = nullptr;

TEST_F(DatabaseTest, PersonCRUD) {
    People person{"John", "Doe", "johndoe", 0, 12121};
    int id = CreatePerson(*txn, person.GetFirstName(), person.GetLastName(),
                         person.GetTgNick(), person.GetAccess(),
                         person.GetSnils());
    EXPECT_GT(id, 0);

    auto [fname, lname, tg, access, snils] = ReadPerson(*txn, id);
    EXPECT_EQ(fname, "John");
    EXPECT_EQ(lname, "Doe");

    DeletePerson(*txn, id);
    EXPECT_THROW(ReadPerson(*txn, id), runtime_error);
}

TEST_F(DatabaseTest, SubjectCRUD) {
    int id = CreateSubject(*txn, "Mathematics");
    EXPECT_GT(id, 0);
    
    string name = ReadSubject(*txn, id);
    EXPECT_EQ(name, "Mathematics");
    
    UpdateSubject(*txn, id, "Physics");
    EXPECT_EQ(ReadSubject(*txn, id), "Physics");
    
    DeleteSubject(*txn, id);
    EXPECT_THROW(ReadSubject(*txn, id), runtime_error);
}

TEST_F(DatabaseTest, SOPFormCRUD) {
    People person{"John", "Doe", "johndoe", 0, 12121};
    int pid = CreatePerson(*txn, person.GetFirstName(), person.GetLastName(),
                         person.GetTgNick(), person.GetAccess(),
                         person.GetSnils());
    
    SOP_Form form{pid, "url", "tg_answer", "url_answer"};
    int id = CreateSOPForm(*txn, form.GetPersonId(), form.GetUrl(),
                          form.GetTgAnswer(), form.GetUrlAnswer());
    EXPECT_GT(id, 0);
    
    auto [_, url, status, tg, url_ans] = ReadSOPForm(*txn, id);
    EXPECT_EQ(url, "url");
    
    UpdateStatus(*txn, id, "APPROVED");
    EXPECT_EQ(get<2>(ReadSOPForm(*txn, id)), "APPROVED");
    
    Delete_SOP_Form(*txn, id);
    EXPECT_THROW(ReadSOPForm(*txn, id), runtime_error);
}

TEST_F(DatabaseTest, GetAllTeachersForStudent) {
    int student_role = CreateRole(*txn, "Student");
    int teacher_role = CreateRole(*txn, "Teacher");
    
    int student_id = CreatePerson(*txn, "Ivan", "Ivanov", "ivanov", 0, 12345);
    CreatePersonRole(*txn, student_id, student_role);
    
    int teacher_id = CreatePerson(*txn, "Petr", "Petrov", "petrov", 1, 54321);
    CreatePersonRole(*txn, teacher_id, teacher_role);
    
    int group_id = CreatePeopleGroup(*txn, "Group1");
    int program_id = CreateProgram(*txn, "Program1");
    int course_id = CreateCourse(*txn, "1");
    int subject_id = CreateSubject(*txn, "Math");
    
    int offer_id = CreateSubjectOffer(*txn, group_id, program_id, course_id);
    CreateTeachingAssigment(*txn, teacher_id, offer_id, subject_id);
    CreateTeachingAssigment(*txn, student_id, offer_id, CreateSubject(*txn, "Student"));

    vector<Teacher> teachers = GetAllTeachersForStudent(*txn, student_id);
    ASSERT_EQ(teachers.size(), 1);
    EXPECT_EQ(teachers[0].first_name, "Petr");
    EXPECT_EQ(teachers[0].last_name, "Petrov");
}

TEST_F(DatabaseTest, CreatePersonWithParams) {
    Person person;
    person.first_name = "Egor";
    person.last_name = "Lukavenko";
    person.tg_nick = "st_luka";
    person.access = 0;
    person.snils = 1337;
    person.role = "Student";
    person.subject_name = "Math";
    person.program_name = "PMI";
    person.course_name = "1";
    person.people_group_name = "GroupA";
    
    CreatePersonWithParams(*txn, person);
    
    pqxx::result res = txn->exec("SELECT * FROM People WHERE last_name = 'Smith'");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0]["first_name"].as<string>(), "Anna");
}

class MockHttpClient : public sop::HttpClient {
public:
    MOCK_METHOD(std::string, performHttpRequest, 
                (const std::string&, const std::string&, const std::string&, const std::string&), 
                (override));
};

TEST_F(DatabaseTest, GenerateQuestions) {
    int student_id = CreatePerson(*txn, "Test", "Student", "test_student", 0, 99999);
    int teacher_id = CreatePerson(*txn, "Math", "Teacher", "math_teacher", 1, 88888);
    
    vector<Teacher> teachers;
    teachers.push_back({
        "Math", 
        "Teacher", 
        {"Teacher"}, 
        "Mathematics"
    });
    
    json questions = sop::generateQuestionsPerStudent(*txn, student_id);
    ASSERT_FALSE(questions.empty());
    EXPECT_TRUE(questions.contains("requests"));

    const auto& requests = questions["requests"];
    ASSERT_GT(requests.size(), 0);
    EXPECT_EQ(requests[0]["createItem"]["item"]["title"], "Mathematics");
}

TEST(ConfigTest, EnvironmentVariables) {
    setenv("GOOGLE_CLIENT_ID", "test_client_id", 1);
    setenv("GOOGLE_CLIENT_SECRET", "test_secret", 1);
    setenv("GOOGLE_REFRESH_TOKEN", "test_token", 1);
    
    sop::Config config;
    EXPECT_EQ(config.getClientId(), "test_client_id");
    EXPECT_EQ(config.getClientSecret(), "test_secret");
    EXPECT_EQ(config.getRefreshToken(), "test_token");
}

TEST(JsonTest, ReadJsonFromFile) {
    ofstream tmpfile("tmp_test.json");
    tmpfile << R"({"test": "value"})";
    tmpfile.close();
    
    json data = sop::readJsonFromFile("tmp_test.json");
    EXPECT_EQ(data["test"], "value");
    remove("tmp_test.json");
}

// Главная функция
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
