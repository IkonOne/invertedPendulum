#include <Arduino.h>

#include <AccelStepper.h>
#include "configuration.h"

///// Endstop
const int ENDSTOP_OPEN = 0;
const int ENDSTOP_CLOSED = 1;
int endstop_state;

void endstop_setup() {
    pinMode(PIN_ENDSTOP, INPUT);
}

void endstop_read() {
    endstop_state = !digitalRead(PIN_ENDSTOP);
}

bool endstop_is_open() {
    return endstop_state == ENDSTOP_OPEN;
}

bool endstop_is_closed() {
    return endstop_state == ENDSTOP_CLOSED;
}

///// Stepper
AccelStepper stepper(AccelStepper::DRIVER, PIN_STEP, PIN_DIR);

void stepper_setup() {
    pinMode(PIN_ENABLE, OUTPUT);
    pinMode(PIN_STEP,   OUTPUT);
    pinMode(PIN_DIR,    OUTPUT);

    stepper.setEnablePin(PIN_ENABLE);
    stepper.setAcceleration(ACCEL);
    stepper.setMaxSpeed(SPEED);
    stepper.setPinsInverted(false, false, true);

    stepper.enableOutputs();
}

///// Motion Control
enum MC_STATES {
   IDLE,
   HOMING, 
};
MC_STATES mc_state;
void mc_homing();

void mc_setup() {
    mc_state = MC_STATES::HOMING;
}

void mc_loop() {
    switch(mc_state) {
        case MC_STATES::IDLE: break;

        case MC_STATES::HOMING:
            mc_homing();
            break;
    }
}

void mc_homing() {
    stepper.setMaxSpeed(HOMING_SPEED);
    stepper.setSpeed(HOMING_SPEED);

    endstop_read();
    while (endstop_is_open()) {
        stepper.runSpeed();
        endstop_read();
    }
    stepper.stop();

    stepper.setMaxSpeed(SPEED);
    stepper.move(-MAX_TRAVEL * 0.5f / MM_PER_MICROSTEP);

    while (stepper.distanceToGo() != 0.0f) {
        stepper.run();
    }

    mc_state = MC_STATES::IDLE;
}

void setup() {
    Serial.begin(9600);

    endstop_setup();
    stepper_setup();
    mc_setup();
}

void loop() {
    mc_loop();
}
