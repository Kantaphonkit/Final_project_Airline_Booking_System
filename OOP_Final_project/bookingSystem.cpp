#include <iostream>
#include "sqlite3.h"
#include "flightDatabase.h"
#include "bookingSystem.h"

using namespace std;

void searchByFlightID(string& flightID);
void searchBydepartureTime(string& flightTime);
void searchByTerminalStation(string& origin, string& destination);

int bookingSystem(flightDatabase& flightDB) {

	char option = '0';
	string flightId, origin, destination, flightTime;

	while (1) {

		if (option == '0') {
			flightDB.showAllFlights();
		} else if(option == '1') {
			flightDB.queryByFlightID(flightId);
		}
		else if (option == '2') {
			flightDB.queryByDepartureTime(flightTime);
		}
		else if (option == '3') {
			flightDB.queryByRoute(origin, destination);
		}

		cout << "---------------- " << "This is booking page" << " ----------------" << endl;
		cout << "Choose your option below:" << endl;
		cout << "0. Reset query" << endl;
		cout << "1. Search a flight by flight ID" << endl;
		cout << "2. Search a flight by depaparture time" << endl;
		cout << "3. Search a flight by terminal station" << endl;
		cout << "4. Book a flight" << endl;
		cout << "5. Cancel a flight" << endl;
		cout << "6. Return to Home page" << endl;
		cout << "Enter your option: ";
		cin >> option;
		switch (option) {
		case'0':
		{
			break;
		}
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

void searchByFlightID(string& flightID) {

	cout << "Enter flight ID: ";
	cin >> flightID;

}

void searchBydepartureTime(string& flightTime) {

	
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush \n
	std::cout << "Enter flight time (YYYY-MM-DD HH:MM): ";
	std::getline(std::cin, flightTime);

}


void searchByTerminalStation(string& origin, string& destination) {

	cout << "Enter origin: ";
	cin >> origin;
	cout << "Enter destination: ";
	cin >> destination;

}