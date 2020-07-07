#include <ArduinoJson.h>
#include <FirebaseArduino.h>
#include <FirebaseObject.h>
#include <Firebase.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include "ESP8266WiFi.h"

#define SSID "hello123"
#define PASSWORD "00000000"
#define FIREBASE_HOST "YOUR"
#define FIREBASE_AUTH "YOUR"

#define TYPE DHT11
#define DHTPIN 5

//DHT dht(DHTPIN, TYPE);

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println(SSID);
 
  WiFi.begin(SSID, PASSWORD);

  Serial.println();
  Serial.print("Connecting...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected!");
  Serial.println("IP Address: ");
  Serial.print(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(300);
  Firebase.stream("/");
  Firebase.setFloat("door", 0);
  Firebase.setFloat("light", 0);
  Firebase.setFloat("/escalator/currentStatus", 0);
  Firebase.setFloat("/escalator/clockwise", 1);
  Firebase.setFloat("/escalator/speed", 5);
}

void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }
  if (Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    String eventPath = event.getString("path");
    handleDoor(eventPath);
    handleLED(eventPath);
    handleEscalator(eventPath);
  }
  
}

  
  

void handleEscalator(String eventPath) {
  
  if (eventPath == "/escalator/currentStatus") {
    int currentStatus =  Firebase.getInt("/escalator/currentStatus");
    if(currentStatus == 1){
        Serial.println("RUN");
    }
    if(currentStatus == 0){
        Serial.println("STOP");
    }
  }
  if (eventPath == "/escalator/clockwise") {
    int currentStatus =  Firebase.getInt("/escalator/clockwise");
     if(currentStatus == 1){
        Serial.println("CLOCKWISE");
    }
    if(currentStatus == 0){
        Serial.println("COUNTER-CLOCKWISE");
    }
  }
  if (eventPath == "/escalator/speed") {
    int currentStatus =  Firebase.getInt("/escalator/speed");
    if(currentStatus == 1){
        Serial.println("SPEED-1");
    }
    if(currentStatus == 2){
        Serial.println("SPEED-2");
    }
    if(currentStatus == 3){
        Serial.println("SPEED-3");
    }
    if(currentStatus == 4){
        Serial.println("SPEED-4");
    }
    if(currentStatus == 5){
        Serial.println("SPEED-5");
    }
  }
}


void handleDoor(String eventPath) {
  if (eventPath == "/door") {
    int currentStatus =  Firebase.getInt("door");
    if (currentStatus == 0) {
      Serial.println("CLOSE");
    }
    if (currentStatus == 1) {
      Serial.println("OPEN");
    }
  }
}
void handleLED(String eventPath) {
  if (eventPath == "/light") {
    int currentStatus =  Firebase.getInt("light");
    if (currentStatus == 0) {
      Serial.println("OFF");
    }
    if (currentStatus == 1) {
      Serial.println("ON");
    }
  }
}
