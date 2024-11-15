#include "vex.h"

#include "Backend/utilityMath.h"

#include "Autonomous/autonSequences.h"

using namespace vex;

void AutonNegativeBlue() {
    aps.SetMirrored(true);
    AutonNegativeRed();
}