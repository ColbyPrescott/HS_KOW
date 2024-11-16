#include "vex.h"

#include "Backend/utilityMath.h"

using namespace vex;

void AutonPositiveRed() {
    // 1 Set up robot in top left of field facing into west wall
    aps.SetPosition(0, 0);
    aps.SetRotation(DegreesToRadians(0));

    // 1 Give drivetrain control to the APS
    aps.SetDriving(true);
    // 1 Move claw and arm off of the wheels, slowly so it also doesn't hit the field wall before starting to drive
    arm.spinToPosition(100, degrees, 250, rpm, false);
    clawPivot.spinToPosition(-200, degrees, 100, rpm, false);

    // 2 Drive off the starting line
    aps.AddPathPoint(1*tiles, 0*tiles, true, 0.3, 0.3, 2);
    aps.EndPath();
}