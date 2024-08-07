#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include <math.h>
#include <cmath>

// fmod but negative numbers will wrap around to positive range
inline double FixedFMod(double a, double b) {
    return fmod(a + b * std::fabs(floor(a / b)), b);
}

// Convert degrees to radians
inline double DegreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// Convert radians to degrees
inline double RadiansToDegrees(double radians) {
    return radians * 180.0 / M_PI;
}

#endif