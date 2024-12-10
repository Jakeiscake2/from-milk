#pragma once
#include "api.h"
#include "global.hpp"
#include "misc.hpp"

#define LOOP_DELAY 0.100
#define DEGREETOINCH (3.25 * M_PI * 48) / (36.0 * 600)

struct PIDclass {
    float prevError = 0, prevIntegral = 0;
    float kP, kI, kD;
    float settleError = 0;
    int settledTime, timeToSettle;
    PIDclass(float setKP, float setKI, float setKD, float setSettleError, int setTimeToSettle) {
        kP = setKP;
        kI = setKI;
        kD = setKD;
        settleError = setSettleError;
        timeToSettle = setTimeToSettle;
    }
    float pidCompute(float error) {
        if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) {
            prevIntegral = 0;
        }
        float proportional = error;
        float integral = prevIntegral + (error * LOOP_DELAY);
        float derivative = (error - prevError) / LOOP_DELAY;
        float output = (kP * proportional) + (kI * integral) + (kD * derivative);
        prevError = error;
        prevIntegral = integral;
        return output;
    }
};

extern PIDclass drivePID;
extern PIDclass turnPID;

void driveForward(float distance, bool activateMogo = false);
extern void turnToAngle(float angle);
extern void turnBy(float angle);
extern void intakeRingDetection(void *keepIntaking);
extern void moveTo(float endX, float endY);