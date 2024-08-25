# BankManagement
BankManagement using c++ and mysql database

Bank Management Project

This is a simple command-line interface program for managing a bank's customer accounts. The program allows bank employees to add, delete, check, and edit customer accounts.
Features

    Add a new customer account
    Delete an existing customer account
    Check if a customer account exists and retrieve the customer's information
    Edit a customer's name or address

Requirements

This program was developed using C++ and requires a C++ compiler to run. The following tools were used to develop the program:

    Visual Studio Code (recommended)
    C++ extension for Visual Studio Code
    MySQL database

Usage

    Clone the repository to your local machine.
    Open the project in Visual Studio Code or your preferred IDE.
    Modify the "Mysql.h" file with your own MySQL database information.
    Compile the program using your C++ compiler.
    Run the program from the command line.

Database Schema

The program uses a MySQL database to store customer account information. The database schema is as follows:

sql

CREATE TABLE customers (
  id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(50) NOT NULL,
  address VARCHAR(100) NOT NULL,
  password VARCHAR(255) NOT NULL,
  account_number INT NOT NULL UNIQUE,
  balance INT NOT NULL
);
