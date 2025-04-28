#include <iostream>
#include "sqlite3.h"
#include "flightDatabase.h"
#include "modifyFlightDB.h"
#include "bookingSystem.h"

using namespace std;

//void insertDummyFlights(flightDatabase& db); //For testing

int main() {

	flightDatabase flightDB("airline.db");
	flightDatabase bookingDB("booking.db");

	flightDB.createFlightTable();
	bookingDB.createFlightTable();

	//insertDummyFlights(flightDB); // For testing

	char option;
    
    while (1) {

        cout << "---------------- " << "Welcome to the Airport Management System" << " ----------------" << endl;
		cout << "Choose your option below:" << endl;
		cout << "1. Modify flight Database" << endl;
		cout << "2. Booking system" << endl; 
		cout << "3. Exit" << endl;
		cout << "Enter your option: ";
		cin >> option;
		switch (option) {
			case '1':
			{
				modifyFlightDB(flightDB);
				break;
			}
			case '2':
			{
				bookingSystem(flightDB);
				break;
			}
			case '3':
				cout << "Exiting the program." << endl;
				return 0;
		}
    }

    return 0;
}

/* -----------------------------------------------------------
   Inserts 10 dummy rows – call once at program start-up
   ----------------------------------------------------------- 
void insertDummyFlights(flightDatabase& db)
{
	struct Row {
		const char* id;
		const char* orig;
		const char* dest;
		const char* time;   // YYYY-MM-DD HH:MM
		int         ticket;
	} sample[10] = {
		{ "TG101", "BKK", "HND", "2025-05-01 08:30", 420 },
		{ "TG102", "HND", "BKK", "2025-05-01 14:45", 430 },
		{ "JL728", "HND", "SIN", "2025-05-02 10:15", 380 },
		{ "SQ611", "SIN", "BKK", "2025-05-03 17:20", 310 },
		{ "CX500", "HKG", "BKK", "2025-05-04 09:50", 295 },
		{ "CX501", "BKK", "HKG", "2025-05-04 13:35", 300 },
		{ "VA200", "SYD", "BKK", "2025-05-05 06:55", 510 },
		{ "VA201", "BKK", "SYD", "2025-05-05 21:10", 520 },
		{ "NH847", "NRT", "BKK", "2025-05-06 15:40", 445 },
		{ "NH848", "BKK", "NRT", "2025-05-06 23:55", 450 }
	};

	for (const auto& r : sample)
		db.insertFlight(r.id, r.orig, r.dest, r.time, r.ticket);
}
*/