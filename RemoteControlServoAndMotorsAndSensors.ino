#include <DabbleESP32.h>
#include <ESP32Servo.h>

Servo myservo;
int pos = 90;
int servoPin = 13;

int enA = 27;
int in1 = 14;
int in2 = 12;

int cm = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Dabble.begin("Simon's ESP32");   

ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
Dabble.processInput();

if (GamePad.getXaxisData() > 2){
  if (pos < 135){
 pos = pos +1;
  }
}

if (GamePad.getXaxisData() < -2){
  
if (pos > 45){
 pos = pos -1;
}
}

if (GamePad.getYaxisData() > 2){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);    
}

if (GamePad.getYaxisData() < -2){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
}

if (GamePad.getYaxisData() < 2 && GamePad.getYaxisData() > -2 ){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);    
}

Serial.print("x_axis: ");
Serial.print(GamePad.getXaxisData());
Serial.print(" y_axis: ");
Serial.print(GamePad.getYaxisData());
Serial.print(" pos: ");
Serial.print(pos);
myservo.write(pos);
cm = 0.01723 * readUltrasonicDistance(27, 26);
Serial.print(" cm: ");
Serial.print(cm);
Serial.print(" distance: ");
Serial.print(readUltrasonicDistance(27, 26));
  Serial.println();
}
