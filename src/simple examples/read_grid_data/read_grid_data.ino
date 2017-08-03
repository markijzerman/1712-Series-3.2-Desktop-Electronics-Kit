#include <i2c_t3.h>
#include <GridEye.h>

GridEye myeye;

void setup(void)
{
  // Join I2C
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_16_17, I2C_PULLUP_INT, 400000);
  // Serial port initialization
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
}

// To save the data
int pixel[64];

void loop(void)
{
  //Read the temperature
  int temp = myeye.thermistorTemp();
  Serial.print(F("Thermistor Temp: "));
  Serial.println(temp * 0.065); // 1 unit = 0.065 degree

  myeye.pixelOut(pixel);
  Serial.println(F("Pixel Output: "));
  for (int i = 0; i < 64; i++) {
    if (i && ((i % 8) == 0)) {
      Serial.println();
    }
    Serial.print(pixel[i] * 0.25); // 1 unit = 0.25 degree
    Serial.print(' ');
  }
  Serial.println();

  // Wait for 0.5 second
  delay(500);
}
