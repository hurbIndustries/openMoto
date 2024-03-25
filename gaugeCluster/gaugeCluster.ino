#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// MASTER VERSION NUM
#define ver_id "0.0.4"

// SERIAL DEBUG SWITCH
#define serialDebug true

// Define some quick constants for the basic MFD
// Adafruit 2.5" ST7789 display
#define mfd_bright 11
#define mfd_CS 7
#define mfd_DC 42
#define mfd_RS 9

//Adafruit_ST7789 tft = Adafruit_ST7789(7, 42, 51, 52, 9);  // Placeholder, Use this *IF* using software SPI 
Adafruit_ST7789 mfd = Adafruit_ST7789(mfd_CS, mfd_DC, mfd_RS);

// Global Variables
int mfd_brt = 160;
int mfd_nightBrt = 40;
int mfd_dayBrt = 255;
bool mfd_night;
bool bt_stat = false; 
bool bt_stateChange = false;
int speed = 0;
int pageNum = 1;
bool pageChange = false;
int lastPage; 
uint16_t ui_color = ST77XX_WHITE;

void setup() {
  if(serialDebug) {
    Serial.begin(9600);
  }
  pinMode(mfd_bright, OUTPUT);
  mfd.init(240, 320); // *Change resolution if different screen used. Code is *NOT* currently optimized for differing resolutions.
  analogWrite(mfd_bright, mfd_brt);
  bootSplash();
  delay(3000); // *Cheap startup delay. Temporary more then anything. 
  mfd.fillScreen(ST77XX_BLACK);
  btDispOff();
}

void loop() {
  analogWrite(mfd_bright, mfd_brt);
  if(serialDebug) {
    checkSerial();
  }
  drawClock();
  btCheck();
  pageBar();
  pageCheck();
}