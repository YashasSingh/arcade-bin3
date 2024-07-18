#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED reset pin
#define OLED_RESET -1

// Create an instance of the SSD1306 display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define the potentiometer and joystick pins
const int potPin = 26; // ADC0
const int joyYPin = 28; // ADC2 (Y-axis)

// Paddle and ball parameters
int paddleHeight = 10;
int paddleWidth = 2;
int paddleY;
int paddleY2;
int ballX, ballY;
int ballSpeedX = 1, ballSpeedY = 1;

void setup() {
  // Initialize serial communication
  Serial1.begin(115200);
  Serial1.println("Pong Game Setup");

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial1.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Initialize paddle and ball positions
  paddleY = SCREEN_HEIGHT / 2 - paddleHeight / 2;
  paddleY2 = SCREEN_HEIGHT / 2 - paddleHeight / 2;
  ballX = SCREEN_WIDTH / 2;
  ballY = SCREEN_HEIGHT / 2;
}

void loop() {
  // Read the analog value from the potentiometer
  int potValue = analogRead(potPin); // Read the ADC value
  paddleY = map(potValue, 0, 4095, 0, 220); // Map to paddle position

  // Read the analog value from the joystick Y-axis
  int joyYValue = analogRead(joyYPin); // Read the ADC value for Y-axis
  paddleY2 = map(joyYValue, 0, 4095, 0, 220); // Map to paddle position

  // Update ball position
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Ball collision with top and bottom
  if (ballY <= 0 || ballY >= SCREEN_HEIGHT - 1) {
    ballSpeedY = -ballSpeedY;
  }

  // Ball collision with left paddle
  if (ballX <= paddleWidth && ballY >= paddleY && ballY <= paddleY + paddleHeight) {
    ballSpeedX = -ballSpeedX;
  }

  // Ball collision with right paddle
  if (ballX >= SCREEN_WIDTH - paddleWidth - 1 && ballY >= paddleY2 && ballY <= paddleY2 + paddleHeight) {
    ballSpeedX = -ballSpeedX;
  }

  // Ball goes out of bounds (right side)
  if (ballX >= SCREEN_WIDTH - 1) {
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;
    ballSpeedX = 1;
    ballSpeedY = 1;
  }

  // Ball goes out of bounds (left side)
  if (ballX <= 0) {
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;
    ballSpeedX = -1;
    ballSpeedY = -1;
  }

  // Clear display
  display.clearDisplay();

  // Draw left paddle
  display.fillRect(0, paddleY, paddleWidth, paddleHeight, SSD1306_WHITE);

  // Draw right paddle
  display.fillRect(SCREEN_WIDTH - paddleWidth, paddleY2, paddleWidth, paddleHeight, SSD1306_WHITE);

  // Draw ball
  display.fillRect(ballX, ballY, 2, 2, SSD1306_WHITE);

  // Update display
  display.display();

  delay(10); // Delay to control the speed of the game
}
