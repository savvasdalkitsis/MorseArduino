#define led 13
#define dot 100
#define dash 600
#define letterDelay 300
#define wordDelay 500

const char* morseCodes[] = {
  "*-",      // A
  "-***",    // B
  "-*-*",    // C
  "-**",     // D
  "*",       // E
  "**-*",    // F
  "--*",     // G
  "****",    // H
  "**",      // I
  "*---",    // J
  "-*-",     // K
  "*-**",    // L
  "--",      // M
  "-*",      // N
  "---",     // O
  "*--*",    // P
  "--*-",    // Q
  "*-*",     // R
  "***",     // S
  "-",       // T
  "**-",     // U
  "***-",    // V
  "*--",     // W
  "-**-",    // X
  "-*--",    // Y
  "--**",    // Z
  "-----",   // 0
  "*----",   // 1
  "**---",   // 2
  "***--",   // 3
  "****-",   // 4
  "*****",   // 5
  "-****",   // 6
  "--***",   // 7
  "---**",   // 8
  "----*",   // 9
};
int input;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);  
  Serial.println("Start writing here. The characters and numbers will be converted to Morse code on the LED on the board");
  Serial.println(); 
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.read();
    if (!isAlphaNumeric(input)) {
      Serial.print("'");
      Serial.print(char(input));
      Serial.println("' is an invalid character. You can only input characters 'a'..'z', 'A'..'Z' and numbers '0'..'9'");
    } else {
      const char* morse = morseCodes[morseIndexFor(input)];
      int i = 0;
      char letter = 0;
      Serial.write(input);
      Serial.print(" = ");
      do {
        letter = morse[i++];
        flashMorseFor(letter);
      } while (letter > 0);
      Serial.println();
      delay(wordDelay);
    }
  }
}

int morseIndexFor(int input) {
  int offset = 0;
  if (isLowerCase(input)) {
    offset = 'a';
  } else if (isUpperCase(input)) {
    offset = 'A';
  } else if (isDigit(input)) {
    offset = '0' - 26;
  }
  return input - offset;
}

void flashMorseFor(char letter) {
  Serial.print(letter);
  digitalWrite(led, HIGH);
  if (letter == '*') {
    delay(dot);
  } else if (letter == '-') {
    delay(dash);
  }
  digitalWrite(led, LOW);
  delay(letterDelay);
}
