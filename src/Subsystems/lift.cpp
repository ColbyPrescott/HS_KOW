#include "vex.h"

using namespace vex;

// Initialize lift at the start of the program
void InitLift() {
    lift.setStopping(hold);

    lift.setVelocity(100, percent);
}

// Initialize lift at the start of driver control
void UserInitLift() {
    // Controls
    PrimaryController.ButtonL1.pressed([](){lift.spin(forward);});
    PrimaryController.ButtonL1.released([](){lift.stop();});
    PrimaryController.ButtonL2.pressed([](){lift.spin(reverse);});
    PrimaryController.ButtonL2.released([](){lift.stop();});
}

// Update lift during driver control
void TickLift() {
    
}