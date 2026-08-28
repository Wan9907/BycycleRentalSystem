#pragma once

#include <string>
#include <vector>
#include "Bicycle.h"

struct Schedule {
    int bike_id = -1;
    char time_slot_status[12] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; //9am - 9pm
};

void scheduleMenu(std::vector<Schedule>& schedules);
void printSchedule(const std::vector<Schedule>& schedules, const std::vector<Bicycle>& bikes, const std::string& bike_type = "All");
void changeTimeSlot(std::vector<Schedule>& schedules, const std::vector<Bicycle>& bikes);
bool checkTimeSlot(const std::vector<Schedule>& schedules, int targetID, int time_slot);
void deleteSchedule(std::vector<Schedule>& schedules, const std::vector<Bicycle>& bikes);
void resetSchedule(std::vector<Schedule>& schedules);
void saveSchedule(const std::vector<Schedule>& schedules);
void loadSchedule(std::vector<Schedule>& schedules);