#include <iostream>
#include <conio.h>
#include "Headers/Mysql.h"
#include "Headers/main.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

// insert your server here
const std::string server = "tcp://localhost:3306";
const std::string username = "root";
const std::string password = "";

sql::Driver* driver;
sql::Connection* con;
sql::Statement* stmt;
sql::PreparedStatement* pstmt;
sql::ResultSet* result;

void Sql::mySqlConnect() {

	try
	{
		driver = get_driver_instance();
		//for demonstration only. never save password in the code!
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
		system("pause");
		exit(1);
	}

	con->setSchema("bankmanagerdb");
}

//Name
//Address
//Account
//Balance

bool Sql::checkAccountExists(int acc) {
    pstmt = con->prepareStatement("SELECT * FROM accounts WHERE accountNo = ?");
    pstmt->setInt(1, acc);
    result = pstmt->executeQuery();

    bool exists = result->next();

    delete result;
    delete pstmt;

    return exists;
}

//drop table for testing purposes
void Sql::sqladdAcc(std::string name, std::string address, std::string hashed_pasW, int acc, int bal) {
    stmt = con->createStatement();
    /*stmt->execute("DROP TABLE IF EXISTS accounts");
    std::cout << "Finished dropping table (if existed)" << std::endl;*/
    stmt->execute("CREATE TABLE IF NOT EXISTS accounts (name VARCHAR(50), address VARCHAR(50), password VARCHAR(128), accountNo serial PRIMARY KEY, balance INTEGER);");
    std::cout << "Finished creating table" << std::endl;
    delete stmt;

    pstmt = con->prepareStatement("INSERT INTO accounts(name, address, password, accountNo, balance) VALUES(?,?,?,?,?)");
    pstmt->setString(1, name);
    pstmt->setString(2, address);
    pstmt->setString(3, hashed_pasW);
    pstmt->setInt(4, acc);
    pstmt->setInt(5, bal);
    pstmt->execute();
    std::cout << "Customer Account Added \n";
  
    system("pause");
    system("CLS");
    mainMenu();
}


//void sqldeleteAcc();
void Sql::sqlDeleteAcc(int acc) {
	//delete
	pstmt = con->prepareStatement("DELETE FROM accounts WHERE accountNo = ?");
	pstmt->setInt(1, acc);
	result = pstmt->executeQuery();
	printf("Row deleted\n");

	delete pstmt;
	delete con;
	delete result;
	system("pause");
	system("CLS");
	mainMenu();
}

void Sql::sqlCheckAcc(std::string name, int acc) {
	//select  
	pstmt = con->prepareStatement("Select name, address, accountNo, balance From accounts WHERE name = ? AND accountNo = ?;");
    pstmt->setString(1, name);
    pstmt->setInt(2, acc);
	result = pstmt->executeQuery();

    // Execute the query and check the result set
    result = pstmt->executeQuery();
    if (result->next()) {
        // Account was found, print the details
        std::cout << "Account found:\n";
        std::cout << "Name: " << result->getString("name") << "\n";
        std::cout << "Address: " << result->getString("address") << "\n";
        std::cout << "Account Number: " << result->getInt("accountNo") << "\n";
        std::cout << "Balance: " << result->getInt("balance") << "\n";
    }
    else {
        // Account not found
        std::cout << "Account not found\n";
    }

    // Clean up and go back to the main menu
    delete result;
    delete pstmt;
    system("pause");
    system("CLS");
    mainMenu();
}

bool Sql::checkBalance(int acc, int amount) {
    // Check if the account exists
    pstmt = con->prepareStatement("SELECT * FROM accounts WHERE accountNo = ?");
    pstmt->setInt(1, acc);
    result = pstmt->executeQuery();

    if (!result->next()) {
        // Account not found
        std::cout << "Error: Account not found\n";
        return false;
    }
    else {
        // Account found, check the balance
        int acct_balance = result->getInt("balance");
        if (acct_balance < amount) {
            // Insufficient balance
            std::cout << "Error: Insufficient balance\n";
            return false;
        }
        else {
            // Sufficient balance
            return true;
        }
    }

    // Clean up
    delete result;
    delete pstmt;
}


void Sql::sqlEditAcc(std::string name, std::string address, int acc, int choice) {
    // Check if the account exists
    pstmt = con->prepareStatement("SELECT * FROM accounts WHERE accountNo = ?");
    pstmt->setInt(1, acc);
    result = pstmt->executeQuery();

    if (!result->next()) {
        // Account not found
        std::cout << "Error: Account not found\n";
    }
    else {
        // Account found, update the appropriate column
        std::string column;
        std::string value;
        if (choice == 1) {
            column = "name";
            value = name;
        }
        else {
            column = "address";
            value = address;
        }

        // Update the row
        pstmt = con->prepareStatement("UPDATE accounts SET " + column + " = ? WHERE accountNo = ?");
        pstmt->setString(1, value);
        pstmt->setInt(2, acc);
        pstmt->executeQuery();

        std::cout << "Row updated\n";
    }

    // Clean up and go back to the main menu
    delete result;
    delete pstmt;
    delete con;
    system("pause");
    system("CLS");
    mainMenu();
}
//void Sql::sqlCheckHistory();
void Sql::sqlTransfer(int acc, int accT, int amount) {
    // Check if the source account exists and has enough funds
    pstmt = con->prepareStatement("SELECT balance FROM accounts WHERE accountNo = ?");
    pstmt->setInt(1, acc);
    result = pstmt->executeQuery();

    if (!result->next()) {
        // Account not found
        std::cout << "Error: Account not found\n";
    }
    else {
        int balance = result->getInt("balance");
        if (balance < amount) {
            // Insufficient funds
            std::cout << "Error: Insufficient funds\n";
        }
        else {
            // Update the balance of the source account
            int new_balance = balance - amount;
            pstmt = con->prepareStatement("UPDATE accounts SET balance = ? WHERE accountNo = ?");
            pstmt->setInt(1, new_balance);
            pstmt->setInt(2, acc);
            pstmt->executeUpdate();

            // Update the balance of the target account
            pstmt = con->prepareStatement("UPDATE accounts SET balance = balance + ? WHERE accountNo = ?");
            pstmt->setInt(1, amount);
            pstmt->setInt(2, accT);
            pstmt->executeUpdate();

            std::cout << "Transfer successful\n";
        }
    }

    // Clean up and go back to the main menu
    delete result;
    delete pstmt;
    delete con;
    system("pause");
    system("CLS");
    mainMenu();
}

void Sql::sqlWithdrawal(int acc, int amount) {
    // Check if the account has sufficient balance
    if (!checkBalance(acc, amount)) {
        std::cout << "Error: Insufficient balance\n";
        return;
    }

    // Deduct the amount from the account
    pstmt = con->prepareStatement("UPDATE accounts SET balance = balance - ? WHERE accountNo = ?");
    pstmt->setInt(1, amount);
    pstmt->setInt(2, acc);
    pstmt->executeQuery();

    std::cout << "Withdrawal successful\n";

    // Clean up and go back to the main menu
    delete pstmt;
    delete con;
    system("pause");
    system("CLS");
    mainMenu();
};
void Sql::sqlDeposit(int acc, int amount) {
    // Add the amount to the account balance
    pstmt = con->prepareStatement("UPDATE accounts SET balance = balance + ? WHERE accountNo = ?");
    pstmt->setInt(1, amount);
    pstmt->setInt(2, acc);
    pstmt->executeQuery();

    std::cout << "Deposit successful\n";

    // Clean up and go back to the main menu
    delete pstmt;
    delete con;
    system("pause");
    system("CLS");
    mainMenu();
}

//void Sql::sqlAddEmployee();
//void Sql::sqlDeleteEmployee();
//void Sql::sqlCheckEmployee();