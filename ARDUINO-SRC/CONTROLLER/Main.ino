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
    for (uint8_t i = 0; i < NUMITEMS(NODE_ADDRESS); i++)
    {
        secondRead = true;
        Nodedata = RadioRead(0, NODE_ADDRESS[i]) ;

        if (!(Nodedata == "e")){
            Serial.println(Nodedata);
        }
        else{
            Serial.println("Error In " + NODE_NAME[i]);
        }
        // Serial.println(Nodedata);
    }
}