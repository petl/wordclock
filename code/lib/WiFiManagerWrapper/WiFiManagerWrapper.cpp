#include "WiFiManagerWrapper.h"

// Define the custom inputs
WiFiManagerParameter custom_hour_box("hour_text", "Hour:", "12", 2);
WiFiManagerParameter custom_minute_box("minute_text", "Minute:", "00", 2);

WiFiManagerWrapper::WiFiManagerWrapper()  {

  this->timeout           = 120; // seconds to run for
  this->startTime         = millis();
  this->portalRunning     = false;
  this->manualTimeSet     = false;
  


}

void WiFiManagerWrapper::init(){
  wfm.setHostname("WordClock");
  wfm.setEnableConfigPortal(false);
  wfm.setConfigPortalBlocking(false);
  wfm.autoConnect();
}


void WiFiManagerWrapper::doWiFiManager(){
  // is auto timeout portal running
  if(portalRunning){
    wfm.process(); // do processing

    if(getHours() != 12 || getMinutes() != 00){
      manualTimeSet = true;
    }

    // check for timeout
    if((millis()-startTime) > (timeout*1000)){
      Serial.println("portaltimeout");
      portalRunning = false;
      wfm.stopConfigPortal();
    }
  }
}

void WiFiManagerWrapper::openPortal(){
  wfm.setDarkMode(true);
  std::vector<const char *> menu = {"wifi", "param", "exit"};
  wfm.setMenu(menu);
  // Add custom parameter
  wfm.addParameter(&custom_hour_box);
  wfm.addParameter(&custom_minute_box);
 

  // is configuration portal requested?
  if(!portalRunning) {
    Serial.println("Button Pressed, Starting Config Portal");
    wfm.setConfigPortalBlocking(false);
    wfm.startConfigPortal("Berni_rulez");
    portalRunning = true;
    startTime = millis();
  }
}

int8_t WiFiManagerWrapper::getMinutes(){
  //Serial.print("custom_minute_box: ");
  //Serial.println(custom_minute_box.getValue());
  return atoi(custom_minute_box.getValue());
}

int8_t WiFiManagerWrapper::getHours(){
  //Serial.print("custom_hour_box: ");
  //Serial.println(custom_hour_box.getValue());
  return atoi(custom_hour_box.getValue());
}

int8_t WiFiManagerWrapper::isManualTimeSet(){
  return manualTimeSet;
}

void WiFiManagerWrapper::closePortal(){
  Serial.println("Closing Portal");

  if(portalRunning){
    Serial.println("Stop wfm");
    portalRunning = false;
    wfm.stopConfigPortal();
  }

  manualTimeSet = false; 
  custom_hour_box.setValue("12", 3);
  custom_minute_box.setValue("00", 3);

}


