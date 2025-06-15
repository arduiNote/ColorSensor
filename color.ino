#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// TCS230 pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define OUT 8

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);

  // Initialize TCS230 pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Color Sensor Ready");
  display.display();
  delay(1000);
}

void loop() {
  // Read red
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(OUT, LOW);

  // Read green
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(OUT, LOW);

  // Read blue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(OUT, LOW);

  // Print to serial monitor
  Serial.print("R=");
  Serial.print(redFrequency);
  Serial.print(" G=");
  Serial.print(greenFrequency);
  Serial.print(" B=");
  Serial.println(blueFrequency);

  // Display on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Color Readings:");
  display.print("R: ");
  display.println(redFrequency);
  display.print("G: ");
  display.println(greenFrequency);
  display.print("B: ");
  display.println(blueFrequency);
  display.display();

  delay(500);
}
