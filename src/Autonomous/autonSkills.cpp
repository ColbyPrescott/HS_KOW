#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"

using namespace vex;

/* APC Save data:

[{"p0":{"x":13.5,"y":72},"p1":{"x":10.5,"y":72},"p2":{"x":27.3,"y":78.84},"p3":{"x":30.08,"y":72.3},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":30.08,"y":72.3},"p1":{"x":32.86,"y":65.76},"p2":{"x":23.47,"y":57.34},"p3":{"x":23.7,"y":49.21},"startSpeed":-40,"endSpeed":-30,"code":"mogoMover.close();\nTriggerAutoHooks();"},{"p0":{"x":23.7,"y":49.21},"p1":{"x":23.78,"y":46.21},"p2":{"x":27.11,"y":31.62},"p3":{"x":36.83,"y":26.27},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":36.83,"y":26.27},"p1":{"x":46.55,"y":20.92},"p2":{"x":74.29,"y":17.45},"p3":{"x":74.29,"y":17.45},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":74.29,"y":17.45},"p1":{"x":74.29,"y":17.45},"p2":{"x":45.19,"y":9.34},"p3":{"x":29.72,"y":9.54},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":29.72,"y":9.54},"p1":{"x":14.25,"y":9.74},"p2":{"x":6.54,"y":24.03},"p3":{"x":13.09,"y":33.75},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":13.09,"y":33.75},"p1":{"x":19.64,"y":43.47},"p2":{"x":34.73,"y":40.31},"p3":{"x":34.34,"y":39.52},"startSpeed":40,"endSpeed":30,"code":"TriggerAutoHooks();"},{"p0":{"x":34.34,"y":39.52},"p1":{"x":33.95,"y":38.73},"p2":{"x":10,"y":10},"p3":{"x":10,"y":10},"startSpeed":-40,"endSpeed":-30,"code":"mogoMover.open();"},{"p0":{"x":10,"y":10},"p1":{"x":10,"y":10},"p2":{"x":27.81,"y":69},"p3":{"x":30.98,"y":77.73},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":30.98,"y":77.73},"p1":{"x":34.15,"y":86.46},"p2":{"x":52.93,"y":102.73},"p3":{"x":53.65,"y":102.85},"startSpeed":40,"endSpeed":30,"code":"TriggerAutoHooks();"},{"p0":{"x":53.65,"y":102.85},"p1":{"x":54.37,"y":102.97},"p2":{"x":51.78,"y":90.97},"p3":{"x":44.24,"y":87.2},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":44.24,"y":87.2},"p1":{"x":36.7,"y":83.43},"p2":{"x":25.76,"y":94.37},"p3":{"x":25.09,"y":94.69},"startSpeed":-40,"endSpeed":-30,"code":"mogoMover.close();\nTriggerAutoHooks();"},{"p0":{"x":25.09,"y":94.69},"p1":{"x":24.42,"y":95.01},"p2":{"x":50.3,"y":82.81},"p3":{"x":28.8,"y":79.17},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":28.8,"y":79.17},"p1":{"x":7.3,"y":75.53},"p2":{"x":10.58,"y":109.77},"p3":{"x":11.68,"y":117.44},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":11.68,"y":117.44},"p1":{"x":12.78,"y":125.11},"p2":{"x":14.3,"y":131.75},"p3":{"x":23.43,"y":131.74},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":23.43,"y":131.74},"p1":{"x":32.56,"y":131.73},"p2":{"x":42.32,"y":101.32},"p3":{"x":42.26,"y":101.1},"startSpeed":40,"endSpeed":30,"code":"TriggerAutoHooks();"},{"p0":{"x":42.26,"y":101.1},"p1":{"x":42.2,"y":100.88},"p2":{"x":10.02,"y":133.98},"p3":{"x":10,"y":134},"startSpeed":-40,"endSpeed":-30,"code":"mogoMover.open();"},{"p0":{"x":10,"y":134},"p1":{"x":7.88,"y":136.12},"p2":{"x":26.42,"y":115.79},"p3":{"x":27.87,"y":111.77},"startSpeed":40,"endSpeed":40,"code":""}]

*/

void AutonSkills() {
    // Manual
    storingRing = true;
    mogoMover.open();

    // Generated with APC
    aps.SetPosition(13.5, 72);
    aps.SetRotation(3.141592653589793);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 72, 10.5, 72, 27.3, 78.84, 30.08, 72.3, -40, -40);
    aps.AddPathSection(30.08, 72.3, 32.86, 65.76, 23.47, 57.34, 23.7, 49.21, -40, -30);
    aps.EndPath();
    mogoMover.close();
    // ExtendNeutralFlip();
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
    // RetractNeutralFlip();
}