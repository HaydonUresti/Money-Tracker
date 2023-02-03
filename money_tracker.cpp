#include <iostream>
using namespace std;
#include <sys/stat.h>
#include <direct.h>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <map>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
using std::vector;

// -----------------------IMPORTANT!!!-----------------------
// In the line below, enter the path to the directory where money_tracker.exe is stored
const char *pathToProgram = "C:/Users/hdure/OneDrive/Documents/School/Winter_2023/Applied_Programming/Sprint2/Money-Tracker";
// Enter the same path below that you entered above, but add /accountDir to the end
const char *pathToAccountDir = "C:/Users/hdure/OneDrive/Documents/School/Winter_2023/Applied_Programming/Sprint2/Money-Tracker/accountDir";

// TCHAR MSpathToAccount = "C:/Users/hdure/OneDrive/Documents/School/Winter_2023/Applied_Programming/Sprint2/Money-Tracker/accountDir";

// const string pathToAccountDir = "C:/Users/hdure/OneDrive/Documents/School/Winter_2023/Applied_Programming/Sprint2/Money-Tracker/accountDir";
// For the class aspect, have the abject be the file the user chooses

// class Account
// {
// public:
//     string accountName;
//     int ballance;

//     Account(string name, int currentBallance)
//     {
//         accountName = name;
//         ballance = currentBallance;
//     }

//     void displayInfo()
//     {
//         cout << "Account Name: " << accountName << endl;
//         cout << "Balance: " << accountName << endl;
//     }
// };

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

void deleteAccount()
{
    string dirName = "./accountDir/";
    char accountName[20];
    int status;
    cout << "Which account would you like to delete? (MAKE SURE to add .txt to the end of the file name)\n"
         << endl;
    cin >> accountName;

    // Change the current working directory to the one containing all the account files
    _chdir(pathToAccountDir);

    // Delete the chosen account
    if (remove(accountName))
    {
        cout << "Please try again with a valid account.";
    }

    // Change the working directory back to the previous directory
    _chdir(pathToProgram);
}

// A function that reads from a selected file
//
string readBalance(char *accountName)
{
    // readFromFile(accountName);
    _chdir(pathToAccountDir);
    std::ifstream file(accountName);

    if (file.is_open())
    {
        std::string line;

        string curBalance;

        int counter = 1;

        while (std::getline(file, line))
        {
            counter += 1;

            auto npos = line.find(":");
            curBalance = line.substr(npos + 1);

            return curBalance;
            // if (counter == 4)
            // {
            //     return curBalance;
            // }
        }

        file.close();
    }
    _chdir(pathToProgram);
}

double getAdditionToAccount(string readBalance, double addend)
{
    double balance = stod(readBalance);

    return balance + addend;
}

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

std::vector<std::string> getAccountVector()
{
    string nameOfFile;
    ifstream file;

    file.open("./accountDir/accountFile.txt");
    vector<string> availableAccounts;
    string line;

    while (!file.eof())
    {
        getline(file, line);
        availableAccounts.push_back(line);
    }
    file.close();

    return availableAccounts;
}

int main()
{
    createMainFolder();

    cout
        << "Hi! Welcome to money tracker" << endl;

    bool run = true;
    int user_choice = 0;

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

            cout << "Choice is 1\n"
                 << endl;

            creatNewAccount();
        }
        else if (user_choice == 2)
        {
            for (auto curLine : getAccountVector())
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
            char accountName[20];
            double ammount;
            cout << "Choice is 3\n"
                 << endl;
            cout << "Which account would you like to take from? (Please be sure to enter '.txt' to the end of the name)\n"
                 << endl;
            cin >> accountName;
            cout << "There is currently $" << readBalance(accountName) << " in your " << accountName
                 << " account. How much would you like to subtract? \n (Enter the ammount with TWO decimal points, Ex 1.00) \n"
                 << endl;
            cin >> ammount;
            double addition = getAdditionToAccount(readBalance(accountName), ammount);

            writeToAccount(accountName, addition);
        }
        else if (user_choice == 4)
        {
            char accountName[20];
            double subAmmount;
            cout << "Choice is 3\n"
                 << endl;
            cout << "Which account would you like to add to? (Please be sure to enter '.txt' to the end of the name)\n"
                 << endl;
            cin >> accountName;
            cout << "There is currently $" << readBalance(accountName) << " in your " << accountName
                 << " account. How much would you like to add? \n (Enter the ammount with TWO decimal points, Ex 1.00) \n"
                 << endl;
            cin >> subAmmount;
            double addition = getSubtractionToAccount(readBalance(accountName), subAmmount);

            writeToAccount(accountName, addition);
        }
        else if (user_choice == 5)
        {
            deleteAccount();
        }
        else if (user_choice == 6)
        {
            cout << "Thank you for using Money Tracker!";
            run = false;
        }
        else
        {
            cout << "Please enter a valid option. \n"
                 << endl;

            cin.clear();
            cin.ignore(123, '\n');
        }

        system("pause>0");
    }
}

// Lets not immedietely worry about haveing account history
// just account ballance