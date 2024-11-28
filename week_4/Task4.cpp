#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>

struct Control {
    int id;           // Unique ID
    std::string type; // "button" or "slider"
    std::string state;// "visible", "invisible", or "disabled"
    
    bool operator<(const Control& other) const {
        return id < other.id; // For sorting by ID
    }
};

// Function to print the list of controls
void printControls(const std::vector<Control>& controls) {
    for (const auto& control : controls) {
        std::cout << "ID: " << control.id << ", Type: " << control.type << ", State: " << control.state << std::endl;
    }
}

// Function to sort controls by ID using std::sort
void sortControlsById(std::vector<Control>& controls) {
    std::sort(controls.begin(), controls.end());
    std::cout << "\nControls sorted by ID:\n";
    printControls(controls);
}

// Function to use std::stable_sort to maintain relative order of controls with equal IDs
void stableSortControlsById(std::vector<Control>& controls) {
    std::stable_sort(controls.begin(), controls.end());
    std::cout << "\nControls sorted by ID using stable_sort (maintaining relative order for equal IDs):\n";
    printControls(controls);
}

// Function to perform binary search for a control by ID using std::lower_bound and std::upper_bound
void binarySearchById(const std::vector<Control>& controls, int id) {
    auto lower = std::lower_bound(controls.begin(), controls.end(), Control{id, "", ""});
    auto upper = std::upper_bound(controls.begin(), controls.end(), Control{id, "", ""});
    
    if (lower != controls.end() && lower->id == id) {
        std::cout << "\nFound control with ID " << id << " using lower_bound: Type = " << lower->type << ", State = " << lower->state << std::endl;
    } else {
        std::cout << "\nControl with ID " << id << " not found using lower_bound." << std::endl;
    }
    
    if (upper != controls.end() && upper != lower) {
        std::cout << "Found control with ID " << id << " using upper_bound: Type = " << upper->type << ", State = " << upper->state << std::endl;
    } else {
        std::cout << "Control with ID " << id << " not found using upper_bound." << std::endl;
    }
}

// Function to merge two sorted lists of controls
void mergeControlLists(std::vector<Control>& list1, std::vector<Control>& list2) {
    std::vector<Control> merged(list1.size() + list2.size());
    std::merge(list1.begin(), list1.end(), list2.begin(), list2.end(), merged.begin());
    
    std::cout << "\nMerged control lists:\n";
    printControls(merged);
}

// Function to perform std::inplace_merge to combine two different segments in the same list
void inplaceMergeControls(std::vector<Control>& controls1, std::vector<Control>& controls2) {
    // Merge both lists into a combined vector
    std::vector<Control> combined;
    combined.reserve(controls1.size() + controls2.size());
    combined.insert(combined.end(), controls1.begin(), controls1.end());
    combined.insert(combined.end(), controls2.begin(), controls2.end());

    // Sort the combined list first to ensure the merging happens correctly
    std::sort(combined.begin(), combined.end());

    // Now, use inplace_merge to combine the first half and second half in the sorted list
    std::inplace_merge(combined.begin(), combined.begin() + controls1.size(), combined.end());

    // Print the result after the inplace merge
    std::cout << "\nIn-place merged controls from both lists:\n";
    printControls(combined);
}

// Function to perform set operations: union and intersection
void setOperations(const std::vector<Control>& list1, const std::vector<Control>& list2) {
    std::set<Control> set1(list1.begin(), list1.end());
    std::set<Control> set2(list2.begin(), list2.end());

    std::vector<Control> unionResult;
    std::vector<Control> intersectionResult;
    
    // Union of the two sets
    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(),
                   std::back_inserter(unionResult));
    
    // Intersection of the two sets
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                          std::back_inserter(intersectionResult));
    
    std::cout << "\nUnion of controls (unique controls from both lists):\n";
    printControls(unionResult);

    std::cout << "\nIntersection of controls (common controls between lists):\n";
    printControls(intersectionResult);
}

int main() {
    std::vector<Control> controls1 = {
        {1, "button", "visible"},
        {2, "slider", "invisible"},
        {3, "button", "disabled"},
        {5, "slider", "visible"},
        {7, "button", "disabled"}
    };

    std::vector<Control> controls2 = {
        {2, "slider", "visible"},
        {3, "button", "invisible"},
        {4, "slider", "disabled"},
        {6, "button", "visible"},
        {7, "slider", "disabled"}
    };

    int choice;
    while (true) {
        std::cout << "\nChoose an operation:\n";
        std::cout << "1. Sort controls by ID using std::sort\n";
        std::cout << "2. Sort controls by ID using std::stable_sort\n";
        std::cout << "3. Perform binary search by ID (using std::lower_bound and std::upper_bound)\n";
        std::cout << "4. Merge two sorted control lists\n";
        std::cout << "5. In-place merge two segments of the control list\n";
        std::cout << "6. Perform set operations (union and intersection) between two lists\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::vector<Control> tempControls = controls1;  // To not modify the original
                sortControlsById(tempControls);
                break;
            }
            case 2: {
                std::vector<Control> tempControls = controls1;
                stableSortControlsById(tempControls);
                break;
            }
            case 3: {
                int id;
                std::cout << "Enter ID to search for: ";
                std::cin >> id;
                binarySearchById(controls1, id);
                break;
            }
            case 4: {
                std::vector<Control> tempControls1 = controls1;
                std::vector<Control> tempControls2 = controls2;
                mergeControlLists(tempControls1, tempControls2);
                break;
            }
            case 5: {
                inplaceMergeControls(controls1, controls2); // Updated for two separate lists
                break;
            }
            case 6: {
                setOperations(controls1, controls2);
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
