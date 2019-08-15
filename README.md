# LED-Clock-7-Segment
Arduino digital clock project, in C++.

TUCKER: July, 2019
This is just a digital clock using an Adafruit 7-segment LED matrix, backpack, and ESP8266. It uses an Arduino Time Library (Time.h) to set and keep track of the time. It requests the time over WIFI using an NTPClient. The time client request for an NTP time is repeated according to the set interval, such as every hour. Otherwise the time is managed by the time client library, and then interpreted into a display form, and output to the 7 segment LED display.

The clock has 4 main parts: a 7-segment LED clock display, an I2C LED driver backpack, an Arduino ESP8266 type dev board, and a prototyping perfboard. I used a Wemos D1 mini pro because of the small size.

First, I soldered the LED display to the backpack. Then I tested it to make sure it was all good.

![parts](http://matttucker.com/photos/2019/LEDclock/parts.jpg)
*In this pic, I have already soldered the LED display to the backpack*

Next, I soldered wires through the back of the perfboard to the D1 which holds it in place.
![soldered back](http://matttucker.com/photos/2019/LEDclock/solderback.jpg)

I chose to have the LED display & backpack assembly overlap the D1 in my case, but it certainly doesn't have to. I was just trying to make it a little more compact. Here is the D1 before it gets covered up.
![D1 front](http://matttucker.com/photos/2019/LEDclock/solderfront.jpg)

Then I soldered the wires up through the perfboard to hold them in place and then through the LED backpack, which holds it in place. This soldering was a little tricky, and next time I will probably use some header pins instead.
![back wires](http://matttucker.com/photos/2019/LEDclock/back.jpg)

The final assembly with the clock running. I plan to 3D print a case for it and mount it below my TV, and it will be permanently powered by the USB cable off the back of the TV. It's on my WIFI LAN, so it will always keep correct time (including DST).
![front](http://matttucker.com/photos/2019/LEDclock/front.jpg)

In the future, this little clock and others like it, will be part of my open-source whole house system. I plan to add a pub/sub client into it, so that it can display notices as well as the time. For instance, if it is after 10pm and I have left my garage door open, or if someone rings the doorbell, etc.
