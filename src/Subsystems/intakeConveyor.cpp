#include "vex.h"

using namespace vex;

const double intakeConveyorSpeed = 0.5;

bool intakeConveyorDirection = 0;

void InitIntakeConveyor() {
    PrimaryController.ButtonUp.pressed([](){
        // If already moving forwards, stop
        if(intakeConveyorDirection == 1) {intakeConveyor.stop(); intakeConveyorDirection = 0;}
        // If stopped or moving backwards, spin forwards
        else {intakeConveyor.spin(forward, fmin(fmax(intakeConveyorDirection * 12, -12), 12), volt); intakeConveyorDirection = 1;}
    });

    PrimaryController.ButtonDown.pressed([](){
        // If already moving backwards, stop
        if(intakeConveyorDirection == -1) {intakeConveyor.stop(); intakeConveyorDirection = 0;}
        // If stopped or moving forwards, spin backwards
        else {intakeConveyor.spin(forward, fmin(fmax(-intakeConveyorDirection * 12, -12), 12), volt); intakeConveyorDirection = -1;}
    });
}

void UserInitIntakeConveyor() {

}

void TickIntakeConveyor() {
    
}