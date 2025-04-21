#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite3.h"

class Database {
private:
    sqlite3* db;
    const char* filename;

public:
    Database(const char* dbFile);
    ~Database();

    void createStudentTable();
    void insertStudent(const std::string& name);
    void showAllStudents();
};

#endif // DATABASE_H