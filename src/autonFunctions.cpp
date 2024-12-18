#include "autonFunctions.hpp"
#include "api.h"
#include "global.hpp"
#include "subsystems.hpp"

struct PIDclass drivePID(10, 1, 1.2, 0.7, 200);
struct PIDclass turnPID(7, 0, 0.6, 2, 200);

void intakeRingDetection(void *param) {
    optical.set_led_pwm(70);

    runIntakeTask = true;
    while (runIntakeTask) {
        if (redSide) {
            if (optical.get_proximity() < 200 && optical.get_hue() > 50) { // blue ring detected
                intakeControl("REDIRECT");
                controls.set_text(0, 0, "BLUE");
            } else {
                intakeControl("INTAKE");
            }
        } else {
            if (optical.get_proximity() < 200 && optical.get_hue() < 20) { // blue ring detected
                intakeControl("REDIRECT");
                controls.set_text(0, 0, "RED");
            } else {
                intakeControl("INTAKE");
            }
        }
    }

    displayToScreen(("Proximity (0-255): " + std::to_string(optical.get_proximity())).c_str());
    displayToScreen(("Hue (0-360): " + std::to_string(optical.get_hue())).c_str());
    displayToScreen(("Red Ring?" + std::to_string(redSide)).c_str());
    resetScreen();
    pros::delay(100);
}
