#include "Database.h"
#include <iostream>

Database::Database(const char* dbFile) : filename(dbFile), db(nullptr) {
    if (sqlite3_open(filename, &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Opened database successfully\n";
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Closed database\n";
    }
}

void Database::createStudentTable() {
    const char* sql = "CREATE TABLE IF NOT EXISTS student ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Database::insertStudent(const std::string& name) {
    std::string sql = "INSERT INTO student (name) VALUES ('" + name + "');";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Insert error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Database::showAllStudents() {
    const char* sql = "SELECT id, name FROM student;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::cout << "ID: " << id << " | Name: " << name << std::endl;
        }
        sqlite3_finalize(stmt);
    }
    else {
        std::cerr << "Failed to fetch data.\n";
    }
}
