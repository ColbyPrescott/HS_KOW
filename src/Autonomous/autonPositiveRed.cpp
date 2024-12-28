#include "vex.h"

#include "Backend/utilityMath.h"

using namespace vex;

void AutonPositiveRed() {
    // 1 Set up robot in bottom left of field facing into west wall
    aps.SetPosition(0, 0);
    aps.SetRotation(DegreesToRadians(0));

    // 1 Give drivetrain control to the APS
    aps.SetDriving(true);

    // 2 Drive off the starting line
    aps.AddPathPoint(1*tiles, 0*tiles, true, 0.3, 0.3, 2);
    aps.EndPath();
}