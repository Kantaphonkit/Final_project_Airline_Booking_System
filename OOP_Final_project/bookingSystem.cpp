#include <iostream>
#include "sqlite3.h"
#include "flightDatabase.h"
#include "bookingSystem.h"

using namespace std;

int bookingSystem(flightDatabase& flightDB) {

	char option = '0';

	while (1) {

		if (option == '0') {
			flightDB.showAllFlights();
		}

		cout << "---------------- " << "This is booking page" << " ----------------" << endl;
		cout << "Choose your option below:" << endl;
		cout << "1. Search a flight by flight ID." << endl;
		cout << "2. Search a flight by depaparture time." << endl;
		cout << "3. Search a flight by terminal station." << endl;
		cout << "4. Book a flight" << endl;
		cout << "5. Cancel a flight" << endl;
		cout << "6. Return to Home page" << endl;
		cout << "Enter your option: ";
		cin >> option;
		switch (option) {
		case '1':
		{
			// bookFlight(flightDB);
			break;
		}
		case '2':
		{
			// cancelFlight(flightDB);
			break;
		}
		case '3':
		{
			cout << "Return to Home." << endl;
			break;
		}
		case '4':
		{
			cout << "Return to Home." << endl;
			break;
		}
		case '5':
		{
			cout << "Return to Home." << endl;
			break;
		}
		case '6':
		{
			cout << "Return to Home." << endl;
			return 0;
		}
		}
	}
}