#include "touchscreen/screen.h"

ScreenManager *ScreenManager::pInstance{nullptr};
std::mutex ScreenManager::pMutex;

ScreenManager *ScreenManager::GetInstance() {
  std::lock_guard<std::mutex> lock(pMutex);
  if (pInstance == nullptr) {
    HardwareManager *hardware = HardwareManager::GetInstance();
    pInstance = new ScreenManager(&hardware->mySPI, SCREEN_CS, SCREEN_D_C, -1);
  }
  return pInstance;
}

bool ScreenManager::read_touch(touchPoint *point) {
  if (touch.read_touch(&point->x, &point->y, &point->z1, &point->z2))
    return true;
  else
    return false;
}

void ScreenManager::init(TwoWire *wire) {
  Serial.println("TFT screen start...");

  tft.begin();

  uint8_t x = tft.readcommand8(HX8357_RDPOWMODE);
  Serial.print("Display Power Mode: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDMADCTL);
  Serial.print("MADCTL Mode: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDCOLMOD);
  Serial.print("Pixel Format: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDIM);
  Serial.print("Image Format: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDSDR);
  Serial.print("Self Diagnostic: 0x");
  Serial.println(x, HEX);

  // Quick benchmark of the screen
  Serial.println(F("Benchmark                Time (microseconds)"));

  tft.setRotation(1);

  Serial.print(F("Fill                     "));
  Serial.println(testFillScreen());
  delay(500);

  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(500);

  Serial.print(F("Lines                    "));
  Serial.println(testLines(HX8357_CYAN));
  delay(500);

  Serial.println(F("Screen => Done!"));

  touch.begin(TSC2007_I2CADDR_DEFAULT, wire);
}

void ScreenManager::welcome_screen() {
  tft.fillScreen(HX8357_BLACK);
  tft.setCursor(160, 100);
  tft.setTextSize(3);
  tft.setTextColor(HX8357_WHITE);
  tft.println("WELCOME TO");
  tft.setCursor(180, 160);
  tft.setTextSize(8);
  tft.setTextColor(HX8357_BLUE);
  tft.println("DAQ");
}

void ScreenManager::logo_screen() {
  tft.fillScreen(HX8357_BLACK);
  tft.setCursor(140, 80);
  tft.setTextSize(8);
  tft.setTextColor(HX8357_WHITE);
  tft.println("PWR");
  tft.setCursor(130, 140);
  tft.setTextColor(HX8357_BLUE);
  tft.print("IN");
  tft.setCursor(140, 200);
  tft.setTextColor(HX8357_WHITE);
  tft.print("SPACE");
}

void ScreenManager::app_sel_screen() {
  tft.fillScreen(HX8357_BLACK);
  tft.fillRoundRect(40, 20, tft.width() - 80, 80, 20, HX8357_BLUE);
  tft.drawRoundRect(40, 20, tft.width() - 80, 80, 20, HX8357_WHITE);
  tft.setCursor(110, 45);
  tft.setTextSize(4);
  tft.setTextColor(HX8357_WHITE);
  tft.println("SENSOR TEST");
  tft.fillRoundRect(40, 120, tft.width() - 80, 80, 20, HX8357_BLUE);
  tft.drawRoundRect(40, 120, tft.width() - 80, 80, 20, HX8357_WHITE);
  tft.setCursor(110, 145);
  tft.setTextSize(4);
  tft.setTextColor(HX8357_WHITE);
  tft.println("STATIC FIRE");
  tft.fillRoundRect(40, 220, tft.width() - 80, 80, 20, HX8357_BLUE);
  tft.drawRoundRect(40, 220, tft.width() - 80, 80, 20, HX8357_WHITE);
  tft.setCursor(130, 245);
  tft.setTextSize(4);
  tft.setTextColor(HX8357_WHITE);
  tft.println("LAUNCHPAD");
}

void ScreenManager::app_logo_screen(AppName app) {
  tft.fillScreen(HX8357_BLACK);
  tft.setTextSize(8);
  tft.setCursor(100, 80);
  tft.setTextColor(HX8357_WHITE);
  if (app == AppName::SENSOR_APP)
    tft.println("SENSOR");
  else if (app == AppName::STATIC_FIRE_APP)
    tft.println("STATIC");
  else if (app == AppName::LAUNCHPAD_APP) {
    tft.setCursor(30, 80);
    tft.println("LAUNCHPAD");
  }
  tft.setCursor(100, 180);
  tft.setTextColor(HX8357_WHITE);
  if (app == AppName::SENSOR_APP)
    tft.print("TESTER");
  else if (app == AppName::STATIC_FIRE_APP)
    tft.println("FIRE");
  else if (app == AppName::LAUNCHPAD_APP) {
    tft.setCursor(80, 180);
    tft.println("CONTROL");
  }
}

void ScreenManager::tester_graph_screen(std::string name, int *values) {
  tft.fillScreen(HX8357_BLACK);
  tft.setTextColor(HX8357_WHITE);
  tft.setTextSize(2);
  tft.setCursor(200, 4);
  tft.println(name.c_str());
  tft.setTextSize(1);
  tft.setCursor(0, 30);
  int max = 500;  // std::max_element(values.begin(), values.end());
  tft.println(max, DEC);
  tft.setCursor(0, 292);
  int min = 0;  // std::min_element(values.begin(), values.end());
  tft.println(min, DEC);
  tft.setCursor(5, 160);
  tft.println("Y");
  tft.setCursor(240, 305);
  tft.println("t");
  tft.drawFastVLine(20, 20, 280, HX8357_WHITE);
  tft.fillTriangle(20, 20, 23, 25, 17, 25, HX8357_WHITE);
  tft.drawFastHLine(20, 300, 440, HX8357_WHITE);
  tft.fillTriangle(460, 300, 455, 303, 455, 297, HX8357_WHITE);
  int value = 0;
  for(int i = 0; i<MAX_X_GRAPH; i++){
    value  = 0 + ((500.0 - 0.0) / (278.0 - 0.0)) * (double)(values[i] - 0) - 278;
    tft.drawPixel(i+21, value+20, HX8357_RED);
  }
}

// ###
// ### test functions ###
// ###

unsigned long ScreenManager::testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(HX8357_RED);
  tft.fillScreen(HX8357_GREEN);
  tft.fillScreen(HX8357_BLUE);
  tft.fillScreen(HX8357_WHITE);
  return micros() - start;
}

unsigned long ScreenManager::testText() {
  tft.fillScreen(HX8357_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(HX8357_WHITE);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(HX8357_YELLOW);
  tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(HX8357_RED);
  tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(HX8357_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");

  tft.setTextColor(HX8357_WHITE);
  tft.println(
      F("Alice was beginning to get very tired of sitting by her sister on the bank, and of having "
        "nothing to do: once or twice she had peeped into the book her sister was reading, but it "
        "had no pictures or conversations in it, 'and what is the use of a book,' thought Alice "
        "'without pictures or conversations?'"));

  tft.println(
      F("So she was considering in her own mind (as well as she could, for the hot day made her "
        "feel very sleepy and stupid), whether the pleasure of making a daisy-chain would be worth "
        "the trouble of getting up and picking the daisies, when suddenly a White Rabbit with pink "
        "eyes ran close by her."));

  tft.println(
      F("There was nothing so very remarkable in that; nor did Alice think it so very much out of "
        "the way to hear the Rabbit say to itself, 'Oh dear! Oh dear! I shall be late!' (when she "
        "thought it over afterwards, it occurred to her that she ought to have wondered at this, "
        "but at the time it all seemed quite natural); but when the Rabbit actually took a watch "
        "out of its waistcoat-pocket, and looked at it, and then hurried on, Alice started to her "
        "feet, for it flashed across her mind that she had never before seen a rabbit with either "
        "a waistcoat-pocket, or a watch to take out of it, and burning with curiosity, she ran "
        "across the field after it, and fortunately was just in time to see it pop down a large "
        "rabbit-hole under the hedge."));

  tft.println(
      F("In another moment down went Alice after it, never once considering how in the world she "
        "was to get out again."));

  tft.println(
      F("The rabbit-hole went straight on like a tunnel for some way, and then dipped suddenly "
        "down, so suddenly that Alice had not a moment to think about stopping herself before she "
        "found herself falling down a very deep well."));

  tft.println(
      F("Either the well was very deep, or she fell very slowly, for she had plenty of time as she "
        "went down to look about her and to wonder what was going to happen next. First, she tried "
        "to look down and make out what she was coming to, but it was too dark to see anything; "
        "then "
        "she looked at the sides of the well, and noticed that they were filled with cupboards and "
        "book-shelves; here and there she saw maps and pictures hung upon pegs. She took down a "
        "jar "
        "from one of the shelves as she passed; it was labelled 'ORANGE MARMALADE', but to her "
        "great "
        "disappointment it was empty: she did not like to drop the jar for fear of killing "
        "somebody, "
        "so managed to put it into one of the cupboards as she fell past it."));

  return micros() - start;
}

unsigned long ScreenManager::testLines(uint16_t color) {
  unsigned long start;
  int x1, y1, x2, y2, w = tft.width(), h = tft.height();

  tft.fillScreen(HX8357_BLACK);

  x1 = y1 = 0;
  y2 = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2 = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}