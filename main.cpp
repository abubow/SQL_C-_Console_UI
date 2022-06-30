#include <stdlib.h>
#include <iostream>

#include "helperFunctions.h"
using namespace std;

int main()
{
    SQL_Driver sqlobj;
    string databaseName;
    string tablename;
    string query;
    vector<string> attributes;
    cout << "Enter the name of your database: ";
    cin >> databaseName;
    sqlobj.setDatabase(databaseName);
    vector<vector<string>> tablesAttributes;
    long long selection = -1;
    do {
        printMenu(databaseName);
        do {
            cout << "Input: ";
            cin >> selection;
            if (selection<0 || selection>MAX_SELECTION) {
                cout << "Invalid input.\n";
            }
        } while (selection<0 || selection>MAX_SELECTION);
        switch (selection)
        {
        case 0:
            tablename = "";
            sqlobj.inputTable(tablename);
            cout << tablename << " created.\n";
            break;
        case 1:
            tablename = "student";
            sqlobj.showAllValuesFromStudents(tablename);
            break;
        case 2:
            tablename = "teacher";
            sqlobj.showAllValuesFromTeacher(tablename);
            break;
        case 3:
            tablename = "course";
            sqlobj.showAllValuesFromCourses(tablename);
            break;
        case 4:
            sqlobj.showAllValuesOfLaiba();
            break;
        case 5:
            sqlobj.showAllValuesPHD();
            break;
        case 6:
            sqlobj.showAllValuesMohsin();
            break;
        case 7:
            query = string("SELECT table_name FROM INFORMATION_SCHEMA.tables WHERE table_type = 'base table' and table_schema = '") + databaseName + string("';");
            sqlobj.showAllTableNames(databaseName);
        case 8:
            cout << "Enter Table: ";
            cin >> tablename;
            sqlobj.showAllColumnNames(tablename);
            break;
        case 9:
            cout << "Enter Table: ";
            cin >> tablename;
            sqlobj.insertIntoTable(tablename);
            break;
        case 10:
            return 0;
            break;
        default:
            break;
        }
        system("pause");
    } while (1);
    system("pause");
    return 0;
}
