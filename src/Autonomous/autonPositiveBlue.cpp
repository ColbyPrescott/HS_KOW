#include "vex.h"

#include "Subsystems/intake.h"
#include "Backend/utilityMath.h"

using namespace vex;

void AutonPositiveBlue() {
    aps.SetPosition(MirrorX(14), 48);
    aps.SetRotation(270);
    storingRing = true;

    aps.SetDriving(true);

    aps.AddPathPoint(MirrorX(8), 72, true, 0.2, 0.3, 3, DegreesToRadians(180));
    aps.EndPath();

    TriggerIntake();
}

// void AutonPositiveBlue() {
//     aps.SetPosition(MirrorX(12), 48);
//     aps.SetRotation(DegreesToRadians(0));
//     storingRing = true;
//     mogoMover.open();

//     aps.SetDriving(true);

//     // Drive to mogo
//     aps.AddPathPoint(MirrorX(24), 36, true, 0.3, 0.3, 10);
//     aps.AddPathPoint(MirrorX(48), 48, true, 0.3, 0.3, 4);
//     aps.EndPath();
//     // Pickup mogo
//     mogoMover.close();
//     // Deposit preload onto mogo
//     TriggerIntake();

//     // Drive to second ring
//     aps.AddPathPoint(MirrorX(48), 24, false, 0.3, 0.3, 1);
//     aps.EndPath();

//     // Pick up and deposit second ring
//     TriggerIntake();
// }