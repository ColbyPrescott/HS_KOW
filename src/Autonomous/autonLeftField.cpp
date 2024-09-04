#include "vex.h"

#include "Subsystems/intake.h"
#include "Backend/utilityMath.h"

using namespace vex;

void AutonLeftField() {
    // aps.SetPosition(9, 96);
    // aps.SetRotation(DegreesToRadians(270));
    // storingRing = true;

    // Give drivetrain control to the APS
    aps.SetDriving(true);

    // aps.AddPathPoint(12, 65);
    // aps.AddPathPoint(9, 72);

    aps.AddPathPoint(-48, 0);
    aps.AddPathPoint(0, 0);

    aps.AddPathPoint(-48, 0, true);

    // // Wait for path to be driven
    aps.EndPath();

    TriggerIntake();
}