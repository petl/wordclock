#include "LedArray.h"

LedArray::LedArray(uint8_t brightness)  {
  this->brightness = brightness;
  this->old_minutes = 0;
  this->old_hours = 0;
  init();
}
void LedArray::init() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( brightness );
  this->LEDcolor[0] = 255;//R
  this->LEDcolor[1] = 255;//G
  this->LEDcolor[2] = 255;//B

  for(int i=0; i<NUM_LEDS; i++){
    leds[i].setRGB( LEDcolor[0] , LEDcolor[1] , LEDcolor[2] );
  }
  FastLED.show();
}

void LedArray::off() {
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

// e.g. 10:46, 12:01, 16:44, 23:05 or 2:13 
void LedArray::setTime(int8_t hours, int8_t minutes, uint8_t fade_delay){

  if(minutes >= 23){ //20 nach --> 5 vor halb 
    hours++;
  }
  if(hours > 12){
    hours = hours - 12;
  }


  // do a fading effect while updating
  // display the old time again, fade out 
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  setPrimer(this->old_minutes); // "VOR" or "NACH" and "UHR"
  setHours(this->old_hours);
  setMinutes(this->old_minutes);
  for(uint8_t i = brightness; i > 0; i--){
    FastLED.setBrightness( i );
    FastLED.show();
    delay(fade_delay);
  }

  //display the new time and fade in
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  setPrimer(minutes); // "VOR" or "NACH" and "UHR"
  setHours(hours);
  setMinutes(minutes);
  for(uint8_t i = 0; i <= brightness; i++){
    FastLED.setBrightness( i );
    FastLED.show();
    delay(fade_delay);
  }

  this->old_hours = hours;
  this->old_minutes = minutes;
}

//"ES IST", "VOR" or "NACH" and "UHR"
/*
* nothing (punkt)
* fünf nach
* zehn nach
* viertel nach
* zwanzig nach
* fünf vor halb 
* halb
* fünf nach halb
* zwanzig vor
* dreiviertel
* zehn vor
* fünf vor
*/
void LedArray::setPrimer(int8_t minutes){
  // ES IST
  for(int i=0; i<5; i++){
    leds[ItIsAddr[i]].setRGB( LEDcolor[0] , LEDcolor[1] , LEDcolor[2] );
  }

  //NACH
  if(minutes >= 3 && minutes < 22){ 
    for(int i=0; i<4; i++){
      if(NachAddr[i] != -1){
        leds[NachAddr[i]].setRGB( LEDcolor[0] , LEDcolor[1] , LEDcolor[2] );
      }
    }
  }
  //VOR
  else if(minutes >= 23 && minutes < 28) {
    for(int i=0; i<4; i++){
      if(VorAddr[i] != -1){
        leds[VorAddr[i]].setRGB( LEDcolor[0] , LEDcolor[1] , LEDcolor[2] );
      }
    }
  }
  //Nothing (halb)
  else if(minutes >= 28 && minutes < 33) {
    //nothing
  }
  //NACH
  else if(minutes >= 33 && minutes < 38) {
    for(int i=0; i<4; i++){
      if(NachAddr[i] != -1){
        leds[NachAddr[i]].setRGB( LEDcolor[0] , LEDcolor[1] , LEDcolor[2] );
      }
    }
  }
  //VOR
  else if(minutes >= 38 && minutes < 43) {
    for(int i=0; i<4; i++){
      if(VorAddr[i] != -1){
        leds[VorAddr[i]].setRGB( LEDcolor[0] , LEDcolor[1] , LEDcolor[2] );
      }
    }
  }
  //Nothing (dreiviertel)
  else if(minutes >= 43 && minutes < 48) {
    //nothing
  }
  //VOR
  else if (minutes >= 48 && minutes < 58){
    for(int i=0; i<4; i++){
      if(VorAddr[i] != -1){
        leds[VorAddr[i]].setRGB( LEDcolor[0] , LEDcolor[1] , LEDcolor[2] );
      }
    }
  }
  //Nothing (punkt)
  else if (minutes >= 58){
    //nothing
  }

  //UHR
  for(int i=0; i<3; i++){
    leds[UhrAddr[i]].setRGB( LEDcolor[0] , LEDcolor[1] , LEDcolor[2] );
  }
}


void LedArray::setHours(int8_t hours){
  for(int i=0; i<6; i++){
    if(HourAddr[hours-1][i] != -1){
      leds[HourAddr[hours-1][i]].setRGB( LEDcolor[0] , LEDcolor[1] , LEDcolor[2] );
    }
  }
}

void LedArray::setMinutes(int8_t minutes){
  for(int i=0; i<11; i++){
    if(MinAddr[minutes][i] != -1){
      leds[MinAddr[minutes][i]].setRGB( LEDcolor[0] , LEDcolor[1] , LEDcolor[2] );
    }
  }
}


void LedArray::setColor(uint8_t red, uint8_t green, uint8_t blue){
  this->LEDcolor[0] = red;//R
  this->LEDcolor[1] = green;//G
  this->LEDcolor[2] = blue;//B
}

void LedArray::setBrightness(uint8_t brightness){
  FastLED.setBrightness( brightness );
}

