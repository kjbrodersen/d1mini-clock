#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TM1637Display.h>

#define CLK D2
#define DIO D3

TM1637Display display = TM1637Display(CLK, DIO);              

const char *ssid     = "COSMOTE-2020";
const char *password = "6977231831";
const long utcOffsetInSeconds = 3600; // UTC + 2h

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "gr.pool.ntp.org", utcOffsetInSeconds);

void setup()
{
  // serial communication
  Serial.begin(115200);
  // clear the display
  display.clear();
  // wifi connection
  WiFi.begin(ssid, password);
  // wait for wifi connection to be established
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  // time client
  timeClient.begin();
}

void loop() {
  int A,B;
  
  timeClient.update();
  display.setBrightness(7);                   
  
  A = timeClient.getHours() *100 + timeClient.getMinutes();
  B = timeClient.getSeconds();
  
  if((B % 2) == 0)
  {
    display.showNumberDecEx(A, 0b01000000 , true, 4, 0); 
  }
  else
  {
    display.showNumberDecEx(A, 0b00000000 , true, 4, 0); 
  }
  // delay for stability
  delay(100);
  
}