// ============================================== SETTINGS /////////////////
const int THRESHOLD = 512;
const int SENSORS_COUNT = 5;
const int SENSOR_PINS[SENSORS_COUNT] = {A0, A1, A2, A3, A4};
const int ERRORS[4] = {0, 1, 2, 3};

const int MAX_SPEED = 255;
const int NORMAL_SPEED = 205;
const int MIN_SPEED = 0;

const int LEFT_IN1 = 6;
const int LEFT_IN2 = 7;
const int LEFT_EN = 5;

const int RIGHT_IN1 = 9;
const int RIGHT_IN2 = 8;
const int RIGHT_EN = 10;

const float KP = 80;
const float KI = 0;
const float KD = 50;

const bool DEBUG = false;
const int DELAY_TIME = 1000;

// ==============================================  /////////////////

#include "Sensors.h"
#include "Motors.h"
#include "PID.h"

Sensors sensors(THRESHOLD, SENSORS_COUNT, SENSOR_PINS, ERRORS);
Motors motors(
    NORMAL_SPEED, MIN_SPEED, MAX_SPEED,
    LEFT_IN1, LEFT_IN2, LEFT_EN,
    RIGHT_IN1, RIGHT_IN2, RIGHT_EN
);
PID pid(KP, KI, KD);

void setup() {
    Serial.begin(9600);
    motors.initialize();
}

void loop() {
    int error = sensors.calculate_error();
    int speed_difference = pid.calculate_speed_difference(error);
    motors.drive(speed_difference, DEBUG);

    if(DEBUG) {
        Serial.print("error: ");
        Serial.println(error);
        Serial.print("speed_difference: ");
        Serial.println(speed_difference);
        Serial.println("--------------------------------------");
        delay(DELAY_TIME);
    }
}
