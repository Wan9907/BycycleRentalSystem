#ifndef BICYCLE_H
#define BICYCLE_H

#include <string>
#include <vector>

struct Bicycle {
    int id;
    std::string type;
    double hourlyRate;
    bool isAvailable;
    std::string rentedBy; // Store user/member name or ID
};

void displayAvailableBikes(const std::vector<Bicycle>& fleet);
void bikeRentalMenu(std::vector<Bicycle>& fleet);
void saveBookingToFile(int bikeId, const std::string& bikeType, int hours, double totalCost, const std::string& userName);
void saveFleetToFile(const std::vector<Bicycle>& fleet);
void loadFleetFromFile(std::vector<Bicycle>& fleet);

#endif