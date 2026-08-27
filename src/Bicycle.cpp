#include <iostream>
#include <iomanip>
#include <fstream>  // Fixed: Added for std::ifstream and std::ofstream
#include <sstream>  // Fixed: Added for std::stringstream
#include <ctime>    // Fixed: Added for timestamp calculations
#include "../header/Bicycle.h"
#include <filesystem> // Include filesystem header at top of src/Bicycle.cpp

using namespace std;

void saveFleetToFile(const std::vector<Bicycle>& fleet) {
    // Automatically create the data folder if it does not exist
    std::filesystem::create_directories("data");

    std::ofstream outFile("data/bikes.txt");
    if (!outFile) {
        std::cerr << "Error: Could not save fleet state!" << std::endl;
        return;
    }

    for (const auto& bike : fleet) {
        outFile << bike.id << "|"
                << bike.type << "|"
                << bike.hourlyRate << "|"
                << bike.isAvailable << "|"
                << (bike.rentedBy.empty() ? "None" : bike.rentedBy) << "\n";
    }
    outFile.close();
}

// Log rental transaction to data/bookings.txt
void saveBookingToFile(int bikeId, const string& bikeType, int hours, double totalCost) {
    ofstream outFile("data/bookings.txt", ios::app);
    if (!outFile) return;

    time_t now = time(0);
    char timeBuffer[80];
    struct tm timeInfo;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&timeInfo, &now);
#else
    localtime_r(&now, &timeInfo);
#endif
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

    outFile << "=== BOOKING RECORD ===" << endl;
    outFile << "Timestamp   : " << timeBuffer << endl;
    outFile << "Bike ID     : " << bikeId << endl;
    outFile << "Bike Type   : " << bikeType << endl;
    outFile << "Duration    : " << hours << " hour(s)" << endl;
    outFile << "Total Cost  : $" << fixed << setprecision(2) << totalCost << endl;
    outFile << "----------------------" << endl << endl;
    outFile.close();
}

void loadFleetFromFile(std::vector<Bicycle>& fleet) {
    std::ifstream inFile("data/bikes.txt");
    if (!inFile) {
        // Fallback default fleet if data/bikes.txt does not exist yet
        fleet = {
            {101, "City Bike", 5.00, true, "None"},
            {102, "Mountain Bike", 8.50, true, "None"},
            {103, "Electric Bike", 15.00, true, "None"},
            {104, "Tandem Bike", 12.00, true, "None"}
        };
        // Removed saveFleetToFile(fleet) here so it won't throw an error if data/ folder is missing on first launch
        return;
    }

    fleet.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string idStr, type, rateStr, availStr, rentedBy;

        std::getline(ss, idStr, '|');
        std::getline(ss, type, '|');
        std::getline(ss, rateStr, '|');
        std::getline(ss, availStr, '|');
        std::getline(ss, rentedBy, '|');

        Bicycle bike;
        bike.id = std::stoi(idStr);
        bike.type = type;
        bike.hourlyRate = std::stod(rateStr);
        bike.isAvailable = (availStr == "1");
        bike.rentedBy = rentedBy;
        fleet.push_back(bike);
    }
    inFile.close();
}

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
