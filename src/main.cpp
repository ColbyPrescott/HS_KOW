#include "vex.h"

#include "Subsystems/drivetrain.h"
#include "Subsystems/mogoMover.h"
#include "Subsystems/intakeConveyor.h"

#include "Displays/controllerMonitors.h"

using namespace vex;

// Called at program start
void pre_auton(void) {
    // Call the program initialization of each subsystem
    InitDrivetrain();
    InitMogoMover();
    InitIntakeConveyor();
}

// Called at start of autonomous
void autonomous(void) {
    
}

// Called at start of driver control
void usercontrol(void) {
    // Call the driver initialization of each subsytem
    UserInitDrivetrain();
    UserInitMogoMover();
    UserInitIntakeConveyor();

    // Update each subsystem continuously during driver control
    while(true) {
        TickDrivetrain();
        TickMogoMover();
        TickIntakeConveyor();
        
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

        // Draw important information to the controller screen for easy monitoring
        DrawControllerMonitors();

        wait(100, msec);
    }
}
