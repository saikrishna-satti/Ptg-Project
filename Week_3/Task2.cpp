#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <algorithm>  

// VehicleData class stores and updates the data for speed, fuel, and temperature
class VehicleData {
public:
    int speed;
    int fuel;
    int temperature;
   
    VehicleData() : speed(0), fuel(100), temperature(80) {}

    // Update the vehicle data: speed, fuel, and temperature
    void update() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> speedDist(0, 120);  // Random speed between 0 and 120 km/h
        std::uniform_int_distribution<> fuelDist(-2, 0);     // Random fuel change (-2 to 0)
        std::uniform_int_distribution<> tempDist(-2, 2);     // Random temperature change (-2 to 2)

        // Update the vehicle data
        speed = speedDist(gen);
        fuel += fuelDist(gen);
        fuel = std::max(0, fuel);  // Ensure fuel is not less than 0
        temperature += tempDist(gen);

        
        
    }
};

// Function to display the vehicle data in real-time
void displayData(VehicleData& data, std::mutex& dataMutex) {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(dataMutex);  // Lock the data to safely access it
            std::cout << "\033[2J\033[1;1H";  // Clear the console screen (ANSI escape sequence)

            // Display the current vehicle data
            std::cout << "Speed: " << data.speed << " km/h\n";
            std::cout << "Fuel: " << data.fuel << "%\n";
            std::cout << "Temperature: " << data.temperature << "°C\n";

            // Check for warning conditions
            if (data.fuel < 10) {
                std::cout << "Warning: Low Fuel!\n";
            }
            if (data.temperature > 100) {
                std::cout << "Warning: High Temperature!\n";
            }
             // If fuel reaches 0 and the vehicle isn't already in electric mode, switch to Electric mode
        if (data.fuel == 0 ) {
           
            std::cout << "Switched to Electric Mode!\n";  // Notify mode change
        }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second
    }
}

// Function to update the vehicle data in real-time
void updateData(VehicleData& data, std::mutex& dataMutex) {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(dataMutex);  // Lock the data to safely update it
            data.update();  // Update the data (speed, fuel, temperature)
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second
    }
}

int main() {
    VehicleData data;  // Vehicle data object to hold the speed, fuel, and temperature
    std::mutex dataMutex;  // Mutex to protect the shared data

    // Create two threads: one to update the data, one to display the data
    std::thread updateThread(updateData, std::ref(data), std::ref(dataMutex));
    std::thread displayThread(displayData, std::ref(data), std::ref(dataMutex));

    // Wait for both threads to finish (they run infinitely in this case)
    updateThread.join();
    displayThread.join();

    return 0;
}