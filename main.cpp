#include <iostream>
#include <vector>

#include "Bicycle.h"
#include "Member.h"
using namespace std;

int main() {
    const string password = "123456";
    string userinput;
    int attempts = 3;
    bool loginSuccessful = false;
    int option;

    vector<Member> members;

    vector<Bicycle> fleet = {
        {101, "City Bike", 5.00, true},
        {102, "Mountain Bike", 8.50, true},
        {103, "Electric Bike", 15.00, true},
        {104, "Tandem Bike", 12.00, true}
    };

    cout << "======================================" << endl;
    cout << "//                                  //" << endl;
    cout << "//       Bicycle Rental System      //" << endl;
    cout << "//                                  //" << endl;
    cout << "======================================" << endl << endl;

    for (int i = 1; i <= attempts; i++) {
        cout << "Please enter password: ";
        cin >> userinput;

        if (userinput == password) {
            cout << "Password correct! Enter program..." << endl;
            loginSuccessful = true;
            break;
        }
        else {
            cout << "Wrong password!" << endl;
            cout << "Attempts left: " << attempts - i << endl;
        }
    }

    if (loginSuccessful) {
        do {
            cout << endl;
            cout << "========== MENU ==========" << endl;
            cout << "1. Customer Management" << endl;
            cout << "2. Bicycle Rental" << endl;
            cout << "3. Schedule Management" << endl;
            cout << "4. Billing and report" << endl;
            cout << "5. Exit" << endl;
            cout << "===========================" << endl;
            cout << "Enter a number to proceed :";

            if (!(cin >> option)) {
                cout << "Invalid input! Please enter a number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            switch (option) {
            case 1:
                cout << "Entering Customer management system..." << endl;
                memberMenu(members);
                break;

            case 2:
                cout << "Bicycle Rental selected." << endl;
                    bikeRentalMenu(fleet);
                break;

            case 3:
                cout << "Schedule Management selected." << endl;
                break;

            case 4:
                cout << "Billing and report selected." << endl;
                break;

            case 5:
                cout << "Exiting program... Goodbye!" << endl;
                break;

            default:
                cout << "Invalid option, please try again." << endl;
            }
        } while (option != 5);
    }
    else {
        cout << endl;
        cout << "Too many failed attempts." << endl;
        cout << "Access denied. Program ended..." << endl;
    }

    return 0;
}