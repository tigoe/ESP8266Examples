/*
 ESP8266 Scan Networks
 
 This example  prints the ESP8266's MAC address, and
 scans for available Wifi networks.
 Every ten seconds, it scans again. It doesn't actually
 connect to any network, so no encryption scheme is specified.


 created 13 July 2010
 by dlf (Metodo2 srl)
 modified for ESP8266 20 Oct 2012
 by Tom Igoe
 */

#include <ESP8266WiFi.h>

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  

  // Print WiFi MAC address:
  printMacAddress();

  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks();
}

void loop() {
  delay(10000);
  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks();
}

void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];

  // print your MAC address:
 Serial.print("MAC address: ");    // print the label
  for (int i = 0; i < 5; i++) {     // iterate over the bytes
    Serial.print(mac[i], HEX);      // print the byte in HEX
    Serial.print(":");              // print a colon
  }
  Serial.println(mac[5], HEX);      // print the last byte with a newline
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1)
  {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    printEncryptionType(WiFi.encryptionType(thisNet));
  }
}

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
  }
}



