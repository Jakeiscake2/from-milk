#include "main.h"
#include "autonFunctions.hpp"
#include "autons.hpp"
#include "global.hpp"
#include "lvglImage.hpp"
#include "misc.hpp"
#include "opFunctions.hpp"
#include "subsystems.hpp"
using namespace pros;

int selectedAuton = 0;
std::string selectedAutonName = "Red Ringside AWP";
void (*autonArray[5])() = {redRingSideAwp, redMogoRush, blueRingSideAwp, blueMogoRush, skills};
std::string autonNames[5] = {"Red Ringside AWP", "Red Mogo Rush", "Blue Ringside AWP", "Blue Mogo Rush", "Skills"};

void addAuton() {
    selectedAuton++;
    if (selectedAuton > 4) {
        selectedAuton = 0;
    }
    selectedAutonName = autonNames[selectedAuton];
    line = 2;
    displayToScreen(selectedAutonName);
}

void initialize() {
    lcd::initialize();
    displayToScreen("Initialize");
    arm.set_brake_mode(MOTOR_BRAKE_HOLD);
    arm.tare_position();
    lcd::set_text(line++, "Auton Tester");
    pros::lcd::register_btn1_cb(addAuton);
}

void disabled() {
    controls.set_text(0, 0, "Disabled");
    resetScreen();
    displayToScreen("Disabled");
    gyro.reset();
    checkUnplugged();
}

void autonomous() {
    placeImage();
    lcd::set_text(line++, "Auton");
    (*autonArray[selectedAuton])();
    //blueMogoRush();
}

void opcontrol() {
    runIntakeTask = false;
    controls.set_text(0, 0, "mogo NOT active");
    // Task debuggingTask(debugFunc);

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
            arm.move(-30);
        }

        checkUnplugged();
        resetScreen();
        delay(20);
    }
}