#pragma once
#include "Bank_Account.h"

void admin() {
	system("CLS");
	Bank_Account bank;

	int choice = 0;
	
	while (choice != 9) {

		std::cout << "Welcome Manager \n";
		std::cout << "Choose the following please \n";
		std::cout << "Press 1 to add account \n";
		std::cout << "Press 2 to delete account \n";
		std::cout << "Press 3 to check an account \n";
		std::cout << "Press 4 to edit account \n";
		std::cout << "Press 5 to check transaction history \n";
		std::cout << "Press 6 to add employees \n";				/// maybe add password check for manager only functions
		std::cout << "Press 7 to delete employees \n";
		std::cout << "Press 8 to check employee record \n";
		std::cout << "Press 9 to exit \n";
		std::cin >> choice;

		switch (choice) {
		case 1: bank.addAcc();
		case 2: bank.deleteAcc();
		case 3: bank.checkAcc();
			// specify user to pull up account
			// find data and return using mysql
		case 4: bank.editAcc(); // specify user whose data to edit 
		case 5: bank.checkHistory(); // specify user to check their transaction history
		case 6: bank.addEmployee(); // add a staff member;
		case 7: bank.deleteEmployee(); // delete a staff member;
		case 8: bank.checkEmployee(); // check employee record, name, employee number, date started, pay ect;
		case 9: exit(0);
		default:
			std::cout << "Please select a number between 1 to 5 \n";
		}

	}
}