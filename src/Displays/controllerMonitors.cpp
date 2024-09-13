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

    // Intake temperature
    int intakeTemp = (int)intake.temperature(percent) / 10;

    // APS
    double apsX = aps.GetX();
    double apsY = aps.GetY();
    double rotation = RadiansToDegrees(aps.GetRotation());

    // Intake
    double intakePos = intake.position(degrees);

    // Draw to screen
    PrimaryController.Screen.clearScreen();
    PrimaryController.Screen.setCursor(1, 1);
    PrimaryController.Screen.print("%d--%d  %d", leftWheelsPrimaryTemp, rightWheelsPrimaryTemp, intakeTemp); PrimaryController.Screen.newLine();
    PrimaryController.Screen.print("%d--%d  %d", leftWheelsSecondaryTemp, rightWheelsSecondaryTemp, (int)rotation); PrimaryController.Screen.newLine();
    // PrimaryController.Screen.print("%s  %s", mogoMoverStatus.c_str());
    PrimaryController.Screen.print("%.1f, %.1f, %.0f", apsX, apsY, intakePos);
}