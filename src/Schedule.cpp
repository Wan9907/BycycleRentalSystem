#include "../header/Schedule.h"
#include "../header/Bicycle.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

void scheduleMenu(vector<Schedule>& schedules, vector<Bicycle>& bikes) {
    int choice;
    do {
        cout << "\n=========================================" << endl;
        cout << "        MEMBER MANAGEMENT SYSTEM         " << endl;
        cout << "=========================================" << endl;
        cout << "1. Display Schedule" << endl;
        cout << "2. Change Time Slot" << endl;
        cout << "3. Delete Time Slot" << endl;
        cout << "4. Reset Schedule" << endl;
        cout << "0. Back to Main Menu" << endl;

        cout << "Enter choice : " << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                printSchedule(schedules, bikes);
                break;
            case 2:
                changeTimeSlot(schedules, bikes);
                break;
            case 3:
               deleteSchedule(schedules, bikes);
                break;
            case 4:
                resetSchedule(schedules);
                break;
            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;
            default:
                cout << "Invalid selection!\n";
        }
    } while (choice != 0);
}
void printSchedule(const vector<Schedule>& schedules, const vector<Bicycle>& bikes, const string& bike_type) {
    cout << "                                         -" + bike_type + "-" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    cout << "| Bike ID | 9.pm- | 10.am-| 11.am-| 12.pm-| 1.pm- | 2.pm- | 3.pm- | 4.pm- | 5.pm- | 6.pm- | 7.pm- | 8.pm- |" << endl;
    cout << "|         | 10.pm | 11.am | 12.pm | 1.pm  | 2.pm  | 3.pm  | 4.pm  | 5.pm  | 6.pm  | 7.pm  | 8.pm  | 9.pm  |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    if (bike_type == "All") {
        for (const auto&[bike_id, time_slot_status] : schedules) {
            cout << "| " << setw(8) << bike_id << "|";
            for (const char tss : time_slot_status) {
                cout << "   " << tss << "   |" ;
            }
            cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        }
    }else {
        for (const auto&[bike_id, time_slot_status] : schedules) {
            for (const auto& bike : bikes) {
                if (bike_id == bike.id && bike_type == bike.type) {
                    cout << "| " << setw(8) << bike_id << "|";
                    for (const char tss : time_slot_status) {
                        cout << "   " << tss << "   |" ;
                    }
                    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
                }
            }
        }
    }
};

void changeTimeSlot(std::vector<Schedule>& schedules, const std::vector<Bicycle>& bikes) {
    printSchedule(schedules, bikes);

    int id,timeSlot;

    cout << "\nEnter bike ID: ";
    cin >> id;
    cout << "Enter time slot(1-12): ";
    cin >> timeSlot;

    if (checkTimeSlot(schedules, id, timeSlot)) {
        for (auto& schedule : schedules) {
            if (schedule.bike_id == id) {
                schedule.time_slot_status[timeSlot - 1] = 'X';
            }
        }
    }
};

bool checkTimeSlot(const std::vector<Schedule>& schedules, int targetID, int time_slot) {
    for (const auto& schedule : schedules) {
        if (schedule.bike_id == targetID) {
            if (schedule.time_slot_status[time_slot - 1] == 'X') {
                return false;
            }
        }
    }

    return true;
};

void deleteSchedule(std::vector<Schedule>& schedules, const vector<Bicycle>& bikes) {
    printSchedule(schedules, bikes);

    int id,timeSlot;

    cout << "\nEnter bike ID: ";
    cin >> id;
    cout << "Enter time slot(1-12): ";
    cin >> timeSlot;

    if (checkTimeSlot(schedules, id, timeSlot)) {
        for (auto& schedule : schedules) {
            if (schedule.bike_id == id) {
                schedule.time_slot_status[timeSlot - 1] = ' ';
            }
        }
    }

};

void resetSchedule(std::vector<Schedule>& schedules) {
    for (auto& schedule : schedules) {
        for (int i = 0;i < 12;i++) {
            schedule.time_slot_status[i] = ' ';
        }
    }
};

void saveSchedule(const std::vector<Schedule>& schedules) {
    ofstream outFile("../data/schedule.csv");

    if (!outFile) {
        cerr << "Can't open file!\n";
        return;
    }

    outFile << "Bike_ID|time_slot_status\n";
    for (const auto& schedule : schedules) {
        outFile << schedule.bike_id << "|";
        for (const auto& time_slot : schedule.time_slot_status) {
            outFile << time_slot << " ";
        }
        outFile << "\n";
    }
    outFile.close();
};

void loadSchedule(std::vector<Schedule>& schedules) {
    ifstream inFile("../data/schedule.csv");

    if (!inFile) {
        cerr << "Can't open file!\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, timeSlotStr;
        vector<char> arr;
        Schedule schedule;

        getline(ss, idStr, '|');
        getline(ss, timeSlotStr, '|');
        schedule.bike_id = stoi(idStr);

        stringstream status_ss(timeSlotStr);
        char single_status;

        while (status_ss >> single_status) {
            for (int i = 0;i < 12;i++) {
                schedule.time_slot_status[i] = single_status;
            }
        }

    schedules.push_back(schedule);
    }
};
