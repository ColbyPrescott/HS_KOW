#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"
#include "Subsystems/neutralFlip.h"

using namespace vex;

/* APC Save data:

[{"p0":{"x":13.5,"y":96},"p1":{"x":10.5,"y":96},"p2":{"x":16.59,"y":95.06},"p3":{"x":19.96,"y":99.21},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":19.96,"y":99.21},"p1":{"x":23.33,"y":103.36},"p2":{"x":29.39,"y":107.15},"p3":{"x":34.13,"y":106.57},"startSpeed":-40,"endSpeed":-50,"code":""},{"p0":{"x":34.13,"y":106.57},"p1":{"x":38.87,"y":105.99},"p2":{"x":45.7,"y":98.57},"p3":{"x":45.33,"y":98.36},"startSpeed":-50,"endSpeed":-30,"code":"ExtendNeutralFlip();\nmogoMover.close();\nTriggerAutoHooks();"},{"p0":{"x":45.33,"y":98.36},"p1":{"x":44.96,"y":98.15},"p2":{"x":41.16,"y":100.61},"p3":{"x":41.96,"y":107.74},"startSpeed":60,"endSpeed":60,"code":""},{"p0":{"x":41.96,"y":107.74},"p1":{"x":42.76,"y":114.87},"p2":{"x":48.75,"y":124.04},"p3":{"x":49.16,"y":123.93},"startSpeed":60,"endSpeed":30,"code":"TriggerAutoHooks();"},{"p0":{"x":49.16,"y":123.93},"p1":{"x":49.57,"y":123.82},"p2":{"x":44.64,"y":115.41},"p3":{"x":43.45,"y":107.48},"startSpeed":-40,"endSpeed":-60,"code":""},{"p0":{"x":43.45,"y":107.48},"p1":{"x":42.26,"y":99.55},"p2":{"x":48.21,"y":91.9},"p3":{"x":55.96,"y":85.64},"startSpeed":-40,"endSpeed":-60,"code":""}]

*/

void AutonNegativeRed() {
    // Manual
    storingRing = true;
    mogoMover.open();

    // Generated with APC
    aps.SetPosition(13.5, 96);
    aps.SetRotation(3.141592653589793);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 96, 10.5, 96, 16.59, 95.06, 19.96, 99.21, -40, -40);
    aps.AddPathSection(19.96, 99.21, 23.33, 103.36, 29.39, 107.15, 34.13, 106.57, -40, -50);
    aps.AddPathSection(34.13, 106.57, 38.87, 105.99, 45.7, 98.57, 45.33, 98.36, -50, -30);
    aps.EndPath();
    ExtendNeutralFlip();
    mogoMover.close();
    TriggerAutoHooks();
    aps.AddPathSection(45.33, 98.36, 44.96, 98.15, 41.16, 100.61, 41.96, 107.74, 60, 60);
    aps.AddPathSection(41.96, 107.74, 42.76, 114.87, 48.75, 124.04, 49.16, 123.93, 60, 30);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(49.16, 123.93, 49.57, 123.82, 44.64, 115.41, 43.45, 107.48, -40, -60);
    aps.AddPathSection(43.45, 107.48, 42.26, 99.55, 48.21, 91.9, 55.96, 85.64, -40, -60);
    aps.EndPath();
}