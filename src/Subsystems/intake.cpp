#include "vex.h"

using namespace vex;

bool intakeSpinning = false;



void StartIntake() {
    intakeSpinning = true;
    intake.spin(forward);
}

void StopIntake() {
    intakeSpinning = false;
    intake.stop();
}

// Toggle intake between spinning and not spinning
void ToggleIntake() {
    intakeSpinning = !intakeSpinning;
    if(intakeSpinning) StartIntake();
    else StopIntake();
}



// Initialize intake at the start of the program
void InitIntake() {
    intake.setVelocity(100, percent);
}

// Initialize intake at the start of driver control
void UserInitIntake() {
    // Controls
    PrimaryController.ButtonRight.pressed(ToggleIntake);
}

// Update intake during driver control
void TickIntake() {

}