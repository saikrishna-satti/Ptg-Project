#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

struct Control {
    int id;
    std::string type;  // "button" or "slider"
    std::string state; // "visible", "invisible", or "disabled"
};

// Function to print the controls
void printControls(const std::vector<Control>& controls) {
    for (const auto& control : controls) {
        std::cout << "ID: " << control.id << ", Type: " << control.type << ", State: " << control.state << std::endl;
    }
}

// 1. Create a backup of the control list
void createBackup(std::vector<Control>& controls) {
    std::vector<Control> backup = controls;
    std::cout << "\nBackup created:\n";
    printControls(backup);
}

// 2. Temporarily set all states to "disabled"
void disableAllControls(std::vector<Control>& controls) {
    std::fill(controls.begin(), controls.end(), Control{0, "", "disabled"});
    std::cout << "\nAll controls are temporarily disabled:\n";
    printControls(controls);
}

// 3. Generate random states ("visible", "invisible", "disabled")
void generateRandomStates(std::vector<Control>& controls) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2); // 0: "visible", 1: "invisible", 2: "disabled"

    std::vector<std::string> states = {"visible", "invisible", "disabled"};
    
    std::for_each(controls.begin(), controls.end(), [&](Control& ctrl) {
        ctrl.state = states[dist(gen)];
    });

    std::cout << "\nRandom states generated for controls:\n";
    printControls(controls);
}

// 4. Transform all sliders to "invisible"
void transformSliders(std::vector<Control>& controls) {
    std::transform(controls.begin(), controls.end(), controls.begin(), [](Control& ctrl) {
        if (ctrl.type == "slider") {
            ctrl.state = "invisible";
        }
        return ctrl;
    });

    std::cout << "\nAll sliders are set to invisible:\n";
    printControls(controls);
}

// 5. Replace "disabled" with "enabled" for testing
void replaceDisabledWithEnabled(std::vector<Control>& controls) {
    std::replace_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "disabled";
    }, Control{0, "", "enabled"});

    std::cout << "\nReplaced 'disabled' with 'enabled' for testing:\n";
    printControls(controls);
}

// 6. Remove invisible controls
void removeInvisibleControls(std::vector<Control>& controls) {
    controls.erase(std::remove_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "invisible";
    }), controls.end());

    std::cout << "\nInvisible controls removed:\n";
    printControls(controls);
}

// 7. Reverse the control order (e.g., for debugging)
void reverseControls(std::vector<Control>& controls) {
    std::reverse(controls.begin(), controls.end());
    std::cout << "\nControls order reversed:\n";
    printControls(controls);
}

// 8. Partition visible controls together
void partitionVisibleControls(std::vector<Control>& controls) {
    std::partition(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "visible";
    });

    std::cout << "\nVisible controls partitioned:\n";
    printControls(controls);
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
    while (true) {
        std::cout << "\nChoose an operation:\n";
        std::cout << "1. Create a backup of the control list\n";
        std::cout << "2. Disable all controls\n";
        std::cout << "3. Generate random states for controls\n";
        std::cout << "4. Transform all sliders to 'invisible'\n";
        std::cout << "5. Replace 'disabled' with 'enabled'\n";
        std::cout << "6. Remove invisible controls\n";
        std::cout << "7. Reverse the control order\n";
        std::cout << "8. Partition visible controls\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                createBackup(controls);
                break;
            case 2:
                disableAllControls(controls);
                break;
            case 3:
                generateRandomStates(controls);
                break;
            case 4:
                transformSliders(controls);
                break;
            case 5:
                replaceDisabledWithEnabled(controls);
                break;
            case 6:
                removeInvisibleControls(controls);
                break;
            case 7:
                reverseControls(controls);
                break;
            case 8:
                partitionVisibleControls(controls);
                break;
            case 0:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}