#include <iostream>
using namespace std;

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

void creatNewAccount(string name, int balance)
{
    Account name
}

int main()
{

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
            ;
        }
        else if (user_choice == 2)
        {
            cout << "Choice is 2\n"
                 << endl;
            Account1.displayInfo();
        }
        else if (user_choice == 3)
        {
            cout << "Choice is 3\n"
                 << endl;
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
