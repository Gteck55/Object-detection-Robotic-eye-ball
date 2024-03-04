#include <Servo.h>

Servo servo1;
Servo servo2;
Servo Xservo;
Servo Yservo;

int x_key = A2;
int y_key = A3;
int Xpin = A0;
int x_pos;
int y_pos;

int XSpin = 9;
int YSpin = 10;

int servo1_pin = 8;
int servo2_pin = 5;
int initial_position = 90;
int initial_position1 = 90;

int minServoValue = 50;  // Minimum servo value
int maxServoValue = 140; // Maximum servo value

int WVx;

int dt = 200;
int minXValue = 50;

void setup() {
  Serial.begin(9600);
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo1.write(initial_position);
  servo2.write(initial_position1);
  pinMode(Xpin, INPUT);
  pinMode(XSpin, OUTPUT);
  pinMode(YSpin, OUTPUT);
  Xservo.attach(XSpin);
  Yservo.attach(YSpin);
  pinMode(x_key, INPUT);
  pinMode(y_key, INPUT);
}

void loop() {
  x_pos = analogRead(x_key);
  y_pos = analogRead(y_key);
  int Xval = analogRead(Xpin);
  
  if (Xval > minXValue) {
    WVx = map(Xval, 0, 1023, 0, 180);  // Map the X-axis value to servo range
  } 
  Xservo.write(WVx);
  Yservo.write(90 - WVx);  // Opposite direction
   delay(dt);
  if (x_pos < 300) {
    if (initial_position > minServoValue + 10) {
      initial_position = initial_position - 20;
      servo1.write(initial_position);
      delay(100);
    }
  } else if (x_pos > 700) {
    if (initial_position < maxServoValue - 20) {
      initial_position = initial_position + 20;
      servo1.write(initial_position);
      delay(100);
    }
  } else {
    // Joystick in the center, return to the initial position
    servo1.write(initial_position);
  }

  if (y_pos < 300) {
    if (initial_position1 > minServoValue + 10) {
      initial_position1 = initial_position1 - 20;
      servo2.write(initial_position1);
      delay(100);
    }
  } else if (y_pos > 700) {
    if (initial_position1 < maxServoValue - 20) {
      initial_position1 = initial_position1 + 20;
      servo2.write(initial_position1);
      delay(100);
    }
  } else {
    // Joystick in the center, return to the initial position
    servo2.write(initial_position1);
  }
}
