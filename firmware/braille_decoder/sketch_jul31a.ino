// ---------------- Braille ----------------
const int dotPins[6] = {2, 3, 4, 5, 6, 7};

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
    bool pressed = !digitalRead(dotPins[i]);
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
void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < 6; i++)
    pinMode(dotPins[i], INPUT_PULLUP);

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
  }

  delay(30);
}