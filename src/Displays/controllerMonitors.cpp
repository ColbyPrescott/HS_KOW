#include "vex.h"

#include <string>
#include "Backend/utilityMath.h"

using namespace vex;

// Draw important information that is useful to monitor to the controller screen
void DrawControllerMonitors() {
    // Drivetrain temperatures 0 to 10
    int leftWheelsPrimaryTemp = (int)leftWheelsPrimary.temperature(percent) / 10;
    int leftWheelsSecondaryTemp = (int)leftWheelsSecondary.temperature(percent) / 10;
    int rightWheelsPrimaryTemp = (int)rightWheelsPrimary.temperature(percent) / 10;
    int rightWheelsSecondaryTemp = (int)rightWheelsSecondary.temperature(percent) / 10;

    // Hooks temperature 0 to 10
    int hooksTemp = (int)hooks.temperature(percent) / 10;

    // Lift temperatures 0 to 10
    int leftLiftTemp = (int)leftLift.temperature(percent) / 10;
    int rightLiftTemp = (int)rightLift.temperature(percent) / 10;

    // Claw temperature 0 to 10
    int clawPivotTemp = (int)clawPivot.temperature(percent) / 10;

    // Claw temperature 0 to 10
    int clawTemp = (int)claw.temperature(percent) / 10;

    // State of whether or not the mogo mover is holding a mogo
    std::string mogoMoverStatus = mogoMover.value() == 0 ? "HOLD" : "____";

    // Draw to screen
    PrimaryController.Screen.clearScreen();
    PrimaryController.Screen.setCursor(1, 1);
    PrimaryController.Screen.print("%d--%d   %d--%d", leftWheelsPrimaryTemp, rightWheelsPrimaryTemp, leftLiftTemp, rightLiftTemp); PrimaryController.Screen.newLine();
    PrimaryController.Screen.print("%d--%d   %d  %d", leftWheelsSecondaryTemp, rightWheelsSecondaryTemp, clawPivotTemp, clawTemp); PrimaryController.Screen.newLine();
    PrimaryController.Screen.print("%s, %d", mogoMoverStatus.c_str(), hooksTemp);
}