#ifdef ESP32
 #include <Arduino.h>
 #include <WiFi.h>
 #include <AsyncTCP.h>
 #include <ESPAsyncWebServer.h>
 #include <AsyncElegantOTA.h>
#else
 #include <Arduino.h>
 #include <ESP8266WiFi.h>
 #include <ESPAsyncTCP.h>
 #include <ESPAsyncWebServer.h>
 #include <AsyncElegantOTA.h>
#endif
AsyncWebServer server(80);
#define BLYNK_TEMPLATE_ID "TMPL3z6ZYJYUn"
#define BLYNK_TEMPLATE_NAME "BUILDING AUTOMATION"
#define BLYNK_AUTH_TOKEN "ItyBMkJeHFbFr6q3KZ60eE3NnJK4o-jz"
#define BLYNK_PRINT Serial
#ifdef ESP32
 #include <WiFi.h>
 #include <BlynkSimpleEsp32.h>
#else
 #include <ESP8266WiFi.h>
 #include <BlynkSimpleEsp8266.h>
#endif
char auth[] = "ItyBMkJeHFbFr6q3KZ60eE3NnJK4o-jz";
char ssid[] = "project17";
char pass[] = "project17";
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#define VPIN_BUTTON V2 
#define light 15
String state1="OFF";
#define entry 18
#define exit 19
int entry_sense,exit_sense;
int count=0;
WidgetLCD lcd1(V0);
WidgetLED indicator(V1);
void setup()
{
 Serial.begin(9600);
 
 pinMode(entry,INPUT);
 pinMode(exit,INPUT);
 pinMode(light,OUTPUT);
 digitalWrite(light,HIGH);
 lcd.init();
 lcd.backlight();
 lcd.clear();
cd.print("CONNECTING TO...");
 lcd.setCursor(0,1);
 lcd.print(ssid);
 delay(1000);
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, pass);
 Serial.print("Connecting to WiFi ..");
 while(WiFi.status() != WL_CONNECTED)
 {
 Serial.print('.');
 delay(500);
 }
 Blynk.config(auth);
 Serial.println("READY");
 lcd.clear();
 lcd.print(" WIFI CONNECTED ");
 lcd.setCursor(0,1);
 lcd.print(WiFi.localIP());
 delay(5000);
 lcd.clear();
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
 request->send(200, "text/plain", "Hi! I am ESP32.");
 });
 AsyncElegantOTA.begin(&server); // Start ElegantOTA
 server.begin();
 Serial.println("HTTP server started");
}
BLYNK_CONNECTED()
{

Blynk.syncVirtual(VPIN_BUTTON);
}
BLYNK_WRITE(VPIN_BUTTON) 
{
 int toggleState = param.asInt();
 Serial.println(toggleState);
 if(toggleState==1)
 {
 state1="ON";
 digitalWrite(light,LOW);
 }
 else
 {
 state1="OFF";
 digitalWrite(light,HIGH);
 }
}
void loop()
{
 entry_sense=digitalRead(entry);
 exit_sense=digitalRead(exit);
 if(entry_sense==0)
 {
 count=count+1;
 lcd.clear();lcd1.clear();
 lcd.print(" * WELCOME * ");lcd1.print(0,0," * WELCOME * ");
 
digitalWrite(2,HIGH);indicator.on();delay(300);digitalWrite(2,LOW);indicator.off();delay(300);
 delay(1000);
 }
 else if(exit_sense==0 && count >=1)
{
count=count-1;
 lcd.clear();lcd1.clear();
 lcd.print("* VISIT AGAIN ");lcd1.print(0,0," VISIT AGAIN *");
 
digitalWrite(2,HIGH);indicator.on();delay(300);digitalWrite(2,LOW);indicator.off();delay(300);
 delay(1000);
 }
 lcd.clear();lcd1.clear();
 lcd.print("COUNT : ");lcd1.print(0,0,"COUNT : ");lcd.print(count);lcd1.print(8,0,count);
 lcd.setCursor(0,1);
 lcd.print("LIGHT : ");lcd1.print(0,1,"LIGHT : ");lcd.print(state1);lcd1.print(8,1,state1);
 
 
digitalWrite(2,HIGH);indicator.on();delay(300);digitalWrite(2,LOW);indicator.off();delay(300);
Blank.run();
}