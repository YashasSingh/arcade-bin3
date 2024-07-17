// Now turn this trash into treasure!

void setup() {
  // Initialize serial communication at 115200 baud
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico W!");

  // ADC pin setup
  analogReadResolution(12); // Set ADC resolution to 12 bits
}

void loop() {
  // Read the analog value from the potentiometer (connected to GP26 / ADC0)
  int potValue = analogRead(26); // Read the ADC value
  float voltage = potValue * (3.3 / 4095.0); // Convert ADC value to voltage

  // Print the potentiometer value and voltage to the serial monitor
  Serial1.print("Potentiometer Value: ");
  Serial1.print(potValue);
  Serial1.print(" | Voltage: ");
  Serial1.println(voltage);

  delay(100); // Delay to avoid overwhelming the serial monitor
}
