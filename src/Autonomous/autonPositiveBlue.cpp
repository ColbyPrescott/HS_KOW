#include "vex.h"

#include "Backend/utilityMath.h"

#include "Autonomous/autonSequences.h"

using namespace vex;

void AutonPositiveBlue() {
    aps.SetMirrored(true);
    AutonPositiveRed();
}