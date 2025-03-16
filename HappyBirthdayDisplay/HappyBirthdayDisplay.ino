#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // LCD pins connected to Arduino

// Define the buzzer pin
int buzzerPin = 9;

// Define the notes for Happy Birthday (in Hz)
int notes[] = { // Frequencies for Happy Birthday Song
  262, 262, 294, 262, 349, 330, 262, 262, 294, 262, 392, 349, // Happy Birthday to you
  262, 262, 523, 440, 349, 330, 294, 466, 466, 440, 349, 392, 349, // Happy Birthday to you
  262, 262, 294, 262, 349, 330, 262, 262, 294, 262, 392, 349, // Happy Birthday dear (Name)
  523, 523, 523, 440, 349, 330, 294, 0 // Happy Birthday to you
};

int durations[] = { // Note durations (in milliseconds)
  400, 400, 800, 400, 400, 400, 400, 400, 400, 800, 400, 400, // Happy Birthday to you
  400, 400, 400, 400, 400, 400, 400, 400, 400, 800, 400, 400, 400,  // Happy Birthday to you
  400, 400, 400, 400, 400, 400, 400, 400, 400, 800, 400, 400, // Happy Birthday dear (Name)
  400, 400, 400, 800, 400, 0 // Happy Birthday to you
};

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  lcd.clear(); 

  // Display the Happy Birthday message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Happy Birthday!");
  lcd.setCursor(0, 1);
  lcd.print("Euclid!");
  
  
}

void loop() {
  playHappyBirthdaySong();  // Play the Happy Birthday song
  delay(1000);  // Wait for 1 second before repeating (if you want to repeat the song, this can be changed)
}

void playHappyBirthdaySong() {
  // Play the Happy Birthday song
  for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {
    int noteDuration = durations[i];
    tone(buzzerPin, notes[i], noteDuration);  // Play the note
    delay(noteDuration * 1.30);  // Wait for the note to finish (add a small pause between notes)
  }
}
