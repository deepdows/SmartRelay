#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <time.h> // including libraries

const int relay = 5; // GPIO5 (D1) port connected to relay
String last; // last state relay was. it has "1" and "0"
unsigned long last_time; // variable for delay for automode
bool flagMode = false; // flag for mode statement

const char* ssid = "...."; //WI-FI name
const char* password = "........"; //WI-FI password

const char* mqttServer = "......"; // server of MQTT
const int mqttPort = ....; // port of MQTT
const char* mqttUser = "...."; // user of MQTT
const char* mqttPassword = "....."; // password of MQTT

WiFiClient espClient; 
PubSubClient client(espClient);
 
void callback(char* topic, byte* payload, unsigned int length) {
  String str;
  for (int i = 0; i < length; i++) {
    str += (char)payload[i];
  }                         // having message
  String t = String(topic); // having topic name
  if(t == "relay" && flagMode) relay1(str);
  if(t == "time1") time1(str);
  if(t == "time2") time2(str);
  if(t == "check") { 
    client.publish("showcheck","on");
    if (last == "1") client.publish("showcheckrelay","on");
    else client.publish("showcheckrelay","off");
  }
  if(t == "mode" ){if(str == "1") flagMode = true; else flagMode = false;}
}
 
void setup() {
  Serial.begin(115200);
  pinMode(relay,OUTPUT);
  EEPROM.begin(256);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("connected"); 
      client.publish("showcheck","on");
      String str1 = (String(EEPROM.read(0)) + ":" + String(EEPROM.read(1)) + String(EEPROM.read(2)));
      client.publish("time1show",str1.c_str()); 
      String str2 = (String(EEPROM.read(3)) + ":" + String(EEPROM.read(4)) + String(EEPROM.read(5)));
      client.publish("time2show",str2.c_str()); 
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  client.subscribe("relay");
  client.subscribe("time1");
  client.subscribe("time2");
  client.subscribe("mode");
  client.subscribe("check");
}
 
void loop() {
  client.loop();
  if(!flagMode){ 
  autoMode();
  }
}
void time1(String str){
  EEPROM.write(0, str.substring(0, 2).toInt());
  EEPROM.write(1, str.substring(3, 4).toInt());
  EEPROM.write(2, str.substring(4, 5).toInt());
  EEPROM.commit();
  String str1 = (String(EEPROM.read(0))+ ":" + String(EEPROM.read(1)) + String(EEPROM.read(2)));
  client.publish("time1show",str1.c_str()); 
  }
void time2(String str){
  EEPROM.write(3, str.substring(0, 2).toInt());
  EEPROM.write(4, str.substring(3, 4).toInt());
  EEPROM.write(5, str.substring(4, 5).toInt());
  EEPROM.commit();
  String str2 = (String(EEPROM.read(3)) + ":" + String(EEPROM.read(4)) + String(EEPROM.read(5)));
  client.publish("time2show",str2.c_str());
  }
void autoMode(){
  if(millis() - last_time > 5000){
  last_time = millis();
    int time1 = (String(EEPROM.read(0)) + String(EEPROM.read(1)) + String(EEPROM.read(2))).toInt();
    int time2 = (String(EEPROM.read(3)) + String(EEPROM.read(4)) + String(EEPROM.read(5))).toInt();
    if(time1 > time2){
      if(((timeNow() - time2)<0) || (0<=(timeNow() - time1))) relay1("1");
      else relay1("0");
    } else {
      if(time1<=timeNow() && timeNow()<time2) relay1("1");
      else relay1("0");
    }
  }
}
bool f = true;
int timeNow() {
  while(f) {
   configTime(2 * 3600, 0, "ua.pool.ntp.org", "nist.time.gov");
   Serial.println("\nWaiting for time");
   while (!time(nullptr)) {
       Serial.print(".");
       delay(500);
       }
   Serial.println();
   f = false;
  }
  time_t now = time(nullptr);
  String str = String(ctime(&now)).substring(11, 13);
  String str2 = String(ctime(&now)).substring(14, 16);
  return (str+str2).toInt();
}
void relay1(String str) {
  if(last != str){
  digitalWrite(relay,str.toInt());
  if(str == "1") client.publish("showcheckrelay","on");
  else client.publish("showcheckrelay","off");
  }
  last = str;
}
