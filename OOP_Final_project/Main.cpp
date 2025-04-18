#include <iostream>
#include "sqlite3.h"

int main() {
    sqlite3* db;
    char* errMsg = nullptr;

    // 1. Open or create the database file
    int rc = sqlite3_open("project.db", &db);
    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    std::cout << "Opened database successfully.\n";

    // 2. Create a table
    const char* createSQL = "CREATE TABLE IF NOT EXISTS student ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL);";
    rc = sqlite3_exec(db, createSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (create): " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // 3. Insert sample data
    const char* insertSQL = "INSERT INTO student (name) VALUES ('Alice'), ('Bob'), ('Charlie');";
    rc = sqlite3_exec(db, insertSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (insert): " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // 4. Query and print data
    const char* selectSQL = "SELECT id, name FROM student;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement\n";
        sqlite3_close(db);
        return 1;
    }

    std::cout << "\n--- Student Table ---\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        std::cout << "ID: " << id << " | Name: " << name << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    std::cout << "\nPress Enter to exit...";
    std::cin.get();  // waits for Enter

    return 0;
}
