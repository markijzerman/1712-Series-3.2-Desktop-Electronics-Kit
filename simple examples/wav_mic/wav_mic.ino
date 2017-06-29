// WAV Trigger commands
#define TRK_PLAY_SOLO 0
#define TRK_PLAY_POLY 1
#define TRK_STOP 4


// microphone on port B
//wav trigger on port a

// based on cable diagrams, we know env pin maps onto portBline2
// aud maps into portBline3
const int kEnveloplePin =  A19; // = Port2.DMLow.getPin('B',2)
const int kAudioPin = A18; // = Port2.DMLow.getPin('B',3)
int envelope_value = 0;
int envelope_trigger = 0;
int envelope_threshold = 700;

const int kRxPin = 9; // = Port2.DMLow.getPin('A',3)
const int kTxPin = 10;// = Port2.DMLow.getPin('A',2)

SoftwareSerial WAVSerial(kRxPin,kTxPin);



void setup() {
  Serial.begin(9600);
  WAVSerial.begin(57600);

}

void loop() {
  envelope_value = analogRead(kEnvelopePin);
  envelope_trigger = envelope_value > envelope_threshold;

  if (envelope_trigger){
    trackControl(1,TRK_PLAY_SOLO);
  }
  

}

// trackControl function - see WAV trigger library
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


