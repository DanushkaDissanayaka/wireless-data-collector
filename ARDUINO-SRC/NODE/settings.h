#ifndef settings_h
    #define settings_h

    const byte      NODE_ADDRESS_READING[6]   =   "000W1";
    const byte      NODE_ADDRESS_WRITING[6]   =   "000R1";

    #define READING_WAITING     2000
    #define WRITING_WAITING     1000
    #define READ_WRITEBUFF_SIZE 128

    // PIN Configuration for RF24
    #define CE_PIN              7
    #define CSN_PIN             8

     // communication defines
    #define DATA_REQUEST "d"
#endif