#include "vex.h"

#include <string>

using namespace vex;

void DrawControllerMonitors() {
    // Drivetrain temperatures
    int leftWheelsPrimaryTemp = (int)leftWheelsPrimary.temperature(percent) / 10;
    int leftWheelsSecondaryTemp = (int)leftWheelsSecondary.temperature(percent) / 10;
    int rightWheelsPrimaryTemp = (int)rightWheelsPrimary.temperature(percent) / 10;
    int rightWheelsSecondaryTemp = (int)rightWheelsSecondary.temperature(percent) / 10;

    // Mobile goal mover
    std::string mogoMoverStatus = mogoMover.value() == 1 ? "HOLD" : "____";

    // Draw to screen
    PrimaryController.Screen.clearScreen();
    PrimaryController.Screen.setCursor(1, 1);
    PrimaryController.Screen.print("%d--%d", leftWheelsPrimaryTemp, rightWheelsPrimaryTemp); PrimaryController.Screen.newLine();
    PrimaryController.Screen.print("%d--%d", leftWheelsSecondaryTemp, rightWheelsSecondaryTemp); PrimaryController.Screen.newLine();
    PrimaryController.Screen.print("%s", mogoMoverStatus.c_str());
}