#include "misc.hpp"

void displayToScreen(std::string text) {
    pros::lcd::set_text(line++, text.c_str());
}

void resetScreen() {
    line = 0;
}

void checkUnplugged(int &line) {
    if (leftDriveMotors.get_temperature() > 100) {
        displayToScreen("frontLeft MOTOR UNPLUGGED");
    }
    if (rightDriveMotors.get_temperature() > 100) {
        displayToScreen("frontRight MOTOR UNPLUGGED");
    }
    if (topIntake.get_temperature() > 100) {
        displayToScreen("topIntake MOTOR UNPLUGGED");
    }
    if (bottomIntake.get_temperature() > 100) {
        displayToScreen("bottomIntake MOTOR UNPLUGGED");
    }
    if (arm.get_temperature() > 100) {
        displayToScreen("arm MOTOR UNPLUGGED");
    }
}

float getAvg(std::vector<double> vals) {
    float sum = 0;
    for (float f : vals) {
        sum += f;
    }
    return sum / (vals.size() + 0.0);
}

float reduce0To360(float angle) {
    while (!(angle >= 0 && angle < 360)) {
        if (angle < 0) {
            angle += 360;
        }
        if (angle >= 360) {
            angle -= 360;
        }
    }
    return (angle);
}

float reduce180To180(float angle) {
    while (!(angle >= -180 && angle <= 180)) {
        if (angle <= -180) {
            angle += 360;
        }
        if (angle >= 180) {
            angle -= 360;
        }
    }
    return (angle);
}

float sgn(float val) {
    if (val > 0) {
        return 1.0;
    }
    if (val < 0) {
        return -1.0;
    }
    return 0.0;
}

void debugFunc(void *param) {
    while (true) {
        displayToScreen("MS " + std::to_string(leftDriveMotors.get_actual_velocity() + rightDriveMotors.get_actual_velocity() / 2));
        controls.set_text(0, 0, ("MS " + std::to_string(leftDriveMotors.get_actual_velocity() + rightDriveMotors.get_actual_velocity() / 2)).c_str());
        pros::delay(20);
    }
}