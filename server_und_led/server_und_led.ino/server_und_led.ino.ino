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
WiFiServer server(80);
int LED = D4;


void spawn_softAP(char* ssid)
{ 
  IPAddress serverIP;
  serverIP.fromString("192.168.4.1");
  WiFi.softAP(ssid);
  /*
   * dhcp server start:(ip:192.168.4.1,mask:255.255.255.0,gw:192.168.4.1)
   *
   */
   
  Serial.print("Soft AP wird gestartet");  
  while(WiFi.softAPIP() != serverIP)
  {
    Serial.print(WiFi.softAPIP());
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Soft AP ist gestartet.");  
}




// prepare a web page to be send to a client (web browser)
String prepareHtmlPage()
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "Analog input:  " + String(analogRead(A0)) +
            "</html>" +
            "\r\n";
  return htmlPage;
}

void setup()
{
  // prepare LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  
  Serial.begin(115200);
  spawn_softAP(ssid);
  server.begin();
}

void loop() {
  WiFi.status();
  /*
   * Wenn sich eine client verbindet gibt WiFi.status():
   * add 1
   * aid 1
   * station: 74:de:2b:86:db:08 join, AID = 1
   */

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val;
  if (req.indexOf("/led_on") != -1) {
    val = 1;
  } else if (req.indexOf("/led_off") != -1) {
    val = 0;
  } else {
    Serial.println("invalid request. Please do: http://192.168.4.1/led/on e.g.");
    val = 404;
  }

  // Set GPIO2 according to the request
  digitalWrite(LED, val);

  client.flush();

  // Prepare the response
  String answer = "LED is now ";
  answer += (val) ? "off" : "on";
  if(val == 404){
    answer = "Keine Eingabe in der URL gefunden";
  }

  // Send the response to the client
  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n" +answer+ "</html>\n");
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}
