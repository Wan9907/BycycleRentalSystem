//
// Created by User on 8/25/2026.
//

#ifndef BYCYCLERENTALSYSTEM_BICYCLE_H
#define BYCYCLERENTALSYSTEM_BICYCLE_H

#endif //BYCYCLERENTALSYSTEM_BICYCLE_H

#ifndef BICYCLE_H
#define BICYCLE_H

#include <string>
#include <vector>

struct Bicycle {
    int id;
    std::string type;
    double hourlyRate;
    bool isAvailable;
};

// Function declarations
void displayAvailableBikes(const std::vector<Bicycle>& fleet);
void bikeRentalMenu(std::vector<Bicycle>& fleet);

#endif