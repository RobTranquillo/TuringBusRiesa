/*
 NodeMCU-BlinkendeD1
 D1 an dem Modul ESP8266 bzw. Board NodeMCU blinken lassen
 Programm erprobt ab Arduino IDE 1.6.13
 Weitere Beispiele unter https://www.mikrocontroller-elektronik.de/
 */
int LED = D4;

void setup() {
 pinMode(LED, OUTPUT); // Port aus Ausgang schalten
 }


void loop()
{
   digitalWrite(LED, LOW); //D1 port ausschalten
   delay(200); //1 Sek Pause
   digitalWrite(LED, HIGH); //D1 port einschlaten
   delay(200);
}
