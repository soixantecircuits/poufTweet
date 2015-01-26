#include <Wire.h>
#include <Bridge.h>
#include <HttpClient.h>
#include "MMA7660.h"

MMA7660 accelemeter;

void setup() {
  Serial.begin(9600);

  accelemeter.init();

  Bridge.begin();
}

void loop() {
  HttpClient client;

  float ax,ay,az;
  accelemeter.getAcceleration(&ax,&ay,&az);
  // Serial.print(abs(ax));
  // Serial.print(", ");
  // Serial.print(abs(ay));
  // Serial.print(", ");
  // Serial.println(abs(az));

  if(abs(ax) + abs(ay) + abs(az) > 1.8){
    Serial.println("send");
    client.get("http://cybertron.meteor.com/twitt/?scrname=NormanQCtheBot&pufNum=7");
  }

  delay(50);
}
