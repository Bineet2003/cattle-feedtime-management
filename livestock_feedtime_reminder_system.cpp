#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iomanip>  // Added header for std::get_time

struct CattleData {
    std::string cattleId;
    std::string cattleName;
    std::string feedTime;
    std::string food;
};

void addData(const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (!file) {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::string cattleId, cattleName, feedTime, food;
    std::cout << "Enter cattle ID: ";
    std::cin >> cattleId;
    std::cout << "Enter cattle name: ";
    std::cin.ignore();
    std::getline(std::cin, cattleName);
    std::cout << "Enter feed time (HH:MM): ";
    std::cin >> feedTime;
    std::cout << "Enter food: ";
    std::cin.ignore();
    std::getline(std::cin, food);

    file << cattleId << " " << cattleName << " " << feedTime << " " << food << std::endl;
    file.close();

    std::cout << "Cattle data added successfully." << std::endl;
}

void removeData(const std::string& filename) {
    std::string cattleId;
    std::cout << "Enter cattle ID to remove: ";
    std::cin >> cattleId;

    std::ifstream fileIn(filename);
    if (!fileIn) {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::vector<CattleData> cattleDataList;
    std::string line;
    while (std::getline(fileIn, line)) {
        std::istringstream iss(line);
        CattleData data;
        iss >> data.cattleId >> data.cattleName >> data.feedTime >> data.food;
        if (data.cattleId != cattleId) {
            cattleDataList.push_back(data);
        }
    }
    fileIn.close();

    std::ofstream fileOut(filename);
    if (!fileOut) {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    for (const auto& data : cattleDataList) {
        fileOut << data.cattleId << " " << data.cattleName << " " << data.feedTime << " " << data.food << std::endl;
    }
    fileOut.close();

    std::cout << "Cattle data removed successfully." << std::endl;
}

void displayCurrentTime() {
    std::time_t currentTime = std::time(nullptr);
    std::cout << "Current time: " << std::asctime(std::localtime(&currentTime)) << std::endl;
}

void displayDataByTime(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::vector<CattleData> cattleDataList;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        CattleData data;
        iss >> data.cattleId >> data.cattleName >> data.feedTime >> data.food;
        cattleDataList.push_back(data);
    }
    file.close();

    std::time_t currentTime = std::time(nullptr);
    std::tm* currentTimeInfo = std::localtime(&currentTime);

    std::sort(cattleDataList.begin(), cattleDataList.end(), [&](const CattleData& a, const CattleData& b) {
        std::tm tmA{}, tmB{};
        std::istringstream issA(a.feedTime), issB(b.feedTime);
        issA >> tmA.tm_hour;
        issA.ignore();
        issA >> tmA.tm_min;
        issB >> tmB.tm_hour;
        issB.ignore();
        issB >> tmB.tm_min;

        // Calculate the time difference in minutes
        int diffMinutesA = ((tmA.tm_hour * 60) + tmA.tm_min) - ((currentTimeInfo->tm_hour * 60) + currentTimeInfo->tm_min);
        int diffMinutesB = ((tmB.tm_hour * 60) + tmB.tm_min) - ((currentTimeInfo->tm_hour * 60) + currentTimeInfo->tm_min);

        // If the time difference is negative, add 24 hours (in minutes) to it
        if (diffMinutesA < 0)
            diffMinutesA += 24 * 60;
        if (diffMinutesB < 0)
            diffMinutesB += 24 * 60;

        // Convert the time difference to seconds
        int diffSecondsA = diffMinutesA * 60;
        int diffSecondsB = diffMinutesB * 60;

        return diffSecondsA < diffSecondsB;
    });

    std::cout << "Cattle ID | Cattle Name | Feed Time | Food | Time Difference" << std::endl;
    for (const auto& data : cattleDataList) {
        std::cout << data.cattleId << " | " << data.cattleName << " | " << data.feedTime << " | " << data.food;

        std::tm tm{};
        std::istringstream iss(data.feedTime);
        iss >> tm.tm_hour;
        iss.ignore();
        iss >> tm.tm_min;

        // Calculate the time difference in minutes
        int diffMinutes = ((tm.tm_hour * 60) + tm.tm_min) - ((currentTimeInfo->tm_hour * 60) + currentTimeInfo->tm_min);

        // If the time difference is negative, add 24 hours (in minutes) to it
        if (diffMinutes < 0)
            diffMinutes += 24 * 60;

        // Convert the time difference to seconds
        int diffSeconds = diffMinutes * 60;
        int diffHours2 = diffSeconds/3600;
        int diffMinutes2=(diffSeconds-3600*diffHours2)/60;

        std::cout << " | " << diffHours2 << " hours " << diffMinutes2 << " minutes" << std::endl;
    }
}


void displayDataById(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::vector<CattleData> cattleDataList;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        CattleData data;
        iss >> data.cattleId >> data.cattleName >> data.feedTime >> data.food;
        cattleDataList.push_back(data);
    }
    file.close();

    std::sort(cattleDataList.begin(), cattleDataList.end(), [](const CattleData& a, const CattleData& b) {
        return a.cattleId < b.cattleId;
    });

    std::cout << "Cattle ID | Cattle Name | Feed Time | Food" << std::endl;
    for (const auto& data : cattleDataList) {
        std::cout << data.cattleId << " | " << data.cattleName << " | " << data.feedTime << " | " << data.food << std::endl;
    }
}

int main() {
    std::string filename = "cattle_data.txt";
    int choice;

    do {
        std::cout << "\n------ Cattle Data Management ------" << std::endl;
        std::cout << "1. Add cattle data" << std::endl;
        std::cout << "2. Remove cattle data" << std::endl;
        std::cout << "3. Display current time" << std::endl;
        std::cout << "4. Display cattle data sorted by time difference" << std::endl;
        std::cout << "5. Display cattle data sorted by cattle ID" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addData(filename);
                break;
            case 2:
                removeData(filename);
                break;
            case 3:
                displayCurrentTime();
                break;
            case 4:
                displayDataByTime(filename);
                break;
            case 5:
                displayDataById(filename);
                break;
            case 6:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
