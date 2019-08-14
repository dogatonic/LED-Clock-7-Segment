//
// TUCKER: July, 2019
// This is just a digital clock using an Adafruit 7-segment LED matrix, backpack, and ESP8266
// It uses an Arduino Time Library (Time.h) to set and keep track of the time. It requests the time over WIFI using an NTPClient.
// The time client request for an NTP time is repeated according to the set interval, such as every hour.
// Otherwise the time is managed by the time client library, and then interpreted into a display form, and output
// the 7 segment LED display.
//
// Libraries needed:
//  Time.h & TimeLib.h:  https://github.com/PaulStoffregen/Time
//  Timezone.h: https://github.com/JChristensen/Timezone
//  NTPClient.h: https://github.com/arduino-libraries/NTPClient
//  ESP8266WiFi.h & WifiUDP.h: https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi
//  Adafruit_GFX.h: https://github.com/adafruit/Adafruit-GFX-Library
//  Adafruit_LEDBackpack.h: https://github.com/adafruit/Adafruit_LED_Backpack

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <SPI.h>
#include <NTPClient.h> // For getting the time from a time server, Like an Atomic Clock!
#include <WifiUDP.h>
#include <Time.h> // handy time management
#include <TimeLib.h>
#include <Timezone.h>

// the DISPLAY Object
Adafruit_7segment display7segment = Adafruit_7segment();

// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "ca.pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)

// Set up the NTP UDP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

// WIFI
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PWORD";
IPAddress ip(192, 168, 0, 0);

// TUCKER TUCKER TUCKER
int timeDigits = 0; // numbers displayed on clock, will be "time" without colon

void wifiConection() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  delay(500);
  int k = 0;
  while(WiFi.status() != WL_CONNECTED && k<20) {
    Serial.println((String)"Attempt number: " + (k+1));
    k++;
    delay(1000);
  }
  ip = WiFi.localIP();
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("Do restart");
//    ESP.restart();
  } else {
    Serial.println((String)"Connected to *" + ssid + "* ! IP Address: " + ip.toString());
  }
}

void showOneDigitInPos(int dig, int pos, int delayed) {
  display7segment.clear();
  delay(delayed);
  display7segment.drawColon(false);
  display7segment.writeDigitNum(pos,dig);
  display7segment.writeDisplay();
}

void makeSwizzle() { // a little graphic effect to show that a Sync Time request is being made
  showOneDigitInPos(1, 0, 100);
  showOneDigitInPos(1, 1, 100);
  showOneDigitInPos(1, 3, 100);
  showOneDigitInPos(1, 4, 100);
  delay(100);
}

time_t returnNPTepoch() {
  Serial.print(">>>>>>>>>> Sync TIME request");

  makeSwizzle();
  delay(100);

  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();

  // convert received time stamp to time_t object
  time_t local, utc;
  utc = epochTime;
  // Then convert the UTC UNIX timestamp to local time
  TimeChangeRule usCDT = {"CDT", Second, Sun, Mar, 2, -360};  //UTC - 5 hours - change this as needed
  TimeChangeRule usCST = {"CST", First, Sun, Nov, 2, -420};   //UTC - 6 hours - change this as needed
  Timezone usCentral(usCDT, usCST);
  local = usCentral.toLocal(utc);

  return local;
}

void setTimeDigits() {
  time_t t = now();
  timeDigits = hourFormat12(t);
  timeDigits = (timeDigits < 1) ? 1200 : timeDigits * 100;
  timeDigits += minute(t);
  // Serial.println(timeDigits);
}

void setup() {
  Serial.begin(9600);
  wifiConection();
  display7segment.begin(0x70);
  display7segment.setBrightness(3); // 1 - 15, Man are these things bright!
  timeClient.begin();   // Start the NTP UDP client
  setSyncProvider(returnNPTepoch);
  setSyncInterval(60 * 60); // in seconds
}

void loop() {
  String t = "888";
  setTimeDigits();
 // Serial.println(timeStatus());

  display7segment.print(timeDigits);
  display7segment.drawColon(true);
  display7segment.writeDisplay();

  delay(1000);
}
