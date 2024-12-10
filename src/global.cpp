#include "global.hpp"
using namespace pros;

Controller controls(E_CONTROLLER_MASTER);

MotorGroup leftDriveMotors({-18, -19, -20}, pros::v5::MotorGears::blue, MotorUnits::degrees);
MotorGroup rightDriveMotors({8, 9, 10}, pros::v5::MotorGears::blue, MotorUnits::degrees);

Motor bottomIntake(-16, pros::v5::MotorGears::green, MotorUnits::degrees);
Motor topIntake(-11, pros::v5::MotorGears::green, MotorUnits::degrees);
Motor arm(-2, pros::v5::MotorGears::red, MotorUnits::degrees);

Imu gyro(7);
Optical optical(15);

pros::adi::DigitalOut sweeperPiston('A');
pros::adi::DigitalOut mogoPiston('C');
pros::adi::DigitalOut armPiston('D');

float curX = 0, curY = 0;
bool redSide = true;
int armAngle = ARM_HOLD_ANGLE;
int line = 0;
bool runIntakeTask = false;