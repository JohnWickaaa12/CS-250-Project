#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

class GroceryTracker {
private:
    map<string, int> itemFrequency;
    string inputFile = "CS210_Project_Three_Input_File.txt";
    string backupFile = "frequency.dat";

    void LoadItems() {
        ifstream inFile(inputFile);
        if (!inFile) {
            cerr << "Error opening input file!" << endl;
            exit(1);
        }
        string item;
        while (inFile >> item) {
            itemFrequency[item]++;
        }
        inFile.close();
    }

    void SaveToBackupFile() {
        ofstream outFile(backupFile);
        for (const auto& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << endl;
        }
        outFile.close();
    }

public:
    GroceryTracker() {
        LoadItems();
        SaveToBackupFile();
    }

    int GetItemFrequency(const string& item) const {
        auto it = itemFrequency.find(item);
        return it != itemFrequency.end() ? it->second : 0;
    }

    void PrintAllItems() const {
        cout << "\nItem Frequency List:\n";
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    void PrintHistogram() const {
        cout << "\nPurchase Frequency Histogram:\n";
        for (const auto& pair : itemFrequency) {
            cout << setw(12) << left << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

void DisplayMenu() {
    cout << "\n======== Corner Grocer Menu ========\n";
    cout << "1. Search for an item frequency\n";
    cout << "2. Display frequency of all items\n";
    cout << "3. Display histogram of item frequencies\n";
    cout << "4. Exit\n";
    cout << "====================================\n";
    cout << "Enter your choice (1-4): ";
}

int main() {
    GroceryTracker tracker;
    int choice;
    string item;

    while (true) {
        DisplayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter item name: ";
            cin >> item;
            cout << item << " was purchased " << tracker.GetItemFrequency(item) << " times.\n";
            break;
        case 2:
            tracker.PrintAllItems();
            break;
        case 3:
            tracker.PrintHistogram();
            break;
        case 4:
            cout << "Exiting program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
