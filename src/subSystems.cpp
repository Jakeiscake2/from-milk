/* Subsystem managment
* Designed for the managment of subsystems like the intake or the arm.
* For use by user control and autonomus routines
* Last Updated on 17/12/2024
*
*/

#include "subsystems.hpp"
#include "api.h"
#include "global.hpp"

void intakeControl(std::string intakeState) {
    if (intakeState == "INTAKE") {
        bottomIntake.move(127);
        topIntake.move(127);
    } else if (intakeState == "EXTAKE") {
        bottomIntake.move(-127);
        topIntake.move(-127);
    } else if (intakeState == "REDIRECT") {
        bottomIntake.move(127);
        topIntake.move(-127);
    } else if (intakeState == "STOP") {
        bottomIntake.move(0);
        topIntake.move(0);
    }
}

void armControl(int armAngle) {
    if (armAngle < arm.get_position()) {
        arm.move_absolute(armAngle, 127);
    } else {
        arm.move_absolute(armAngle, -127);
    }
}
