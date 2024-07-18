#include "vex.h"

using namespace vex;

bool intakePropState = false;

void ToggleIntakeProp() {
    intakePropState = !intakePropState;
    intakeProp.set(intakePropState);
}

void InitIntakeProp() {
    // intakeProp.open(); // Activate piston. Currently needs to be rewired opposite
}

void UserInitIntakeProp() {
    PrimaryController.ButtonR2.pressed(ToggleIntakeProp);
}

void TickIntakeProp() {

}