#pragma once
#include <iostream>

class Sql
{
public:
	void mySqlConnect();
	bool checkAccountExists(int acc);
	bool checkBalance(int acc, int amount);
	void sqladdAcc(std::string name,std::string address, std::string pasW, int acc, int bal);
	void sqlDeleteAcc(int acc);
	void sqlCheckAcc(std::string name, int acc);
	void sqlEditAcc(std::string name, std::string address, int acc, int choice);
	void sqlCheckHistory();
	void sqlTransfer(int acc, int accT, int amount);
	void sqlWithdrawal(int acc, int amount);
	void sqlDeposit(int acc, int amount);

	void sqlAddEmployee();
	void sqlDeleteEmployee();
	void sqlCheckEmployee();
};

