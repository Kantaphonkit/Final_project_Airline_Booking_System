#include <iostream>
#include "sqlite3.h"
#include "Database.h"

using namespace std;

int main() {

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
				cout << "option 1 was called" << endl;
				break;
			}
			case '2':
			{
				cout << "option 2 was called" << endl;
				break;
			}
			case '3':
				cout << "Exiting the program." << endl;
				return 0;
		}
    }

    return 0;
}
