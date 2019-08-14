# LED-Clock-7-Segment
Arduino digital clock project, in C++.

TUCKER: July, 2019
This is just a digital clock using an Adafruit 7-segment LED matrix, backpack, and ESP8266. It uses an Arduino Time Library (Time.h) to set and keep track of the time. It requests the time over WIFI using an NTPClient. The time client request for an NTP time is repeated according to the set interval, such as every hour. Otherwise the time is managed by the time client library, and then interpreted into a display form, and output to the 7 segment LED display.
