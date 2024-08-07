#ifndef INERTIAL_INTERCEPT_H
#define INERTIAL_INTERCEPT_H

#include "v5.h"
#include "v5_vcs.h"

// Class that will publicly expose the vex::inertial::temperature() protected function as GetTemperature()
class InertialIntercept : protected vex::inertial {
    private:
        // The inertial sensor gains error the further away it is from 0 degrees. Multiply the raw rotation by this bias to correct for that
        double mBias = 1.0;

    public:
        // Bias is calculated with a 18000 degree test.
        // 1. Preheat sensor for 8 - 10 minutes or until its temperature is close to resting temperature, 44.25 degrees Celsius
        // 2. Align robot with a line on the ground.
        // 3. Recalibrate sensor.
        // 4. Rotate the robot for 50 revolutions, 18000 degrees.
        // 5. Align the robot back with the line on the ground.
        // 6. Note the current measured angle that may be different from 18000 degrees.
        // 7. Bias is equal to 18000 divided by the measured angle.
        InertialIntercept(int32_t index, vex::turnType dir = vex::turnType::right, double bias = 1.0) :
            vex::inertial(index, dir),
            mBias(bias) {}

        void Calibrate();

        double GetRotation();
        double GetHeading();
        bool GetInstalled();
        bool GetCalibrating();
        double GetTemperature();
};

#endif