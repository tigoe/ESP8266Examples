/*
  This sketch makes a telnet client on port 8080 to a server
  It echoes any serial bytes to the server, and any server bytes
  to the serial port. This is a modified version of the EspWiFiTelnetClient

  note: the header file "settings.h" is not included in this repository.
  Add a new tab in Arduino, call it "settings.h", and Include the following variables:
  char ssid[]     = "ssid";     // your network SSID
  char password[] = "password"; // your network password
  char host[] = "192.168.0.2";  // the IP address of the device running the server

  You need to run a telnet server on port 8080 of the host to talk to this
  sketch.

  created 26 Jun 2015
  modified 29 Oct 2015
  by Tom Igoe

 */

#include <ESP8266WiFi.h>
#include "settings.h"

WiFiClient socket;      // variable for the socket connection
const int port = 8080;  // port for the socket connection

// set the pin numbers for the indicator LEDS:
const int leftPin = 13;
const int rightPin = 12;
const int upPin = 14;
const int downPin = 16;
const int connectedPin = 15;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  socket.setTimeout(10);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(upPin, OUTPUT);
  pinMode(downPin, OUTPUT);
  pinMode(connectedPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");   // connect to access point
  Serial.println(ssid);
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
}

void loop() {
  // Read the reply from server and print them to serial port:
  while (socket.available()) {
    Serial.print("Got something");
    String input = socket.readString();
    Serial.print(input);
  }

  // Read the reply from serial port and print them to server:
  while (Serial.available()) {
    char input = Serial.read();
    // turn on the LEDs depending on what comes in the serial:
    switch (input) {
      case 'l':       // left
        digitalWrite(leftPin, HIGH);
        socket.print(input);
        break;
      case 'r':       // right
        socket.print(input);
        digitalWrite(rightPin, HIGH);
        break;
      case 'u':       // up
        socket.print(input);
        digitalWrite(upPin, HIGH);
        break;
      case 'd':      // down
        socket.print(input);
        digitalWrite(downPin, HIGH);
        break;
      case '1':      // button pushed
        if (socket.connected()) {   // if the socket's connected, disconnect
          socket.print('x');        // by sending an x
        } else {                    // if the socket's not connected,
          login();                  // login to the server
        }
        break;
    }
  }
  // if there's no serial input, turn the LEDs off:
  digitalWrite(leftPin, LOW);
  digitalWrite(rightPin, LOW);
  digitalWrite(upPin, LOW);
  digitalWrite(downPin, LOW);

  // set the connected LED based on the state of the connection:
  digitalWrite(connectedPin, socket.connected());
}

boolean login() {
  socket.connect(host, port);   // attempt to connect

  while (!socket.connected()) { // While not connected, try again
    delay(1000);
    if (socket.connected()) {   // if you connected,
      socket.println("hello");  // say hello to the server
    } else {
      // if not connected, try again:
      Serial.println("connection failed, trying again");
      socket.connect(host, port);
    }
  }
}
