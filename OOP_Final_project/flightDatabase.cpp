#include "flightDatabase.h"
#include <iostream>


flightDatabase::flightDatabase(const char* dbFile)
    : db(nullptr), filename(dbFile)
{
    if (sqlite3_open(filename, &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << '\n';
        db = nullptr;
    }
    else {
        std::cout << "Opened database successfully\n";
    }
}
flightDatabase::~flightDatabase()
{
    if (db) {
        sqlite3_close(db);
        std::cout << "Closed database\n";
    }
}

/* ---------- schema ---------- */
void flightDatabase::createFlightTable()
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS flight ("
        "  flight_id     TEXT PRIMARY KEY,"
        "  origin        TEXT NOT NULL,"
        "  destination   TEXT NOT NULL,"
        "  flight_time   TEXT NOT NULL,"   /* YYYY-MM-DD HH:MM */
        "  ticket        INTEGER NOT NULL"
        ");";

    char* err = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        std::cerr << "SQL error (createFlightTable): " << err << '\n';
        sqlite3_free(err);
    }
}

/* ---------- insert ---------- */
bool flightDatabase::insertFlight(const std::string& flightId,
    const std::string& origin,
    const std::string& destination,
    const std::string& flightTime,
    int               ticket)
{
    const char* sql =
        "INSERT INTO flight (flight_id, origin, destination, flight_time, ticket) "
        "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare error: " << sqlite3_errmsg(db) << '\n';
        return false;
    }
    // bind parameters
    sqlite3_bind_text(stmt, 1, flightId.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, origin.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, destination.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, flightTime.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, ticket);

    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!ok)
        std::cerr << "Insert error: " << sqlite3_errmsg(db) << '\n';

    sqlite3_finalize(stmt);
    return ok;
}

/* ---------- delete by primary key ---------- */
bool flightDatabase::deleteFlight(const std::string& flightId)
{
    const char* sql = "DELETE FROM flight WHERE flight_id = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Delete prepare error: " << sqlite3_errmsg(db) << '\n';
        return false;
    }

    sqlite3_bind_text(stmt, 1, flightId.c_str(), -1, SQLITE_TRANSIENT);

    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!ok)
        std::cerr << "Delete error: " << sqlite3_errmsg(db) << '\n';
    else if (sqlite3_changes(db) == 0)
        std::cerr << "Delete warning: flight_id not found\n";

    sqlite3_finalize(stmt);
    return ok;
}

/* ---------- select / print ---------- */
void flightDatabase::showAllFlights()
{
    const char* sql =
        "SELECT rowid AS orderno, flight_id, origin, destination, "
        "       flight_time, ticket "
        "FROM   flight "
        "ORDER  BY orderno;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Query prepare error: " << sqlite3_errmsg(db) << '\n';
        return;
    }

    std::cout << "\nOrder | Flight | Origin -> Dest | Time | Ticket\n";
    std::cout << "---------------------------------------------------------\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int orderno = sqlite3_column_int(stmt, 0);
        const char* flightId = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* origin = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        const char* flightTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        int ticket = sqlite3_column_int(stmt, 5);

        std::cout << orderno << " | " << flightId << " | "
            << origin << " -> " << destination << " | "
            << flightTime << " | " << ticket << '\n';
    }
    sqlite3_finalize(stmt);
}

/* ---------- helper: prints a prepared statement result ---------- */
static void printResult(sqlite3_stmt* stmt)
{
    std::cout << "\nOrder | Flight | Origin -> Dest | Time | Ticket\n"
        << "---------------------------------------------------------\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int  orderno = sqlite3_column_int(stmt, 0);
        auto flightId = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        auto origin = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        auto destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        auto flightTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        int  ticket = sqlite3_column_int(stmt, 5);

        std::cout << orderno << " | " << flightId << " | "
            << origin << " -> " << destination << " | "
            << flightTime << " | " << ticket << '\n';
    }
    sqlite3_finalize(stmt);
}

/* -------- query by primary key -------- */
void flightDatabase::queryByFlightID(const std::string& flightId)
{
    const char* sql =
        "SELECT rowid AS orderno, flight_id, origin, destination, "
        "       flight_time, ticket "
        "FROM flight WHERE flight_id = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, flightId.c_str(), -1, SQLITE_TRANSIENT);
        printResult(stmt);
    }
    else {
        std::cerr << "Prepare error: " << sqlite3_errmsg(db) << '\n';
    }
}

/* -------- query by exact departure timestamp -------- */
void flightDatabase::queryByDepartureTime(const std::string& flightTime)
{
    const char* sql =
        "SELECT rowid, flight_id, origin, destination, flight_time, ticket "
        "FROM flight WHERE flight_time = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, flightTime.c_str(), -1, SQLITE_TRANSIENT);
        printResult(stmt);
    }
    else {
        std::cerr << "Prepare error: " << sqlite3_errmsg(db) << '\n';
    }
}

/* -------- query by both origin AND destination -------- */
void flightDatabase::queryByRoute(const std::string& origin,
    const std::string& destination)
{
    const char* sql =
        "SELECT rowid AS orderno, flight_id, origin, destination, "
        "       flight_time, ticket "
        "FROM flight "
        "WHERE origin = ? AND destination = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, origin.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, destination.c_str(), -1, SQLITE_TRANSIENT);
        printResult(stmt);          // reuse the helper added earlier
    }
    else {
        std::cerr << "Prepare error: " << sqlite3_errmsg(db) << '\n';
    }
}


/* -----------------------------------------------------------
   Helper: fetch current ticket count (returns −1 if not found)
   ----------------------------------------------------------- */
static int getTicket(sqlite3* db, const std::string& flightId)
{
    const char* sql = "SELECT ticket FROM flight WHERE flight_id = ?;";
    sqlite3_stmt* st = nullptr;
    int ticket = -1;

    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(st, 1, flightId.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(st) == SQLITE_ROW)
            ticket = sqlite3_column_int(st, 0);
    }
    sqlite3_finalize(st);
    return ticket;
}

/* -----------------------------------------------------------
   Helper: copy full row from src → dst when booking first time
   ----------------------------------------------------------- */
static bool copyRow(sqlite3* dst, sqlite3* src, const std::string& flightId,
    int initialTicket)
{
    /* grab origin, destination, time from src */
    const char* sel =
        "SELECT origin, destination, flight_time "
        "FROM flight WHERE flight_id = ?;";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(src, sel, -1, &st, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(st, 1, flightId.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(st) != SQLITE_ROW) { sqlite3_finalize(st); return false; }

    std::string origin =
        reinterpret_cast<const char*>(sqlite3_column_text(st, 0));
    std::string destination =
        reinterpret_cast<const char*>(sqlite3_column_text(st, 1));
    std::string flightTime =
        reinterpret_cast<const char*>(sqlite3_column_text(st, 2));
    sqlite3_finalize(st);

    /* insert into dst */
    const char* ins =
        "INSERT INTO flight (flight_id, origin, destination, flight_time, ticket) "
        "VALUES (?, ?, ?, ?, ?);";
    if (sqlite3_prepare_v2(dst, ins, -1, &st, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(st, 1, flightId.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(st, 2, origin.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(st, 3, destination.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(st, 4, flightTime.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(st, 5, initialTicket);

    bool ok = (sqlite3_step(st) == SQLITE_DONE);
    sqlite3_finalize(st);
    return ok;
}

/* -----------------------------------------------------------
   MAIN routine: modifyTicket
   ----------------------------------------------------------- */
bool flightDatabase::modifyTicket(flightDatabase& flightDB,
    flightDatabase& bookingDB,
    const std::string& flightId,
    int mode, int change)
{
    if (change <= 0) { std::cerr << "change must be positive\n"; return false; }
    if (mode != 0 && mode != 1) { std::cerr << "mode must be 0 or 1\n"; return false; }

    sqlite3* fdb = flightDB.db;
    sqlite3* bdb = bookingDB.db;

    /* 1. start Tx on both DBs */
    sqlite3_exec(fdb, "BEGIN IMMEDIATE;", nullptr, nullptr, nullptr);
    sqlite3_exec(bdb, "BEGIN IMMEDIATE;", nullptr, nullptr, nullptr);

    auto rollback = [&]() {
        sqlite3_exec(fdb, "ROLLBACK;", nullptr, nullptr, nullptr);
        sqlite3_exec(bdb, "ROLLBACK;", nullptr, nullptr, nullptr);
        };

    /* 2. fetch ticket counts */
    int fTicket = getTicket(fdb, flightId);
    int bTicket = getTicket(bdb, flightId);

    if (mode == 0) {                             /* ---- BOOK ---- */
        if (fTicket < 0) { std::cerr << "Flight not found.\n"; rollback(); return false; }
        if (fTicket < change) { std::cerr << "Not enough seats.\n"; rollback(); return false; }

        /* update flightDB (−change) */
        const char* updF = "UPDATE flight SET ticket = ticket - ? WHERE flight_id = ?;";
        sqlite3_stmt* st = nullptr;
        sqlite3_prepare_v2(fdb, updF, -1, &st, nullptr);
        sqlite3_bind_int(st, 1, change);
        sqlite3_bind_text(st, 2, flightId.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(st); sqlite3_finalize(st);

        /* booking DB: insert or increment */
        if (bTicket < 0) {
            if (!copyRow(bdb, fdb, flightId, change)) { rollback(); return false; }
        }
        else {
            const char* updB = "UPDATE flight SET ticket = ticket + ? WHERE flight_id = ?;";
            sqlite3_prepare_v2(bdb, updB, -1, &st, nullptr);
            sqlite3_bind_int(st, 1, change);
            sqlite3_bind_text(st, 2, flightId.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_step(st); sqlite3_finalize(st);
        }
    }
    else {                                       /* ---- CANCEL ---- */
        if (bTicket < 0) { std::cerr << "Booking not found.\n"; rollback(); return false; }
        if (bTicket < change) { std::cerr << "Cancel exceeds booking.\n"; rollback(); return false; }

        /* update bookingDB (−change) or delete row if zero */
        const char* updB =
            "UPDATE flight SET ticket = ticket - ? WHERE flight_id = ?;";
        sqlite3_stmt* st = nullptr;
        sqlite3_prepare_v2(bdb, updB, -1, &st, nullptr);
        sqlite3_bind_int(st, 1, change);
        sqlite3_bind_text(st, 2, flightId.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(st); sqlite3_finalize(st);

        sqlite3_exec(bdb,
            "DELETE FROM flight WHERE ticket = 0 AND flight_id = ?1;",
            nullptr, nullptr, nullptr);

        /* update flightDB (+change) */
        const char* updF =
            "UPDATE flight SET ticket = ticket + ? WHERE flight_id = ?;";
        sqlite3_prepare_v2(fdb, updF, -1, &st, nullptr);
        sqlite3_bind_int(st, 1, change);
        sqlite3_bind_text(st, 2, flightId.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(st); sqlite3_finalize(st);
    }

    /* 3. commit both */
    sqlite3_exec(fdb, "COMMIT;", nullptr, nullptr, nullptr);
    sqlite3_exec(bdb, "COMMIT;", nullptr, nullptr, nullptr);
    return true;
}


