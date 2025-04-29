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

        /* queries */
        void queryByFlightID(const std::string& flightId);
        void queryByDepartureTime(const std::string& flightTime);     // exact “YYYY-MM-DD HH:MM”
        void queryByRoute(const std::string& origin,
                          const std::string& destination);

        static bool modifyTicket(flightDatabase& flightDB,
                                 flightDatabase& bookingDB,
                                 const std::string& flightId,
                                 int mode,          // 0 = book, 1 = cancel
                                 int change);       // seats to add/remove

    };

#endif  // FLIGHT_DATABASE_H
