#include "vex.h"

#include "Subsystems/hooks.h"

using namespace vex;

void AutonPositiveRed() {
    storingRing = true;
    mogoMover.open();

    aps.SetPosition(13.5, 48);
    aps.SetRotation(3.141592653589793);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 48, 10.5, 48, 19.29, 42.76, 35.52, 38.02, -40, -50);
    aps.AddPathSection(35.52, 38.02, 51.75, 33.28, 52.58, 27.08, 57.74, 24.9, -50, -50);
    aps.AddPathSection(57.74, 24.9, 62.9, 22.72, 67.12, 23.55, 66.71, 23.46, -50, -30);
    aps.EndPath();
    mogoMover.close();
    aps.AddPathSection(66.71, 23.46, 66.3, 23.37, 35.09, 23.08, 34.59, 23.38, 40, 40);
    aps.EndPath();
    // TODO Check position
    hooks.spinToPosition(0, degrees, false);
    mogoMover.open();
    aps.AddPathSection(34.59, 23.38, 34.09, 23.68, 32.81, 36.47, 36.58, 39.23, -40, -40);
    aps.AddPathSection(36.58, 39.23, 40.35, 41.99, 45.26, 46.37, 45.93, 46.28, -40, -40);
    aps.EndPath();
    mogoMover.close();
    TriggerAutoHooks();
    mogoMover.open();
    aps.AddPathSection(45.93, 46.28, 48.9, 45.88, 8.49, 53.01, 7.9, 64.89, 40, 40);
    aps.AddPathSection(7.9, 64.89, 7.31, 76.77, 31.65, 71.63, 32.05, 71.83, 40, 40);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(32.05, 71.83, 32.45, 72.03, 9.78, 71.63, 9.95, 71.83, -40, -20);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(9.95, 71.83, 10.12, 72.03, 25.77, 86.89, 32.11, 94.22, 40, 40);
    aps.AddPathSection(32.11, 94.22, 38.45, 101.55, 47.27, 120.3, 47.7, 120.74, 50, 40);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(47.7, 120.74, 48.13, 121.18, 48.57, 104.79, 48.2, 98.31, -40, -40);
    aps.EndPath();
}