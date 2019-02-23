#include "settings.h"
#include "Radio.h"

String Nodedata = "";

#define NUMITEMS(arg) ((unsigned int)(sizeof(arg) / sizeof(arg[0]))) // Count number of arry Items

void setup()
{
    Serial.begin(9600);
    RadioInit();
}
void loop()
{
    // for (uint8_t i = 0; i < NUMITEMS(NODE_ADDRESS); i++)
    // {

    //     Nodedata = RadioRead(0, NODE_ADDRESS[i], 2);

    //     if (!(Nodedata == "e"))
    //     {
    //         Serial.println(Nodedata);
    //     }
    //     else
    //     {
    //         Serial.println("Error In " + NODE_NAME[i]);
    //     }
    //     // Serial.println(Nodedata);
    // }
    for (uint8_t i = 0; i < NUMITEMS(NODE_ADDRESS_READING); i++)
    {
        readFromNode(i);
    }
    delay(5000);
}

String readFromNode(uint8_t i)
{

    if (RadioWrite(DATA_REQUEST, NODE_ADDRESS_WRITING[i], 2))
    {
        // if  get ack from node do communication task here
        Nodedata = RadioRead(0, NODE_ADDRESS_READING[i], 2);

        if (!(Nodedata == "e"))
        {
            Serial.println(Nodedata);
            return Nodedata;
        }
        else
        {
            Serial.println("Error In Read " + NODE_NAME[i]);
            return "Error In Read " + NODE_NAME[i];
        }
    }
    else
    {
        // if not gert ack from node return error here
        Serial.println("Error In Write " + NODE_NAME[i]);
        return "Error In Write " + NODE_NAME[i];
    }
}