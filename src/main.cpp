#include "main.h"
#include "autonFunctions.hpp"
#include "global.hpp"
#include "lvglImage.hpp"
#include "misc.hpp"
#include "opFunctions.hpp"
#include "subsystems.hpp"
using namespace pros;

void initialize() {
    lcd::initialize();
    displayToScreen("Initialize");
    arm.set_brake_mode(MOTOR_BRAKE_HOLD);
    arm.tare_position();
}

void disabled() {
    line = 0;
    displayToScreen("Disabled");
    gyro.reset();
    checkUnplugged(line);
    // pickAuton(selectedAuton);
    placeImage();
}

void autonomous() {
    displayToScreen("Auton");
    controls.set_text(0, 0, "v1");
    gyro.set_rotation(0);
    curX = +55;
    curY = -15;
    redSide = true;
    sweeperPiston.set_value(true);
    armPiston.set_value(true);
    armControl(ARM_ALLIANCE_ANGLE);
    delay(700);
    sweeperPiston.set_value(false);
    driveForward(8);
    turnToAngle(60);
    armControl(ARM_WALL_ANGLE);
    delay(200);
    driveForward(-34, true);
    armControl(ARM_UP_ANGLE);
    Task intakeTask(intakeRingDetection);
    // turnToAngle(180);
    // driveForward(22);
    moveTo(24, -48);
    turnToAngle(270);
    driveForward(12);
    turnToAngle(305);
    driveForward(6);
    driveForward(-6);
    turnToAngle(15);
    driveForward(38);
    rightDriveMotors.move(60);
}

void opcontrol() {
    runIntakeTask = false;
    controls.set_text(0, 0, "mogo NOT active");
    // Task debuggingTask(debugFunc);
    // driveForward(24);
    bool disableArm = false;
    while (true) {
        leftDriveMotors.move(controls.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + controls.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        rightDriveMotors.move(controls.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - controls.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

        armOpControl(armAngle);
        intakeOpControl();
        pneumaticsOpControl();

        if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            disableArm = !disableArm;
            if (!disableArm) {
                arm.tare_position();
            }
        }

        if (disableArm) {
            arm.move(-20);
        }

        if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            driveForward(-24);
        }

        checkUnplugged(line);
        line = 0;
        delay(20);
    }
}