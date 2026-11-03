#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 4
#define OLED_SCL 5

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool oledOK = false; // tracks whether OLED initialized successfully

// ---------------- Braille ----------------
const int dotPins[6] = {2, 3, 9, 8, 7, 6};

struct BrailleLetter
{
  byte pattern;
  char letter;
};

BrailleLetter brailleTable[] =
{
  {0b100000, 'A'},
  {0b110000, 'B'},
  {0b100100, 'C'},
  {0b100110, 'D'},
  {0b100010, 'E'},
  {0b110100, 'F'},
  {0b110110, 'G'},
  {0b110010, 'H'},
  {0b010100, 'I'},
  {0b010110, 'J'},
  {0b101000, 'K'},
  {0b111000, 'L'},
  {0b101100, 'M'},
  {0b101110, 'N'},
  {0b101010, 'O'},
  {0b111100, 'P'},
  {0b111110, 'Q'},
  {0b111010, 'R'},
  {0b011100, 'S'},
  {0b011110, 'T'},
  {0b101001, 'U'},
  {0b111001, 'V'},
  {0b010111, 'W'},
  {0b101101, 'X'},
  {0b101111, 'Y'},
  {0b101011, 'Z'}
};

const int tableSize = sizeof(brailleTable) / sizeof(brailleTable[0]);

// ------------------------------------------------
byte readPattern()
{
  byte pattern = 0;
  for (int i = 0; i < 6; i++)
  {
    bool pressed = digitalRead(dotPins[i]); // unpressed = 1 (rest state), pressed = 0
    if (pressed)
      pattern |= (1 << (5 - i));
  }
  return pattern;
}

// ------------------------------------------------
char decode(byte pattern)
{
  for (int i = 0; i < tableSize; i++)
  {
    if (pattern == brailleTable[i].pattern)
      return brailleTable[i].letter;
  }
  return '?';
}

// ------------------------------------------------
void showLetter(char letter)
{
  if (!oledOK) return; // skip silently if OLED never initialized

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Braille Decoder");
  display.drawLine(0, 12, 128, 12, SSD1306_WHITE);

  display.setTextSize(5);
  display.setCursor(45, 25);
  display.print(letter);

  display.display();
}

// ------------------------------------------------
void setup()
{
  Serial.begin(115200);

  // Switches
  for (int i = 0; i < 6; i++)
    pinMode(dotPins[i], INPUT_PULLUP);

  // OLED - set pins before begin()
  Wire.setSDA(OLED_SDA);
  Wire.setSCL(OLED_SCL);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED not found! Continuing without display.");
    oledOK = false;
  }
  else
  {
    oledOK = true;
    display.clearDisplay();
    display.display();
    showLetter('-');
  }

  Serial.println("================================");
  Serial.println(" Braille Decoder Ready");
  Serial.println("================================");
}

// ------------------------------------------------
void loop()
{
  static byte lastPattern = 255;
  byte pattern = readPattern();

  if (pattern != lastPattern)
  {
    lastPattern = pattern;
    char letter = decode(pattern);

    Serial.print("Pattern : ");
    for (int i = 5; i >= 0; i--)
      Serial.print(bitRead(pattern, i));

    Serial.print("   Letter : ");
    Serial.println(letter);

    showLetter(letter);
  }

  delay(30);
}
