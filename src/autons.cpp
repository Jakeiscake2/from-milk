#include "autons.hpp"
#include "api.h"
#include "autonFunctions.hpp"
#include "global.hpp"
#include "subsystems.hpp"

void redRingSideAwp() {
    PIDclass mogoPID(6, 1, 1, 0.8, 300);
    gyro.set_rotation(0);
    redSide = true;
    sweeperPiston.set_value(true);
    armControl(ARM_WALL_ANGLE);
    pros::delay(500);
    sweeperPiston.set_value(false);
    drivePID.driveForward(7.5);
    turnPID.turnToAngle(60);
    pros::delay(100);
    armPiston.set_value(true);
    pros::delay(500);
    mogoPID.driveForward(-40, true);
    armControl(ARM_UP_ANGLE);
    // Task intakeTask(intakeRingDetection);
    intakeControl("INTAKE");
    turnPID.turnToAngle(180);
    drivePID.driveForward(25);
    armControl(ARM_HOLD_ANGLE);
    armPiston.set_value(false);
    // moveTo(24, -48);
    turnPID.turnToAngle(270);
    drivePID.driveForward(15.2);
    drivePID.driveForward(-2);
    turnPID.turnToAngle(310);
    drivePID.driveForward(6);
    drivePID.driveForward(-6);
    turnPID.turnToAngle(0);
    rightDriveMotors.move(50);
    leftDriveMotors.move(35);
    pros::delay(500);
    armPiston.set_value(true);
}

void redMogoRush() {
    gyro.set_rotation(270);
    drivePID.driveForward(42);
    turnPID.turnToAngle(300);
    sweeperPiston.set_value(true);
    pros::delay(600);
    drivePID.driveForward(-18, true);
    intakeControl("INTAKE");
    // Task intakeTask(intakeRingDetection);
    sweeperPiston.set_value(false);
    pros::delay(700);
    mogoPiston.set_value(false);
    turnPID.turnToAngle(135);
    drivePID.driveForward(-21, true);
    turnPID.turnToAngle(70);
    drivePID.driveForward(49);
    sweeperPiston.set_value(true);
    pros::delay(400);
    leftDriveMotors.move(-60);
    rightDriveMotors.move(60);
    pros::delay(800);
    sweeperPiston.set_value(false);
    intakeControl("STOP");
    pros::delay(2000);
    leftDriveMotors.move(0);
    rightDriveMotors.move(0);
    turnPID.turnToAngle(270);
}

void blueRingSideAwp() {
    PIDclass mogoPID(6, 1, 1, 0.8, 300);
    gyro.set_rotation(0);
    redSide = false;
    sweeperPiston.set_value(true);
    armControl(ARM_WALL_ANGLE);
    pros::delay(500);
    sweeperPiston.set_value(false);
    drivePID.driveForward(7);
    turnPID.turnToAngle(300);
    drivePID.driveForward(3);
    pros::delay(100);
    armPiston.set_value(true);
    pros::delay(500);
    mogoPID.driveForward(-43, true);
    armControl(ARM_UP_ANGLE);
    // Task intakeTask(intakeRingDetection);
    intakeControl("INTAKE");
    turnPID.turnToAngle(180);
    drivePID.driveForward(25);
    armControl(ARM_HOLD_ANGLE);
    armPiston.set_value(false);
    // moveTo(24, -48);
    turnPID.turnToAngle(90);
    drivePID.driveForward(15.2);
    drivePID.driveForward(-2);
    turnPID.turnToAngle(50);
    drivePID.driveForward(6);
    drivePID.driveForward(-6);
    turnPID.turnToAngle(0);
    rightDriveMotors.move(35);
    leftDriveMotors.move(50);
    pros::delay(500);
    armPiston.set_value(true);
    pros::delay(5000);
    intakeControl("STOP");
}

void blueMogoRush() {
    gyro.set_rotation(90);
    drivePID.driveForward(42);
    turnPID.turnToAngle(30);
    sweeperPiston.set_value(true);
    pros::delay(600);
    drivePID.driveForward(-18, true);
    intakeControl("INTAKE");
    // Task intakeTask(intakeRingDetection);
    sweeperPiston.set_value(false);
    pros::delay(700);
    mogoPiston.set_value(false);
    turnPID.turnToAngle(225);
    drivePID.driveForward(-19, true);
    turnPID.turnToAngle(290);
    drivePID.driveForward(48.5);
    sweeperPiston.set_value(true);
    pros::delay(400);
    leftDriveMotors.move(-60);
    rightDriveMotors.move(60);
    pros::delay(800);
    sweeperPiston.set_value(false);
    intakeControl("STOP");
    pros::delay(2000);
    leftDriveMotors.move(0);
    rightDriveMotors.move(0);
    turnPID.turnToAngle(90);
}

void skills() {
    PIDclass mogoPID(5, 1, 1.2, 0.8, 300, 60);
    gyro.set_rotation(90);
    sweeperPiston.set_value(true);
    pros::delay(200);
    sweeperPiston.set_value(false);
    armControl(ARM_WALL_ANGLE);
    pros::delay(200);
    armPiston.set_value(true);
    pros::delay(600);
    drivePID.driveForward(-11);

    turnPID.turnToAngle(180);
    armControl(ARM_HOLD_ANGLE);
    armPiston.set_value(false);
    drivePID.driveForward(-26, true);
    turnPID.turnToAngle(270);
    intakeControl("INTAKE");
    drivePID.driveForward(24);
    turnPID.turnToAngle(0);
    drivePID.driveForward(24);
    turnPID.turnToAngle(305);
    drivePID.driveForward(26);
    drivePID.driveForward(-26);

    turnPID.turnToAngle(90);
    drivePID.driveForward(38);
    drivePID.driveForward(-16);
    turnPID.turnToAngle(0);
    drivePID.driveForward(10);
    drivePID.driveForward(-10);

    turnPID.turnToAngle(225);
    mogoPiston.set_value(false);
    leftDriveMotors.move(-60);
    rightDriveMotors.move(-60);
    pros::delay(1000);

    drivePID.driveForward(9.7);
    turnPID.turnToAngle(0);
    intakeControl("STOP");
    mogoPID.driveForward(-84, true);
    
    turnPID.turnToAngle(270);
    intakeControl("INTAKE");
    drivePID.driveForward(24);
    turnPID.turnToAngle(180);
    drivePID.driveForward(26);
    drivePID.driveForward(-2);
    
    turnPID.turnToAngle(245);
    drivePID.driveForward(26);
    drivePID.driveForward(-26);
    
    turnPID.turnToAngle(90);
    drivePID.driveForward(35);
    drivePID.driveForward(-12);
    turnPID.turnToAngle(180);
    drivePID.driveForward(11);
    drivePID.driveForward(-11);
    
    turnPID.turnToAngle(315);
    mogoPiston.set_value(false);
    leftDriveMotors.move(-60);
    rightDriveMotors.move(-60);
    pros::delay(1000);
    drivePID.driveForward(17);
    
    turnPID.turnToAngle(270);
    mogoPID.driveForward(96);
    topIntake.brake();
    turnPID.turnToAngle(180);
    drivePID.driveForward(-50, true);
    topIntake.move(127);
    turnPID.turnToAngle(135);
    drivePID.driveForward(36);
    drivePID.driveForward(-36);
    turnPID.turnToAngle(45);
    drivePID.driveForward(36);
    turnPID.turnToAngle(0);
    drivePID.driveForward(24);
    turnPID.turnToAngle(270);
    drivePID.driveForward(28);
    turnPID.turnToAngle(0);
    drivePID.driveForward(12);
    turnPID.turnToAngle(90);

    mogoPiston.set_value(false);
    turnPID.turnToAngle(0);
    leftDriveMotors.move(-45);
    rightDriveMotors.move(-45);
    pros::delay(1000);

    turnPID.turnToAngle(0);
    intakeControl("STOP");
    drivePID.driveForward(-132);
    sweeperPiston.set_value(true);
}