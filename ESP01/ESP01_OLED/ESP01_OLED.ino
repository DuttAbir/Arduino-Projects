#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C //Most common small OLEDs use 0x3C.

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);  // For 128x64 display

// Define the SDA and SCL pins for I2C communication with the OLED
#define SDA_PIN 2 // GPIO2 
#define SCL_PIN 0 // GPIO0 


void setup() {
  Serial.begin(9600);

  // Initialize I2C communication with custom pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay(); // Clear the buffer
  display.println("Hello, ESP-01!"); // Print some text
  display.display(); // Show what we've written
  delay(2000);
}

void loop() {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel size
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println("Uptime:");
  display.println(millis()/1000);

  display.setTextSize(2);             // Draw 2X larger text
  display.setCursor(0, 16);           // Start below the small text
  display.print("Seconds:");
  display.println(millis()/1000);
  
  display.display();
  delay(100);
}
