/** Simple variometer based on ESP32, BMP280 and I2C oled screen 
  Connect ESP32 with periferals via I2C according ESP pin mapping.
*/

#include <Wire.h>
#include "openVarioDisplay.h"
#include "openVarioSound.h"
#include "openVarioBMP.h"

int dt;
float prev_alt;
float alt;
float current_pressure;

unsigned long prev_read_millis;
float vario;

void setup() {
  setCpuFrequencyMhz(80);
  current_pressure = 1013.25;

  initBMP(current_pressure);
  initDisplay();

  prev_alt = bmp.readAltitude(current_pressure);
  prev_read_millis = millis();
}

void loop() {
  dt = millis() - prev_read_millis;
  if (dt > 500) {
    alt = bmp.readAltitude(current_pressure);
    vario = (alt - prev_alt) * 1000 / dt;
    playTone(vario);
    displayData(alt, vario, current_pressure);
    
    save_next_step();
  }
  noTone(25);
}

void save_next_step() {
  prev_alt = alt;
  prev_read_millis = millis();
}



