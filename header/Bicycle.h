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

void saveFleetToFile(const vector<Bicycle>& fleet);
void loadFleetFromFile(vector<Bicycle>& fleet);
void saveBookingToFile(int bikeId, const string& bikeType, int hours, double totalCost);
void displayAvailableBikes(const vector<Bicycle>& fleet);
void viewAllBikes(const vector<Bicycle>& fleet);
void rentBike(vector<Bicycle>& fleet);
void returnBike(vector<Bicycle>& fleet);
void addBike(vector<Bicycle>& fleet);
void removeBike(vector<Bicycle>& fleet);
void bikeRentalMenu(vector<Bicycle>& fleet);