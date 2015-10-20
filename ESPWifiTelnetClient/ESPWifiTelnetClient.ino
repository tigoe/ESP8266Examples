/*
  This sketch makes a telnet client on port 8080 to a server
  It echoes any serial bytes to the server, and any server bytes
  to the serial port

  note: the header file "settings.h" is not included in this repository.
  Add a new tab in Arduino, call it "settings.h", and Include the following variables:
  char ssid[]     = "ssid";     // your network SSID
  char password[] = "password"; // your network password
  char host[] = "192.168.0.2";  // the IP address of the device running the server

  You need to run a telnet server on port 8080 of the host to talk to this
  sketch.

  created 26 Jun 2015
  modified 20 Oct 2015
  by Tom Igoe

 */

#include <ESP8266WiFi.h>
#include "settings.h"

WiFiClient socket;
const int port = 8080;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  socket.setTimeout(10);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");   // connect to access point
  // wait for connection to network access point:
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // when connected to access point, acknowledge it:
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // print device's IP address
  login();                        // log into the server
}


void loop() {
  // Read all the lines of the reply from server 
  // and print them to Serial"
  while (socket.available()) {
    Serial.print("Got something");
    String input = socket.readStringUntil('\n');
    Serial.println(input);
  }

  // Read all the lines of the reply from serial 
  // and print them to server:
  while (Serial.available()) {
    String output = Serial.readStringUntil('\n');
    socket.println(output);
  }

  if (millis() % 1000 < 5)  {   // if one second has passed,
    if (!socket.connected()) {  // check connection
      login();                  // if not connected, login
    }
  }
}

boolean login() {
  socket.connect(host, port);   // attempt to connect

  while (!socket.connected()) { // While not connected, try again
    delay(2000);
    if (socket.connected()) {   // if you connected,
      socket.println("hello");  // say hello to the server
    } else {
      // if not connected, try again:
      Serial.println("connection failed, trying again");
      socket.connect(host, port);
    }
  }
}


