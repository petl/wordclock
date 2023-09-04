#ifndef WIFIMNANAGERWRAPPER_H
#define WIFIMNANAGERWRAPPER_H
#include <Arduino.h>
#include "CustomWiFiManager.h"


class WiFiManagerWrapper {
  private:
    int8_t portalRunning;
    int8_t manualTimeSet;
    unsigned int  startTime;
    unsigned int  timeout;

    WiFiManager wfm;

    
  public:
    WiFiManagerWrapper();
    void doWiFiManager();
    void init();
    void openPortal();
    int8_t getHours();
    int8_t getMinutes();
    int8_t isManualTimeSet();
    void closePortal();
};


#endif