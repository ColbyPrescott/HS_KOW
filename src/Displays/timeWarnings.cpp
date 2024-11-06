#include "vex.h"

#include "Displays/autonSelector.h"
#include "Autonomous/autonSequences.h"

using namespace vex;

// Set up events to vibrate the controller and show other indicators at specific times throughout a match
void UserInitTimeWarnings() {
    // Set up indicators for a normal 1:45 driver control match
    if(selectedAutonSequence != AutonSkills) {
        // Rumble controller in the last 20 seconds of a competition match (Multiple packets because packets have a size limit and are sometimes missed)
        Brain.Timer.event([](){PrimaryController.rumble("- - - -");}, (1 * 60 + 45 - 20) * 1000);
        Brain.Timer.event([](){PrimaryController.rumble("- - - -");}, (1 * 60 + 45 - 15) * 1000);
        Brain.Timer.event([](){PrimaryController.rumble("- - - -");}, (1 * 60 + 45 - 10) * 1000);
        Brain.Timer.event([](){PrimaryController.rumble("- - - -");}, (1 * 60 + 45 - 5 ) * 1000);
    
    // Set up indicators for a 1:00 skills match
    } else {
        // Rumble controller in the last 20 seconds of a driver skills match
        Brain.Timer.event([](){PrimaryController.rumble("- - - -");}, (1 * 60 - 20) * 1000);
        Brain.Timer.event([](){PrimaryController.rumble("- - - -");}, (1 * 60 - 15) * 1000);
        Brain.Timer.event([](){PrimaryController.rumble("- - - -");}, (1 * 60 - 10) * 1000);
        Brain.Timer.event([](){PrimaryController.rumble("- - - -");}, (1 * 60 - 5 ) * 1000);
    }
}