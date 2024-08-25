#pragma once
#include "Bank_Account.h"
#include <iostream>


void staff() {
	Bank_Account bank;
	system("CLS");

	int choice = 0;

	while (choice != 9) {
		std::cout << "Welcome STAFF \n";
		std::cout << "Choose the following please \n";
		std::cout << "Press 1 to add account \n";
		std::cout << "Press 2 to delete account \n";
		std::cout << "Press 3 to check an account \n";
		std::cout << "Press 4 to edit account \n";
		std::cout << "Press 5 to see transaction history \n";
		std::cout << "Press 6 to transfer \n";
		std::cout << "Press 7 to withdraw \n";
		std::cout << "Press 8 to deposit \n";
		std::cout << "Press 9 to exit \n";
		std::cin >> choice;

		switch (choice){
		case 1: bank.addAcc();
		case 2: bank.deleteAcc();
		case 3: bank.checkAcc();// Specify user whose account to check
		case 4:	bank.editAcc();// specify user whose account to edit
		case 5: bank.checkHistory();// specify user whose transaction history to show
		case 6: bank.transfer();// select user acc for transfer, user whose money will be going to, then amount;
		case 7: bank.withdrawal();// select account number for withdrawal, how much, check its not over balance
		case 8: bank.deposit();// select account for deposit, then ammount;
		case 9: exit(0);
		default: std::cout << "Please select from 1 to 5 \n"; break;
		}
	}
}