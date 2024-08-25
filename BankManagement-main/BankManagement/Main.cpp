#include <iostream>
#include "Headers/admin.h"
#include "Headers/Customer.h"
#include "Headers/Staff.h"
#include "Headers/Mysql.h"
#include "Headers/main.h"


int main() {
	Sql sql;
	
	sql.mySqlConnect();
	mainMenu();

	system("pause");
	return 0;
}

void mainMenu() {
	int choice = 0;

	while (choice != 4) {
		std::cout << "You want to login as: \t\t\t\t\t\t \n";		// setup login system instead with user permissions
		std::cout << "1 - Admin \n";
		std::cout << "2 - Staff \n";
		std::cout << "3 - Customer \n";
		std::cout << "4 - to_Exit \n";

		std::cin >> choice;
		switch (choice) {
		case 1:	admin(); break;
		case 2: staff();
		case 3: customer(); break;
		case 4: exit(0);
		default: std::cout << "Please enter a number 1 through 4 ";
		}
	}
}