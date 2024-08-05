#ifndef DUAL_INERTIAL_H
#define DUAL_INERTIAL_H

#include "v5.h"
#include "v5_vcs.h"

class DualInertial {
    private:
        vex::inertial mInertialA;
        vex::inertial mInertialB;

    public:
        DualInertial(vex::inertial inertialA, vex::inertial inertialB) :
            mInertialA(inertialA),
            mInertialB(inertialB) {}
        
        void Calibrate();

        double GetRotation();
        double GetHeading();
        bool GetCalibrating();
};

#endif