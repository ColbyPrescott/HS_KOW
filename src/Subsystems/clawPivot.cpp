#include "vex.h"

using namespace vex;

// Initialize claw pivot at the start of the program
void InitClawPivot() {
    // Don't let claw fall down when not being actively moved
    clawPivot.setStopping(hold);

    clawPivot.setMaxTorque(100, percent);

    clawPivot.setVelocity(20, percent);
}

// Initialize claw pivot at the start of driver control
void UserInitClawPivot() {
    // Controls
    PrimaryController.ButtonR1.pressed([](){clawPivot.spin(forward);});
    PrimaryController.ButtonR2.pressed([](){clawPivot.spin(reverse);});
    PrimaryController.ButtonR1.released([](){clawPivot.stop();});
    PrimaryController.ButtonR2.released([](){clawPivot.stop();});
}

// Update claw pivot during driver control
void TickClawPivot() {
    
}