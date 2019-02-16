#ifndef settings_h
    #define settings_h
    const byte      CONTROLLER_ADDRESS[6]   =   "00001";
    const byte      NODE_ADDRESS[][6]       =   {"00001","00002"};
    const String    NODE_NAME[]             =   {"NODE1","NODE2"};

    #define READING_WAITING     2000
    
    // PIN Configuration for RF24
    #define CE_PIN              7
    #define CSN_PIN             8
#endif