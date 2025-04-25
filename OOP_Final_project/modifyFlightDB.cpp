#include <iostream>
#include "sqlite3.h"
#include "flightDatabase.h"
#include "modifyFlightDB.h"

using namespace std;

int insertFlight(flightDatabase& flightDB);
int deleteFlight(flightDatabase& flightDB);

int modifyFlightDB(flightDatabase& flightDB) {

	char option;

	while (1) {

		flightDB.showAllFlights();

		cout << "---------------- " << "This is modify page" << " ----------------" << endl;
		cout << "Choose your option below:" << endl;
		cout << "1. Insert flgiht data" << endl;
		cout << "2. Delete flgiht data" << endl;
		cout << "3. Return to Home page" << endl;
		cout << "Enter your option: ";
		cin >> option;
		switch (option) {
		case '1':
		{
			insertFlight(flightDB);
			break;
		}
		case '2':
		{
			deleteFlight(flightDB);
			break;
		}
		case '3':
			cout << "Return to Home." << endl;
			return 0;
		}
	}
}


int insertFlight(flightDatabase& flightDB) {

	string flightId, origin, destination, flightTime;
	int ticket;

	cout << "Enter flight ID: ";
	cin >> flightId;
	cout << "Enter origin: ";
	cin >> origin;
	cout << "Enter destination: ";
	cin >> destination;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush \n
	std::cout << "Enter flight time (YYYY-MM-DD HH:MM): ";
	std::getline(std::cin, flightTime);
	cout << "Enter number of ticket : ";
	cin >> ticket;

	if (flightDB.insertFlight(flightId, origin, destination, flightTime, ticket)) {

		cout << "Flight inserted successfully." << endl;
		return 1;

	}
	else {

		cout << "Failed to insert flight." << endl;
		return 0;

	}
}

int deleteFlight(flightDatabase& flightDB) {

	string flightId;

	cout << "Enter flight ID to delete: ";
	cin >> flightId;

	if (flightDB.deleteFlight(flightId)) {

		cout << "Flight deleted successfully." << endl;
		return 1;

	}
	else {

		cout << "Failed to delete flight." << endl;
		return 0;

	}
}

