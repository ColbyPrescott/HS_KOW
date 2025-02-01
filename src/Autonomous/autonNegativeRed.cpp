#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"
#include "Subsystems/neutralFlip.h"

using namespace vex;

/* APC Save data:

[{"p0":{"x":13.5,"y":96},"p1":{"x":10.5,"y":96},"p2":{"x":16.59,"y":95.26},"p3":{"x":19.96,"y":99.21},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":19.96,"y":99.21},"p1":{"x":23.33,"y":103.16},"p2":{"x":29.39,"y":106.76},"p3":{"x":34.13,"y":106.57},"startSpeed":-40,"endSpeed":-50,"code":""},{"p0":{"x":34.13,"y":106.57},"p1":{"x":38.87,"y":106.38},"p2":{"x":45.7,"y":98.57},"p3":{"x":45.33,"y":98.36},"startSpeed":-50,"endSpeed":-30,"code":"ExtendNeutralFlip();\nmogoMover.close();\nTriggerAutoHooks();"},{"p0":{"x":45.33,"y":98.36},"p1":{"x":44.96,"y":98.15},"p2":{"x":43.74,"y":101.6},"p3":{"x":45.14,"y":108.73},"startSpeed":60,"endSpeed":60,"code":""},{"p0":{"x":45.14,"y":108.73},"p1":{"x":46.54,"y":115.86},"p2":{"x":47.76,"y":123.47},"p3":{"x":48.17,"y":123.36},"startSpeed":60,"endSpeed":30,"code":"TriggerAutoHooks();\nRetractNeutralFlip();"},{"p0":{"x":48.17,"y":123.36},"p1":{"x":48.58,"y":123.25},"p2":{"x":43.61,"y":105.54},"p3":{"x":43.61,"y":105.54},"startSpeed":-40,"endSpeed":-60,"code":""},{"p0":{"x":43.61,"y":105.54},"p1":{"x":43.61,"y":105.54},"p2":{"x":38.3,"y":93.02},"p3":{"x":37.89,"y":92.62},"startSpeed":-60,"endSpeed":-30,"code":""},{"p0":{"x":37.89,"y":92.62},"p1":{"x":37.48,"y":92.22},"p2":{"x":47.42,"y":96.07},"p3":{"x":54.57,"y":88.22},"startSpeed":40,"endSpeed":60,"code":""}]

*/

void AutonNegativeRed() {
    // Manual
    storingRing = true;
    mogoMover.open();

    // Generated with APC
    aps.SetPosition(13.5, 96);
    aps.SetRotation(3.141592653589793);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 96, 10.5, 96, 16.59, 95.26, 19.96, 99.21, -40, -40);
    aps.AddPathSection(19.96, 99.21, 23.33, 103.16, 29.39, 106.76, 34.13, 106.57, -40, -50);
    aps.AddPathSection(34.13, 106.57, 38.87, 106.38, 45.7, 98.57, 45.33, 98.36, -50, -30);
    aps.EndPath();
    ExtendNeutralFlip();
    mogoMover.close();
    TriggerAutoHooks();
    aps.AddPathSection(45.33, 98.36, 44.96, 98.15, 43.74, 101.6, 45.14, 108.73, 60, 60);
    aps.AddPathSection(45.14, 108.73, 46.54, 115.86, 47.76, 123.47, 48.17, 123.36, 60, 30);
    aps.EndPath();
    TriggerAutoHooks();
    RetractNeutralFlip();
    aps.AddPathSection(48.17, 123.36, 48.58, 123.25, 43.61, 105.54, 43.61, 105.54, -40, -60);
    aps.AddPathSection(43.61, 105.54, 43.61, 105.54, 38.3, 93.02, 37.89, 92.62, -60, -30);
    aps.AddPathSection(37.89, 92.62, 37.48, 92.22, 47.42, 96.07, 54.57, 88.22, 40, 60);
    aps.EndPath();
}