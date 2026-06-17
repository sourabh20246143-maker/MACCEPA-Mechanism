#include <Servo.h>

Servo servo1;
Servo servo2;

const int SERVO1_PIN = 9;
const int SERVO2_PIN = 10;

int currentPos1 = 0;
int currentPos2 = 0;

void setup() {
  Serial.begin(115200);

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);

  servo1.write(0);
  servo2.write(0);
  delay(500);

  Serial.println("\n--- Dual Servo Controller Ready ---");
  Serial.println("Enter two angles separated by a comma, e.g. 90,45");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int commaIndex = input.indexOf(',');
    if (commaIndex > 0) {
      int angle1 = input.substring(0, commaIndex).toInt();
      int angle2 = input.substring(commaIndex + 1).toInt();

      if (angle1 >= 0 && angle1 <= 180 && angle2 >= 0 && angle2 <= 180) {
        Serial.print("Moving servo1 to ");
        Serial.print(angle1);
        Serial.print("° and servo2 to ");
        Serial.print(angle2);
        Serial.println("°...");

        moveServoSlowly(servo1, currentPos1, angle1);
        currentPos1 = angle1;

        moveServoSlowly(servo2, currentPos2, angle2);
        currentPos2 = angle2;

        Serial.println("Movement complete.\n");
      } else {
        Serial.println("Error: Angles must be between 0 and 180.");
      }
    } else {
      Serial.println("Error: Please enter angles as A,B (e.g. 90,45)");
    }
  }
}

void moveServoSlowly(Servo &chosenServo, int startAngle, int endAngle) {
  if (startAngle < endAngle) {
    for (int pos = startAngle; pos <= endAngle; pos++) {
      chosenServo.write(pos);
      delay(15);
    }
  } else {
    for (int pos = startAngle; pos >= endAngle; pos--) {
      chosenServo.write(pos);
      delay(15);
    }
  }
}