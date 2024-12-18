#pragma once
#include "api.h"
#include "global.hpp"
#include "misc.hpp"

#define LOOP_DELAY 0.03
#define DEGREE_TO_INCH (3.25 * M_PI * 48) / (36.0 * 600)

struct PIDclass {
    float prevError = 0, prevIntegral = 0;
    float kP, kI, kD;
    float settleError = 0;
    int settledTime, timeToSettle;
    int maxSpeed = 127;
    PIDclass(float setKP, float setKI, float setKD, float setSettleError, int setTimeToSettle) {
        kP = setKP;
        kI = setKI;
        kD = setKD;
        settleError = setSettleError;
        timeToSettle = setTimeToSettle;
    }
    PIDclass(float setKP, float setKI, float setKD, float setSettleError, int setTimeToSettle, int tempMaxSpeed) {
        kP = setKP;
        kI = setKI;
        kD = setKD;
        settleError = setSettleError;
        timeToSettle = setTimeToSettle;
        maxSpeed = tempMaxSpeed;
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
    void driveForward(int moveVal, bool activateMogo = false) {
        settledTime = 0;
        prevError = 0;
        prevIntegral = 0;
        float error;
        float curVal = (leftDriveMotors.get_position() + rightDriveMotors.get_position()) * DEGREE_TO_INCH / 2;
        float targetVal = curVal + moveVal;
        float motorVal;
        long startTime = pros::c::millis();
        while (settledTime <= timeToSettle) {
            if (pros::c::millis() - startTime > 3000) {
                break;
            }
            curVal = (leftDriveMotors.get_position() + rightDriveMotors.get_position()) * DEGREE_TO_INCH / 2;
            error = targetVal - curVal;
            motorVal = pidCompute(error);

            if (abs(moveVal) > maxSpeed) {
                moveVal = sgn(moveVal) * maxSpeed;
            }

            controls.set_text(0, 0, (std::to_string(error) + " " + std::to_string(motorVal)).c_str());

            leftDriveMotors.move(motorVal);
            rightDriveMotors.move(motorVal);

            if (activateMogo && fabs(error) < 10) {
                sweeperPiston.set_value(false);
            }

            if (activateMogo && fabs(error) < 2) {
                mogoPiston.set_value(true);
            }

            if (fabs(error) < settleError) {
                settledTime += LOOP_DELAY * 1000;
            } else {
                settledTime = 0;
            }
            pros::delay(LOOP_DELAY * 1000);
        }
    }
    void turnBy(int turnVal) {
        settledTime = 0;
        prevError = 0;
        prevIntegral = 0;
        float error, motorVal;
        float curVal = gyro.get_rotation();
        float targetVal = reduce180To180(turnVal + curVal);
        long startTime = pros::c::millis();
        while (settledTime <= timeToSettle) {
            if (pros::c::millis() - startTime > 3000) {
                break;
            }
            curVal = gyro.get_rotation();
            error = targetVal - curVal;
            error = reduce180To180(targetVal - curVal);
            controls.set_text(0, 0, std::to_string(error).c_str());
            motorVal = pidCompute(error);
            leftDriveMotors.move(motorVal);
            rightDriveMotors.move(-motorVal);
            if (fabs(error) < settleError) {
                settledTime += LOOP_DELAY * 1000;
            } else {
                settledTime = 0;
            }
            pros::delay(LOOP_DELAY * 1000);
        }
    }
    void turnToAngle(int angle) {
        turnBy(reduce180To180(angle - reduce0To360(gyro.get_rotation())));
    }
};

extern PIDclass drivePID;
extern PIDclass turnPID;

extern void intakeRingDetection(void *keepIntaking);
