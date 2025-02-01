#include "vex.h"

#include "Backend/utilityMath.h"

#include "Subsystems/hooks.h"
#include "Subsystems/neutralFlip.h"

using namespace vex;

/* APC Save data:

[{"p0":{"x":13.5,"y":72},"p1":{"x":10.5,"y":72},"p2":{"x":19.17,"y":73.68},"p3":{"x":21.95,"y":67.14},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":21.95,"y":67.14},"p1":{"x":24.73,"y":60.6},"p2":{"x":23.47,"y":57.34},"p3":{"x":23.7,"y":49.21},"startSpeed":-40,"endSpeed":-40,"code":"mogoMover.close();\nExtendNeutralFlip();\nTriggerAutoHooks();"},{"p0":{"x":23.7,"y":49.21},"p1":{"x":23.78,"y":46.21},"p2":{"x":24.14,"y":59.1},"p3":{"x":32.47,"y":58.7},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":32.47,"y":58.7},"p1":{"x":40.8,"y":58.3},"p2":{"x":45.29,"y":49.17},"p3":{"x":50.13,"y":44.98},"startSpeed":40,"endSpeed":40,"code":"TriggerAutoHooks();"},{"p0":{"x":50.13,"y":44.98},"p1":{"x":52.4,"y":43.02},"p2":{"x":66.63,"y":37.18},"p3":{"x":66.63,"y":32.22},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":66.63,"y":32.22},"p1":{"x":66.63,"y":27.26},"p2":{"x":58.25,"y":24.78},"p3":{"x":47.02,"y":25.21},"startSpeed":40,"endSpeed":40,"code":"TriggerAutoHooks();"},{"p0":{"x":47.02,"y":25.21},"p1":{"x":35.79,"y":25.64},"p2":{"x":22.36,"y":26.95},"p3":{"x":21.94,"y":26.82},"startSpeed":40,"endSpeed":40,"code":"TriggerAutoHooks();"},{"p0":{"x":21.94,"y":26.82},"p1":{"x":21.52,"y":26.69},"p2":{"x":33.21,"y":29.72},"p3":{"x":43.13,"y":20.4},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":43.13,"y":20.4},"p1":{"x":53.05,"y":11.08},"p2":{"x":57.11,"y":13.29},"p3":{"x":57.38,"y":13.15},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":57.38,"y":13.15},"p1":{"x":57.65,"y":13.01},"p2":{"x":22.23,"y":12.49},"p3":{"x":21.9,"y":12.55},"startSpeed":40,"endSpeed":40,"code":"TriggerAutoHooks();"},{"p0":{"x":21.9,"y":12.55},"p1":{"x":18.95,"y":13.09},"p2":{"x":63.6,"y":12.05},"p3":{"x":51.73,"y":31.22},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":51.73,"y":31.22},"p1":{"x":39.86,"y":50.39},"p2":{"x":17,"y":17},"p3":{"x":13,"y":13},"startSpeed":-40,"endSpeed":-40,"code":"mogoMover.open();"},{"p0":{"x":13,"y":13},"p1":{"x":10.88,"y":10.88},"p2":{"x":26.15,"y":27.06},"p3":{"x":26.35,"y":45.11},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":26.35,"y":45.11},"p1":{"x":26.55,"y":63.16},"p2":{"x":28.41,"y":69.6},"p3":{"x":30.98,"y":77.73},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":30.98,"y":77.73},"p1":{"x":33.55,"y":85.86},"p2":{"x":52.93,"y":102.73},"p3":{"x":53.65,"y":102.85},"startSpeed":40,"endSpeed":40,"code":"TriggerAutoHooks();"},{"p0":{"x":53.65,"y":102.85},"p1":{"x":54.37,"y":102.97},"p2":{"x":49.4,"y":94.14},"p3":{"x":41.86,"y":90.37},"startSpeed":-40,"endSpeed":-40,"code":""},{"p0":{"x":41.86,"y":90.37},"p1":{"x":34.32,"y":86.6},"p2":{"x":25.76,"y":94.37},"p3":{"x":25.09,"y":94.69},"startSpeed":-40,"endSpeed":-40,"code":"mogoMover.close();\nTriggerAutoHooks();"},{"p0":{"x":25.09,"y":94.69},"p1":{"x":24.42,"y":95.01},"p2":{"x":50.3,"y":82.81},"p3":{"x":28.8,"y":79.17},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":28.8,"y":79.17},"p1":{"x":7.3,"y":75.53},"p2":{"x":10.58,"y":109.77},"p3":{"x":11.68,"y":117.44},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":11.68,"y":117.44},"p1":{"x":12.78,"y":125.11},"p2":{"x":14.7,"y":128.57},"p3":{"x":23.83,"y":128.56},"startSpeed":40,"endSpeed":40,"code":""},{"p0":{"x":23.83,"y":128.56},"p1":{"x":32.96,"y":128.55},"p2":{"x":42.32,"y":101.32},"p3":{"x":42.26,"y":101.1},"startSpeed":40,"endSpeed":40,"code":"TriggerAutoHooks();"},{"p0":{"x":42.26,"y":101.1},"p1":{"x":42.2,"y":100.88},"p2":{"x":13.02,"y":130.98},"p3":{"x":13,"y":131},"startSpeed":-40,"endSpeed":-40,"code":"mogoMover.open();"},{"p0":{"x":13,"y":131},"p1":{"x":10.88,"y":133.12},"p2":{"x":26.42,"y":115.79},"p3":{"x":27.87,"y":111.77},"startSpeed":40,"endSpeed":40,"code":"RetractNeutralFlip();"}]

*/

void AutonSkills() {
    // Manual
    storingRing = true;
    mogoMover.open();

    // Generated with APC
    aps.SetPosition(13.5, 72);
    aps.SetRotation(3.141592653589793);
    aps.SetDriving(true);
    aps.AddPathSection(13.5, 72, 10.5, 72, 19.17, 73.68, 21.95, 67.14, -40, -40);
    aps.AddPathSection(21.95, 67.14, 24.73, 60.6, 23.47, 57.34, 23.7, 49.21, -40, -40);
    aps.EndPath();
    mogoMover.close();
    ExtendNeutralFlip();
    TriggerAutoHooks();
    aps.AddPathSection(23.7, 49.21, 23.78, 46.21, 24.14, 59.1, 32.47, 58.7, 40, 40);
    aps.AddPathSection(32.47, 58.7, 40.8, 58.3, 45.29, 49.17, 50.13, 44.98, 40, 40);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(50.13, 44.98, 52.4, 43.02, 66.63, 37.18, 66.63, 32.22, 40, 40);
    aps.AddPathSection(66.63, 32.22, 66.63, 27.26, 58.25, 24.78, 47.02, 25.21, 40, 40);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(47.02, 25.21, 35.79, 25.64, 22.36, 26.95, 21.94, 26.82, 40, 40);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(21.94, 26.82, 21.52, 26.69, 33.21, 29.72, 43.13, 20.4, -40, -40);
    aps.AddPathSection(43.13, 20.4, 53.05, 11.08, 57.11, 13.29, 57.38, 13.15, -40, -40);
    aps.AddPathSection(57.38, 13.15, 57.65, 13.01, 22.23, 12.49, 21.9, 12.55, 40, 40);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(21.9, 12.55, 18.95, 13.09, 63.6, 12.05, 51.73, 31.22, -40, -40);
    aps.AddPathSection(51.73, 31.22, 39.86, 50.39, 17, 17, 13, 13, -40, -40);
    aps.EndPath();
    mogoMover.open();
    aps.AddPathSection(13, 13, 10.88, 10.88, 26.15, 27.06, 26.35, 45.11, 40, 40);
    aps.AddPathSection(26.35, 45.11, 26.55, 63.16, 28.41, 69.6, 30.98, 77.73, 40, 40);
    aps.AddPathSection(30.98, 77.73, 33.55, 85.86, 52.93, 102.73, 53.65, 102.85, 40, 40);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(53.65, 102.85, 54.37, 102.97, 49.4, 94.14, 41.86, 90.37, -40, -40);
    aps.AddPathSection(41.86, 90.37, 34.32, 86.6, 25.76, 94.37, 25.09, 94.69, -40, -40);
    aps.EndPath();
    mogoMover.close();
    TriggerAutoHooks();
    aps.AddPathSection(25.09, 94.69, 24.42, 95.01, 50.3, 82.81, 28.8, 79.17, 40, 40);
    aps.AddPathSection(28.8, 79.17, 7.3, 75.53, 10.58, 109.77, 11.68, 117.44, 40, 40);
    aps.AddPathSection(11.68, 117.44, 12.78, 125.11, 14.7, 128.57, 23.83, 128.56, 40, 40);
    aps.AddPathSection(23.83, 128.56, 32.96, 128.55, 42.32, 101.32, 42.26, 101.1, 40, 40);
    aps.EndPath();
    TriggerAutoHooks();
    aps.AddPathSection(42.26, 101.1, 42.2, 100.88, 13.02, 130.98, 13, 131, -40, -40);
    aps.EndPath();
    mogoMover.open();
    aps.AddPathSection(13, 131, 10.88, 133.12, 26.42, 115.79, 27.87, 111.77, 40, 40);
    aps.EndPath();
    RetractNeutralFlip();
}