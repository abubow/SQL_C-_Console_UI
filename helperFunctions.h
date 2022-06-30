#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;
    const string server = "tcp://127.0.0.1:3306";
    const string username = "root";
    const string password = "";

class SQL_Driver {
    sql::Driver* driver;
    sql::Connection* con;
public:
    SQL_Driver() {
        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }
    }
    void setDatabase(string name) {
        con->setSchema(name);
    }
    void createTable(string tableName, vector<string> attributes) {
        string dropStatement = string("DROP TABLE IF EXISTS ") + tableName;
        sql::PreparedStatement* stmt = con->prepareStatement(dropStatement);
        stmt->execute(); 
        string createStatement = string("CREATE TABLE ") + tableName + string("( ");
        for (int i = 0; i < attributes.size()-1; i++)
        {
            createStatement += attributes[i] + string(", ");
        }
        createStatement += attributes[attributes.size() - 1] + string(");");
        stmt = con->prepareStatement(createStatement);
        stmt->execute();
        delete stmt;
    }
    void showAllValuesFromStudents(string tableName) {
        string query = "SELECT ID, Student_Name, year_enroll, marks, grade, DOB, address,teacherID FROM student";
        sql::Statement* stmt = this->con->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        while (res->next()) {
            cout << "id = " << res->getInt(1)<<endl;
            cout << "Student_Name = '" << res->getString("Student_Name") << "'" << endl;
            cout << "year_enroll = '" << res->getInt(2) << "'" << endl;
            cout << "Marks = '" << res->getInt(3) << "'" << endl;
            cout << "Grade = '" << res->getString("grade") << "'" << endl;
            cout << "Date of birth = '" << res->getString("DOB") << "'" << endl;
            cout << "Address = '" << res->getString("address") << "'" << endl;
            cout << "teacherID = '" << res->getString("teacherID") << "'" << endl;
            cout << endl;
        }
        delete res;
        delete stmt;
    }
    void showAllValuesFromTeacher(string tableName) {
        string query = string("SELECT ID,teacher_Name,qualification,DOB,address,phone FROM ") + tableName + string(" ;");
        sql::Statement* stmt = this->con->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        while (res->next()) {
            cout << "id = " << res->getInt(1);
            cout << "teacher_Name = '" << res->getString("teacher_Name") << "'" << endl;
            cout << "qualification = '" << res->getString("qualification") << "'" << endl;
            cout << "address = '" << res->getString("address") << "'" << endl;
            cout << "Date of birth = '" << res->getInt(2) << "'" << endl;
            cout << "Phone = '" << res->getString("phone") << "'" << endl;
            cout << endl;
        }
        delete res;
        delete stmt;
    }
    void showAllValuesFromCourses(string tableName) {
        string query = string("SELECT CourseID, CourseName, teacherID FROM ") + tableName + string(" ;");
        sql::Statement* stmt = this->con->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        while (res->next()) {
            cout << "Course ID = " << res->getInt(1);
            cout << endl;
            cout << "Course Name = '" << res->getString("CourseName") << "'" << endl;
            cout << "teacherID = '" << res->getString("teacherID") << "'" << endl;
        }
        delete res;
        delete stmt;
    }
    void showAllValuesOfLaiba() {
        string query = "SELECT ID, Student_Name, year_enroll, marks, grade, DOB, address, teacherID FROM student ;";
        sql::Statement* stmt = this->con->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        while (res->next()) {
            if (res->getString("teacherID") == sql::SQLString("3")) {
                cout << "id = " << res->getInt(1) << endl;
                cout << "Student_Name = '" << res->getString("Student_Name") << "'" << endl;
                cout << "year_enroll = '" << res->getInt(2) << "'" << endl;
                cout << "Marks = '" << res->getInt(3) << "'" << endl;
                cout << "Grade = '" << res->getString("grade") << "'" << endl;
                cout << "Date of birth = '" << res->getString("DOB") << "'" << endl;
                cout << "Address = '" << res->getString("address") << "'" << endl;
                cout << endl;
            }
        }
        delete res;
        delete stmt;
    }
    void showAllValuesPHD() {
        string query = "SELECT ID,teacher_Name,qualification,DOB,address,phone FROM teacher ;";
        sql::Statement* stmt = this->con->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        while (res->next()) {
            if (res->getString("qualification")==sql::SQLString("PHD-Database++")) {
                cout << "id = " << res->getInt(1);
                cout << "teacher_Name = '" << res->getString("teacher_Name") << "'" << endl;
                cout << "qualification = '" << res->getString("qualification") << "'" << endl;
                cout << "address = '" << res->getString("address") << "'" << endl;
                cout << "Date of birth = '" << res->getInt(2) << "'" << endl;
                cout << "Phone = '" << res->getString("phone") << "'" << endl;
                cout << endl;
            }
        }
        delete res;
        delete stmt;
    }
    void showAllValuesMohsin() {
        string query = "SELECT CourseID, CourseName, teacherID FROM course;";
        sql::Statement* stmt = this->con->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        while (res->next()) {
            if (res->getString("teacherID") == sql::SQLString("2")) {
                cout << "Course ID = " << res->getInt(1);
                cout << endl;
                cout << "Course Name = '" << res->getString("CourseName") << "'" << endl;
                cout << "teacherID = '" << res->getString("teacherID") << "'" << endl;
            }
        }
        
        delete res;
        delete stmt;
    }
    void showAllColumnNames(string table) {
        string query = string("SELECT column_name FROM INFORMATION_SCHEMA.columns WHERE table_name = '" + table + "' ; ");
        cout << "Query executed: " << query << endl;
        sql::Statement* stmt = this->con->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        int count = 0;
        while (res->next()) {
            cout << ++count << ". '" << res->getString("column_name") << "'" << endl;
        }
    }
    void showAllTableNames(string database) {
        string query = string("SELECT table_name FROM INFORMATION_SCHEMA.tables WHERE table_type = 'base table' and table_schema = '")+database+string("';");
        cout << "Query executed: " << query << endl;
        sql::Statement* stmt = this->con->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        int count = 0;
        while (res->next()) {
            cout << ++count << ". '" << res->getString("table_name") << "'" << endl;
        }
    }
    vector<pair<string, string>> getColumns(string& tablename) {
        vector<pair<string,string>> columns;
        string query = string("SELECT column_name, data_type FROM INFORMATION_SCHEMA.columns WHERE table_name = '" + tablename + "' ; ");
        cout << "Query executed: " << query << endl;
        sql::Statement* stmt = this->con->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        int count = 0;
        while (res->next()) {
            pair<string, string> pr;
            pr.first = res->getString("column_name").c_str();
            pr.second = res->getString("data_type").c_str();
            columns.push_back(pr);
        }
        return columns;
    }
    void insertIntoTable(string &table) {
        vector<pair<string, string>> columns = getColumns(table);
        string query = string("INSERT INTO ") + table + string(" ( ");
        for (int i = 0; i < columns.size()-1;i++) {
            query += columns[i].first + string(", ");
        }
        query += columns[columns.size()-1].first + string (") VALUES (");
        int i = 0;
        string inputStr;
        int inputInt;
        bool breakFlag = false;
        do {
            do {
                if (columns[i].second == "int"|| columns[i].second == "float" || columns[i].second == "numeric") {
                    cout << columns[i].first << ": ";
                    cin >> inputInt;
                    query += to_string(inputInt);
                }
                else {
                    cout << columns[i].first << ": ";
                    cin >> inputStr;
                    query += "'"+inputStr+"'";
                }
                i++;
                if (i < columns.size())
                    query += ", ";
                else
                    query += ")";
            } while (i < columns.size());
            cout << "Do you wish to insert another value? ";
            cin >> inputStr;
            breakFlag = !(inputStr == "y" || inputStr == "Y" || inputStr == "1");
            if (!breakFlag)
                query += string(", (");
        } while (!breakFlag);
        cout << "Query executed: " << query << endl;
        sql::PreparedStatement* stmt = con->prepareStatement(query);
        stmt->execute();
    }
    void inputTable(string& tableName) {
        cout << "Enter tablename: ";
        cin >> tableName;
        vector<string> attributes;
        bool continueFlag = false;
        do {
            string attribute;
            string attributeName;
            string type;
            cout << "Enter attribute name: ";
            cin >> attributeName;
            cout << "Enter attribute type: \n";
            long selection = -1;
            int s;
            do {
                cout << "1. Int\n";
                cout << "2. Varchar\n";
                cout << "3. Char\n";
                cout << "4. Date\n";
                cout << "Input: ";
                cin >> selection;
                if (selection < 1 || selection>4) {
                    cout << "Invalid input.\n";
                }
            } while (selection < 1 || selection>4);
            switch (selection)
            {
            case 1:
                type = " int ";
                break;
            case 2:
                cout << "Varchar size: ";
                cin >> s;
                type = string(" VARCHAR(") + to_string(s) + string(") ");
                break;
            case 3:
                cout << "Char size: ";
                cin >> s;
                type = string(" CHAR(") + to_string(s) + string(") ");
                break;
            case 4:
                type = " DATE ";
                break;
            default:
                break;
            }
            string unique = "";
            string nullConstraint = "";
            string defaultConstraint = "";
            bool yes = false;
            cout << "Is it unique?";
            cin >> yes;
            unique += yes ? " UNIQUE " : "";
            cout << "Is it not null?";
            cin >> yes;
            nullConstraint += yes ? " NOT NULL " : "";

            string defaultValue = "";
            cout << "Do you wish to enter a default value?";
            cin >> yes;
            if (yes) {
                cout << "Enter default value: ";
                cin >> defaultValue;
                defaultValue = string(" DEFAULT ") + defaultValue;
            }
            attribute = attributeName + type + unique + nullConstraint + defaultValue;
            attributes.push_back(attribute);
            cout << "Do you wish to add more attributes?";
            cin >> continueFlag;
        } while (continueFlag);
        createTable(tableName, attributes);
    }
    ~SQL_Driver() {
        delete con;
    }
};
#define MAX_SELECTION 9
void printMenu(string database) {
    system("cls");
    printf("Database : \t%s\n\n", database.c_str());
    printf("0. Create new Table.\n");
    printf("1. Select all from Students.\n");
    printf("2. Select all from Teachers\n");
    printf("3. Select all from Courses\n");
    printf("4. Select all Students whose teacher is Laiba Mushtaq.\n");
    printf("5. Select all teacher whose Qualification is PHD.\n");
    printf("6. Select all Courses whose teacher is Mohsin Abbas.\n");
    printf("7. Show all table names.\n");
    printf("8. Show all column names.\n");
    printf("9. Insert into table.\n");
    printf("10. Quit.\n");
}