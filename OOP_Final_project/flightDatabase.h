#ifndef FLIGHT_DATABASE_H
#define FLIGHT_DATABASE_H

#include <string>
#include "sqlite3.h"

class flightDatabase {
private:
    sqlite3* db;
    const char* filename;

public:
    explicit flightDatabase(const char* dbFile);
    ~flightDatabase();

    // schema + CRUD
    void createFlightTable();
    bool insertFlight(const std::string& flightId,
        const std::string& origin,
        const std::string& destination,
        const std::string& flightTime,  // "YYYY-MM-DD HH:MM"
        int                ticket);
    bool deleteFlight(const std::string& flightId);   
    void showAllFlights();        // prints: order, flightId, origin→dest, time, ticket
};

#endif  // FLIGHT_DATABASE_H
