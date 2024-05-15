
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
#define ONE_WIRE_BUS 8

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

DeviceAddress temperature1 {0x28, 0x2A, 0xAC, 0x29, 0x07, 0x00, 0x00, 0xEC};

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)

void setup() {
  Serial.begin(115200);
  // sensors initialisation
  sensors.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.clearDisplay();
  display.display();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    sensors.requestTemperatures();
    float t1 = sensors.getTempC(temperature1);
    Serial.print(t1);Serial.println(F(" °C"));
    // display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,4);
    display.println("Ambient");

    display.setTextSize(2);
    display.setCursor(50,0);
    display.println(t1,1);

    display.setCursor(110,0);
    display.println("C");

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.println("Target");

    display.setTextSize(2);
    display.setCursor(50,17);
    display.println(t1,1);

    display.setCursor(110,17);
    display.println("C");

    display.display();
  }
}
