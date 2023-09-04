/*
 * 2023, wordclock
 * made for and with Michael Wolf
 *
 * by peter@traunmueller.net
 * 
 */


#include <Arduino.h>
#include "LedArray.h"
#include "Time.h"
#include "Button.h"
#include "CustomWiFiManager.h"
#include "WiFiManagerWrapper.h"
#include "ESP8266mDNS.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

LedArray ledArr(25); // Initialize the LED brighness to 25
Time RTime(12, 0); // Initialize the time to 12:00
Button hourButton(10);
Button minuteButton(14);
Button modeButton(16);
WiFiManagerWrapper wifiWrap;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

uint8_t r, g, b;
uint8_t buttons_last[3];
uint8_t hour_last, minute_last;

unsigned int next_ntp_update;
 

void setup() {
  //ledArr.setBrightness(30); // set LED brighness to 30
  //RTime.setTime(16, 45); // set time to 16:45
  Serial.begin(115200);

  wifiWrap.init();
  if(!modeButton.get()){
    wifiWrap.openPortal();
  }

  r = 255;
  ledArr.setColor(r, g, b);

}

void loop() {



  if(hour_last != RTime.getHours()|| minute_last != RTime.getMinutes()){
    uint8_t fade_delay = 50;
    ledArr.setTime(RTime.getHours(), RTime.getMinutes(), fade_delay);
    Serial.printf("Time: %d:%d\n", RTime.getHours(), RTime.getMinutes());
    hour_last = RTime.getHours();
    minute_last = RTime.getMinutes();
  }




  if (WiFi.status() == WL_CONNECTED && millis() > next_ntp_update ) {
    timeClient.begin();
    // GMT +1 = 3600
    timeClient.setTimeOffset(7200);
    timeClient.update();
    Serial.print("Grabbing NTP update. ");
    int currentHour = timeClient.getHours();
    Serial.print("Hour: ");
    Serial.println(currentHour);  

    int currentMinute = timeClient.getMinutes();
    Serial.print("Minutes: ");
    Serial.println(currentMinute); 

    RTime.setTime(currentHour, currentMinute);

    next_ntp_update = millis() + 24 * 60 * 60 * 1000; // grab a new update every 24 hours
  }


  uint8_t buttons[3] = {hourButton.get(), minuteButton.get(), modeButton.get()}; 

  if(buttons[0] != buttons_last[0] || buttons[1] != buttons_last[1] || buttons[2] != buttons_last[2]){
    //Serial.println("Button pressed: ");
    //Serial.print(buttons[0]);
    //Serial.print(buttons[1]);
    //Serial.print(buttons[2]);

    if(!hourButton.get()){
      RTime.setTime(RTime.getHours()+1, RTime.getMinutes());
      while(!hourButton.get()){}//debunce
    }
    if(!minuteButton.get()){
      RTime.setTime(RTime.getHours(), RTime.getMinutes()+1);
      while(!minuteButton.get()){}//debunce
    }
    uint8_t fade_delay = 0;
    ledArr.setTime(RTime.getHours(), RTime.getMinutes(), fade_delay);
    Serial.printf("Button Set Time: %d:%d\n", RTime.getHours(), RTime.getMinutes());
    hour_last = RTime.getHours();
    minute_last = RTime.getMinutes();
    /*
    if(!modeButton.get()){
      g = g + 10;
      b = b + 5;
      Serial.printf("R: %d, G:%d, B:%d\n", r, g, b);
      while(!modeButton.get()){}//debunce
    }*/

    for(int i=0; i<3; i++){
      buttons_last[i] = buttons[i];
    }
  }

    //update time if it was set manually
    if(wifiWrap.isManualTimeSet()){
      Serial.print("Time set manually via Wifi: ");
      Serial.print(wifiWrap.getHours());
      Serial.print(":");
      Serial.println(wifiWrap.getMinutes());
      RTime.setTime(wifiWrap.getHours(), wifiWrap.getMinutes());
      wifiWrap.closePortal();
    }

  uint16_t LDR_val = analogRead(A0);
  int16_t brightness = (LDR_val-500)/2+10;
  if(brightness > 200){
    brightness = 200;
  }
  else if(brightness < 0){
    brightness = 10;
  }
  //Serial.printf("Brightness set to: %d\n", brightness);
  ledArr.setBrightness((uint8_t)brightness);

  MDNS.update();
  wifiWrap.doWiFiManager();
  delay(100);
}
