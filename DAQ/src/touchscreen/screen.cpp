#include "touchscreen/screen.h"

bool ScreenManager::init() {
  reset();

  identifier = readID();

  if (identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if (identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if (identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if (identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if (identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  }

  begin(identifier);

  // Quick benchmark of the screen
  Serial.println("Quick benchmark of the screen");

  Serial.print(F("Screen fill              "));
  Serial.println(testFillScreen());
  delay(500);

  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(3000);

  Serial.print(F("Lines                    "));
  Serial.println(testLines(CYAN));
  delay(500);

  Serial.println(F("Done!"));
}

void ScreenManager::welcome_screen() {}

uint8_t ScreenManager::app_sel_screen() {}

// ###
// ### test functions ###
// ###

unsigned long ScreenManager::testFillScreen() {
  unsigned long start = micros();
  fillScreen(BLACK);
  fillScreen(RED);
  fillScreen(GREEN);
  fillScreen(BLUE);
  fillScreen(BLACK);
  return micros() - start;
}

unsigned long ScreenManager::testText() {
  fillScreen(BLACK);
  unsigned long start = micros();
  setCursor(0, 0);
  setTextColor(WHITE);
  setTextSize(1);
  println("Hello World!");
  setTextColor(YELLOW);
  setTextSize(2);
  println(1234.56);
  setTextColor(RED);
  setTextSize(3);
  println(0xDEADBEEF, HEX);
  println();
  setTextColor(GREEN);
  setTextSize(5);
  println("Groop");
  setTextSize(2);
  println("I implore thee,");
  setTextSize(1);
  println("my foonting turlingdromes.");
  println("And hooptiously drangle me");
  println("with crinkly bindlewurdles,");
  println("Or I will rend thee");
  println("in the gobberwarts");
  println("with my blurglecruncheon,");
  println("see if I don't!");
  return micros() - start;
}

unsigned long ScreenManager::testLines(uint16_t color) {
  unsigned long start, t;
  int x1, y1, x2, y2, w = width(), h = height();

  fillScreen(BLACK);

  x1 = y1 = 0;
  y2 = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) drawLine(x1, y1, x2, y2, color);
  x2 = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) drawLine(x1, y1, x2, y2, color);
  t = micros() - start;  // fillScreen doesn't count against timing

  fillScreen(BLACK);

  x1 = w - 1;
  y1 = 0;
  y2 = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) drawLine(x1, y1, x2, y2, color);
  x2 = 0;
  for (y2 = 0; y2 < h; y2 += 6) drawLine(x1, y1, x2, y2, color);
  t += micros() - start;

  fillScreen(BLACK);

  x1 = 0;
  y1 = h - 1;
  y2 = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) drawLine(x1, y1, x2, y2, color);
  x2 = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) drawLine(x1, y1, x2, y2, color);
  t += micros() - start;

  fillScreen(BLACK);

  x1 = w - 1;
  y1 = h - 1;
  y2 = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) drawLine(x1, y1, x2, y2, color);
  x2 = 0;
  for (y2 = 0; y2 < h; y2 += 6) drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}