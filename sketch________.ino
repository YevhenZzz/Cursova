#include "WiFi.h"
#include "ESPAsyncWebServer.h"
const char* ssid = "TP-LINK_4830";  //replace
const char* password =  "15722089"; //replace
AsyncWebServer server(80);
int relayPin = 23;
void setup()
{
 pinMode(relayPin, OUTPUT);
 digitalWrite(relayPin, HIGH);
 Serial.begin(115200);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) 
 {
   delay(1000);
   Serial.println("Connecting to WiFi..");
 }
 Serial.println(WiFi.localIP());
 server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send(200, "text/plain", "Hello World");
 });
 server.on("/relay/off", HTTP_GET   , [](AsyncWebServerRequest *request){
   request->send(200, "text/plain", "ok");
   digitalWrite(relayPin, HIGH);
 });
  server.on("/relay/on", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send(200, "text/plain","ok");
   digitalWrite(relayPin, LOW);
 });  
 server.on("/relay/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send(200, "text/plain","ok");
   digitalWrite(relayPin, !digitalRead(relayPin));
 });
 server.on("/relay", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send(200, "text/plain", String(digitalRead(relayPin)));
 });
 server.begin();
}
void loop(){}
