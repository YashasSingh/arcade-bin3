// Now turn this trash into treasure!

const int buzzerPin = 21; // Pin for the buzzer

void setup() {
  // Initialize serial communication at 115200 baud
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico W!");

  // ADC pin setup
  analogReadResolution(12); // Set ADC resolution to 12 bits

  // Joystick button pin setup
  pinMode(22, INPUT_PULLUP); // Set button pin as input with internal pull-up

  // Buzzer pin setup
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Read the analog value from the potentiometer (connected to GP26 / ADC0)
  int potValue = analogRead(26); // Read the ADC value
  float potVoltage = potValue * (3.3 / 4095.0); // Convert ADC value to voltage

  // Read the analog values from the joystick (connected to GP27 / ADC1 and GP28 / ADC2)
  int joyXValue = analogRead(27); // Read the ADC value for X-axis
  float joyXVoltage = joyXValue * (3.3 / 4095.0); // Convert ADC value to voltage

  int joyYValue = analogRead(28); // Read the ADC value for Y-axis
  float joyYVoltage = joyYValue * (3.3 / 4095.0); // Convert ADC value to voltage

  // Read the button state from the joystick (connected to GP22)
  int joyButtonState = digitalRead(22); // Read the button state (0 = pressed, 1 = not pressed)

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

  delay(100); // Delay to avoid overwhelming the serial monitor
}
