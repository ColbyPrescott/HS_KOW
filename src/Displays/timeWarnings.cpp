#include "vex.h"

#include "Displays/autonSelector.h"
#include "Autonomous/autonSequences.h"

using namespace vex;

// Set up events to vibrate the controller and show other indicators at specific times throughout a match
void UserInitTimeWarnings() {
    // Don't do anything if autonomous was not selected and the program is on for testing instead of competition
    if(selectedAutonSequence == nullptr) return;
    // Set up indicators for a normal 1:45 driver control match
    else if(selectedAutonSequence != AutonSkills) {
        // Rumble controller in the last 35 seconds of a competition match (Multiple packets because packets have a size limit and are sometimes missed)
        for(int offset = 5; offset <= 35; offset += 5) {
            Brain.Timer.event([](){PrimaryController.rumble("- - - -");}, (1 * 60 + 45 - offset) * 1000);
        }
    
    // Set up indicators for a 1:00 skills match
    } else {
        // Rumble controller in the last 20 seconds of a driver skills match
        for(int offset = 5; offset <= 20; offset += 5) {
            Brain.Timer.event([](){PrimaryController.rumble("- - - -");}, (1 * 60 + 0 - offset) * 1000);
        }
    }
}