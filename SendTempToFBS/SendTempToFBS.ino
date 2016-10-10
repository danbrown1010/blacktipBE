/*
  Yún HTTP Client

 This example for the Arduino Yún shows how create a basic
 HTTP client that connects to the internet and downloads
 content. In this case, you'll connect to the Arduino
 website and download a version of the logo as ASCII text.

 created by Tom igoe
 May 2013

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/HttpClient

 */

#include <Bridge.h>
#include <HttpClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 10

char temperatureF[6];

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float tempC = 0;
float tempF = 0;

void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  sensors.begin();
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  SerialUSB.begin(9600);

  //while (!SerialUSB); // wait for a serial connection
}

void loop() {
  // Initialize the client library
  HttpClient client;
  int sensor = random(50,100);
  sensors.requestTemperatures();

  Serial.println(sensors.getTempFByIndex(0));
  
  //tempC = sensors.getTempCByIndex(0);
  //tempF = sensors.toFahrenheit(tempC);
  

  // Make a HTTP request:
  client.get("http://10.0.0.200:8080/blacktip/measurements?id=wSVuDv51X4Xxn4K2hncytcfG3n43&tank=-KTeoKM5GO2yVjAy-7lg&name=CurrTemp&val="+String(sensors.getTempFByIndex(0)));

  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    SerialUSB.print(c);
  }
  SerialUSB.println();
  SerialUSB.flush();

  delay(10000);
}


