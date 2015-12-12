
#include<EEPROM.h>
#include <ESP8266WiFi.h>
const char* ssid_AP = "reset";
const char* pass_AP = "128";
void setup() {
int i;
char ssid[20],pass[20];
EEPROM.begin(9600);
if(EEPROM.read(0)=='1')
{
  for(i=1;i<=10;i++)
  {
    ssid[i]=EEPROM.read(i);
  }
  for(i=11;pass[i]!='\0';i++)
  {
    pass[i]= EEPROM.read(11);
  }
  WiFi.begin(ssid, pass);
}
else if(EEPROM.read(0)=='0')
{
  WiFi.begin(ssid_AP, pass_AP);
}

}

void loop() {
  // put your main code here, to run repeatedly:

}
