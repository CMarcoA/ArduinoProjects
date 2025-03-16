#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // LCD pins connected to Arduino

int timerMinutes = 0;  // User-defined timer minutes (0-25)
int timerSeconds = 0;  // Timer countdown seconds
bool timerRunning = false;  // Timer status (running or stopped)
int settingTimer = 0;  // Flag to track if the timer is being set
int firstLoop = true;  // Flag for the first loop (Pomodoro message)

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  lcd.clear();
  
  Serial.begin(9600);

  // Setup pin modes with internal pull-up resistors
  pinMode(13, INPUT_PULLUP); // Seconds adjustment button (Pin 13)
  pinMode(11, INPUT_PULLUP); // Minutes adjustment button (Pin 11)
  pinMode(10, INPUT_PULLUP); // Set timer button (Pin 10)
  pinMode(8, INPUT_PULLUP);  // Start/Stop timer button (Pin 8)
  
  pinMode(9, OUTPUT);  // Active buzzer
}

void loop() {
  if (firstLoop) {
    lcd.setCursor(0, 0);
    lcd.print("Pomodoro Timer");
    lcd.setCursor(0, 1);
    lcd.print("1-25 mins");
    firstLoop = false;  // Set the flag to false to avoid showing the message again
    
  }

  // Adjust timer values when buttons are pressed
  adjustTimer();
  
  // Set the timer when the user presses the set timer button (Pin 10)
  setTimer();
  
  // Start or stop the timer based on button press (Pin 8)
  startStopTimer();
  
  // If the timer is running, countdown
  if (timerRunning) {
    countdownTimer();
  }
}

// Adjust the timer minutes and seconds before setting
void adjustTimer() {
  // Adjust minutes when button on Pin 11 is pressed
  if (digitalRead(11) == LOW && timerMinutes < 25) {
    timerMinutes++;
    displayTimer();
    delay(200);  // Debounce delay
  }

  // Adjust seconds when button on Pin 13 is pressed
  if (digitalRead(13) == LOW) {
    if (timerSeconds < 59) {
      timerSeconds++;
    } else {
      timerSeconds = 0;  // Reset seconds to 0 if it reaches 59
    }
    displayTimer();
    delay(200);  // Debounce delay
  }
}

// Set the timer with button on Pin 10
void setTimer() {
  if (digitalRead(10) == LOW) {
    if (settingTimer == 0) {
      displayTimer();
      settingTimer = 1;  // Timer is now set
    } else {
      settingTimer = 0;
      timerMinutes = 0;
      timerSeconds = 0;
      timerRunning = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Timer Reset");
      delay(1000);
      displayTimer();
    }
    delay(200);  // Debounce delay
  }
}

// Start or stop the timer with Pin 8
void startStopTimer() {
  if (digitalRead(8) == LOW) {
    timerRunning = !timerRunning;  // Toggle the timer state
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(timerRunning ? "Timer Started" : "Timer Stopped");
    delay(1000);
  }
}

// Countdown the timer
void countdownTimer() {
  if (timerSeconds == 0 && timerMinutes > 0) {
    timerMinutes--;  // Decrease minutes
    timerSeconds = 59;  // Reset seconds to 59
  } else if (timerSeconds > 0) {
    timerSeconds--;  // Decrease seconds
  }

  displayTimer();  // Update LCD display

  // If the timer reaches 0, stop and sound the buzzer
  if (timerMinutes == 0 && timerSeconds == 0) {
    tone(9, 1000, 1000);  // Play a 1-second tone at 1000 Hz
    timerRunning = false;  // Stop the timer
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time's Up!");
    delay(2000);  // Wait for 2 seconds to show the message
    lcd.clear();
    displayMovingEmoji();  // Display the moving emoji after "Time's Up!"
  }

  delay(1000);  // Wait for 1 second before updating
}

// Display the current timer on the LCD
void displayTimer() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Timer Set:");
  lcd.setCursor(0, 1);
  
  // Display minutes and seconds in "MM:SS" format
  lcd.print(timerMinutes < 10 ? "0" : "");
  lcd.print(timerMinutes);
  lcd.print(":");
  lcd.print(timerSeconds < 10 ? "0" : "");
  lcd.print(timerSeconds);
}

// Function to show a moving emoji after the timer ends
void displayMovingEmoji() {
  String emoji = "(O ____ O)";  // Emoji to move across the screen

  // Loop to move the emoji from left to right
  for (int i = 0; i < 16; i++) {  // Move the emoji across the screen
    lcd.setCursor(i, 0);  // Set the cursor at column 'i', row 0
    lcd.print(emoji);  // Print the emoji
    delay(300);  // Wait for 300 milliseconds before moving to the next position
    lcd.clear();  // Clear the LCD for the next frame
  }

  // Now loop it back from right to left
  for (int i = 15; i >= 0; i--) {
    lcd.setCursor(i, 0);  // Set the cursor at column 'i', row 0
    lcd.print(emoji);  // Print the emoji
    delay(300);  // Wait for 300 milliseconds before moving to the next position
    lcd.clear();  // Clear the LCD for the next frame
  }

  // Call this function again to keep looping the emoji movement
  displayMovingEmoji();
}
