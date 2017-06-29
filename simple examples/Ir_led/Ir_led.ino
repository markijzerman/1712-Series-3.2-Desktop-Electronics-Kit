// IR sensor is plugged into port E on DM, DM plugged into port 1 on node
// from 3.1 Device Module A schematics we see port E is connected to I/O line 4
// from pinout diagram (or node controller schematics) we see port 1 line 4 is connect to Teensy pin A7
const int kIrPin = A7; // or Port1.DMLow.getPin('E')
const int kIrThreshold = 400;
bool ir_trigger = false;
int ir_value = 0;

// similarly, an LED on port F is controlled by Teensy pin 6
const int kLedPin = 6; //or Port1.DMLow.getPin('F')


void setup() {
  Serial.begin(9600);

}

void loop() {
  ir_value = analogRead(kIrPin);
  ir_trigger = ir_value > 400;

  digitalWrite(kLedPin, ir_trigger);
  Serial.write("IR sensor triggered");

}
