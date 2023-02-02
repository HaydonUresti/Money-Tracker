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

// -----------------------IMPORTANT!!!-----------------------
// In the line below, enter the path to the directory where money_tracker.exe is stored
const char *pathToProgram = "C:/Users/hdure/OneDrive/Documents/School/Winter_2023/Applied_Programming/Sprint2/Money-Tracker";
// Enter the same path below that you entered above, but add /accountDir to the end
const char *pathToAccountDir = "C:/Users/hdure/OneDrive/Documents/School/Winter_2023/Applied_Programming/Sprint2/Money-Tracker/accountDir";

// TCHAR MSpathToAccount = "C:/Users/hdure/OneDrive/Documents/School/Winter_2023/Applied_Programming/Sprint2/Money-Tracker/accountDir";

// const string pathToAccountDir = "C:/Users/hdure/OneDrive/Documents/School/Winter_2023/Applied_Programming/Sprint2/Money-Tracker/accountDir";
// For the class aspect, have the abject be the file the user chooses

class Account
{
public:
    string accountName;
    int ballance;

    Account(string name, int currentBallance)
    {
        accountName = name;
        ballance = currentBallance;
    }

    void displayInfo()
    {
        cout << "Account Name: " << accountName << endl;
        cout << "Balance: " << accountName << endl;
    }
};

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

// Creates a new a new txt file representing an account for a user
// Parameters: nameOfAccount: The name of the account to be created
//             balanceOfAccount: The starting ballance of the account
// Returns: None
void creatNewAccount()
{

    string accountName;
    string accountBalance;
    // string path(pathToAccountDir);

    cout << "What would you like to name your new account? (do not enter any file extensions): \n"
         << endl;
    cin >> accountName;
    cout << "What is the begining balance of your new account? (do not enter a $): \n"
         << endl;
    cin >> accountBalance;

    // Add to the file then close it
    ofstream newFile("./accountDir/" + accountName + ".txt");
    newFile << "AccountName-" + accountName + "\n\n";
    newFile << "Balance:" + accountBalance;
    newFile.close();
}

// A function that reads from a selected file
void readFromFile(string filePath)
{

    cout << filePath;
    map<string, string> configuration;
    ifstream fin(filePath);
    string line;

    // Change the current working directory to the one containing all the account files
    _chdir(pathToAccountDir);

    while (getline(fin, line))
    {
        cout << "Loop is working \n"
             << endl;
        string key;
        string value;
        stringstream ss(line);
        getline(ss, key, ':');
        ss >> ws;

        configuration[key] = value;
    }

    cout << "The current ballance of " << configuration["AccountName"] << "is " << configuration["Balance"] << endl;

    // Change the working directory back to the previous directory
    _chdir(pathToProgram);
}

int main()
{
    createMainFolder();

    Account Account1("Main Account", 100);

    cout
        << "Hi! Welcome to money tracker" << endl;

    bool run = true;
    int user_choice = 0;

    while (run != false)
    {
        cout << "Please pick an option from those bellow: \n"
             << endl;
        cout << "Create a new account: 1 " << endl;
        cout << "View a current account: 2 " << endl;
        cout << "Delete an account: 3 " << endl;
        cout << "Exit the program: 4 " << endl;

        cout << "------------------ " << endl;
        cin >> user_choice;

        if (user_choice == 1)
        {

            cout << "Choice is 1\n"
                 << endl;

            creatNewAccount();
        }
        else if (user_choice == 2)
        {
            cout << "Choice is 2\n"
                 << endl;
            char accountName[20];
            int status;
            cout << "Which account would you like to view? (MAKE SURE to add .txt to the end of the file name)\n"
                 << endl;
            cin >> accountName;

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

                    if (counter == 4)
                    {
                        cout << "\n The current balance of your " << accountName << " account is $"
                             << curBalance << "\n"
                             << endl;
                    }
                }

                file.close();
            }
            _chdir(pathToProgram);
        }

        else if (user_choice == 3)
        {
            cout << "Choice is 3\n"
                 << endl;
            deleteAccount();
        }
        else if (user_choice == 4)
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