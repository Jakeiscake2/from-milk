#include "autonFunctions.hpp"
#include "api.h"
#include "global.hpp"
#include "subsystems.hpp"

struct PIDclass drivePID(10, 0.00001, 1, 0.3, 300);
struct PIDclass turnPID(9, 0, 0.3, 1, 300);

void driveForward(float distance, bool activateMogo) {
    PIDclass tempPID = drivePID;
    float error, targetVal = ((leftDriveMotors.get_position() + rightDriveMotors.get_position()) * DEGREETOINCH / 2) + distance;
    float motorVal;
    long startTime = pros::c::millis();
    while (tempPID.settledTime <= tempPID.timeToSettle) {
        if (pros::c::millis() - startTime > 5000) {
            break;
        }

        error = targetVal - (leftDriveMotors.get_position() + rightDriveMotors.get_position()) * DEGREETOINCH / 2;

        controls.set_text(0, 0, ("err " + std::to_string(error)).c_str());

        motorVal = tempPID.pidCompute(error);
        if (motorVal < 5) {
            motorVal = 5;
        }
        leftDriveMotors.move(motorVal);
        rightDriveMotors.move(motorVal);

        if (activateMogo && fabs(error) < 2) {
            mogoPiston.set_value(true);
        }

        if (fabs(error) < tempPID.settleError) {
            tempPID.settledTime += LOOP_DELAY * 1000;
        } else {
            tempPID.settledTime = 0;
        }
        pros::delay(LOOP_DELAY * 1000);
    }
}

void turnBy(float turnVal) {
    PIDclass tempPID = turnPID;
    float targetVal = reduce0To360(gyro.get_rotation() + turnVal), error = targetVal - gyro.get_rotation();
    float motorVal;
    long startTime = pros::c::millis();
    while (tempPID.settledTime <= tempPID.timeToSettle) {
        if (pros::c::millis() - startTime > 10000) {
            break;
        }

        error = targetVal - gyro.get_rotation();
        motorVal = tempPID.pidCompute(error);
        leftDriveMotors.move(motorVal);
        rightDriveMotors.move(-motorVal);

        if (fabs(error) < tempPID.settleError) {
            tempPID.settledTime += LOOP_DELAY * 1000;
        } else {
            tempPID.settledTime = 0;
        }
        pros::delay(LOOP_DELAY * 1000);
    }
}

void turnToAngle(float angle) {
    turnBy(reduce180To180(angle - reduce0To360(gyro.get_rotation())));
}

void moveTo(float endX, float endY) {
    float deltaX = (endX - curX), deltaY = (endY - curY);
    float angle = atan2(deltaY, deltaX) * 180 / M_PI;
    turnToAngle(angle);
    controls.set_text(0, 0, (std::to_string(deltaX) + std::to_string(deltaY).c_str()));
    driveForward(sqrt((deltaY * deltaY) + (deltaX * deltaX)));
}

void intakeRingDetection(void *param) {
    optical.set_led_pwm(70);
    runIntakeTask = true;
    while (runIntakeTask) {
        if (optical.get_proximity() < 200) { // ring detected
            if (redSide) {
                if (optical.get_hue() < 100) { // red
                    intakeControl("INTAKE");
                } else {
                    intakeControl("REDIRECT");
                    pros::delay(200);
                }
            } else {
                if (optical.get_hue() < 15) { // blue ring detected
                    intakeControl("REDIRECT");
                    pros::delay(200);
                } else {
                    intakeControl("INTAKE");
                }
            }
        } else {
            intakeControl("INTAKE");
        }
        pros::lcd::set_text(line++, ("Proximity (0-255): " + std::to_string(optical.get_proximity())).c_str());
        pros::lcd::set_text(line++, ("Hue (0-360): " + std::to_string(optical.get_hue())).c_str());
        pros::lcd::set_text(line++, ("Red = 1, Blue = 0: " + std::to_string(redSide)).c_str());
        pros::delay(20);
    }
}
