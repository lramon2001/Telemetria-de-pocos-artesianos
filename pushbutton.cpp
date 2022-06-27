int led = 2;
int botao = 3;
int pressionado=0;
int contador =0;
void setup()
{
  pinMode(botao,INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
 pressionado = digitalRead(botao);
 if(pressionado == HIGH)
 {
  digitalWrite(led,HIGH);
  contador++;
   delay(1000);
 }
  else
  {
    digitalWrite(led,LOW);
  }
  Serial.println(contador);
  
  
    
}
