#pragma once
#include <string>
#include <vector>
using namespace std;

struct Bicycle {
    int    id;
    string type;
    double hourlyRate;
    bool   isAvailable;
    string rentedBy;
};

struct Rental {
    string rentBy;
    int bikeId;
    int hours;
    bool isReturn;
};

void saveFleetToFile(const vector<Bicycle>& fleet);
void loadFleetFromFile(vector<Bicycle>& fleet);
void saveBookingToFile(int bikeId, const string& bikeType, int hours, double totalCost);
void saveRentalRecord(const vector<Rental>& rentals);
void loadRentalRecord(vector<Rental>& rentals);
void displayAvailableBikes(const vector<Bicycle>& fleet);
void viewAllBikes(const vector<Bicycle>& fleet);
void rentBike(vector<Bicycle>& fleet, vector<Rental>& rentals);
void returnBike(vector<Bicycle>& fleet, vector<Rental>& rentals);
void addBike(vector<Bicycle>& fleet);
void removeBike(vector<Bicycle>& fleet);
void bikeRentalMenu(vector<Bicycle>& fleet, vector<Rental>& rentals);