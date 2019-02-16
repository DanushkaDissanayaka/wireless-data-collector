
// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

#include "settings.h"
#include "Radio.h"

// RF24 radio(7, 8); // CE, CSN
// const byte address[6] = "00001";

void setup() {
  RadioInit();
  Serial.begin(9600);
  /*radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();*/
  
}
void loop() {

 if(RadioWrite(GetData(),NODE_ADDRESS)){
   Serial.println("Write success");
 } 
 else{
   Serial.println("Fail to Write data");
 }
 delay(WRITING_WAITING);
  /*String data = GetData();
  const char datatoWrite[32];
  data.toCharArray(datatoWrite,32);
  radio.write(&datatoWrite, sizeof(datatoWrite));
  delay(1000);*/
}

String GetData(void){

  return "Data From Node 1";
}