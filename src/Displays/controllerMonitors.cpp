#include "vex.h"

#include "Subsystems/intakeConveyor.h"

#include <string>

using namespace vex;

void DrawControllerMonitors() {
    // Drivetrain temperatures
    int leftWheelsPrimaryTemp = (int)leftWheelsPrimary.temperature(percent) / 10;
    int leftWheelsSecondaryTemp = (int)leftWheelsSecondary.temperature(percent) / 10;
    int rightWheelsPrimaryTemp = (int)rightWheelsPrimary.temperature(percent) / 10;
    int rightWheelsSecondaryTemp = (int)rightWheelsSecondary.temperature(percent) / 10;

    // Mobile goal mover
    std::string mogoMoverStatus = mogoMover.value() == 0 ? "____" : "HOLD";

    // Intake / conveyor
    std::string intakeConveyorStatus = intakeConveyorDirection == 0 ? "___" : (intakeConveyorDirection == 1 ? "IN " : "OUT");

    // Draw to screen
    PrimaryController.Screen.clearScreen();
    PrimaryController.Screen.setCursor(1, 1);
    PrimaryController.Screen.print("%d--%d", leftWheelsPrimaryTemp, rightWheelsPrimaryTemp); PrimaryController.Screen.newLine();
    PrimaryController.Screen.print("%d--%d", leftWheelsSecondaryTemp, rightWheelsSecondaryTemp); PrimaryController.Screen.newLine();
    PrimaryController.Screen.print("%s  %s", mogoMoverStatus.c_str(), intakeConveyorStatus.c_str());
}