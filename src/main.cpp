#include "main.h"
#include "Pneumatic.hpp"
using namespace pros;

#define logToConsole(header, msg) printf("%s %lu: %s\n", std::string(header).c_str(), millis(), std::string(msg).c_str());
#define logToConsole(header) printf("%s %lu \n", std::string(header).c_str(), millis());

#define ARM_UP_ANGLE 500

Controller controls(E_CONTROLLER_MASTER);

MotorGroup leftDriveMotors({18, 19, 20}, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
MotorGroup rightDriveMotors({8, 9, 10}, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);

Motor bottomIntake(16, E_MOTOR_GEAR_GREEN, true, E_MOTOR_ENCODER_DEGREES);
Motor topIntake(11, E_MOTOR_GEAR_GREEN, true, E_MOTOR_ENCODER_DEGREES);
Motor arm(1, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);

Pneumatic sweeperPiston('A');
Pneumatic hangPiston('B');
Pneumatic mogoPiston('C');
Pneumatic armPiston('D');

Imu gyro(20);

void initialize() {
    lcd::initialize();
    lcd::set_text(1, "Initialize");
    logToConsole("Initialize");
    arm.tare_position();
}

void disabled() {
    lcd::set_text(1, "Disabled");
    logToConsole("Disabled");
}

void autonomous() {
    lcd::set_text(1, "Autonomous");
    logToConsole("Autonomous");
}

void opcontrol() {
    lcd::initialize();
    // lcd::set_text(1, "Opcontrol");
    controls.set_text(0, 0, "Opcontrol");
    logToConsole("Opcontrol");
    arm.set_brake_mode(MOTOR_BRAKE_HOLD);

    arm.tare_position();
    // gyro.reset();

    bool armActive = false;
    while (true) {
        // drive control
        leftDriveMotors.move(controls.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + controls.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        rightDriveMotors.move(controls.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - controls.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

        if (controls.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            // intake
            bottomIntake.move(127);
            topIntake.move(127);
        } else if (controls.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            // extake
            bottomIntake.move(-127);
            topIntake.move(-127);
        } else if (controls.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
            // redirect
            bottomIntake.move(127);
            topIntake.move(-10);
        } else {
            // nothing
            bottomIntake.brake();
            topIntake.brake();
        }

        // arm control
        if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
            if (armActive) {
                arm.move_absolute(0, 127);
            } else if (!armActive) {
                arm.move_absolute(ARM_UP_ANGLE, -127);
            }
            armActive = !armActive;
        }

        lcd::set_text(2, std::to_string(arm.get_position()));

        if (controls.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            arm.move(127);
        } else if (controls.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            arm.move(-127);
        }

        if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            armPiston.switchPiston();
        }

        // mogo control
        if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            mogoPiston.switchPiston();
        }

        // hang control
        if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            hangPiston.switchPiston();
        }

        // sweeper or doinker
        if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            sweeperPiston.switchPiston();
        }
        delay(20);
    }
}