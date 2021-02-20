#include <Arduino.h>
// KEYPAD ADJUST
#include <Keypad.h>
#include <Keypad.h>
// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 3;
// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// OLED ADJUST
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
int variable = 15;
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RTC MODULE ADJUST
#include "RTClib.h"
RTC_DS1307 rtc;

// My variables
int muhour = 0;
int mu_min = 0;
int mu_sec = 0;
int shock = 8;
// Counter for character entries
byte data_count = 0;
// Character to hold key input
char customKey;
char some;
int count = 0;
int flag;
int shock_hour;
int shock_min;
char data[] = {'0', '0'};
int i = 0;
int current_min;
void oled_println(String pro)
{
  display.clearDisplay();
  display.setTextSize(1); // Normal 1:1 pixel scale
}

void setup()
{
  pinMode(shock, OUTPUT);
#ifndef ESP8266
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB
#endif

  if (!rtc.begin())
  {
    abort();
  }

  if (!rtc.isrunning())
  {

    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop()
{
  DateTime now = rtc.now();
  if (now.minute() != current_min)
  {
    display.setTextSize(1); 
    current_min = now.minute();
    display.setCursor(0, 0);
    display.print(now.minute());
    display.print(":");
    display.println(now.hour());
  }
  // Look for keypress
  customKey = customKeypad.getKey();
  if (customKey == '#')
  {
    display.println("shock time");
    while (flag != 4)
    {
      customKey = customKeypad.getKey();
      display.write(customKey);
      flag++;
      some += customKey;
      if (flag == 2)
      {
        shock_hour = int(some);
        display.write(':');
        count = 0;
        some =0;
      }
      if (flag == 4)
      {
        shock_min = int(some);
        display.write(':');
        count = 0;
        some =0;
      }
    }
  }
  if (customKey == '*')
  {
    shock_hour = 66;
    shock_min = 66;
  }
}