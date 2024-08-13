#include "vex.h"

#include <string>
#include "Backend/utilityMath.h"

using namespace vex;

// Draw important information that is useful to monitor to the controller screen
void DrawControllerMonitors() {
    // Drivetrain temperatures
    int leftWheelsPrimaryTemp = (int)leftWheelsPrimary.temperature(percent) / 10;
    int leftWheelsSecondaryTemp = (int)leftWheelsSecondary.temperature(percent) / 10;
    int rightWheelsPrimaryTemp = (int)rightWheelsPrimary.temperature(percent) / 10;
    int rightWheelsSecondaryTemp = (int)rightWheelsSecondary.temperature(percent) / 10;

    // Mobile goal mover
    std::string mogoMoverStatus = mogoMover.value() == 0 ? "HOLD" : "____";

    // Inertial sensor
    double heading = RadiansToDegrees(dualInertial.GetRotation());
    double inertialTemp = dualInertial.GetTemperature();

    // APS
    double apsX = aps.GetX();
    double apsY = aps.GetY();

    // Draw to screen
    PrimaryController.Screen.clearScreen();
    PrimaryController.Screen.setCursor(1, 1);
    PrimaryController.Screen.print("%d--%d  %.0f", leftWheelsPrimaryTemp, rightWheelsPrimaryTemp, heading); PrimaryController.Screen.newLine();
    PrimaryController.Screen.print("%d--%d  %.2f", leftWheelsSecondaryTemp, rightWheelsSecondaryTemp, inertialTemp); PrimaryController.Screen.newLine();
    // PrimaryController.Screen.print("%s  %s", mogoMoverStatus.c_str());
    PrimaryController.Screen.print("%.1f, %.1f", apsX, apsY);
}