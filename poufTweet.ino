#include <Bridge.h>
#include <HttpClient.h>

// http://localhost:3000/twitt/?scrname=hugohil&pufNum=1

int xInput = A0;
int yInput = A1;
int zInput = A2;

int xPrev = 0;
int yPrev = 0;
int zPrev = 0;

// Raw Ranges:
// initialize to mid-range and allow calibration to
// find the minimum and maximum for each axis
int xRawMin = 512;
int xRawMax = 512;

int yRawMin = 512;
int yRawMax = 512;

int zRawMin = 512;
int zRawMax = 512;

const int sampleSize = 10;

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
}

void loop() {
  HttpClient client;

  int xRaw = analogRead(xInput);
  int yRaw = analogRead(yInput);
  int zRaw = analogRead(zInput);

  if((abs(xRaw) - abs(xPrev)) + (abs(yRaw) - abs(yPrev)) + (abs(zRaw) - abs(zPrev)) > 10){
    Serial.print(xRaw);
    Serial.print(", ");
    Serial.print(yRaw);
    Serial.print(", ");
    Serial.println(zRaw);
    client.get("http://192.168.1.16:3000/twitt/?scrname=hugohil&pufNum=1");
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    Serial.flush();
  }

  xPrev = xRaw;
  yPrev = yRaw;
  zPrev = zRaw;

  delay(100);
}
