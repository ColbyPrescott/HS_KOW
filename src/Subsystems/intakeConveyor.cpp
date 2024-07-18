#include "vex.h"

using namespace vex;

const double intakeConveyorSpeed = 0.8;

int intakeConveyorDirection = 0;

void InitIntakeConveyor() {
    PrimaryController.ButtonUp.pressed([](){
        // If already moving forwards, stop
        if(intakeConveyorDirection == 1) {intakeConveyor.stop(); intakeConveyorDirection = 0;}
        // If stopped or moving backwards, spin forwards
        else {intakeConveyor.spin(forward, fmin(fmax(intakeConveyorSpeed * 12, -12), 12), volt); intakeConveyorDirection = 1;}
    });

    PrimaryController.ButtonDown.pressed([](){
        // If already moving backwards, stop
        if(intakeConveyorDirection == -1) {intakeConveyor.stop(); intakeConveyorDirection = 0;}
        // If stopped or moving forwards, spin backwards
        else {intakeConveyor.spin(reverse, fmin(fmax(intakeConveyorSpeed * 12, -12), 12), volt); intakeConveyorDirection = -1;}
    });
    PrimaryController.ButtonLeft.pressed([](){
        if(intakeConveyorDirection == 1) intakeConveyor.spin(forward, fmin(fmax(intakeConveyorSpeed * 0.5 * 12, -12), 12), volt);
        if(intakeConveyorDirection == -1) intakeConveyor.spin(reverse, fmin(fmax(intakeConveyorSpeed * 0.5 * 12, -12), 12), volt);
    });
}

void UserInitIntakeConveyor() {

}

void TickIntakeConveyor() {
    
}