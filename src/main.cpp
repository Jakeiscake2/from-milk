#include "main.h"
using namespace pros;

Controller controls(E_CONTROLLER_MASTER);

Motor frontLeft(18, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor midLeft(19, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor backLeft(20, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
MotorGroup leftMotors({frontLeft, midLeft, backLeft});

Motor frontRight(8, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor midRight(9, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor backRight(10, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
MotorGroup rightMotors({frontRight, midRight, backRight});

Motor bottomIntake(16, E_MOTOR_GEAR_GREEN, true, E_MOTOR_ENCODER_DEGREES);
Motor topIntake(11, E_MOTOR_GEAR_GREEN, true, E_MOTOR_ENCODER_DEGREES);
Motor arm(1, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);

ADIDigitalOut sweeper('A');
ADIDigitalOut hang('B');
ADIDigitalOut mogoMech('C');
ADIDigitalOut armPiston('D');

Imu gyro(20);

void initialize() {
    lcd::initialize();
    lcd::set_text(1, "Initialize");
    arm.tare_position();
}

void disabled() {
    lcd::set_text(1, "Disabled");
}

void autonomous() {
    lcd::set_text(1, "Autonomous");
}

void opcontrol() {
    lcd::initialize();
    // lcd::set_text(1, "Opcontrol");
    controls.set_text(0, 0, "Opcontrol");
    arm.set_brake_mode(MOTOR_BRAKE_HOLD);

    arm.tare_position();
    // gyro.reset();

    bool mogoActive = false, hangActive = false, armActive = false, sweeperActive = false, armPistonActive = false;
    while (true) {
        // drive control
        leftMotors.move(controls.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + controls.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        rightMotors.move(controls.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - controls.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

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
                arm.move_absolute(500, -127);
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
            armPistonActive = !armPistonActive;
            armPiston.set_value(armPistonActive);
        }

        // mogo control
        if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            mogoActive = !mogoActive;
            mogoMech.set_value(mogoActive);
        }

        // hang control
        if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            hangActive = !hangActive;
            hang.set_value(hangActive);
        }

        // sweeper or doinker
        if (controls.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            sweeperActive = !sweeperActive;
            sweeper.set_value(sweeperActive);
        }

        delay(20);
    }
}
