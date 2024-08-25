#pragma once
#include <vector>
#include <string>
class Bank_Account
{
public:
	void addAcc();
	void deleteAcc();
	void checkAcc();
	void editAcc();
	void checkHistory();
	void transfer();
	void withdrawal();
	void deposit();
	std::vector<unsigned char> hashPassword(const std::string& password);

	//Manager privlages
	void addEmployee();
	void deleteEmployee();
	void checkEmployee();
};

