/*


  nRF24    Arduino UNO/NANO
 
  CE    -> 7
  CSN   -> 8
  MOSI  -> 11
  MISO  -> 12
  SCK   -> 13
  IRQ   -> -
  VCC   -> 3.3V
  GND   -> GND
  ---------------------------

  Arduino UNO/NANO

  Buzzer 
  Vcc     -> D6
  Gnd     -> Gnd
  
  DHT11 
  Vcc     -> 5V
  Gnd     -> Gnd
  Out     -> D4

  Gas Sensor
  Vcc     -> 5V
  Gnd     -> Gnd
  Analog  -> A0

  RGB led 
  R        -? 9
  G        -? 10
  B        -? 3
  Gnd      -> Gnd

  BMP280 
  Vcc      -> 5V
  GND      -> GND
  SDA      -> A4
  SCL      -> A5

  MPU6050   
 
  Vcc      -> 5V
  GND      -> GND
  SDA      -> A4
  SCL      -> A5

  HMC5883L

  Vcc      -> 5V
  GND      -> GND
  SDA      -> A4
  SCL      -> A5


*/


#include <SPI.h>
#include <NRFLite.h>
#include <Wire.h>



const static uint8_t RADIO_ID = 1;              // Our radio id
const static uint8_t DESTINATION_RADIO_ID = 0;  // Id of the radio we will transmit to
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
  Serial.println("Calibrating...");



 
  Serial.println("Done Calibration");


  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)) {
    Serial.println("Cannot communicate with radio");
    while (1);
  }


  _radioData.FromRadioId = RADIO_ID;


}


void loop() {


  mpu.Execute();


  while (mpu.GetRawAccX() <= -8000) {


    _radioData.Data = 1;
    sendData();
    Serial.println("front");
    mpu.Execute();


  }


  while (mpu.GetRawAccX() >= 8000) {


    _radioData.Data = 2;
    sendData();
    Serial.println("back");
    mpu.Execute();


  }


  while (mpu.GetRawAccY() <= -8000) {


    _radioData.Data = 3;
    sendData();
    Serial.println("left");
    mpu.Execute();


  }


  while (mpu.GetRawAccY() >= 8000) {


    _radioData.Data = 4;
    sendData();
    Serial.println("right");
    mpu.Execute();


  }


  while (mpu.GetRawAccX() < 8000 and mpu.GetRawAccX() > -8000 and mpu.GetRawAccY() < 8000 and mpu.GetRawAccY() > -8000) {


    _radioData.Data = 5;
    sendData();
    Serial.println("none");
    mpu.Execute();


  }


}


void sendData(){


  Serial.print("Sending");


  if (_radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData))) {
    Serial.println("...  Success");
  }
  else {
    Serial.println("...  Failed");
  }


  mpu.Execute();
  delay(500);


}

