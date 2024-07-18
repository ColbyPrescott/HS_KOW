#include "vex.h"

#include "Subsystems/drivetrain.h"
#include "Subsystems/mogoMover.h"
#include "Subsystems/intakeConveyor.h"
#include "Subsystems/intakeProp.h"

#include "Displays/controllerMonitors.h"

using namespace vex;

void pre_auton(void) {
    InitDrivetrain();
    InitMogoMover();
    InitIntakeConveyor();
    InitIntakeProp();
}

void autonomous(void) {
    
}

void usercontrol(void) {
    UserInitDrivetrain();
    UserInitMogoMover();
    UserInitIntakeConveyor();
    UserInitIntakeProp();

    while(true) {
        TickDrivetrain();
        TickMogoMover();
        TickIntakeConveyor();
        TickIntakeProp();
        
        wait(20, msec);
    }
}

int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while(true) {

        DrawControllerMonitors();

        wait(100, msec);
    }
}
