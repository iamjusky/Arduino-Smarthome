#include <stdio.h>
#include <string.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Stepper.h>

Servo myservo;
SoftwareSerial espSerial =  SoftwareSerial(2, 3);  // arduino RX pin=2  arduino TX pin=3    connect the arduino RX pin to esp8266 TX pin   -  connect the arduino TX pin to esp8266 RX pin.


int Pin1 = 4;
int Pin2 = 5;
int Pin3 = 6;
int Pin4 = 7;
int pole1[] = {0, 0, 0, 0, 0, 1, 1, 1, 0}; //pole1, 8 step values
int pole2[] = {0, 0, 0, 1, 1, 1, 0, 0, 0}; //pole2, 8 step values
int pole3[] = {0, 1, 1, 1, 0, 0, 0, 0, 0}; //pole3, 8 step values
int pole4[] = {1, 1, 0, 0, 0, 0, 0, 1, 0}; //pole4, 8 step values

int poleStep = 0;
int speed;
boolean dir;// false=clockwise, true=counter clockwise
boolean escuStatus;
//LED
int led = 13;
//DOOR
int door = 9;

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  //LED
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  //door
  myservo.attach(door);
  myservo.write(0);
  //esculator
  escuStatus = false;
  dir = 1;
  speed = 5;
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);
}
//==============================

void loop() {
 
  //ESCULATOR
  if (escuStatus) {
    if (dir) {
      driveStepper(poleStep);
      poleStep++;
    } else {
      driveStepper(poleStep);
      poleStep--;
    }
    if (poleStep > 7) {
      poleStep = 0;
    }
    if (poleStep < 0) {
      poleStep = 7;
    }
    delay(speed);
  }
  if (espSerial.available()) {
    String ch = espSerial.readString();
    ch.trim();
    
    handleDoor(ch);
    handleLED(ch);
    handleEscalator(ch);

    Serial.println(ch);
  }
}
void handleDoor(String status) {
   if (status == "CLOSE") {
      myservo.write(0);
    }
    if (status == "OPEN") {
      myservo.write(90);
    }
}
void handleLED(String status) {
    if (status== "OFF") {
      digitalWrite(led, LOW);
    }
    if (status == "ON" ) {
      digitalWrite(led, HIGH);
    }
}
void driveStepper(int c)
{
  digitalWrite(Pin1, pole1[c]);
  digitalWrite(Pin2, pole2[c]);
  digitalWrite(Pin3, pole3[c]);
  digitalWrite(Pin4, pole4[c]);
}

void handleEscalator(String status) {
  //---------DIR
  if(status == "CLOCKWISE"){
    dir = true;
  }
   if(status == "COUNTER-CLOCKWISE"){
    dir = false;
  }
  //---------SPEED
  if(status == "SPEED-1"){
    speed = 1;
  };
  if(status == "SPEED-2"){
    speed = 2;
  };
  if(status == "SPEED-3"){
    speed = 3;
  };
  if(status == "SPEED-4"){
    speed = 4;
  };
  if(status == "SPEED-5"){
    speed = 5;
  };
  //---------STATUS
  if(status == "RUN"){
    escuStatus = true;
  };
  if(status == "STOP"){
    escuStatus = false;
  };
}
