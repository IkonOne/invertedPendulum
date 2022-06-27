#pragma once

/*
We have a GT2 belt which has a 2mm pitch.
The pulley has 20 teeth.
This results in 40mm of travel per rotation.

The motor is 1.8 degrees per step.
The TMC2208 defaults to 1/8 microstepping, sort of.
I say sort of because the MS1 and MS2 pins are actually floating at the moment, which appears to mean ground.
See: https://wiki.fysetc.com/TMC2208/#micro-stepping
*/

///// HARDWARE
const int BELT_PITCH = 2; // mm
const int PULLEY_TEETH = 20;
const int STEPS_PER_ROTATION = 200;
const float MAX_TRAVEL = 280.0f; // mm

///// TMC2208
const int MICROSTEPS = 8;
const float MM_PER_MICROSTEP =
    (float)(BELT_PITCH * PULLEY_TEETH) / (float)(STEPS_PER_ROTATION) / (float)(MICROSTEPS);

const int PIN_ENABLE = 15;
const int PIN_STEP = 2;
const int PIN_DIR = 0;

///// ENDSTOP
const int PIN_ENDSTOP = 13;

///// MOTION CONTROL
const float ACCEL = 40000.0f;
const float SPEED = 20000.0f;
const float HOMING_SPEED = 1050.0f;