#include <iostream>
using namespace std;
#include <sys/stat.h>
#include <direct.h>
#include <fstream>
#include <stdio.h>
#include <tchar.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "accountVector.h"
using std::vector;

// -----------------------IMPORTANT!!!-----------------------
// In the line below, enter the path to the directory where money_tracker.exe is stored
const char *pathToProgram = ;

// Enter the same path below that you entered above, but add /accountDir to the end

const char *pathToAccountDir = "/accountDir";

// A function that creates the directory accountsDir if it does not exist
// Parameters: None
// Returns: None
void createMainFolder()
{
    struct stat sb;

    if (stat(pathToAccountDir, &sb) == 0)
        return;
    else
        mkdir(pathToAccountDir);
    cout
        << "The directory is created";

    // change the current directory to the newly created one and create a file to store the current accounts.
    _chdir(pathToAccountDir);
    ofstream accountFile("accountFile.txt");
    _chdir(pathToProgram);
}

// A function that deletes a deleted account within accountFile.txt
// Parameters: string toDelete - the account to be deleted
// Returns: None
void reWriteToAccountFile(string toDelete)
{
    ofstream accountFile;
    AccountVector curVector;
    accountFile.open("./accountDir/accountFile.txt", std::ofstream::out | std::ofstream::trunc);
    for (auto curLine : curVector.printVector())
    {
        if (curLine != toDelete)
        {

            accountFile << curLine << endl;
        }
    }
    accountFile.close();
}

// A function that deletes an account selected by the user within the function
// Parameters: None
// Return: None
void deleteAccount()
{
    string dirName = "./accountDir/";
    char accountName[20];
    int status;
    cout << "Which account would you like to delete? (MAKE SURE to add .txt to the end of the file name)\n"
         << endl;
    cin >> accountName;

    // Change the current working directory to the one containing all the account files. This is done so the program can access the files it creates. 
    // The user must have updated the value of the pathToProgram variable 
    _chdir(pathToAccountDir);

    // Delete the chosen account
    if (remove(accountName))
    {
        cout << "Please try again with a valid account.";
    }

    // Change the working directory back to the previous directory
    _chdir(pathToProgram);
    reWriteToAccountFile(accountName);
}

// A function that reads from a selected file
// Parameters: char *accountName - the path to the account to be read
// Returns: None
string readBalance(char *accountName)
{
    // Change directory to the one containing the accountDir
    _chdir(pathToAccountDir);

    // open the chosen account
    std::ifstream file(accountName);
    if (file.is_open())
    {
        std::string line;

        string curBalance;

        // Read from the account file
        while (std::getline(file, line))
        {
            auto npos = line.find(":");
            curBalance = line.substr(npos + 1);
            return curBalance;
        }

        file.close();
    }
    _chdir(pathToProgram);
}

// A funtion that adds a given amount to the saved ammmount in the account
// Parameters: string readBalance - the current balance saved in the account
//             double addend - the amount to be added to the account
// Returns: The new balance after addition
double getAdditionToAccount(string readBalance, double addend)
{
    double balance = stod(readBalance);

    return balance + addend;
}

// A funtion that subtracts a given amount from the saved ammmount in the account
// Parameters: string readBalance - the current balance saved in the account
//             double subtrahend - the amount to be taken from the account
// Returns: The new balance after subtraction
double getSubtractionToAccount(string readBalance, double subtrahend)
{
    double balance = stod(readBalance);

    return balance - subtrahend;
}

// A function that writes to the chosen account.
// Parameters: char *account: The path to the file to be written to
//             string data: The data to be written to the account.
// Returns: None
void writeToAccount(char *account, double data)
{
    // Delete current contents of the file
    ofstream curFile;

    // Format the number to only have 2 decimal places
    float fixedData = ceil(data * 100.0) / 100.0;

    // Write to file
    curFile.open(account, std::ofstream::out | std::ofstream::trunc);
    curFile << "Balance:";
    curFile << fixedData;
    curFile.close();
}

// Creates a new a new txt file representing an account for a user
// Parameters: nameOfAccount: The name of the account to be created
//             balanceOfAccount: The starting ballance of the account
// Returns: None
void creatNewAccount()
{

    string accountName;
    string accountBalance;
    ofstream foutput;
    ifstream finput;

    cout << "What would you like to name your new account? (do not enter any file extensions): \n"
         << endl;
    cin >> accountName;
    cout << "What is the begining balance of your new account? (do not enter a $): \n"
         << endl;
    cin >> accountBalance;

    // Add to the file then close it
    ofstream newFile("./accountDir/" + accountName + ".txt");

    newFile << "Balance:" + accountBalance;
    newFile.close();

    // Open the file in append mode so no data is deleted
    finput.open("./accountDir/accountFile.txt");
    foutput.open("./accountDir/accountFile.txt", ios::app);
    foutput << accountName + ".txt"
            << endl;

    finput.close();
    foutput.close();
}

// Main function of the program
int main()
{
    // Create the accountDir folder if it does not exist
    createMainFolder();

    cout
        << "Hi! Welcome to money tracker" << endl;

    bool run = true;
    int user_choice = 0;

    // The main loop
    while (run != false)
    {
        cout << "\n ------------------ " << endl;
        cout << "Please pick an option from those bellow: \n"
             << endl;
        cout << "Create a new account: 1 " << endl;
        cout << "View a current account: 2 " << endl;
        cout << "Add to account: 3 " << endl;
        cout << "Withdraw from account: 4 " << endl;
        cout << "Delete an account: 5 " << endl;
        cout << "Exit the program: 6 " << endl;

        cout << "------------------ " << endl;
        cin >> user_choice;
        cout << "------------------ " << endl;

        if (user_choice == 1)
        {
            creatNewAccount();
        }
        else if (user_choice == 2)
        {
            AccountVector curVector;
            for (auto curLine : curVector.printVector())
            {
                cout << curLine << endl;
            }

            char nameOfAccount[20];
            int status;
            cout << "Which account would you like to view? (MAKE SURE to add .txt to the end of the file name)\n"
                 << endl;
            cin >> nameOfAccount;

            // string balanceOfAccount = readBalance(nameOfAccount);

            cout << "\n The current balance of your " << nameOfAccount << " account is $"
                 << readBalance(nameOfAccount) << "\n"
                 << endl;
        }

        else if (user_choice == 3)
        {
            // Create a vector containing the current accounts, then dsiplay them
            AccountVector curVector;
            for (auto curLine : curVector.printVector())
            {
                cout << curLine << endl;
            }

            char accountName[20];
            double amount;

            cout << "Which account would you like to add to? (Please be sure to enter '.txt' to the end of the name)\n"
                 << endl;
            cin >> accountName;
            cout << "There is currently $" << readBalance(accountName) << " in your " << accountName
                 << " account. How much would you like to add? \n (Enter the amount with TWO decimal points, Ex 1.00) \n"
                 << endl;
            cin >> amount;
            double addition = getAdditionToAccount(readBalance(accountName), amount);

            writeToAccount(accountName, addition);
        }
        else if (user_choice == 4)
        {
            // Create a vector containing the current accounts, then dsiplay them
            AccountVector curVector;
            for (auto curLine : curVector.printVector())
            {
                cout << curLine << endl;
            }

            char accountName[20];
            double subamount;

            cout << "Which account would you like to withdraw from? (Please be sure to enter '.txt' to the end of the name)\n"
                 << endl;
            cin >> accountName;
            cout << "There is currently $" << readBalance(accountName) << " in your " << accountName
                 << " account. How much would you like to withdraw? \n (Enter the amount with TWO decimal points, Ex 1.00) \n"
                 << endl;
            cin >> subamount;
            double subtraction = getSubtractionToAccount(readBalance(accountName), subamount);

            writeToAccount(accountName, subtraction);
        }
        else if (user_choice == 5)
        {
            // Create a vector containing the current accounts, then dsiplay them
            AccountVector curVector;
            for (auto curLine : curVector.printVector())
            {
                cout << curLine << endl;
            }

            deleteAccount();
        }
        else if (user_choice == 6)
        {
            // exit the program
            cout << "Thank you for using Money Tracker!";
            run = false;
        }
        else
        {
            // Handle invalid input to the main menu
            cout << "Please enter a valid option. \n"
                 << endl;

            cin.clear();
            cin.ignore(123, '\n');
        }

        system("pause>0");
    }
}
