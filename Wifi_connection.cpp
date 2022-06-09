#include <WiFi.h>         
#include <IOXhop_FirebaseESP32.h>                           
#include <ArduinoJson.h>                   

#define WIFI_SSID "nome do wifi"                   
#define WIFI_PASSWORD "senha do wifi"         
#define FIREBASE_HOST "link do firebase"    
#define FIREBASE_AUTH "senha do banco"   

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print("Conectando ao wifi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
