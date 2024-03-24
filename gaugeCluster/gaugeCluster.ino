#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// MASTER VERSION NUM
#define ver_id "0.0.1"

// Define some quick constants for the basic MFD
// Adafruit 2.5" ST7789 display
#define mfd_bright 11
#define mfd_CS 7
#define mfd_DC 42
#define mfd_RS 9

//Adafruit_ST7789 tft = Adafruit_ST7789(7, 42, 51, 52, 9);  // Placeholder, Use this *IF* using software SPI 
Adafruit_ST7789 mfd = Adafruit_ST7789(mfd_CS, mfd_DC, mfd_RS);

// Global Variables
int mfd_brt = 170;
bool bt_stat = false; 
int speed = 0;
int pageNum = 1;

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

void btIcon() {
  if(bt_stat == true) {
    mfd.drawBitmap(208, 0, epd_bitmap_Pictogrammers_Material_Light_Bluetooth, 32, 32, ST77XX_CYAN);
  } else {
    mfd.drawBitmap(208, 0, epd_bitmap_Pictogrammers_Material_Light_Bluetooth, 32, 32, ST77XX_WHITE);
    mfd.drawLine(208, 0, 240, 32, ST77XX_WHITE);
    mfd.drawLine(208, 32, 240, 0, ST77XX_WHITE);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(mfd_bright, OUTPUT);
  mfd.init(240, 320);
  analogWrite(mfd_bright, 170);
  bootSplash();
  delay(3000);
  mfd.fillScreen(ST77XX_BLACK);
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
  mfd.setCursor(5, 300);
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

void loop() {
  btIcon();
  pageBar();
  switch(pageNum) {
    case 1:
      speedPage();
      break;
  }
}
