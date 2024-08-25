#include "Headers/Bank_Account.h"
#include "Headers/Mysql.h"
//#include "Mysql.cpp"
#include <iostream>
#include <string>
#include <vector>
//#include <bcrypt.h>
//#include <Windows.h>


Sql sql;

void Bank_Account::addAcc() {
    std::string name, address, pasW;
    int acc, bal;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Address: ";
    std::getline(std::cin, address);

    std::cout << "Enter Account Number: ";
    while (!(std::cin >> acc)) {
        std::cout << "Invalid input. Please enter an integer value: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter Password: ";
    std::cin >> pasW;
    // Encrypt or hash the password before storing it

    std::cout << "Enter Balance: ";
    while (!(std::cin >> bal)) {
        std::cout << "Invalid input. Please enter an integer value: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Output the entered values for verification
    std::cout << "Name: " << name << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Password : HIDDEN "<< std::endl;
    std::cout << "Account Number: " << acc << std::endl;
    std::cout << "Balance: " << bal << std::endl;

    //std::cout << "Are you sure these are the values you would like to be entered ? ";
    // give chance to redo;

    sql.sqladdAcc(name, address, pasW, acc, bal);
    
}
// Hash password with bcrypt, return to store into database, library errors
//std::vector<unsigned char> Bank_Account::hashPassword(const std::string& password)
//{
//    // Generate a salt
//    std::vector<unsigned char> salt(16);
//    if (BCryptGenRandom(NULL, salt.data(), salt.size(), BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0)
//    {
//        // Hash the password with the salt
//        std::vector<unsigned char> hash(32);
//        if (BCryptHashData(NULL, salt.data(), salt.size(), const_cast<LPBYTE>(reinterpret_cast<const BYTE*>(password.data())), password.size(), hash.data(), hash.size()) == 0)
//        {
//            // Concatenate the salt and hash
//            std::vector<unsigned char> result(salt.size() + hash.size());
//            std::copy(salt.begin(), salt.end(), result.begin());
//            std::copy(hash.begin(), hash.end(), result.begin() + salt.size());
//            return result;
//        }
//    }
//    return std::vector<unsigned char>();
//}

//bool verifyPassword(const std::string& password, const std::vector<unsigned char>& hash)
//{
//    if (hash.size() == 48)
//    {
//        // Extract the salt and hash from the stored hash value
//        std::vector<unsigned char> salt(hash.begin(), hash.begin() + 16);
//        std::vector<unsigned char> storedHash(hash.begin() + 16, hash.end());
//
//        // Hash the password with the salt
//        std::vector<unsigned char> computedHash(storedHash.size());
//        if (BCryptHashData(NULL, salt.data(), salt.size(), const_cast<LPBYTE>(reinterpret_cast<const BYTE*>(password.data())), password.size(), computedHash.data(), computedHash.size()) == 0)
//        {
//            // Compare the computed hash to the stored hash
//            return std::equal(computedHash.begin(), computedHash.end(), storedHash.begin());
//        }
//    }
//    return false;
//}



void Bank_Account::deleteAcc() {
    int acc = 0;
    std::cout << "Enter Account Number \n";
    std::cin >> acc;
    std::cout << "Are u sure you would like to delete this acc? " << acc << "\n";

    sql.sqlDeleteAcc(acc);

}

    /// <summary>
    /// check acc can take in a number 1, 2, 3 says if its customer or not
    /// if customer it passes in the customers acc..
    /// </summary> 
void Bank_Account::checkAcc() {
    std::string name;
    int acc = 0;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "please Enter Customers Name \n";
    std::getline(std::cin, name);

    std::cout << "Please Enter Customers Account Number \n";
    std::cin >> acc;

    sql.sqlCheckAcc(name, acc);
};
void Bank_Account::editAcc() {
    std::string name, address;
    int acc = 0, choice = 0;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (choice != 1 && choice != 2) {
        std::cout << "Would you like to update  \n";
        std::cout << "1 - Name \n";
        std::cout << "2 - Address \n";

        std::cin >> choice;
        switch (choice)
        {
        case 1: {
            std::cout << "Please Enter Customers New Name \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, name);
            break;
        }
        case 2: {
            std::cout << "Please Enter Customers New Address \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, address);
            break;
        }
        default: std::cout << "Select an appropriate number \n";
        }
    }
    

    std::cout << "Please Enter Customers Account Number \n";
    std::cin >> acc;

    sql.sqlEditAcc(name, address, acc, choice);
};
void Bank_Account::checkHistory() {
    std::string name;
    int acc = 0;
    std::cout << "please Enter Customers Name \n";
    std::getline(std::cin, name);

    std::cout << "Please Enter Customers Account Number \n";
    std::cin >> acc;
};
void Bank_Account::transfer() {
    int acc = 0, accT = 0, amount = 0;

    std::cout << "Please Enter Customer Account Number: \n";
    std::cin >> acc;

    // Check if the account exists
    if (!sql.checkAccountExists(acc)) {
        std::cout << "Error: Account not found \n";
        return;
    }

    std::cout << "Please Enter Account Number to Transfer To: \n";
    std::cin >> accT;

    // Check if the transfer account exists
    if (!sql.checkAccountExists(accT)) {
        std::cout << "Error: Transfer account not found \n";
        return;
    }

    std::cout << "Please Enter Transfer Amount: \n";
    std::cin >> amount;

    // Check if the transfer amount is valid
    if (amount <= 0) {
        std::cout << "Error: Invalid transfer amount \n";
        return;
    }

    // Check if the balance is sufficient
    if (!sql.checkBalance(acc, amount)) {
        std::cout << "Error: Insufficient balance \n";
        return;
    }

    // Perform the transfer
    sql.sqlTransfer(acc, accT, amount);
}
void Bank_Account::withdrawal() {
    int acc = 0, amount = 0;

    std::cout << "Please Enter Customer's Account Number: ";
    std::cin >> acc;

    if (!sql.checkAccountExists(acc)) {
        std::cout << "Error: Account not found.\n";
        return;
    }

    std::cout << "Please Enter Withdrawal Amount: ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "Error: Invalid withdrawal amount.\n";
        return;
    }

    sql.sqlWithdrawal(acc, amount);
}
void Bank_Account::deposit() {
    int acc = 0, amount = 0;

    std::cout << "Please Enter Customers Account Number \n";
    std::cin >> acc;

    if (!sql.checkAccountExists(acc)) {
        std::cout << "Error: Account not found.\n";
        return;
    }

    std::cout << "Please Enter Deposit Amount \n";
    std::cin >> amount;

    sql.sqlDeposit(acc, amount);
}

void Bank_Account::addEmployee() {
    std::string name, address;
    int empNo;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Address: ";
    std::getline(std::cin, address);
    std::cout << "Enter Employee Number ";      // ideally done auto
    std::cin >> empNo;
};
void Bank_Account::deleteEmployee() {
    std::string name;
    int empNo;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Employee Number ";      
    std::cin >> empNo;

    // delete from database
};
void Bank_Account::checkEmployee() {
    std::string name;
    int empNo;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Employee Number ";      
    std::cin >> empNo;

    // return employee info from database;
};