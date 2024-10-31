#include "vex.h"

using namespace vex;

// Initialize claw at the start of the program
void InitClaw() {
    // Don't let claw fall down when not being actively moved
    claw.setStopping(hold);

    claw.setMaxTorque(100, percent);

    claw.setVelocity(20, percent);
}

// Initialize claw at the start of driver control
void UserInitClaw() {
    // Controls
    PrimaryController.ButtonR1.pressed([](){claw.spin(forward);});
    PrimaryController.ButtonR2.pressed([](){claw.spin(reverse);});
    PrimaryController.ButtonR1.released([](){claw.stop();});
    PrimaryController.ButtonR2.released([](){claw.stop();});
}

// Update claw during driver control
void TickClaw() {
    
}