/*
 NodeMCU-BlinkendeD1
 D4 an dem Modul ESP8266 bzw. Board NodeMCU blinken lassen
 Programm erprobt ab Arduino IDE 1.6.13
 Weitere Beispiele unter https://www.mikrocontroller-elektronik.de/

  Soft Acces Point Reference:
  https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
  
  WiFi.softAP(ssid=char*, password=char*, channel=int, hidden=bool);
  WiFi.softAPIP();

 */
#include <ESP8266WiFi.h>

char* ssid = "ESP";


void spawn_softAP(char* ssid)
{
  WiFi.softAP(ssid);
  /*
   * dhcp server start:(ip:192.168.4.1,mask:255.255.255.0,gw:192.168.4.1)
   *
   */
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  spawn_softAP(ssid);
}

void loop() {
  WiFi.status();
  /*
   * Wenn sich eine client verbindet gibt WiFi.status():
   * add 1
   * aid 1
   * station: 74:de:2b:86:db:08 join, AID = 1
   */
  delay(1000);
  Serial.print(".");
}
