#include <EEPROM.h>
#define EEPROM_SIZE 64

byte porta;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }

  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }

   porta = EEPROM.read(0);
   porta = 2;
   EEPROM.write(0, porta);
   EEPROM.commit();

   Serial.println();
   Serial.print("Testando Porta ");
   Serial.println(porta);

   pinMode(porta, INPUT);
   delay(500);
}

void loop() {
 Serial.println(analogRead(porta));
  delay(100); // this speeds up the simulation
}
