#ifndef DUAL_INERTIAL_H
#define DUAL_INERTIAL_H

#include "v5.h"
#include "v5_vcs.h"

// Class that will publicly expose the vex::inertial::temperature() protected function as GetTemperature()
class InertialIntercept : public vex::inertial {
    public:
        // Copy constructor
        using vex::inertial::inertial;
        double GetTemperature() {
            return temperature();
        }
};

class DualInertial {
    private:
        InertialIntercept mInertialA;
        InertialIntercept mInertialB;

        double mBiasA = 1;
        double mBiasB = 1;

    public:
        // Provide the two vex::inertial objects and an optional bias.
        // To figure out the biases, run a 18000 degree test on each sensor individually. 
        // That is, unplug one sensor, spin the robot until the working sensor reads 18000 degrees (50 revolutions), 
        // then align the robot back to the proper starting angle.
        // The bias will be equal to 18000 divided by the current sensor's reading.
        DualInertial(InertialIntercept inertialA, InertialIntercept inertialB, double biasA = 1, double biasB = 1) :
            mInertialA(inertialA),
            mInertialB(inertialB),
            mBiasA(biasA),
            mBiasB(biasB) {}
        
        void Calibrate();

        double GetRotation();
        double GetHeading();
        bool GetCalibrating();
        double GetTemperature();
};

#endif