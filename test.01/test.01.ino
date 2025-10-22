#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// Pin definitions
#define TFT_CS     10
#define TFT_RST    8
#define TFT_DC     9  // RS

// constants won't change. They're used here to set pin numbers:
const int buttonRED = 3;  // the number of the pushbutton pin


// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

// Create display object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.initR(INITR_BLACKTAB);  // Use INITR_BLACKTAB for ST7735B
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.println("Hello, ST7735!");
    // initialize the LED pin as an output:
  // initialize the pushbutton pin as an input:
  pinMode(buttonRED, INPUT);
}

void loop() {
   buttonState = digitalRead(buttonRED);
   if (buttonState == HIGH)
   {
    tft.println("RED Pressed");
   }
   else
   {
    
   }

  
}