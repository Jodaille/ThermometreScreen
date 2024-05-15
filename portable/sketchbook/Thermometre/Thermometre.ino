
long previousMillis;// keep last loop millis()
const long interval = 500;

/**
 *  We need OneWire library to access DS18B20 sensors
 *  the library must be placed in libraries directory
 *  in the sketchs directory of Arduino IDE (settings menu)
 *
 *  cf: https://github.com/PaulStoffregen/OneWire/archive/master.zip
 */
#include <OneWire.h>

/**
 * We also need DallasTemperature library
 * cf: https://github.com/milesburton/Arduino-Temperature-Control-Library
 */
#include <DallasTemperature.h>

/*
 *  The data wire of DS18B20 (often yellow?) is wired to pin 8 (D8) of Arduino
 *  a 4,7kOhm resistor is wired between Vcc and D8
 */
#define ONE_WIRE_BUS 2

/**
 * Cretae a oneWire instance to be able to
 * communicate with OneWire devices
 * Nb: not only Maxim/Dallas sensors
 */
OneWire oneWire(ONE_WIRE_BUS);

/**
 * Passing Onewire instance to our new
 * sensors object DallasTemperature
 */
DallasTemperature sensors(&oneWire);

DeviceAddress temperature1 {0x28, 0xFF, 0x84, 0x28, 0x90, 0x15, 0x04, 0xAA};

void setup() {
  Serial.begin(115200);
  // sensors initialisation
  sensors.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    sensors.requestTemperatures();
    float t1 = sensors.getTempC(temperature1);
    Serial.print(t1);Serial.println(F(" °C"));
  }
}
