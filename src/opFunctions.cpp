#include "opFunctions.hpp"
#include "api.h"
#include "global.hpp"
#include "misc.hpp"
#include "subsystems.hpp"

int nextRedirect = pros::millis();

void intakeOpControl() {
    line = 0;

    optical.set_led_pwm(0);
    std::string intakeState = "STOP";
    if (controls.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intakeState = "INTAKE";
    } else if (controls.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        intakeState = "EXTAKE";
    } else if (controls.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        optical.set_led_pwm(70);
        armControl(ARM_HOLD_ANGLE);
        if (optical.get_proximity() < 200) {
            intakeState = "REDIRECT";
            if (pros::millis() >= nextRedirect) {
                nextRedirect = pros::c::millis() + 200;
            } else {
                intakeState = "INTAKE";
            }
        }
    }
    if (pros::millis() <= nextRedirect) {
        intakeState = "REDIRECT";
    }
    intakeControl(intakeState);
}

void armOpControl(int &armAngle) {
    if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        if (armAngle == ARM_WALL_ANGLE) {
            armAngle = ARM_ALLIANCE_ANGLE;
        } else {
            armAngle = ARM_WALL_ANGLE;
        }
    } else if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        if (armAngle == ARM_WALL_ANGLE) {
            armAngle = ARM_UP_ANGLE;
        } else {
            armAngle = ARM_WALL_ANGLE;
        }
    }
    armControl(armAngle);
}

bool armState = false, mogoState = false, sweeperState = false;
void pneumaticsOpControl() {
    if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        armState = !armState;
        armPiston.set_value(armState);
    }

    if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        mogoState = !mogoState;
        mogoPiston.set_value(mogoState);
        if (mogoState) {
            controls.set_text(0, 0, "mogo active");
        } else {
            controls.set_text(0, 0, "Mogo NOT active");
        }
    }

    if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        sweeperState = !sweeperState;
        sweeperPiston.set_value(sweeperState);
    }
}