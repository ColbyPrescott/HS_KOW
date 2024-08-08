#include "vex.h"

#include "Backend/utilityMath.h"

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

    // Calibrate inertial sensor
    dualInertial.Calibrate();
    while(dualInertial.GetCalibrating()) wait(0.2, seconds);
    PrimaryController.rumble(".");

    // Start APS
    aps.StartTracking(200);

    PrimaryController.ButtonX.pressed([](){
        static int logNum = -1;
        logNum++;

        printf("%.3f, %d, %d, %.2f\n", Brain.Timer.system() / 1000.0, 360 * 5 * logNum, (int)RadiansToDegrees(dualInertial.GetRotation()), dualInertial.GetTemperature());
    });
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

        // Plot APS to screen
        const double scale = 0.95;
        Brain.Screen.setPenColor(white);
        Brain.Screen.drawPixel(480.0 / 2.0 + aps.GetX() * scale, 
                                240.0 / 2.0 - aps.GetY() * scale);

        wait(100, msec);
    }
}
