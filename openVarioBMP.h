#include <Adafruit_BMP3XX.h>

Adafruit_BMP3XX bmp; 

void initBMP(float pressure) {
  bmp.begin_I2C();

  bmp.setPressureOversampling(BMP3_OVERSAMPLING_16X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_7);
  bmp.setOutputDataRate(BMP3_ODR_6_25_HZ);

  bmp.readAltitude(pressure);
}