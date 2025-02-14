#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include <math.h>
#include <cmath>

#define tiles 24

// fmod but negative numbers will wrap around to positive range
inline double FixedFMod(double a, double b) {
    return fmod(a + b * std::fabs(floor(a / b)), b);
}

// Set n to min or max if it is smaller or larger respectively
inline double Clamp(double n, double min, double max) {
    return fmin(fmax(n, min), max);
}

// Linearly interpolate between a and b by fraction t
inline double Lerp(double a, double b, double t) {
    return a + (b - a) * t;
}

// Map a value from one range to another
inline double Map(double n, double min1, double max1, double min2, double max2) {
    return (n - min1) / (max1 - min1) * (max2 - min2) + min2;
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

// Flip an X coordinate from one side of the field to the other
inline double MirrorX(double inches) {
    return 144.0 - inches;
}

// Flip an angle from one side of the field to the other
inline double MirrorHeading(double radians) {
    return M_PI - radians;
}

#endif