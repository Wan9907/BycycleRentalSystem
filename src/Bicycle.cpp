//
// Created by User on 8/25/2026.
//
#include "Bicycle.h"
#include <iostream>
#include <iomanip>

using namespace std;

void displayAvailableBikes(const vector<Bicycle>& fleet) {
    cout << "\n--- Available Bicycles ---" << endl;
    cout << left << setw(8) << "ID" << setw(18) << "Type" << setw(12) << "Rate/Hour" << "Status" << endl;
    cout << "--------------------------------------------" << endl;

    for (const auto& bike : fleet) {
        cout << left << setw(8) << bike.id
             << setw(18) << bike.type
             << "$" << setw(11) << fixed << setprecision(2) << bike.hourlyRate
             << (bike.isAvailable ? "Available" : "Rented Out") << endl;
    }
}

void bikeRentalMenu(vector<Bicycle>& fleet) {
    int choice;
    do {
        cout << "\n--- BICYCLE RENTAL MODULE ---" << endl;
        cout << "1. View All Bikes & Status" << endl;
        cout << "2. Rent a Bike" << endl;
        cout << "3. Return a Bike" << endl;
        cout << "4. Return to Main Menu" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }

        if (choice == 1) {
            displayAvailableBikes(fleet);
        }
        else if (choice == 2) {
            displayAvailableBikes(fleet);
            int bikeId, hours;
            cout << "\nEnter Bike ID to rent: ";
            cin >> bikeId;

            bool found = false;
            for (auto& bike : fleet) {
                if (bike.id == bikeId) {
                    found = true;
                    if (!bike.isAvailable) {
                        cout << "Sorry, this bike is currently rented out." << endl;
                    } else {
                        cout << "Enter rental duration (hours): ";
                        cin >> hours;

                        double total = bike.hourlyRate * hours;
                        bike.isAvailable = false;

                        cout << "\nRental Confirmed!" << endl;
                        cout << "Bike: " << bike.type << endl;
                        cout << "Total Cost: $" << fixed << setprecision(2) << total << endl;
                    }
                    break;
                }
            }
            if (!found) cout << "Invalid Bike ID!" << endl;
        }
        else if (choice == 3) {
            int bikeId;
            cout << "\nEnter Bike ID to return: ";
            cin >> bikeId;

            bool found = false;
            for (auto& bike : fleet) {
                if (bike.id == bikeId) {
                    found = true;
                    if (bike.isAvailable) {
                        cout << "This bike was not rented out." << endl;
                    } else {
                        bike.isAvailable = true;
                        cout << "Bike ID " << bikeId << " successfully returned!" << endl;
                    }
                    break;
                }
            }
            if (!found) cout << "Invalid Bike ID!" << endl;
        }
    } while (choice != 4);
}