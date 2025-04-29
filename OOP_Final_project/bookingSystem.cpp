#include <iostream>
#include "sqlite3.h"
#include "flightDatabase.h"
#include "bookingSystem.h"

using namespace std;

void searchByFlightID(string& flightID);
void searchBydepartureTime(string& flightTime);
void searchByTerminalStation(string& origin, string& destination);

void booking(flightDatabase& flightDB, flightDatabase& bookingDB);
void cancel(flightDatabase& flightDB, flightDatabase& bookingDB);

int bookingSystem(flightDatabase& flightDB, flightDatabase& bookingDB) {

	char option = '0';
	string flightId, origin, destination, flightTime;

	while (1) {

		if (option == '0') {
			flightDB.showAllFlights();
		} 
		else if (option == '1') {
			bookingDB.showAllFlights();
		}
		else if(option == '2') {
			flightDB.queryByFlightID(flightId);
		}
		else if (option == '3') {
			flightDB.queryByDepartureTime(flightTime);
		}
		else if (option == '4') {
			flightDB.queryByRoute(origin, destination);
		}

		cout << "---------------- " << "This is booking page" << " ----------------" << endl;
		cout << "Choose your option below:" << endl;
		cout << "0. Reset query" << endl;
		cout << "1. show booked flight" << endl;
		cout << "2. Search a flight by flight ID" << endl;
		cout << "3. Search a flight by depaparture time" << endl;
		cout << "4. Search a flight by terminal station" << endl;
		cout << "5. Book a flight" << endl;
		cout << "6. Cancel a flight" << endl;
		cout << "7. Return to Home page" << endl;
		cout << "Enter your option: ";
		cin >> option;

		switch (option) {
			case'0':
			{
				break;
			}
			case'1':
			{
				break;
			}
			case '2':
			{
				searchByFlightID(flightId);
				break;
			}
			case '3':
			{
				searchBydepartureTime(flightTime);
				break;
			}
			case '4':
			{
				searchByTerminalStation(origin, destination);
				break;
			}
			case '5':
			{
				booking(flightDB, bookingDB);
				break;
			}
			case '6':
			{
				cancel(flightDB, bookingDB);
				break;
			}
			case '7':
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

void booking(flightDatabase& flightDB, flightDatabase& bookingDB) {

	string flightID;
	int seat;

	cout << "Enter flight ID: ";
	cin >> flightID;
	cout << "Enter number of seats: ";
	cin >> seat;

	if (!flightDatabase::modifyTicket(flightDB, bookingDB, flightID, 0, seat))
		std::cout << "Booking failed due to invalid flightID or invalid seat.\n";
	else {
		cout << "Booking successful.\n";
	}

}

void cancel(flightDatabase& flightDB, flightDatabase& bookingDB) {

	string flightID;
	int seat;

	bookingDB.showAllFlights();

	cout << "Enter flight ID: ";
	cin >> flightID;
	cout << "Enter number of seats: ";
	cin >> seat;
	if (!flightDatabase::modifyTicket(flightDB, bookingDB, flightID, 1, seat))
		std::cout << "Cancel failed due to invalid flightID or invalid seat.\n";
	else {
		cout << "Cancel successful.\n";
	}

}