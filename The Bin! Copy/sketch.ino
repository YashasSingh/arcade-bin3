// Now turn this trash into treasure!
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

// Pin definitions
const int buzzerPin = 21; // Pin for the buzzer
const int potPin = 26;    // ADC0
const int joyXPin = 27;   // ADC1
const int joyYPin = 28;   // ADC2
const int joyButtonPin = 22; // Joystick button

void setup() {
  // Initialize serial communication at 115200 baud
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico W!");

  // ADC pin setup
  analogReadResolution(12); // Set ADC resolution to 12 bits

  // Joystick button pin setup
  pinMode(joyButtonPin, INPUT_PULLUP); // Set button pin as input with internal pull-up

  // Buzzer pin setup
  pinMode(buzzerPin, OUTPUT);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial1.println(F("SSD1306 allocation failed"));
    for (;;);
    }
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
}

void loop() {
  // Read the analog value from the potentiometer (connected to GP26 / ADC0)
  int potValue = analogRead(potPin); // Read the ADC value
  float potVoltage = potValue * (3.3 / 4095.0); // Convert ADC value to voltage

  // Read the analog values from the joystick (connected to GP27 / ADC1 and GP28 / ADC2)
  int joyXValue = analogRead(joyXPin); // Read the ADC value for X-axis
  float joyXVoltage = joyXValue * (3.3 / 4095.0); // Convert ADC value to voltage

  int joyYValue = analogRead(joyYPin); // Read the ADC value for Y-axis
  float joyYVoltage = joyYValue * (3.3 / 4095.0); // Convert ADC value to voltage

  // Read the button state from the joystick (connected to GP22)
  int joyButtonState = digitalRead(joyButtonPin); // Read the button state (0 = pressed, 1 = not pressed)

  // Print the potentiometer value and voltage to the serial monitor
  Serial1.print("Potentiometer Value: ");
  Serial1.print(potValue);
  Serial1.print(" | Voltage: ");
  Serial1.print(potVoltage);
  Serial1.print(" V | ");

  // Print the joystick X and Y values and voltages to the serial monitor
  Serial1.print("Joystick X Value: ");
  Serial1.print(joyXValue);
  Serial1.print(" | X Voltage: ");
  Serial1.print(joyXVoltage);
  Serial1.print(" V | ");

  Serial1.print("Joystick Y Value: ");
  Serial1.print(joyYValue);
  Serial1.print(" | Y Voltage: ");
  Serial1.print(joyYVoltage);
  Serial1.print(" V | ");

  // Print the joystick button state to the serial monitor
  Serial1.print("Joystick Button State: ");
  Serial1.println(joyButtonState == 0 ? "Pressed" : "Not Pressed");

  // Control the buzzer with the joystick button
  if (joyButtonState == 0) { // If the button is pressed
    tone(buzzerPin, 1000); // Play a tone at 1000 Hz
  } else {
    noTone(buzzerPin); // Stop the tone
  }

  // Display values on the OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Pot: ");
  display.print(potValue);
  display.print(" | ");
  display.print(potVoltage);
  display.println("V");

  display.setCursor(0, 10);
  display.print("Joy X: ");
  display.print(joyXValue);
  display.print(" | ");
  display.print(joyXVoltage);
  display.println("V");

  display.setCursor(0, 20);
  display.print("Joy Y: ");
  display.print(joyYValue);
  display.print(" | ");
  display.print(joyYVoltage);
  display.println("V");

  display.setCursor(0, 30);
  display.print("Button: ");
  display.println(joyButtonState == 0 ? "Pressed" : "Not Pressed");

  display.display();

  delay(100); // Delay to avoid overwhelming the serial monitor
}
