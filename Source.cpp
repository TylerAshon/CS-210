#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

class ItemTracker {
private:
    std::map<std::string, int> itemFrequency; // Stores the frequency of each item

public:
    // Method to load data from a file
    void loadData(const std::string& filename);

    // Method to query frequency of a specific item
    int getFrequency(const std::string& item) const;

    // Method to print all items and their frequencies
    void printFrequencies() const;

    // Method to print histogram of item frequencies
    void printHistogram() const;

    // Method to save frequencies to a backup file
    void saveToBackup(const std::string& filename) const;
};

void ItemTracker::loadData(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string item;
    while (inputFile >> item) {
        itemFrequency[item]++;
    }
    inputFile.close();
}

int ItemTracker::getFrequency(const std::string& item) const {
    auto it = itemFrequency.find(item);
    if (it != itemFrequency.end()) {
        return it->second;
    }
    return 0;
}

void ItemTracker::printFrequencies() const {
    std::cout << "Item Frequencies:\n";
    for (const auto& entry : itemFrequency) {
        std::cout << std::setw(15) << std::left << entry.first << " : " << entry.second << std::endl;
    }
}

void ItemTracker::printHistogram() const {
    std::cout << "Item Histogram:\n";
    for (const auto& entry : itemFrequency) {
        std::cout << std::setw(15) << std::left << entry.first << " : " << std::string(entry.second, '*') << std::endl;
    }
}

void ItemTracker::saveToBackup(const std::string& filename) const {
    std::ofstream backupFile(filename);
    if (!backupFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& entry : itemFrequency) {
        backupFile << entry.first << " " << entry.second << std::endl;
    }
    backupFile.close();
}

int main() {
    ItemTracker tracker;
    tracker.loadData("CS210_Project_Three_Input_File.txt");
    tracker.saveToBackup("frequency.dat");

    int choice;
    std::string item;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Find frequency of a specific item\n";
        std::cout << "2. Print all items and their frequencies\n";
        std::cout << "3. Print histogram of item frequencies\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter item to find frequency: ";
            std::cin >> item;
            std::cout << item << " frequency: " << tracker.getFrequency(item) << std::endl;
            break;
        case 2:
            tracker.printFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice, please try again.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}

