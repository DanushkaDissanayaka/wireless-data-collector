# 1 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
# 1 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
# 2 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 2
# 3 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 2
# 4 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 2
# 5 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 2
# 6 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 2
# 7 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 2
# 8 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 2
# 9 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 2

/* jason declarations */
StaticJsonDocument<512> doc;
String jsonOutput = "";
/*************************/

static uint32_t message_count = 0;
static bool dataWaitingFlag = false;
static bool dataDecriptionFlag = false;
static bool badDataFlag = false;
unsigned int startTime = 0;
unsigned int endTime = 0;
unsigned long packetCounter = 0;

String incomingData; // hold incoming data before store

void setup()
{
  Serial.begin(115200);
  printf_begin();
  // Setup and configure rf radio
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.enableAckPayload(); // We will be using the Ack Payload feature, so please enable it
  radio.enableDynamicPayloads(); // Ack payloads are dynamic payloads

  // Open pipes to other node for communication
  radio.openWritingPipe(NODE_ADDRESS[0]);
  radio.openReadingPipe(1, CONTROLLER_ADDRESS);

  radio.printDetails(); // Dump the configuration of the rf unit for debugging
  delay(50);
  attachInterrupt(0, checkRadio, 0x0); // Attach interrupt handler to interrupt #0 (using pin 2) on BOTH the sender and receiver
}

void loop()
{

  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 48 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 48 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                "\tNew cycle bigin..."
# 48 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                ); &__c[0];}))
# 48 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                )));
  packetCounter ++; // incriment packet Count
  String nodeData[((unsigned int) (sizeof(NODE_ADDRESS) / sizeof(NODE_ADDRESS[0]))) /* Count number of arry Items*/]; // hold every node data to this array;

  for (uint8_t i = 0; i < ((unsigned int) (sizeof(NODE_ADDRESS) / sizeof(NODE_ADDRESS[0]))) /* Count number of arry Items*/; i++)
  {
    radio.openWritingPipe(NODE_ADDRESS[i]);
    delay(200); // add some delay to configure radio
    nodeData[i] = getData();
  }

  jsonOutput = "";
  JsonObject data = doc.to<JsonObject>(); // create json object

  for (uint8_t i = 0; i < ((unsigned int) (sizeof(NODE_ADDRESS) / sizeof(NODE_ADDRESS[0]))) /* Count number of arry Items*/; i++)
  {
    data["node" + String(i)] = nodeData[i];
  }

  data["centralName"] = "Test Location"; // Insert data collecting central name
  data["DateTime"] = "2019/03/16 20:25"; // Add date time
  data["packet"] = packetCounter; // Add Packet number
  serializeJson(data, jsonOutput);
  Serial.println(jsonOutput);
  Serial.println(jsonOutput.length());
  delay(10000); // Wait some time before beign next cycle
}

String getData()
{
  uint8_t retry = 0;
  bool badCommunicationLinkFlag = false; // Indicate link is not working

  if (!dataWaitingFlag && !dataDecriptionFlag) // send data request if we not wait data from node
  {
    sendRequest();
    dataWaitingFlag = true;
  }
  while (dataWaitingFlag)
  {
    // Do nothing wait for data receive
    //If bad Data resived try Again
    if(false) Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 90 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 90 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                            "Waiting for data"
# 90 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                            ); &__c[0];}))
# 90 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                            )));
    if (badDataFlag)
    {
      sendRequest();
      if (retry > 5)
      { // if reach the maximum retrys break the loop
        if(false) Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 96 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 96 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                                "Communication error"
# 96 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                                ); &__c[0];}))
# 96 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                                )));
        badCommunicationLinkFlag = true;
        break;
      }
      retry++;
      delay(500);
    }
    else
    {
      delay(100);
    }
  }
  while (!dataDecriptionFlag && !badCommunicationLinkFlag)
  {
    //Wait for data to set for decript
    if(false) Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 111 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 111 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                            "\tWaiting for Decript"
# 111 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                            ); &__c[0];}))
# 111 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                            )));
    delay(50);
  }

  if (dataDecriptionFlag)
  {
    dataDecriptionFlag = false;
    return decriptData(incomingData,retry);
  }
  return decriptData("ERROR",retry);
}

void sendRequest()
{
 if(false) Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 125 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                          (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 125 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                          "Now sending request"
# 125 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                          ); &__c[0];}))
# 125 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                          )));
  radio.startWrite(&REQUEST_CODE, sizeof(REQUEST_CODE), 0);
}

void checkRadio(void)
{

  bool tx, fail, rx;
  radio.whatHappened(tx, fail, rx); // What happened to trigger interrupt?

  if (tx)
  {
    // Have we successfully transmitted request?
    // If we successfully send the request wait for the data
    if(false) Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 139 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 139 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                            "Send:OK"
# 139 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                            ); &__c[0];}))
# 139 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                            )));
    badDataFlag = false;
  }

  if (fail)
  {
    // Have we failed to transmit request?
    // The retry to get data from node
    if(false) Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 147 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 147 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                            "Send:Failed retrying now"
# 147 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                            ); &__c[0];}))
# 147 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                            )));
    badDataFlag = true;
  }

  if (rx || radio.available())
  {
    // Did we receive data form node ?
    char dataFromNode[32 /* Buffer size canot get more than 32byte*/] = "";
    radio.read(&dataFromNode, sizeof(dataFromNode));
    incomingData = dataFromNode; // convert to string for futer use
    if(false) Serial.println(incomingData);
    if (incomingData == "")
    {
      if(false) Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 160 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 160 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                              "Receive: Bad data retrying now"
# 160 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                              ); &__c[0];}))
# 160 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                              )));
      badDataFlag = true;
    }
    else
    {
      if(false) Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 165 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                              (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 165 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                              "Receive: OK"
# 165 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino" 3
                              ); &__c[0];}))
# 165 "f:\\OneDrive - Faculty of Information Technology - University of Moratuwa\\GIT\\wireless data collector\\ARDUINO-SRC\\Controller\\controller.ino"
                              )));
      dataDecriptionFlag = true;
      dataWaitingFlag = false;
    }
  }
}

String decriptData(String Nodedata,uint8_t retry)
{
  uint8_t j = 0;
  String subData[10];
  for (uint8_t i = 0; i < Nodedata.length(); i++)
  {
    if (Nodedata[i] == '&')
    {
      j++;
    }
    else
    {
      subData[j] = subData[j] + Nodedata[i];
    }
  }
  jsonOutput = "";
  JsonObject data = doc.to<JsonObject>(); // create json object
  for (uint8_t i = 0; i <= j; i++)
  {
    data["data" + String(i)] = subData[i];
  }
  data["retry"] = retry;
  serializeJson(data, jsonOutput);
  if(false) Serial.println(jsonOutput); // print to serilal monitoro for debug purpuses
  return jsonOutput;
}
