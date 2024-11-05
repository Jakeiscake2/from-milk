#ifndef _PNEUMATIC_CLASS_
#define _PNEUMATIC_CLASS_

#include "pros\adi.hpp"

struct Pneumatic {
public:
    explicit Pneumatic(std::uint8_t portLetter);

    std::uint8_t portLetter;
    pros::ADIDigitalOut piston = pros::ADIDigitalOut(portLetter);
    bool pistonActivated = false;

    void setValue(bool value) {
        piston.set_value(value);
        pistonActivated = value;
    }

    void switchPiston() {
        piston.set_value(pistonActivated);
        pistonActivated = !pistonActivated;
    }

    bool get_state() {
        return pistonActivated;
    }
};

#endif