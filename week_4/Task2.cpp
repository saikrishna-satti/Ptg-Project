#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// Function to print all dynamic widgets using an iterator
void printDynamicWidgets(const std::vector<std::string>& dynamicWidgets) {
    std::cout << "Dynamic Widgets: " << std::endl;
    for (auto it = dynamicWidgets.begin(); it != dynamicWidgets.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

// Function to find a specific widget in the set (e.g., "WarningLights")
void findStaticWidget(const std::set<std::string>& staticWidgets, const std::string& widget) {
    auto found = staticWidgets.find(widget);
    if (found != staticWidgets.end()) {
        std::cout << "\"" << widget << "\" is found in static widgets." << std::endl;
    } else {
        std::cout << "\"" << widget << "\" is NOT found in static widgets." << std::endl;
    }
}

// Function to combine dynamic and static widgets into a single vector
std::vector<std::string> combineWidgets(const std::vector<std::string>& dynamicWidgets, const std::set<std::string>& staticWidgets) {
    std::vector<std::string> allWidgets;
    std::copy(dynamicWidgets.begin(), dynamicWidgets.end(), std::back_inserter(allWidgets));
    std::copy(staticWidgets.begin(), staticWidgets.end(), std::back_inserter(allWidgets));
    return allWidgets;
}

// Function to find a widget in the combined vector
void findWidgetInCombinedList(const std::vector<std::string>& combinedWidgets, const std::string& widget) {
    auto it = std::find(combinedWidgets.begin(), combinedWidgets.end(), widget);
    if (it != combinedWidgets.end()) {
        std::cout << "\"" << widget << "\" is found in the combined widget list." << std::endl;
    } else {
        std::cout << "\"" << widget << "\" is NOT found in the combined widget list." << std::endl;
    }
}

// Function to print all widgets (combined list)
void printAllWidgets(const std::vector<std::string>& allWidgets) {
    std::cout << "All Widgets: " << std::endl;
    for (const auto& widget : allWidgets) {
        std::cout << widget << std::endl;
    }
}

// Main function to interact with the user and perform the chosen operation
int main() {
    // Initialize containers
    std::vector<std::string> dynamicWidgets = {"Speedometer", "Tachometer", "FuelGauge", "TemperatureMeter"};
    std::set<std::string> staticWidgets = {"Logo", "WarningLights", "BatteryStatus"};

    int choice;
    std::string widgetName;

    do {
        std::cout << "\nSelect an operation:\n";
        std::cout << "1. Print dynamic widgets\n";
        std::cout << "2. Find a static widget (e.g., WarningLights)\n";
        std::cout << "3. Combine dynamic and static widgets\n";
        std::cout << "4. Find a widget in the combined list\n";
        std::cout << "5. Print all widgets\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Print dynamic widgets
                printDynamicWidgets(dynamicWidgets);
                break;

            case 2:
                // Find a static widget
                std::cout << "Enter the name of the static widget you want to find: ";
                std::cin >> widgetName;
                findStaticWidget(staticWidgets, widgetName);
                break;

            case 3:
                // Combine dynamic and static widgets
                {
                    std::vector<std::string> allWidgets = combineWidgets(dynamicWidgets, staticWidgets);
                    std::cout << "Dynamic and static widgets have been combined.\n";
                }
                break;

            case 4:
                // Find a widget in the combined list
                {
                    std::vector<std::string> allWidgets = combineWidgets(dynamicWidgets, staticWidgets);
                    std::cout << "Enter the name of the widget you want to find in the combined list: ";
                    std::cin >> widgetName;
                    findWidgetInCombinedList(allWidgets, widgetName);
                }
                break;

            case 5:
                // Print all widgets
                {
                    std::vector<std::string> allWidgets = combineWidgets(dynamicWidgets, staticWidgets);
                    printAllWidgets(allWidgets);
                }
                break;

            case 0:
                std::cout << "Exiting program...\n";
                break;

            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);

    return 0;
}