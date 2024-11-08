#include "vex.h"

#include "Backend/utilityMath.h"

using namespace vex;

void AutonPositiveRed() {
    // aps.SetPosition(14, 48);
    // aps.SetRotation(270);
    // storingRing = true;
    
    // aps.SetDriving(true);

    // aps.AddPathPoint(8, 72, true, 0.2, 0.3, 3, DegreesToRadians(0));
    // aps.EndPath();

    // TriggerIntake();
}

// void AutonPositiveRed() {
//     aps.SetPosition(12, 48);
//     aps.SetRotation(DegreesToRadians(180));
//     storingRing = true;
//     mogoMover.open();

//     aps.SetDriving(true);

//     // Drive to mogo
//     aps.AddPathPoint(24, 36, true, 0.3, 0.3, 10);
//     aps.AddPathPoint(48, 48, true, 0.3, 0.3, 4);
//     aps.EndPath();
//     // Pickup mogo
//     mogoMover.close();
//     // Deposit preload onto mogo
//     TriggerIntake();

//     // Drive to second ring
//     aps.AddPathPoint(48, 24, false, 0.3, 0.3, 1);
//     aps.EndPath();

//     // Pick up and deposit second ring
//     TriggerIntake();
// }