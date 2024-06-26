/*


  nRF24    Arduino UNO/NANO
  
  VCC   -> 3.3V
  GND   -> GND
  CE    -> 7
  CSN   -> 8
  MOSI  -> 11
  MISO  -> 12
  SCK   -> 13
  IRQ   -> -


*/


#include <SPI.h>
#include <NRFLite.h>


const static uint8_t RADIO_ID = 0;  // Our radio id
const static uint8_t PIN_RADIO_CE = 7;
const static uint8_t PIN_RADIO_CSN = 8;


struct RadioPacket {
  uint8_t FromRadioId;
  uint32_t Data;
};


NRFLite _radio;
RadioPacket _radioData;


void setup() {


  Serial.begin(9600);


  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)) {
    Serial.println("Cannot communicate with radio");
    while (1);
  }


}


void loop() {


  while (_radio.hasData()) {


    _radio.readData(&_radioData);


    int data = _radioData.Data;
    if (data == 1) Serial.println("front");
    else if (data == 2) Serial.println("back");
    else if (data == 3) Serial.println("left");
    else if (data == 4) Serial.println("right");
    else if (data == 5) Serial.println("none");


  }


}

