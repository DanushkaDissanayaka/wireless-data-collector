# 1 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\DatatransferProtocall.h"
# 1 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\DatatransferProtocall.h"
# 1 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
# 2 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 2
# 3 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 2
# 4 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 2
# 5 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 2
# 6 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 2
# 7 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 2
# 8 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 2

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
        beep(100, 3); // Indicate radio error
    }

    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
    radio.enableAckPayload(); // We will be using the Ack Payload feature, so please enable it
    radio.enableDynamicPayloads(); // Ack payloads are dynamic payloads

    // Open pipes to other node for communication
    radio.openWritingPipe(CONTROLLER_ADDRESS);
    radio.openReadingPipe(1, NODE_ADDRESS);
    radio.startListening();
    radio.writeAckPayload(1, &message_count, sizeof(message_count)); // Add an ack packet for the next time around.  This is a simple
    ++message_count;

    radio.printDetails(); // Dump the configuration of the rf unit for debugging
    delay(50);
    attachInterrupt(0, checkRadio, 0x0); // Attach interrupt handler to interrupt #0 (using pin 2) on BOTH the sender and receiver
    beep(100, 2);
}

/********************** Main Loop *********************/
void loop()
{
    if (successFlag)
    {
        // Idicate successfully send the data;
        beep(100, 1);
        successFlag = false;
    }
    else if (errorflag)
    {
        // Idicate Tere is an error sending failed
        beep(100, 3);
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
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 69 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 69 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
                      "Send:OK"
# 69 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 3
                      ); &__c[0];}))
# 69 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
                      )));
        successFlag = true;
    }

    if (fail)
    {
        // Have we failed to transmit request?
        // Try to resend data again if we fails
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 77 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 77 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
                      "Send:Failed"
# 77 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 3
                      ); &__c[0];}))
# 77 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
                      )));
        errorflag = true;
    }

    if (rx || radio.available())
    {
        // Did we receive data  request form centrall ?
        Serial.println("data request received");
        uint8_t code; // Get the request code
        radio.read(&code, sizeof(code));
        Serial.println(code);
        char data[64];
        if (code == REQUEST_CODE)
        {
            strcpy(data, getData().c_str());
            radio.writeAckPayload(1, &data, sizeof(data));
        }
        else
        {
            Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 96 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 3
                          (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 96 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
                          "Invalid request"
# 96 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino" 3
                          ); &__c[0];}))
# 96 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Node\\node.ino"
                          )));
            beep(100, 3);
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
