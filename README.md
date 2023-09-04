# Wordclock 

<p><h2> Motivation</h2> </p><br />
Mike asked me if I wanted to code some stuff for his workclock. He's a laser cutting wizard and made a beautiful workclock (see his project here: https://michaelwolf.at/wordclock) and I was glad to be of help. The PCB and schematics are also over there and from this it was just a bit of playing around with the hardware. It is based around a ESP-12F board (ESP8266) and features USB programming, a AHT20 temp&humi sensor, LDR, buttons and a 110 WS2812 addressable RGB LEDs .<br><br>
Long story short: I made an open source C++ based wordclock firmware. <br><br>

<img src='https://github.com/petl/wordclock/front_lit_cut.png' width='100%'>

<p><h2> C++ ?</h2> </p><br />
There was a certain curiosity that made me use C++ instead of my usual C (with C++ aroma). The result is fully obejct orientend code, that doesn't really need it. On the plus side, this keeps the code readable and functions well structured. It even features fading the old time out and the new in. 

<p><h2> Implementation progress</h2> </p><br />
☒ Display time via WS2812<br>
☒ Set time via buttons<br>
☒ Use LDR to dim the LEDs at night<br>
☒ Open a WiFi hotspot to be able to set the time<br>
☒ Set time via Wifi<br>
☒ Set time via NTP<br>
☐ Change modi (e.g. ws2812 colors) fia buttons/WiFi<br>
☐ AHT20 (Temp, Humidity) readout<br>
☐ DS3231 (RTC) readout (future board revision)<br>

<p><h2> Conclusion</h2> </p><br />
There are still a lot more things that can be implemented, especially on the gimmicky side. For now, the features seem to work and a lot of time in testing is needed to see how stable everything is. Not having a RTC (DS3231) makes keeping the time a bit finicky and an overflow of the internal counter is probably going to glitch out the clock until the next time update. <br>
<p>If you're interested in this project, take a look at the source or just write a message or leave a comment. </p>
