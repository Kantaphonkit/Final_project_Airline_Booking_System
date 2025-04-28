#include <iostream>
#include "sqlite3.h"
#include "flightDatabase.h"
#include "modifyFlightDB.h"
#include "bookingSystem.h"

using namespace std;

int main() {

	flightDatabase flightDB("airline.db");
	flightDatabase bookingDB("booking.db");

	flightDB.createFlightTable();
	bookingDB.createFlightTable();

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
