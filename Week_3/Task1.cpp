#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <limits>

// Define the MenuItem class to represent each menu
class MenuItem {
public:
    std::string name;
    std::vector<std::shared_ptr<MenuItem>> children;

    MenuItem(std::string name) : name(name) {}

    // Add child menu
    void addChild(std::shared_ptr<MenuItem> child) {
        children.push_back(child);
    }

    // Display the current menu with a cursor for selection
    void displayMenu(int cursorIndex) {
        std::cout << "\n" << name << ":\n";
        for (size_t i = 0; i < children.size(); ++i) {
            if (i == cursorIndex) {
                std::cout << "> " << children[i]->name << "\n"; // Highlight the selected option
            } else {
                std::cout << "  " << children[i]->name << "\n"; // Regular unhighlighted option
            }
        }
    }
};

// Define the MenuSystem class for handling navigation
class MenuSystem {
private:
    std::shared_ptr<MenuItem> rootMenu;      // The root menu
    std::shared_ptr<MenuItem> currentMenu;   // The currently selected menu
    std::vector<std::shared_ptr<MenuItem>> navigationHistory; // History for 'back' functionality
    int cursorIndex;  // The current position of the cursor (which menu item is selected)

public:
    MenuSystem() {
        // Initialize root menu
        rootMenu = std::make_shared<MenuItem>("Main Menu");

        // Setting menu and its submenus
        auto settingsMenu = std::make_shared<MenuItem>("Settings");

        // Display settings menu and its theme options
        auto displaySettings = std::make_shared<MenuItem>("Display Settings");
        auto changeTheme = std::make_shared<MenuItem>("Change Theme");
        displaySettings->addChild(changeTheme);

        // Audio settings menu with additional submenus
        auto audioSettings = std::make_shared<MenuItem>("Audio Settings");
        auto volumeControl = std::make_shared<MenuItem>("Volume Control");
        auto equalizerSettings = std::make_shared<MenuItem>("Equalizer Settings");
        auto bluetoothAudio = std::make_shared<MenuItem>("Bluetooth Audio");

        audioSettings->addChild(volumeControl);
        audioSettings->addChild(equalizerSettings);
        audioSettings->addChild(bluetoothAudio);

        settingsMenu->addChild(displaySettings);
        settingsMenu->addChild(audioSettings);

        // Media menu and its submenus
        auto mediaMenu = std::make_shared<MenuItem>("Media");
        auto radio = std::make_shared<MenuItem>("Radio");
        auto bluetoothMedia = std::make_shared<MenuItem>("Bluetooth Audio");
        mediaMenu->addChild(radio);
        mediaMenu->addChild(bluetoothMedia);

        // Add Settings and Media to the root menu
        rootMenu->addChild(settingsMenu);
        rootMenu->addChild(mediaMenu);

        currentMenu = rootMenu;  // Start at the root menu
        cursorIndex = 0;         // Start with the first menu option selected
    }

    // Function to handle navigation in the menu
    void navigate() {
        while (true) {
            currentMenu->displayMenu(cursorIndex);
            std::cout << "\nNavigation Options:\n";
            std::cout << "1. Move down\n";
            std::cout << "2. Move up\n";
            std::cout << "3. Enter submenu\n";
            std::cout << "4. Go back to the parent menu\n";
            std::cout << "5. Exit\n";

            int choice;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            if (choice == 1) {
                // Move down (cursor goes to the next item)
                if (cursorIndex < currentMenu->children.size() - 1) {
                    cursorIndex++;
                }
            } else if (choice == 2) {
                // Move up (cursor goes to the previous item)
                if (cursorIndex > 0) {
                    cursorIndex--;
                }
            } else if (choice == 3) {
                // Enter submenu (if a submenu exists at the cursor position)
                enterSubMenu();
            } else if (choice == 4) {
                // Go back to parent menu
                goBack();
            } else if (choice == 5) {
                // Exit the menu system
                std::cout << "Exiting the menu system...\n";
                break;
            } else {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    // Function to handle entering into a submenu
    void enterSubMenu() {
        if (currentMenu->children.empty()) {
            std::cout << "No submenu to enter. Returning to previous menu.\n";
            return;
        }
        navigationHistory.push_back(currentMenu); // Save current menu for 'back' functionality
        currentMenu = currentMenu->children[cursorIndex];  // Enter the submenu at the cursor index
        cursorIndex = 0;  // Reset cursor position for the new submenu
    }

    // Function to go back to the parent menu
    void goBack() {
        if (!navigationHistory.empty()) {
            currentMenu = navigationHistory.back();
            navigationHistory.pop_back();
            cursorIndex = 0;  // Reset cursor position when going back
        } else {
            std::cout << "You are already at the root menu.\n";
        }
    }
};

int main() {
    MenuSystem menuSystem;
    menuSystem.navigate();  // Start the navigation system
    return 0;
}