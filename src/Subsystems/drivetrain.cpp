#include "vex.h"

using namespace vex;

// Quick settings
// Drivetrain motor speed going forwards and backwards, 0 - 1
const double driveSpeed = 1;
// Drivetrain motor speed turning left and right, 0 - 1
const double turnSpeed = 0.5;
// Value that controller joystick axes must exceed to avoid being considered joystick drift, 0 - 1
const double driftThreshold = 0.08;


// Initialize drivetrain at the start of the program
void InitDrivetrain() {

}

// Initialize drivetrain at the start of driver control
void UserInitDrivetrain() {

}

// Update drivetrain during driver control
void TickDrivetrain() {
    // Get controller input
    double forwardInput = PrimaryController.Axis3.value() / 127.0;
    double rightwardInput = PrimaryController.Axis1.value() / 127.0;

    // Nullify input if it could be drifting
    if(fabs(forwardInput) < driftThreshold) forwardInput = 0;
    if(fabs(rightwardInput) < driftThreshold) rightwardInput = 0; 

    // if(forwardInput > 0.5) forwardInput = 0.5;

    // Apply speed
    forwardInput *= driveSpeed;
    rightwardInput *= turnSpeed;

    // Increase / decrease voltage of one side to help correct drifting caused by drivetrain friction or center of mass
    double rightWheelsVoltageBias = forwardInput >= 0 ? -0.03 : 0.03;

    // Set motor velocities
    // // RPM control can't seem to drive super slowly, but the PID controller will keep the sides even better...
    // leftWheels.spin(forward, fmin(fmax((forwardInput + rightwardInput) * 200, -200), 200), rpm);
    // rightWheels.spin(forward, fmin(fmax((forwardInput - rightwardInput) * 200, -200), 200), rpm);
    // Voltage control can be slower, but torque differences on both sides will skew average without any PID controller
    leftWheels.spin(forward, fmin(fmax((forwardInput + rightwardInput) * 12, -12), 12), volt);
    rightWheels.spin(forward, fmin(fmax((forwardInput - rightwardInput + rightWheelsVoltageBias) * 12, -12), 12), volt);


    // 100 inch tests
    // 0.3   forward,      0         volts,     -10     inches
    // 0.3   forward,     -0.03      volts,     -0.75   inches
    // 0.3   forward,     -0.0301    volts,      0.5    inches
    // 0.3   forward,     -0.031     volts,      2.75   inches
    // 0.3   forward,     -0.04      volts,      3      inches
    // 0.3   forward,     -0.05      volts,      5.5    inches
    // 0.3   forward,     -0.1       volts,      50     inches 

    // 0.4   forward,     -0.03      volts,      0.5    inches
    // 0.5   forward,     -0.03      volts,      0      inches
}