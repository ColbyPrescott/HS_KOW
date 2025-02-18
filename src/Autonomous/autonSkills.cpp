#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"

using namespace vex;

void AutonSkills() {
    storingRing = true;
    mogoMover.open();

    aps.SetPosition(13.5, 72);
    aps.SetRotation(3.141592653589793);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 72, 10.5, 72, 27.3, 78.84, 30.08, 72.3, -40, -40);
    aps.AddPathSection(30.08, 72.3, 32.86, 65.76, 23.47, 57.34, 23.7, 49.21, -40, -30);
    aps.EndPath();
    mogoMover.close();
    TriggerAutoHooks();
    aps.AddPathSection(23.7, 49.21, 23.78, 46.21, 27.11, 31.62, 36.83, 26.27, -40, -40);
    aps.AddPathSection(36.83, 26.27, 46.55, 20.92, 74.29, 17.45, 74.29, 17.45, -40, -40);
    aps.AddPathSection(74.29, 17.45, 74.29, 17.45, 45.19, 9.34, 29.72, 9.54, 40, 40);
    aps.AddPathSection(29.72, 9.54, 14.25, 9.74, 6.54, 24.03, 13.09, 33.75, 40, 40);
    aps.AddPathSection(13.09, 33.75, 19.64, 43.47, 34.73, 40.31, 34.34, 39.52, 40, 30);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(34.34, 39.52, 33.95, 38.73, 10, 10, 10, 10, -40, -30);
    aps.EndPath();
    mogoMover.open();
    aps.AddPathSection(10, 10, 10, 10, 27.81, 69, 30.98, 77.73, 40, 40);
    aps.AddPathSection(30.98, 77.73, 34.15, 86.46, 52.93, 102.73, 53.65, 102.85, 40, 30);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(53.65, 102.85, 54.37, 102.97, 51.78, 90.97, 44.24, 87.2, -40, -40);
    aps.AddPathSection(44.24, 87.2, 36.7, 83.43, 25.76, 94.37, 25.09, 94.69, -40, -30);
    aps.EndPath();
    mogoMover.close();
    TriggerAutoHooks();
    aps.AddPathSection(25.09, 94.69, 24.42, 95.01, 50.3, 82.81, 28.8, 79.17, 40, 40);
    aps.AddPathSection(28.8, 79.17, 7.3, 75.53, 10.58, 109.77, 11.68, 117.44, 40, 40);
    aps.AddPathSection(11.68, 117.44, 12.78, 125.11, 14.3, 131.75, 23.43, 131.74, 40, 40);
    aps.AddPathSection(23.43, 131.74, 32.56, 131.73, 42.32, 101.32, 42.26, 101.1, 40, 30);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(42.26, 101.1, 42.2, 100.88, 10.02, 133.98, 10, 134, -40, -30);
    aps.EndPath();
    mogoMover.open();
    aps.AddPathSection(10, 134, 7.88, 136.12, 26.42, 115.79, 27.87, 111.77, 40, 40);
    aps.EndPath();
}