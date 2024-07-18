#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Display dimensions for OLED
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

// Reset pin for OLED display
#define OLED_RESET_PIN -1

// Initialize SSD1306 OLED display
Adafruit_SSD1306 oledDisplay(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET_PIN);

// Pins for potentiometer and joystick
const int potentiometerPin = 26; // ADC0
const int joystickYPin = 28; // ADC2 (Y-axis)

// Pin for buzzer
const int buzzerPin = 21; // Choose a suitable pin for the buzzer

// Dimensions and positions for paddle and ball
int paddleHeight = 10;
int paddleWidth = 2;
int paddleLeftY;
int paddleRightY;
int ballPosX, ballPosY;
int ballVelocityX = 1, ballVelocityY = 1;
int paddleMoveStep = 1;
int screenBottom = 220;
int speedMultiplier = 1;

// Scores for players
int playerLeftScore = 0;
int playerRightScore = 0;

// Increment for speed
float speedIncrease = 0.2;

// Winning score
const int maxScore = 5;

// Function to generate a tone on the buzzer
void generateTone(int frequency, int duration) {
  tone(buzzerPin, frequency, duration);
  delay(duration);
  noTone(buzzerPin);
}

// Function to play point sound
void playPointSound() {
  generateTone(1000, 50);
}

// Function to play victory sound
void playVictorySound() {
  generateTone(1000, 50);
  generateTone(2000, 50);
  generateTone(3000, 50);
  generateTone(4000, 100);
  generateTone(500, 150);
}

// Function to display victory message
void showVictoryMessage(const char* winner) {
  oledDisplay.clearDisplay();
  oledDisplay.setTextSize(2);
  oledDisplay.setTextColor(SSD1306_WHITE);
  oledDisplay.setCursor(10, 20);
  oledDisplay.print(winner);
  oledDisplay.display();
  playVictorySound();
  while (true) {
    // Stop the game
  }
}

void setup() {
  // Initialize serial communication
  Serial1.begin(115200);
  Serial1.println("Pong Game Initialization");

  // Initialize the OLED display
  if (!oledDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial1.println(F("Failed to initialize SSD1306"));
    for (;;);
  }
  oledDisplay.display();
  delay(2000); // Pause for 2 seconds

  // Clear the display buffer
  oledDisplay.clearDisplay();

  // Set initial positions for paddles and ball
  paddleLeftY = OLED_HEIGHT / 2 - paddleHeight / 2;
  paddleRightY = OLED_HEIGHT / 2 - paddleHeight / 2;
  ballPosX = OLED_WIDTH / 2;
  ballPosY = OLED_HEIGHT / 2;
}

void loop() {
  // Check for a winner
  if (playerLeftScore >= maxScore) {
    showVictoryMessage("P1 Wins!");
  }
  if (playerRightScore >= maxScore) {
    showVictoryMessage("P2 Wins!");
  }

  // Read potentiometer value
  int potValue = analogRead(potentiometerPin); // ADC read
  paddleLeftY = map(potValue, 0, 4095, 0, screenBottom); // Map to paddle position

  // Read joystick Y-axis value
  int joystickValueY = analogRead(joystickYPin); // ADC read for Y-axis
  Serial1.println(joystickValueY);

  // Move right paddle based on joystick position
  if (joystickValueY > 1020) { // Move up
    paddleRightY -= paddleMoveStep;
    if (paddleRightY < 0) paddleRightY = 0;
  }
  if (joystickValueY < 511) { // Move down
    paddleRightY += paddleMoveStep;
    if (paddleRightY > screenBottom) paddleRightY = screenBottom;
  }

  // Update ball position
  ballPosX += ballVelocityX * speedMultiplier;
  ballPosY += ballVelocityY * speedMultiplier;

  // Ball collision with top and bottom
  if (ballPosY <= 0 || ballPosY >= OLED_HEIGHT - 1) {
    ballVelocityY = -ballVelocityY;
  }

  // Ball collision with left paddle
  if (ballPosX <= paddleWidth && ballPosY >= paddleLeftY && ballPosY <= paddleLeftY + paddleHeight) {
    ballVelocityX = -ballVelocityX;
    ballVelocityX += (ballVelocityX > 0 ? speedIncrease : -speedIncrease);
    ballVelocityY += (ballVelocityY > 0 ? speedIncrease : -speedIncrease);
    speedMultiplier += 1;
  }

  // Ball collision with right paddle
  if (ballPosX >= OLED_WIDTH - paddleWidth - 1 && ballPosY >= paddleRightY && ballPosY <= paddleRightY + paddleHeight) {
    ballVelocityX = -ballVelocityX;
    ballVelocityX += (ballVelocityX > 0 ? speedIncrease : -speedIncrease);
    ballVelocityY += (ballVelocityY > 0 ? speedIncrease : -speedIncrease);
    Serial1.println("hit");
    speedMultiplier += 1;
  }

  // Ball out of bounds (right side)
  if (ballPosX >= OLED_WIDTH - 1) {
    playerLeftScore++; // Increment left player's score
    playPointSound(); // Play point sound
    ballPosX = OLED_WIDTH / 2;
    ballPosY = OLED_HEIGHT / 2;
    ballVelocityX = 1;
    ballVelocityY = 1;
    Serial1.println("out");
    speedMultiplier = 1;
  }

  // Ball out of bounds (left side)
  if (ballPosX <= 0) {
    playerRightScore++; // Increment right player's score
    playPointSound(); // Play point sound
    ballPosX = OLED_WIDTH / 2;
    ballPosY = OLED_HEIGHT / 2;
    ballVelocityX = -1;
    ballVelocityY = -1;
    speedMultiplier = 1;
  }

  // Clear the display
  oledDisplay.clearDisplay();

  // Draw left paddle
  oledDisplay.fillRect(0, paddleLeftY, paddleWidth, paddleHeight, SSD1306_WHITE);

  // Draw right paddle
  oledDisplay.fillRect(OLED_WIDTH - paddleWidth, paddleRightY, paddleWidth, paddleHeight, SSD1306_WHITE);

  // Draw ball
  oledDisplay.fillRect(ballPosX, ballPosY, 2, 2, SSD1306_WHITE);

  // Display scores
  oledDisplay.setTextSize(1);
  oledDisplay.setTextColor(SSD1306_WHITE);
  oledDisplay.setCursor(30, 0);
  oledDisplay.print("P1: ");
  oledDisplay.print(playerLeftScore);
  oledDisplay.setCursor(80, 0);
  oledDisplay.print("P2: ");
  oledDisplay.print(playerRightScore);

  // Update the display
  oledDisplay.display();

  delay(10); // Control game speed
}
