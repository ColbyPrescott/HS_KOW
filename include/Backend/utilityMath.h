#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include <math.h>
#include <cmath>

// fmod but negative numbers will wrap around to positive range
inline double FixedFMod(double a, double b) {
    return fmod(a + b * std::fabs(floor(a / b)), b);
}

// Set n to min or max if it is smaller or larger respectively
inline double Clamp(double n, double min, double max) {
    return fmin(fmax(n, min), max);
}

// Convert degrees to radians
inline double DegreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// Convert radians to degrees
inline double RadiansToDegrees(double radians) {
    return radians * 180.0 / M_PI;
}

// Smallest distance from one heading to another, including sign for direction
inline double DifferenceBetweenHeadings(double radiansA, double radiansB) {
    return FixedFMod(radiansB - radiansA + M_PI, M_PI * 2.0) - M_PI;
}

inline double MirrorX(double x) {
    return 144.0 - x;
}

#endif