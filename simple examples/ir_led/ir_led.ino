// Living Architecture Systems
// ir_led.ino
// Turns on an LED after passing a pre-defined proximity threshold

// Hardware Setup:
// one node controller, one low current device module
// one LED, one IR sensor
// Connect node controller and RPi over USB
// Plug the device module into node controller port 1
// Plug IR sensor into device module port E
// Plug LED into device module port F

//IR SENSOR SETUP

// from 3.1 Device Module A schematics we see DM port E is connected to I/O pin 4
// from pinout diagram (or node controller schematics) NC port 1 pin 4 is connected to Teensy pin A7
// and if using node_ports library you'll find Port1.DMLow.getPin('E') == A7
int ir_pin = A7;
int ir_threshold = 400;
bool ir_trigger = false;
int ir_value = 0;

// LED SETUP
// from 3.1 Device Module A schematics we see DM port F is connected to DM pin 3
// from pinout diagram (or node controller schematics) NC port 1 pin 3 is connected to Teensy pin 6
// and if using node_ports library you'll find Port1.DMLow.getPin('F') == 6
int led_pin = 6;


void setup() {
  pinMode(ir_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  ir_value = analogRead(ir_pin);
  ir_trigger = ir_value > 400;
  digitalWrite(led_pin, ir_trigger);
}
