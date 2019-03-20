#if !defined(SETTING_H)
    #define SETTING_H
    const char REQUEST_CODE ='d';

    #define WAITING_DELAY   2000
    #define BUFF_SIZE   64

    const byte NODE_ADDRESS[5]          =   {0xCC, 0xCE, 0xCC, 0xCE, 0xEE};
    const byte CONTROLLER_ADDRESS[5]    =   {0xCE, 0xCC, 0xCE, 0xCC, 0xCE};

    // Buzzer
    #define ERROR_BEEP              3
    #define INFO_BEEP               2
    #define SUCCESS_BEEP            1
    #define BEEP_TIME_INTERVAL      100

#endif // SETTING_H
