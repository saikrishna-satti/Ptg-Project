#include <iostream>
#include <unordered_map>
using namespace std;

class Theme {
    string backgroundColor;
    string fontColor;
    int fontSize;
    string iconStyle;

public:
    // Default constructor
    Theme() : backgroundColor("default"), fontColor("default"), fontSize(12), iconStyle("default") {}

    // Constructor to initialize theme settings
    Theme(string bgc, string fc, int fs, string is)
        : backgroundColor(bgc), fontColor(fc), fontSize(fs), iconStyle(is) {}

    // Method to display the settings of the theme
    void displaySettings(const string& themeName) const {
        cout << themeName << " Theme: " 
             << backgroundColor << " Background, " 
             << fontColor << " Font, " 
             << iconStyle << " Icon Style, " 
             << fontSize << " Font Size" << endl;
    }
};

int main() {
    // Create an unordered_map to store themes with their names
    unordered_map<string, Theme> themeMap;

    // Create theme objects with their respective settings
    Theme classic("Blue", "White", 12, "Square");
    Theme sport("Red", "White", 14, "Round");
    Theme eco("Green", "Dark Green", 10, "Simple");

    // Insert themes into the map
    themeMap["Classic"] = classic;
    themeMap["Sport"] = sport;
    themeMap["Eco"] = eco;

    // Menu loop for user interaction
    while (true) {
        cout << "\n1. Select a theme" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter option: ";
        int option;
        cin >> option;

        if (option == 1) {
            // Display available themes to the user
            cout << "Available Themes:" << endl;
            cout << " Classic" << endl;
            cout << " Sport" << endl;
            cout << " Eco" << endl;
            cout << "\nEnter the theme name : ";
            
            // Ask the user to select a theme
            string selectedTheme;
            cin >> selectedTheme;
            
            // Check if the theme exists in the map and display its settings
            if (themeMap.find(selectedTheme) != themeMap.end()) {
                cout << "\nApplying settings for the " << selectedTheme << " theme:" << endl;
                // Directly call displaySettings for the selected theme
                themeMap[selectedTheme].displaySettings(selectedTheme);
            } else {
                cout << "Invalid theme selected!" << endl;
            }
        } else if (option == 2) {
            // Exit the loop and end the program
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;  
}