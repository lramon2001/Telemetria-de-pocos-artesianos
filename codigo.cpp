#include <WiFi.h>
#include <FirebaseESP32.h>
#include <ArduinoJson.h>
 
 
#define FIREBASE_HOST "https://teste-potenciometro-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "DxD4uGRwxnTGdK6vsjI7ya0fakeOZEVejlB0tLnu"

#define WIFI_SSID "MARIAJOSE-2G"
#define WIFI_PASSWORD "JFM-8635"
 
 
//Define FirebaseESP32 data object
FirebaseData firebaseData;
FirebaseJson json;

int porta = A0; //pino 36
int pulso = 0; 

 
void setup()
{
 
 Serial.begin(115200);
 
 pinMode(porta, INPUT);
 
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
 
  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */
 
  //String path = "/data";
  
 
  Serial.println("------------------------------------");
  Serial.println("Connected...");
  
}

int retorna_pulso_paramametrizado(int pulso)
{
 return map(pulso,0,4095,0,1000); 
}
void envia_pulso_firebase()
{
  int dado = retorna_pulso_paramametrizado(analogRead(porta));
  Serial.println(dado); 
   json.set("/data", dado);
  Firebase.pushJSON(firebaseData,"/Sensor",json);

}
void loop()
{
 envia_pulso_firebase();
 delay(500); 
  
 
}
