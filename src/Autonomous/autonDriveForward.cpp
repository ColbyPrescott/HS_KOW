#include "vex.h"

using namespace vex;

void AutonDriveForward() {
    basicDrive.driveFor(8, inches, 100, rpm, true);
}