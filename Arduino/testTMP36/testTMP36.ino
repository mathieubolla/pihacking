const int power = 12;
const int monitor = 13;
const int analog = A0;
const int serialRate = 9600;

int current = 0;
float lastValues[5];

void setup() {
  // Beware: This is for Arduino Pro Mini 8MHz
  // most boards do not need this division
  Serial.begin(serialRate / 2);
  pinMode(power, OUTPUT);
  digitalWrite(power, HIGH);
  pinMode(monitor, OUTPUT);
}

void loop() {
  // Power up the thermo sensor
  digitalWrite(power, HIGH);
  // Power up monitor led
  digitalWrite(monitor, HIGH);
  // Wait for consistent ADC reading and enough to see led light
  delay(1000);
  // Read sensor value
  int value = analogRead(analog);
  
  lastValues[current] = value;
  
  digitalWrite(power, LOW);
  digitalWrite(monitor, LOW);
  
  // Print values to serial
  // Formula is 10mV per degree celsius for this sensor
  // Arduino reference is 3.3 on this board
  // ADC range is 0 to 1023 (10 bits)
  // Shift at zero is 500mV or .5V
  Serial.println(100 * (average(lastValues) * (3.3 / 1023) - .5));
  // Flush serial to get more consistent decoding at the other end of serial link
  Serial.flush();
  
  // Wait for next loop
  delay(2000);
  
  current = current + 1;
  if (current == 5) {
    current = 0;
  }
}

float average(float input[]) {
  float sum = 0.0;
  for (int i = 0; i < 5; i++) {
    sum += input[i];
  }
  return sum / 5;
}
