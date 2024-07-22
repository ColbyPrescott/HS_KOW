#include "vex.h"

using namespace vex;

// Quick settings
// Speed for the intake conveyor motors, 0 - 1
const double intakeConveyorSpeed = 0.8;


// Variables needed for system functionality
// Direction of the intake conveyor motors. -1 is backwards, 0 is stopped, and 1 is forwards
int intakeConveyorDirection = 0;


// Initialize intake conveyor at the start of the program
void InitIntakeConveyor() {
    // Controls
    // Start or stop intake conveyor moving forwards when the up arrow button is pressed
    PrimaryController.ButtonUp.pressed([](){
        // If already moving forwards, stop
        if(intakeConveyorDirection == 1) {intakeConveyor.stop(); intakeConveyorDirection = 0;}
        // If stopped or moving backwards, spin forwards
        else {intakeConveyor.spin(forward, fmin(fmax(intakeConveyorSpeed * 12, -12), 12), volt); intakeConveyorDirection = 1;}
    });

    // Start or stop intake conveyor moving backwards when the down arrow button is pressed
    PrimaryController.ButtonDown.pressed([](){
        // If already moving backwards, stop
        if(intakeConveyorDirection == -1) {intakeConveyor.stop(); intakeConveyorDirection = 0;}
        // If stopped or moving forwards, spin backwards
        else {intakeConveyor.spin(reverse, fmin(fmax(intakeConveyorSpeed * 12, -12), 12), volt); intakeConveyorDirection = -1;}
    });

    // TEST Slow down intake conveyor when the left arrow button is pressed
    PrimaryController.ButtonLeft.pressed([](){
        if(intakeConveyorDirection == 1) intakeConveyor.spin(forward, fmin(fmax(intakeConveyorSpeed * 0.5 * 12, -12), 12), volt);
        if(intakeConveyorDirection == -1) intakeConveyor.spin(reverse, fmin(fmax(intakeConveyorSpeed * 0.5 * 12, -12), 12), volt);
    });
}

// Initialize intake conveyor at the start of driver control
void UserInitIntakeConveyor() {

}

// Update intake conveyor during driver control
void TickIntakeConveyor() {
    
}