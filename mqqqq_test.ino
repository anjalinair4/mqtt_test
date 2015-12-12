
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include<EEPROM.h>

char ssid[] = "startup village,star north circle";
const char* mqtt_server = "athul.semita.tk";
const int GPIO = 16;
char essid[50];
int n,i,q;  
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
char mac[50];
char location[50];
int value = 0;
String tmp;

void setup() {
  pinMode(GPIO,OUTPUT);
  EEPROM.begin(512);
  for(i=0;i<=(sizeof(ssid))-1;i++)
 { 
  EEPROM.write(i,ssid[i]);
  essid[i] = EEPROM.read(i);
 // Serial.print(essid);
  }
EEPROM.commit();
if (GPIO==HIGH) {
    // turn LED on:
    for (int i = 0; i < 512; i++)
    EEPROM.write(i, 0);
  }
  
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(essid);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
   Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      
     Serial.println("connected");
     WiFi.status(0);
     Serial.print(WiFi.status());
     ("location/" + WiFi.macAddress()).toCharArray(mac,27);

     Serial.print("mac address=");
     Serial.println(mac);
     digitalWrite(BUILTIN_LED, LOW);
      // Once connected, publish an announcement...
      client.publish(mac, "Connected !");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
     Serial.print("failed, rc=");
     digitalWrite(BUILTIN_LED, HIGH);
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
    if(Serial.available()>0){
        Serial.readString().toCharArray(msg,50);
        client.publish(mac,msg);
        Serial.print("Publish message: ");
        Serial.println(msg);
       

    }
}
