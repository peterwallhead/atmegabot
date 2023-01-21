int EN1 = 9;  // Pin 9 of the Atmega32U4 connects to pin 6 on the Motor Shield
int EN2 = 10; // Pin 10 of the Atmega32U4 connects to pin 5 on the Motor Shield
int IN1 = 7;  // Pin 7 of the Motor Shield is pulled to GND to provide manual motor direction control (pull this pin to 5V to reverse motor direction)
int IN2 = 4;  // Pin 4 of the Motor Shield is pulled to GND to provide manual motor direction control (pull this pin to 5V to reverse motor direction)

int leftLDRPin = A0;
int rightLDRPin = A1;
int rearLDRPin = A2;

int leftLDRValue = 0;
int rightLDRValue = 0;
int rearLDRValue = 0;

int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

void leftMotor(int pwm) {
  analogWrite(EN2, pwm);
}

void rightMotor(int pwm) {
  analogWrite(EN1, pwm);
}

void setup() {
  int i;
  for (i = 9; i <= 10; i++)
    pinMode(i, OUTPUT);  // Set pins 9 & 10 to output mode

  pinMode(LED_BUILTIN, OUTPUT);
  
  //Serial.begin(9600);

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  leftLDRValue = analogRead(leftLDRPin);
  rightLDRValue = analogRead(rightLDRPin);
  rearLDRValue = analogRead(rearLDRPin);

  if(rearLDRValue > leftLDRValue && rearLDRValue > rightLDRValue) {
    leftMotorSpeed = 0;
    rightMotorSpeed = 100;
  } else {
    leftMotorSpeed = map(rightLDRValue, 0, 1024, 0, 100);
    rightMotorSpeed = map(leftLDRValue, 0, 1024, 0, 100);
  }

  leftMotor(leftMotorSpeed);
  rightMotor(rightMotorSpeed);
  
  //Serial.println(leftLDRValue);
  //Serial.println(rightLDRValue);
  //Serial.println(rearLDRValue);
}
