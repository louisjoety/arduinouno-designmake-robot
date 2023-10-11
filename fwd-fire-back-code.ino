#include <Servo.h>

Servo servo;
int servo_pin = 2;
int TRIG_PIN = 13;
int ECHO_PIN = 12;
int MOTOR_PIN1 = 6;
int MOTOR_PIN2 = 5;
int MOTOR_PIN3 = 3;   // Add a pin for motor 3
int MOTOR_PIN4 = 11;  // Add a pin for motor 4
float SPEED_OF_SOUND = 0.0345;
int delay_time = 4;           // Adjust this delay for servo speed
bool motionExecuted = false;  // Flag to track motion execution

void setup() {
  servo.attach(servo_pin, 660, 2400);
  servo.write(0);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);  // Add pin mode for motor 3
  pinMode(MOTOR_PIN4, OUTPUT);  // Add pin mode for motor 4
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH);
  float cms = microsecs * SPEED_OF_SOUND / 2;
  Serial.println(cms);

  if (cms < 9) {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
    digitalWrite(MOTOR_PIN3, LOW);
    digitalWrite(MOTOR_PIN4, LOW);

    if (!motionExecuted) {
      // Control servo movement
      for (int i = 0; i <= 140; i += 10) {
        servo.write(i);
      }

      delay(1000);  // Pause for 1 second at the end position

      // Reverse servo movement
      for (int i = 140; i >= 0; i -= 10) {
        servo.write(i);
      }

      delay(1000);  // Pause for 1 second at the end position

      motionExecuted = true;  // Set the flag to indicate that motion has been executed
    }

    while (motionExecuted) {
      digitalWrite(MOTOR_PIN1, LOW);
      digitalWrite(MOTOR_PIN2, HIGH);
      digitalWrite(MOTOR_PIN3, LOW);
      digitalWrite(MOTOR_PIN4, HIGH);
    }

  }

  else {
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, LOW);
    digitalWrite(MOTOR_PIN3, HIGH);  // Start motor 3
    digitalWrite(MOTOR_PIN4, LOW);   // Start motor 4
    motionExecuted = false;          // Reset the flag when no obstacle is detected
  }
  delay(10);
}