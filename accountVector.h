#include <iostream>
using namespace std;
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>
using std::vector;

// A class that creats and returns a vector of available accounts.
class AccountVector
{
public:
    string path = "accountFile.txt";
    vector<string> availableAccounts;

    // The constructor of the class. Creates a vector object containing the names of
    // the currently available file accounts.
    AccountVector()
    {
        string nameOfFile;
        ifstream file;

        file.open("./accountDir/accountFile.txt");

        string line;

        while (!file.eof())
        {
            getline(file, line);
            availableAccounts.push_back(line);
        }
        file.close();
    }

    // A method that returns the vector containing the acitve accounts.
    // Parameters: None
    // Returns: Vector availableAccounts -> a vector of the available accounts
    std::vector<std::string> printVector()
    {
        return availableAccounts;
    }
};