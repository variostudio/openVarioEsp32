#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 128 // OLED display height, in pixels
#define OLED_RESET -1     // can set an oled reset pin if desired
Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 100000, 100000);


void displayData(float alt, float vario, float current_pressure) {
  display.clearDisplay();
  display.setTextSize(1);                  
  display.setCursor(0,0);
  display.setTextColor(SH110X_WHITE);             
  display.print(alt, 2);
  display.print(" m");

  display.setCursor(0,10);
  display.print(alt * 3.28, 2);
  display.print(" ft");

  display.setCursor(0,20);
  display.print(current_pressure, 2);
  display.print(" mb");

  display.setCursor(0,120);
  display.print("OpenVario esp32 0.1");

  display.setTextSize(3);                  
  display.setCursor(0,30);        
  display.setTextColor(SH110X_WHITE);     
  display.print(" ");
  if (vario >= 0) {
    display.print("+");
  } 
  display.print(vario, 2);

  display.display();
}

void displayWelcome() {
  display.clearDisplay();
  display.setTextSize(1);                  
  display.setCursor(0,0);
  display.setTextColor(SH110X_WHITE);             
  display.print("Version:  0.1");

  display.setTextSize(2);                  
  display.setCursor(0,10);        
  display.setTextColor(SH110X_WHITE);     
  display.print(" OpenVario");

  display.display();
}

void initDisplay() {
  display.begin(0x3C, true);
  
  displayWelcome();
  delay(1000);
}
