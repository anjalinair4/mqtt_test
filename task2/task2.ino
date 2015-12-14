
#include<EEPROM.h>
#include <ESP8266WiFi.h>

const int Pin = 2;
void setup() {
int i;
char ssid[20],pass[20];
pinMode(Pin, INPUT);
EEPROM.begin(9600);

WiFiServer Server(80);
//read ssid and password from eeprom
if(Pin==LOW)
{
  for(i=0;i<10;i++)
  {
    ssid[i]=EEPROM.read(i);
  }
  for(i=10;i<19;i++)
  {
    pass[i]= EEPROM.read(i);;
  }
  WiFi.begin(ssid, pass);
}
// starting WiFiWebServer
else 
{
 Server.begin();
 Server.print("hello world"); 
}

}

void loop() {
  // put your main code here, to run repeatedly:

}