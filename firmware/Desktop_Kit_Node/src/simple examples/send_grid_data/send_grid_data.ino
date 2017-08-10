#include "config.h"
#include "usb_serial_comm.h"

#include <i2c_t3.h>
#include <GridEye.h>

GridEye myeye;
USBSerialComm PiSerial(57600);

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
  // int temp = myeye.thermistorTemp();
  // Serial.print(F("Thermistor Temp: "));
  // Serial.println(temp * 0.065); // 1 unit = 0.065 degree
  //
  // myeye.pixelOut(pixel);
  // Serial.println(F("Pixel Output: "));
  // for (int i = 0; i < 64; i++) {
  //   if (i && ((i % 8) == 0)) {
  //     Serial.println();
  //   }
  //   Serial.print(pixel[i] * 0.25); // 1 unit = 0.25 degree
  //   Serial.print(' ');
  // }
  // Serial.println();
  //
  // // Wait for 0.5 second
  // delay(500);


  int temp = myeye.thermistorTemp();

  Serial.print(F("\nThermistor Temp: "));
  Serial.println(temp * 0.065); // 1 unit = 0.065 degree

  myeye.pixelOut(pixel);
//  dataGenerator(pixel);

  Serial.println(F("Pixel Output: "));

  int counter = 0;
  uint8_t pxlindex[64];

  for (int i = 0; i < 64; i++) {
    if(pixel[i]*0.25 > 35){
      pxlindex[counter] = lowByte(i); // since i<64, converting into 8-bit using lowByte() does not lose accuracy.
      counter += 1;
    }

    if (i && ((i% 8 ) == 0 )){
      Serial.println();
    }
    Serial.print(pixel[i] * 0.25); // 1 unit = 0.25 degree
    Serial.print(' ');
  }
  Serial.println();

  for (int i = 0; i < counter; i++){
    if (i && ((i% 8 ) == 0 )) {
      Serial.println();
    }
    Serial.print(pxlindex[i]);
    Serial.print(' ');
  }

  Serial.print("Counter : ");
  Serial.print(counter);
  Serial.print('\n');
  
  PiSerial.SendMessage(TRIGGER_CODE_GRIDEYE_THRESHOLD,pxlindex, counter);
  // Wait for 0.5 second
  delay(500);
}
//
//void readPixels(){
//  int temp = myeye.thermistorTemp();
//
//  Serial.print(F("Thermistor Temp: "));
//  Serial.println(temp * 0.065); // 1 unit = 0.065 degree
//
//  myeye.pixelOut(pixel);
//  Serial.println(F("Pixel Output: "));
//
//  int counter = 0;
//  uint8_t pxlindex[64];
//
//  for (int i = 0; i < 64; i++) {
//    if(pixel[i] > 35){
//      pxlindex[counter] = lowByte(i); // since i<64, converting into 8-bit using lowByte() does not lose accuracy.
//      counter += 1;
//    }
//    Serial.print(pixel[i] * 0.25);  // 1 unit = 0.25 degree
//    Serial.print(' ');
//  }
//  Serial.println();
//
//  for (int i = 0; i < counter; i++){
//    Serial.print(pxlindex[i]);
//    Serial.print(' ');
//  }
////  PiSerial.SendMessage(TRIGGER_CODE_GRIDEYE_THRESHOLD,pxlindex, counter);
//  // Wait for 0.5 second
//  delay(500);
//}

void dataGenerator(int *data){
  
  for(int i = 0; i < 64; i++){
    data[i] = random(120,160);
  }

}

