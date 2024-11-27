#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>

enum class EventType {
    Tap,
    Swipe
};

// Event class to represent a touchscreen event
class Event {
public:
    Event(EventType type, int x, int y, std::string timestamp)
        : eventType(type), xCoord(x), yCoord(y), timestamp(timestamp) {}

    EventType getEventType() const { return eventType; }
    int getX() const { return xCoord; }
    int getY() const { return yCoord; }
    std::string getTimestamp() const { return timestamp; }

private:
    EventType eventType;
    int xCoord;
    int yCoord;
    std::string timestamp;
};

// Function to get the current timestamp in "HH:MM:SS" format
std::string getCurrentTime() {
    using namespace std::chrono;
    
    // Get the current system time with high precision
    auto now = high_resolution_clock::now();
    auto time_point = system_clock::to_time_t(now);
    
    // Convert to tm struct
    std::tm* tm_ptr = std::localtime(&time_point);
    
    // Create a string stream to format the time
    std::stringstream ss;
    ss << std::put_time(tm_ptr, "%H:%M:%S");
    
    return ss.str();
}

// Function to simulate the generation of random events
Event generateRandomEvent() {
    // Randomly decide whether it's a Tap or Swipe
    EventType type = (rand() % 2 == 0) ? EventType::Tap : EventType::Swipe;

    // Randomly generate coordinates (assuming screen size 800x600)
    int x = rand() % 800;
    int y = rand() % 600;

    // Get the current timestamp
    std::string timestamp = getCurrentTime();
    
    return Event(type, x, y, timestamp);
}

// Function to process the Tap event
void handleTapEvent(const Event& event) {
    std::cout << "Tap event detected at position (" << event.getX() << ", " << event.getY() << ") at time " << event.getTimestamp() << std::endl;
}

// Function to process the Swipe event
void handleSwipeEvent(const Event& event) {
    // For swipe, we assume there is some direction calculation based on consecutive events
    // In this simulation, we will generate a random direction for simplicity.
    const char* directions[] = {"Up", "Down", "Left", "Right"};
    int dir = rand() % 4;

    std::cout << "Swipe event detected in direction: " << directions[dir] << " at position (" 
              << event.getX() << ", " << event.getY() << ") at time " << event.getTimestamp() << std::endl;
}

int main() {
    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    // Event queue
    std::queue<Event> eventQueue;

    // Simulate event generation and processing
    const int numEvents = 10; // Generate 10 random events

    // Generate random events and enqueue them
    for (int i = 0; i < numEvents; ++i) {
        eventQueue.push(generateRandomEvent());

        // Small delay to simulate real-time event generation
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Delay for 100 milliseconds
    }

    // Process the events in the queue
    while (!eventQueue.empty()) {
        Event currentEvent = eventQueue.front();
        eventQueue.pop();

        // Handle the event based on its type
        if (currentEvent.getEventType() == EventType::Tap) {
            handleTapEvent(currentEvent);
        } else if (currentEvent.getEventType() == EventType::Swipe) {
            handleSwipeEvent(currentEvent);
        }
    }

    return 0;
}
