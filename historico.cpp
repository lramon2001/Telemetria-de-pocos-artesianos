#include <WiFi.h>
#include <FirebaseESP32.h>
#include <ArduinoJson.h>
#include "time.h"

 
#define FIREBASE_HOST "https://telemetria-143af-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "gRQfrmAq68ifv910T2MTOaB2WvXYCqUxmQGbpeml"

#define WIFI_SSID "MARIAJOSE-2G"
#define WIFI_PASSWORD "JFM-8635"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
 
//Define FirebaseESP32 data object
FirebaseData firebaseData;
FirebaseJson json;

int porta = A0; //pino 36
int nivel = 0; 

 
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

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
 

}

void altera_string(char *data,int dia,int mes,int ano,int hora,int minuto, int segundo)
{
    
    char text_dia[2];
    sprintf(text_dia, "%d", dia);
   if(dia<10)
   {
    data[0] = '0';
    data[1] = text_dia[0];
   }
   else{
    data[0] = text_dia[0];
    data[1] = text_dia[1];
   }
   
    
    data[2]='/';
    
    char text_mes[2];
    sprintf(text_mes, "%d",mes);
  if(mes<10)
  {
      data[3] ='0';
    data[4] = text_mes[0];
  }
  else{
      data[3] = text_mes[0];
    data[4] = text_mes[1];
  }
    
    data[5]='/';
    
     char text_ano[2];
  
    sprintf(text_ano, "%d", ano);
    
    data[6] = text_ano[2];
    data[7] = text_ano[3];
    
   
    
    data[8]=' ';
    
    char text_hora[2];
  
    sprintf(text_hora, "%d", hora);  
   if(hora<10)
   {
       data[9] = '0';
    data[10] = text_hora[0];
   }
   else
   {
    data[9] = text_hora[0];
    data[10] = text_hora[1];
   }
    data[11]=':';
    
    char text_minuto[2];
    sprintf(text_minuto, "%d", minuto); 
  if (minuto<10)
  {
    data[12] = '0';
    data[13] = text_minuto[0];
  }
  else{
    data[12] = text_minuto[0];
    data[13] = text_minuto[1];
  }
    data[14]=':';
    
    char text_segundo[2];
    sprintf(text_segundo, "%d", segundo);  
   if(segundo<10)
   {
       data[15]= '0';
    data[16] = text_segundo[0];
   }
   else{
       
   
    data[15]= text_segundo[0];
    data[16] = text_segundo[1];
   } 
    
}

int retorna_nivel_parametrizado(int nivel)
{
 return map(nivel,0,4095,0,1000); 
}
void envia_nivel_firebase()
{
  int dado = retorna_nivel_parametrizado(analogRead(porta));
  Serial.println(dado); 
   json.set("/sinal", dado);
  Firebase.pushJSON(firebaseData,"/nivel",json);

   struct tm timeinfo;

 char datat[20] = "00/00/00 00:00:00";

altera_string(datat,timeinfo.tm_mday,timeinfo.tm_mon + 1,timeinfo.tm_year +1900,timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
json.set("/dataHora", datat);
   Firebase.pushJSON(firebaseData,"/nivel",json);

}
void loop()
{
 envia_nivel_firebase();
 delay(500); 
  
 
}

