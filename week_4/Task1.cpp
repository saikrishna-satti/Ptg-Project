#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Control {
    int id;               // Unique ID
    std::string type;     // "button" or "slider"
    std::string state;    // "visible", "invisible", or "disabled"

    // Overload the equality operator to compare based on the `id`
    bool operator==(const Control& other) const {
        return this->id == other.id;  // Compare only the `id`
    }
};

// Function to iterate through all controls and print their details using std::for_each
void printControls(const std::vector<Control>& controls) {
    std::cout << "All controls:" << std::endl;
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) {
        std::cout << "ID: " << ctrl.id << ", Type: " << ctrl.type << ", State: " << ctrl.state << std::endl;
    });
}

// Function to find a control by ID using std::find
void findControlById(const std::vector<Control>& controls, int searchId) {
    Control searchControl = {searchId, "", ""};  // We only care about the ID, other fields are irrelevant
    auto controlWithId = std::find(controls.begin(), controls.end(), searchControl);

    if (controlWithId != controls.end()) {
        std::cout << "Found control with ID " << searchId << ": Type = " << controlWithId->type 
                  << ", State = " << controlWithId->state << std::endl;
    } else {
        std::cout << "Control with ID " << searchId << " not found!" << std::endl;
    }
}

// Function to find the first invisible control using std::find_if
void findFirstInvisibleControl(const std::vector<Control>& controls) {
    auto invisibleControl = std::find_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "invisible";
    });
    if (invisibleControl != controls.end()) {
        std::cout << "First invisible control: ID = " << invisibleControl->id << ", Type = " 
                  << invisibleControl->type << std::endl;
    } else {
        std::cout << "No invisible controls found!" << std::endl;
    }
}

// Function to find consecutive controls with the same state using std::adjacent_find
void findConsecutiveSameStateControls(const std::vector<Control>& controls) {
    auto consecutiveSameState = std::adjacent_find(controls.begin(), controls.end(), [](const Control& a, const Control& b) {
        return a.state == b.state;
    });
    if (consecutiveSameState != controls.end()) {
        std::cout << "Found consecutive controls with the same state: ID1 = " << consecutiveSameState->id 
                  << ", ID2 = " << (consecutiveSameState + 1)->id << std::endl;
    } else {
        std::cout << "No consecutive controls with the same state!" << std::endl;
    }
}

// Function to count the number of visible controls using std::count_if
void countVisibleControls(const std::vector<Control>& controls) {
    int visibleCount = std::count_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "visible";
    });
    std::cout << "Number of visible controls: " << visibleCount << std::endl;
}

// Function to count the number of disabled sliders using std::count_if
void countDisabledSliders(const std::vector<Control>& controls) {
    int disabledSlidersCount = std::count_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.type == "slider" && ctrl.state == "disabled";
    });
    std::cout << "Number of disabled sliders: " << disabledSlidersCount << std::endl;
}

// Function to compare the first 5 controls with the next 5 controls using std::equal
void compareFirstFiveControls(const std::vector<Control>& controls) {
    bool areIdentical = std::equal(controls.begin(), controls.begin() + 5, controls.begin() + 5);
    if (areIdentical) {
        std::cout << "The first 5 controls are identical to the next 5 controls." << std::endl;
    } else {
        std::cout << "The first 5 controls are NOT identical to the next 5 controls." << std::endl;
    }
}

int main() {
    std::vector<Control> controls = {
        {1, "button", "visible"},
        {2, "button", "invisible"},
        {3, "slider", "visible"},
        {4, "slider", "disabled"},
        {5, "button", "disabled"},
        {6, "button", "visible"},
        {7, "slider", "invisible"},
        {8, "slider", "disabled"},
        {9, "button", "invisible"},
        {10, "slider", "visible"}
    };

    int choice;
    do {
        std::cout << "\nChoose an option (0 to exit):\n";
        std::cout << "1. Print all controls\n";
        std::cout << "2. Find control by ID\n";
        std::cout << "3. Find first invisible control\n";
        std::cout << "4. Find consecutive controls with the same state\n";
        std::cout << "5. Count visible controls\n";
        std::cout << "6. Count disabled sliders\n";
        std::cout << "7. Compare the first 5 controls with the next 5 controls\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                printControls(controls);
                break;

            case 2: {
                int searchId;
                std::cout << "Enter ID to search for: ";
                std::cin >> searchId;
                findControlById(controls, searchId);
                break;
            }

            case 3:
                findFirstInvisibleControl(controls);
                break;

            case 4:
                findConsecutiveSameStateControls(controls);
                break;

            case 5:
                countVisibleControls(controls);
                break;

            case 6:
                countDisabledSliders(controls);
                break;

            case 7:
                compareFirstFiveControls(controls);
                break;

            case 0:
                std::cout << "Exiting program." << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != 0);

    return 0;
}

