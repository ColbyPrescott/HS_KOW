#ifndef VEX_H
#define VEX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "Backend/inertialIntercept.h"
#include "Backend/dualInertial.h"
#include "Backend/absolutePositioningSystem.h"
#include "KOWGUI/kowgui.h"
#include "robotConfig.h"

#define waitUntil(condition)                                                   \
    do {                                                                       \
        wait(5, msec);                                                         \
    } while (!(condition))

#define repeat(iterations)                                                     \
    for (int iterator = 0; iterator < iterations; iterator++)

#endif