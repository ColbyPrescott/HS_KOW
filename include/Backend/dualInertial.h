#ifndef DUAL_INERTIAL_H
#define DUAL_INERTIAL_H

#include "Backend/inertialIntercept.h"

class DualInertial {
    private:
        InertialIntercept mInertialA;
        InertialIntercept mInertialB;

    public:
        DualInertial(InertialIntercept inertialA, InertialIntercept inertialB) :
            mInertialA(inertialA),
            mInertialB(inertialB) {}
        
        void Calibrate();

        void SetRotation(double rotation);

        double GetRotation();
        double GetHeading();
        bool GetCalibrating();
        double GetTemperature();
};

#endif