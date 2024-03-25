#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// MASTER VERSION NUM
#define ver_id "0.0.3"

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

// Bluetooth test bitmap
// 'Pictogrammers-Material-Light-Bluetooth', 32x32px
const unsigned char epd_bitmap_Pictogrammers_Material_Light_Bluetooth [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x01, 0x30, 0x00, 
	0x00, 0x01, 0x18, 0x00, 0x00, 0x81, 0x0c, 0x00, 0x00, 0xc1, 0x0e, 0x00, 0x00, 0x61, 0x1c, 0x00, 
	0x00, 0x31, 0x38, 0x00, 0x00, 0x19, 0x70, 0x00, 0x00, 0x0d, 0xe0, 0x00, 0x00, 0x07, 0xc0, 0x00, 
	0x00, 0x03, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x1d, 0x60, 0x00, 
	0x00, 0x39, 0x30, 0x00, 0x00, 0x71, 0x18, 0x00, 0x00, 0xe1, 0x0c, 0x00, 0x00, 0xc1, 0x0c, 0x00, 
	0x00, 0x01, 0x18, 0x00, 0x00, 0x01, 0x30, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x01, 0xc0, 0x00, 
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void btDispOn() {
  bt_stat = true;
  mfd.fillRect(207, 0, 33, 33, ST77XX_BLACK);
  mfd.drawBitmap(208, 0, epd_bitmap_Pictogrammers_Material_Light_Bluetooth, 32, 32, ST77XX_CYAN);
  bt_stateChange = false;
}

void btDispOff() {
  bt_stat = false;
  mfd.fillRect(207, 0, 33, 33, ST77XX_BLACK);
  mfd.drawBitmap(208, 0, epd_bitmap_Pictogrammers_Material_Light_Bluetooth, 32, 32, ST77XX_WHITE);
  mfd.drawLine(208, 0, 240, 32, ST77XX_WHITE);
  mfd.drawLine(208, 32, 240, 0, ST77XX_WHITE);
  bt_stateChange = false;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(mfd_bright, OUTPUT);
  mfd.init(240, 320);
  analogWrite(mfd_bright, mfd_brt);
  bootSplash();
  delay(3000);
  mfd.fillScreen(ST77XX_BLACK);
  btDispOff();
}

// Bootsplash.
void bootSplash() {
  mfd.fillScreen(ST77XX_BLACK);
  mfd.fillTriangle(120, 190, 70, 280, 170, 280, ST77XX_ORANGE);
  mfd.setTextSize(2);
  mfd.setCursor(7, 7);
  mfd.print(ver_id);
  mfd.setCursor(108, 230);
  mfd.setTextSize(5);
  mfd.write("!");
  mfd.setTextSize(3);
  mfd.setCursor(20, 100);
  mfd.write("Starting...");
}


// Initialize the page bar at the bottom of the UI.
void pageBar() {
  mfd.drawLine(0, 290, 320, 290, ST77XX_WHITE);
  mfd.setTextSize(2);
  mfd.setCursor(7, 300);
  mfd.print("SPD");
  mfd.drawLine(50, 290, 50, 320, ST77XX_WHITE);
  mfd.setCursor(60, 300);
  mfd.print("MPG");
  mfd.drawLine(105, 290, 105, 320, ST77XX_WHITE);
  mfd.setCursor(115, 300);
  mfd.print("MUS");
  mfd.drawLine(160, 290, 160, 320, ST77XX_WHITE);
  mfd.setCursor(170, 300);
  mfd.print("AFR");
  mfd.drawLine(215, 290, 215, 320, ST77XX_WHITE);
  mfd.setCursor(225, 300);
  mfd.print("C");
}

void setPage(int page) {
  if(pageChange) {
    mfd.fillRect(0, 275, 240, 10, ST77XX_BLACK);
    resetArea();
    pageChange = false;
  }
  if(pageNum == 1) {
    mfd.fillTriangle(20, 277, 30, 277, 25, 285, ST77XX_WHITE); 
  } else
  if(pageNum == 2) {
    mfd.fillTriangle(70, 277, 80, 277, 75, 285, ST77XX_WHITE);
  } else 
  if(pageNum == 3) {
    mfd.fillTriangle(125, 277, 135, 277, 130, 285, ST77XX_WHITE);
  } else
  if(pageNum == 4) {
    mfd.fillTriangle(180, 277, 190, 277, 185, 285, ST77XX_WHITE);
  } else 
  if(pageNum == 5) {
    mfd.fillTriangle(225, 277, 235, 277, 230, 285, ST77XX_WHITE);
  } else {
    pageNum = 1;
  }
}

void resetArea() {
  mfd.fillRect(0, 33, 240, 260, ST77XX_BLACK);
}

void speedPage() {
  mfd.setTextSize(10);
  if(speed <= 9) {
    mfd.setCursor(50, 120);
  } else if(speed >= 10 && speed <= 99) {
    mfd.setCursor(15, 120);
  } else {
    mfd.setTextSize(8);
    mfd.setCursor(0, 120);
  }
  mfd.print(speed);
  mfd.setTextSize(5);
  mfd.print("mph");
}

void mpgPage() {
}

void musPage() {
}

void afrPage() {
}

void cfgPage() {
}

void loop() {
  analogWrite(mfd_bright, mfd_brt);
  // Debug serial stuff <3 
  if(Serial.available()) {
    String data = Serial.readString();
    if(data == "n") {
      pageNum++;
      Serial.println(pageNum);
    } else
    if(data == "p") {
      pageNum--;
      Serial.println(pageNum);
    } else 
    if(data == "bt") {
      if(bt_stat) {
        bt_stateChange = true;
        Serial.println("Bluetooth test off");
      } else {
        bt_stateChange = true;
        Serial.println("Bluetooth test on;");
      }
    } else
    if(data == "blTime") {
      if(mfd_night) {
        Serial.println("Setting MFD to Day...");
        mfd_brt = mfd_dayBrt;
        mfd_night = false;
       } else {
        Serial.println("Setting MFD to Night...");
        mfd_brt = mfd_nightBrt;
        mfd_night = true;
       }
    } else 
    if(data == "blIncr") {
      mfd_brt = mfd_brt + 20;
    } else 
    if(data == "blDecr") {
      mfd_brt = mfd_brt - 20;
    }
  }
  if(bt_stat && bt_stateChange) {
    btDispOff(); 
  } else 
  if(bt_stateChange) {
    btDispOn();
  }
  pageBar();
  if(lastPage != pageNum) {
    pageChange = true;
  }
  lastPage = pageNum;
  switch(pageNum) {
    case 0:
      pageNum = 5;
      setPage(pageNum);
      break;
    case 1:
      setPage(pageNum);
      speedPage();
      break;
    case 2:
      setPage(pageNum);
      mpgPage();
      break;
    case 3:
      setPage(pageNum);
      musPage();
      break;
    case 4:
      setPage(pageNum);
      musPage();
      break;
    case 5:
      pageBar();
      setPage(pageNum);
      cfgPage();
      break;
    case 6:
      pageNum = 1;
      setPage(pageNum);
      break;
    default:
      pageNum = 1;
      setPage(pageNum);
      break;
  }
}
