/** Simple variometer based on ESP32, BMPXXX and I2C oled screen 
  Connect ESP32 with periferals via I2C according ESP pin mapping.
*/

#include <Wire.h>
#include "openVarioDisplay.h"
#include "openVarioSound.h"
#include "openVarioBMP.h"

float prev_alt;
float current_pressure;
int cycle_delay = 500;
unsigned long prev_read_millis;

void setup() {
  setCpuFrequencyMhz(40);

  current_pressure = 1013.25;

  initBMP(current_pressure);
  initDisplay();

  prev_alt = bmp.readAltitude(current_pressure);
  prev_read_millis = millis();
}

void loop() {
  int dt = millis() - prev_read_millis;
  if (dt > 0) {
    long start = millis();
    float alt = bmp.readAltitude(current_pressure);
    float vario = (alt - prev_alt) * 1000 / dt;
    int dur = playTone(vario);
    delay(dur);
    displayData(alt, vario, current_pressure);
    
    save_next_step(alt);  
    light_sleep(cycle_delay - (millis() - start));
  }
}

void light_sleep(int ms) {
  esp_sleep_enable_timer_wakeup(1000 * ms);
  esp_light_sleep_start();
}

void save_next_step(float alt) {
  prev_alt = alt;
  prev_read_millis = millis();
}