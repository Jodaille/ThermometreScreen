/*=================================================================
Ce sketch est un scanner I2C: il essaye de communiquer avec toutes 
les adresses I2C possibles et affiche celle(s) qui réponde(nt).
  
                      BRANCHEMENT
* Pin SCD du moule à scanner  ----------->  SCD A5 de l’Arduino
* Pin SDA du moule à scanner  ----------->  SDA A4 de l’Arduino
================================================================ */
#define STATUS_LED 6
#define RTC_power_pin 9
#include <Wire.h>
void setup()
{
  pinMode(RTC_power_pin, OUTPUT);
  digitalWrite(RTC_power_pin, HIGH);
  Serial.begin(115200);
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(STATUS_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);

  Wire.begin();
  //Wire.begin(0, 2); // Change for D1mini
  
  Serial.println("\nI2C Scanner");
}

void loop()
{
  byte error, address;
  int nDevices;
  Serial.println("Recherche en cours...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("Equipment I2C trouve a l'addresse 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Erreur inconnue a l'address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("Aucun Equipement I2C trouve\n");
  else
    Serial.println("Fini\n");

  digitalWrite(STATUS_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(STATUS_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);           
}
