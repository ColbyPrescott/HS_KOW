#include "vex.h"

#include "Subsystems/lift.h"

using namespace vex;

void ResetLift() {
    lift.setMaxTorque(10, percent);
    lift.setStopping(coast);
    lift.setVelocity(60, percent);

    lift.spin(reverse);
    wait(3.5, seconds);

    lift.stop();
    lift.setPosition(0, degrees);

    InitLift();

    PrimaryController.rumble(".");
}



// Initialize lift at the start of the program
void InitLift() {
    lift.setStopping(hold);

    lift.setVelocity(60, percent);

    lift.setMaxTorque(100, percent);
}

// Initialize lift at the start of driver control
void UserInitLift() {
    // Controls
    PrimaryController.ButtonL1.pressed([](){lift.spin(forward);});
    PrimaryController.ButtonL1.released([](){lift.stop();});
    PrimaryController.ButtonL2.pressed([](){lift.spin(reverse);});
    PrimaryController.ButtonL2.released([](){lift.stop();});

    PrimaryController.ButtonA.released(ResetLift);
}

// Update lift during driver control
void TickLift() {
    
}