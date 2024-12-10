#pragma once
#include "api.h"

#define ARM_ALLIANCE_ANGLE 520
#define ARM_UP_ANGLE 600
#define ARM_HANG_ANGLE 750
#define ARM_HOLD_ANGLE 90
#define ARM_WALL_ANGLE 300

#define INTAKE_DELAY 1000
#define EXTAKE_DELAY 400
#define REDIRECT_DELAY 1000

extern pros::Controller controls;

extern pros::MotorGroup leftDriveMotors;
extern pros::MotorGroup rightDriveMotors;

extern pros::Motor bottomIntake;
extern pros::Motor topIntake;
extern pros::Motor arm;

extern pros::Imu gyro;
extern pros::Optical optical;

extern pros::adi::DigitalOut sweeperPiston;
extern pros::adi::DigitalOut mogoPiston;
extern pros::adi::DigitalOut armPiston;

extern float curX, curY;
extern bool redSide;
extern int armAngle;
extern int line;
extern bool runIntakeTask;