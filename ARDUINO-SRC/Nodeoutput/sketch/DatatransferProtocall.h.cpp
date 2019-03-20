#include <Arduino.h>
#line 1 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\DatatransferProtocall.h"
#line 14 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
void setup();
#line 44 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
void loop();
#line 60 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
void checkRadio(void);
#line 102 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
String getData();
#line 109 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
uint16_t voltageTest();
#line 0 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
#line 1 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\DatatransferProtocall.h"
#ifndef DATA_TRANSFER_H
    #define DATA_TRANSFER_H
#endif
#line 1 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "setting.h"
#include "buzzer.h"
#include "radio.h"

static uint32_t message_count = 0;
bool sendData = false;
bool successFlag = false;
bool errorflag = false;

void setup()
{
    Serial.begin(115200);
    printf_begin();
    buzInit(10);
    // Setup and configure rf radio
    while (!radio.begin())
    {
        beep(BEEP_TIME_INTERVAL, ERROR_BEEP); // Indicate radio error
    }

    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
    radio.enableAckPayload();      // We will be using the Ack Payload feature, so please enable it
    radio.enableDynamicPayloads(); // Ack payloads are dynamic payloads

    // Open pipes to other node for communication
    radio.openWritingPipe(CONTROLLER_ADDRESS);
    radio.openReadingPipe(1, NODE_ADDRESS);
    radio.startListening();
    radio.writeAckPayload(1, &message_count, sizeof(message_count)); // Add an ack packet for the next time around.  This is a simple
    ++message_count;

    radio.printDetails(); // Dump the configuration of the rf unit for debugging
    delay(50);
    attachInterrupt(0, checkRadio, LOW); // Attach interrupt handler to interrupt #0 (using pin 2) on BOTH the sender and receiver
    beep(BEEP_TIME_INTERVAL, INFO_BEEP);
}

/********************** Main Loop *********************/
void loop()
{
    if (successFlag)
    {
        // Idicate successfully send the data;
        beep(BEEP_TIME_INTERVAL, SUCCESS_BEEP);
        successFlag = false;
    }
    else if (errorflag)
    {
        // Idicate Tere is an error sending failed
        beep(BEEP_TIME_INTERVAL, ERROR_BEEP);
        errorflag = false;
    }
}

void checkRadio(void)
{

    bool tx, fail, rx;
    radio.whatHappened(tx, fail, rx); // What happened to trigger interrupt?

    if (tx)
    {
        // Have we successfully transmitted request?
        Serial.println(F("Send:OK"));
        successFlag = true;
    }

    if (fail)
    {
        // Have we failed to transmit request?
        // Try to resend data again if we fails
        Serial.println(F("Send:Failed"));
        errorflag = true;
    }

    if (rx || radio.available())
    {
        // Did we receive data  request form centrall ?
        Serial.println("data request received");
        uint8_t code; // Get the request code
        radio.read(&code, sizeof(code));
        Serial.println(code);
        char data[BUFF_SIZE];
        if (code == REQUEST_CODE)
        {
            strcpy(data, getData().c_str());
            radio.writeAckPayload(1, &data, sizeof(data));
        }
        else
        {
            Serial.println(F("Invalid request"));
            beep(BEEP_TIME_INTERVAL, ERROR_BEEP);
        }
    }
}

String getData()
{
    uint32_t time = millis();

    return String(time) + "&" + String(voltageTest());
}

uint16_t voltageTest()
{
    return analogRead(A3);
}

