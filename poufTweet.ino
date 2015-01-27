#include <Wire.h>
#include <Bridge.h>
#include <HttpClient.h>
#include "MMA7660.h"

MMA7660 accelemeter;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 1000;    // the debounce time; increase if the output flickers

  int8_t x;
  int8_t y;
  int8_t z;
  int8_t sum;

void setup() {
  Serial.begin(9600);

  accelemeter.init();

  Bridge.begin();
}

void loop() {
  HttpClient client;
  accelemeter.getXYZ(&x,&y,&z);
  /*
  Serial.print("x = ");
  Serial.println(x);
  Serial.print("y = ");
  Serial.println(y);
  Serial.print("z = ");
  Serial.println(z);
  */

  //accelemeter.getAcceleration(&ax,&ay,&az);
  // Serial.print(abs(ax));
  // Serial.print(", ");
  // Serial.print(abs(ay));
  // Serial.print(", ");
  // Serial.println(abs(az));
  sum = abs(x) + abs(y) + abs(z);
  Serial.println(sum);

  if( sum > 50 && (millis() - lastDebounceTime) > debounceDelay){
    Serial.println("send");
    lastDebounceTime = millis();
    //client.get("http://cybertron.meteor.com/twitt/?scrname=WilliamTheBot");
    client.get("http://cybertron.meteor.com/twitt/?scrname=NormanQCtheBot&pufNum=7");
  }


  delay(50);
}
