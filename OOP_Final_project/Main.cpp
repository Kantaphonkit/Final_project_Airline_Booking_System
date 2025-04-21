#include <iostream>
#include "sqlite3.h"
#include "Database.h"

using namespace std;

int main() {
    
    Database db("project.db");

    db.createStudentTable();
    db.insertStudent("Alice");
    db.insertStudent("Bob");

    db.showAllStudents();

    return 0;

    return 0;
}
