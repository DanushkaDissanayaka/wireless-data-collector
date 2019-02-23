#include "settings.h"
#include "Radio.h"

void setup()
{
  Serial.begin(9600);
  RadioInit();
}
void loop()
{

  // if (RadioWrite(GetData(), NODE_ADDRESS, 3))
  // {
  //   Serial.println("Write success");
  // }
  // else
  // {
  //   Serial.println("Fail to Write data");
  // }

  // delay(WRITING_WAITING);
  sendData();
}

String GetData(void)
{
  return "Data From Node 1";
}

void sendData(void)
{
  // Wait for get data request from controller
  if (RadioRead(0, NODE_ADDRESS_READING, 0) == DATA_REQUEST)
  {
    // Serial.println("Found data request");
    if (RadioWrite(GetData(), NODE_ADDRESS_WRITING, 3))
    {
      Serial.println("Write success");
    }
    else
    {
      Serial.println("Fail to Write data");
    }
  }
}