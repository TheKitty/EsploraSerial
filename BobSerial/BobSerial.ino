// Controlling Robotic Head with Arduino Uno and Adafruit Motorshield via serial port 
//    Be sure you select Arduino Uno from board list (others may give errors)
//
// Anne Barela, 1/2/2013

#include <Servo.h>
#include <Serial.h>
#include <AFMotor.h>

#define DEBUG 0

#define FRONT   55   // Move eye servo to front
#define LEFT   117   // max servo eyes left
#define RIGHT   21   // max servo eyes right
#define CLOSED 113   // servo when mouth fully closed
#define OPEN    68   // servo when mouth fully open
#define NECK     1   // Motorshield Motor 1 is the neck
#define CHIN     2   // Motorshield Motor 2 is the chin

AF_DCMotor neckmotor(NECK, MOTOR12_64KHZ); // create motor #1, 1KHz pwm
AF_DCMotor chinmotor(CHIN, MOTOR12_64KHZ); // create motor #2, 1KHz pwm
 
Servo Eyeservo, Mouthservo;  // create servo object to control a servo 
  
int eyecount=FRONT;     // eyes front
int mouthcount=CLOSED; // mouth shut
char cmdChar;    // read commands from serial port 
 
void setup() 
{ 
  Serial.begin(9600);    // Open serial to read commands
  Eyeservo.attach(10);   // attach the servo on pin 10 to the eyeservo object (Motorshield "Servo1")
  Mouthservo.attach(9);  // attach servo on pin 9 to the mouthservo object (Motorshield "Servo2")
  Eyeservo.write(eyecount);  
  Mouthservo.write(mouthcount);  
  neckmotor.setSpeed(200);     // set the speed to 100/255  
  chinmotor.setSpeed(200);
} 
 
void loop() 
{ 
  if(Serial.available())  {
    cmdChar = Serial.read();
    if(DEBUG)  {
       Serial.print(cmdChar); // echo
       Serial.print(" - ");
       Serial.print(eyecount);
       Serial.print(", ");
       Serial.println(mouthcount);
    }
    switch(cmdChar) {
      case '1': 
        if(eyecount > RIGHT) eyecount=eyecount-2;
        Eyeservo.write(eyecount); 
        break;
      case '2': 
        if(eyecount < LEFT) eyecount=eyecount+2;
        Eyeservo.write(eyecount);
        break;
      case '3': 
        if(mouthcount > OPEN) mouthcount--;
        Mouthservo.write(mouthcount); 
        break;
      case '4': 
        if(mouthcount < CLOSED) mouthcount++;
        Mouthservo.write(mouthcount); 
        break;
      case '0':              // reset to defaults on eyes and mouth
        mouthcount=CLOSED;
        eyecount=FRONT;
        Mouthservo.write(mouthcount);
        Eyeservo.write(eyecount);
        break;
      case 'D':    // move head DOWN
        chinmotor.run(FORWARD);      // turn it on going forward
        delay(500);
        chinmotor.run(RELEASE);      // stopped
        break;
      case 'U':    // move head UP
        chinmotor.run(BACKWARD);     // turn it on going forward
        delay(500);
        chinmotor.run(RELEASE);      // stopped
        break;
      case 'L':    // turn head left
        neckmotor.run(FORWARD);      // turn it on going forward
        delay(500);
        neckmotor.run(RELEASE);      // stopped
        break;
      case 'R':    // turn head right
        neckmotor.run(BACKWARD);     // turn it on going forward
        delay(500);
        neckmotor.run(RELEASE);      // stopped
        break;
    }
    delay(15);                       // waits for the servo to get there 
  }
} 
