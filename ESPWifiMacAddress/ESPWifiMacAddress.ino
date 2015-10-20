/*
  This sketch prints the MAC address on an ESP8266

  created 29 Jun 2015
  modified 20 Oct 2015
  by Tom Igoe

 */

#include <ESP8266WiFi.h>

byte mac[6];    // array to hold the MAC address

void setup() {
  Serial.begin(9600);   // initialize serial communication

  WiFi.macAddress(mac); // read the MAC address into the array
  Serial.print("MAC address: ");    // print the label
  for (int i = 0; i < 5; i++) {     // iterate over the bytes
    Serial.print(mac[i], HEX);      // print the byte in HEX
    Serial.print(":");              // print a colon
  }
  Serial.println(mac[5], HEX);      // print the last byte with a newline
}


void loop() {
    // nothing to do here
}
