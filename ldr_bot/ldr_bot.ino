// Notes:
// - Using the Duinotech Leonardo Tiny Atmega32U4 Development Board (runs on 5V. 3 digital and 3 analog pins).
// - Motor Shield is the Arduino Motor Shield L293 from DFROBOT.
// - Motor Shield requires an external voltage supply on the VIN pin to provide enough current to the motors.   

int EN1 = 9;  // Pin 9 of the Atmega32U4 connects to pin 6 on the Motor Shield
int EN2 = 10; // Pin 10 of the Atmega32U4 connects to pin 5 on the Motor Shield
int directionControlPin = 11;  // Pin 11 of the Atmega32U5 connects to both pin 7 and pin 4 of the Motor Shield to provide limited direction control

int leftLDRPin = A0;
int rightLDRPin = A1;
int rearLDRPin = A2;

int leftLDRValue = 0;
int rightLDRValue = 0;
int rearLDRValue = 0;

int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

boolean doReverse = true;
volatile unsigned long currentTime;
volatile unsigned long lastReverseTime = 0;

void leftMotor(int pwm, boolean reverse) {
  analogWrite(EN2, pwm);
  if (reverse)  {
    digitalWrite(directionControlPin, HIGH);
  }
  else  {
    digitalWrite(directionControlPin, LOW);
  }
}

void rightMotor(int pwm, boolean reverse) {
  analogWrite(EN1, pwm);
  if (reverse)  {
    digitalWrite(directionControlPin, HIGH);
  }
  else  {
    digitalWrite(directionControlPin, LOW);
  }
}

void setup() {
  int i;
  for (i = 9; i <= 11; i++)
    pinMode(i, OUTPUT);  // Set pins 9, 10, 11 to output mode

  pinMode(LED_BUILTIN, OUTPUT);
  
  //Serial.begin(9600);

  digitalWrite(LED_BUILTIN, HIGH);

  digitalWrite(directionControlPin, LOW); // Sets the motor direction to forwards (set to HIGH to reverse motor direction)
}

void loop() {
  currentTime = millis();
  
  leftLDRValue = analogRead(leftLDRPin);
  rightLDRValue = analogRead(rightLDRPin);
  rearLDRValue = analogRead(rearLDRPin);

  if(rearLDRValue > leftLDRValue && rearLDRValue > rightLDRValue && !doReverse) {
    lastReverseTime = currentTime;
    doReverse = true;
  }

  if(currentTime <= lastReverseTime + 2000 && doReverse) {
    leftMotorSpeed = map(rightLDRValue, 0, 1024, 0, 100);
    rightMotorSpeed = map(leftLDRValue, 0, 1024, 0, 100);

    if(leftMotorSpeed > rightMotorSpeed) {
      leftMotor(leftMotorSpeed, true);
      rightMotor(random(100,200), true); // Adds randomness to help prevent the robot fom getting stuck in corners
    } else {
      leftMotor(random(100,200), true);
      rightMotor(rightMotorSpeed, true);
    }
    doReverse = true;
    
  } else {
    leftMotorSpeed = map(rightLDRValue, 0, 1024, 0, 255);
    rightMotorSpeed = map(leftLDRValue, 0, 1024, 0, 255);

    leftMotor(leftMotorSpeed, false);
    rightMotor(rightMotorSpeed, false);

    doReverse = false;
  }
  
  //Serial.println(leftLDRValue);
  //Serial.println(rightLDRValue);
  //Serial.println(rearLDRValue);
}
