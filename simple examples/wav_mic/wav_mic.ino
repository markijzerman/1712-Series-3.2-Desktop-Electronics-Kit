// Living Architecture Systems
// wav_mic.ino
// Plays a sound after passing a pre-defined volume threshold
// Bonus example: it can get tricky, but never impossible, to manually find pin numbers

// Hardware Setup:
// One node controller, one low current device module
// One WAV Trigger and speaker, one sound detector

// Plug the device module into node controller port 2
// Plug WAV trigger into device module port A
// Plug sound detector into device module port B

// SOUND DETECTOR SETUP

// DM port B has two data pins: DM port B pin 2 and DM port B pin 3
// from 3.1 Device Module A schematics we see DM port B pin 2 = DM pin 8 and DM port B pin 3 = DM pin 7
// from pinout diagram (or node controller schematics) NC port 2 pin 8 is connected to Teensy pin A19
// and NC port 2 pin 7 is connected to Teensy pin A18
// and if using node_ports library you'll find that
// Port2.DMLow.getPin('B',2) == A19
// Port2.DMLow.getPin('B',3) == A18

// sound detector cable mapping shows
// envelope == DM port B pin 2
// audio == DM port B pin 3

// Therefore, 
int envelope_pin =  A19;
int audio_pin = A18;

// rest of variables for sound detector
int envelope_value = 0;
int envelope_trigger = 0;
int envelope_threshold = 700;


// WAV TRIGGER SETUP

// DM port A has two data pins: DM port A pin 2 and DM port A pin 3
// from 3.1 Device Module A schematics we see DM port B pin 2 = DM pin 2 and DM port B pin 3 = DM pin 1
// from pinout diagram (or node controller schematics) NC port 2 pin 2 is connected to Teensy pin 10
// and NC port 2 pin 1 is connected to Teensy pin 9
// and if using node_ports library you'll find that
// Port2.DMLow.getPin('A',2) == 10
// Port2.DMLow.getPin('A',3) == 9

// WAV trigger cable mapping shows
// WAV rx == DM port B pin 2
// WAV tx == DM port B pin 3

// Therefore (REMINDER: controller rx connects to WAV trigger tx, vice versa),
int rx_pin = 9;
int tx_pin = 10;

// WAV triggers are controlled by a serial connection
// Not by coincidence, Teensy pins 9 and 10 can be used as hardware Serial2
// However, a SoftwareSerial is limited but has enough function to control a WAV trigger
// if not using hardware serial pins the following line will become SoftwareSerial WAVSerial(rx_pin,tx_pin);
#define WAVSerial Serial2

// WAV Trigger commands (usually, these are defined in a separate header file)
#define TRK_PLAY_SOLO 0
#define TRK_PLAY_POLY 1
#define TRK_STOP 4

// trackControl function - see WAV trigger library for details
void trackControl(int trk, int code){
  uint8_t txbuf[8];
  txbuf[0] = 0xf0; // SOM1;
  txbuf[1] = 0xaa; // SOM2;
  txbuf[2] = 0x08;
  txbuf[3] = 3; // CMD_TRACK_CONTROL;
  txbuf[4] = (uint8_t)code;
  txbuf[5] = (uint8_t)trk;
  txbuf[6] = (uint8_t)(trk>>8);
  txbuf[7] = 0x55; // EOM;
  WAVSerial.write(txbuf,8);
}


void setup() {
  // start the serial port for the WAV trigger
  WAVSerial.begin(57600);
}

void loop() {
  envelope_value = analogRead(envelope_pin);
  envelope_trigger = envelope_value > envelope_threshold;
  if (envelope_trigger){
    trackControl(1,TRK_PLAY_SOLO);
  }
}




