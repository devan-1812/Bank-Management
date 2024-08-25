#pragma once
#include "Bank_Account.h"

void customer() {
	system("CLS");
	Bank_Account bank;

	int choice = 0;
	while (choice != 3) {
		std::cout << "Welcome CUSTOMER \n";
		std::cout << "Choose the following please \n";
		std::cout << "Press 1 to see account details \n";
		std::cout << "Press 2 to see transaction history \n";
		std::cout << "Press 3 for transfer \n";
		std::cout << "Press 4 to exit \n";
		std::cin >> choice;

		switch (choice) {
		case 1: bank.checkAcc();// return account details of account
		case 2: bank.checkHistory();// see transaction history of own account
		case 4: bank.transfer(); //  transfer
		case 3: exit(0);
		}

	}
}