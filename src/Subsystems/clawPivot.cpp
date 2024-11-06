#include "vex.h"

#include "Subsystems/clawPivot.h"

using namespace vex;

void ResetClawPivot() {
    clawPivot.setMaxTorque(60, percent);
    clawPivot.setStopping(coast);
    clawPivot.setVelocity(40, percent);

    clawPivot.spin(forward);
    wait(3.5, seconds);

    clawPivot.stop();
    clawPivot.setPosition(0, degrees);

    InitClawPivot();
}


// Initialize claw pivot at the start of the program
void InitClawPivot() {
    // Don't let claw fall down when not being actively moved
    clawPivot.setStopping(hold);

    clawPivot.setMaxTorque(100, percent);

    clawPivot.setVelocity(50, percent);
}

// Initialize claw pivot at the start of driver control
void UserInitClawPivot() {
    // Controls
    PrimaryController.ButtonR1.pressed([](){clawPivot.spin(forward);});
    PrimaryController.ButtonR2.pressed([](){clawPivot.spin(reverse);});
    PrimaryController.ButtonR1.released([](){clawPivot.stop();});
    PrimaryController.ButtonR2.released([](){clawPivot.stop();});

    PrimaryController.ButtonA.released(ResetClawPivot);
}

// Update claw pivot during driver control
void TickClawPivot() {
    
}