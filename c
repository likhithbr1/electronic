/*******************************************************
 *  Simple Alcohol Detection:
 *  - Reads MQ-3 sensor on analog pin A0.
 *  - If reading > threshold => Alcohol detected:
 *       Motor OFF (via Relay), Buzzer ON
 *  - Else => No alcohol:
 *       Motor ON (via Relay), Buzzer OFF
 *******************************************************/

#define GAS_SENSOR A0    // MQ-3 analog output
#define RELAY_PIN  6     // Relay controlling DC motor
#define BUZZER_PIN 7     // Buzzer pin

// Adjust this threshold to your specific MQ-3 readings.
int alcoholThreshold = 300;

void setup() {
  Serial.begin(9600);
  
  pinMode(GAS_SENSOR, INPUT);  // Analog pin for MQ-3
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initial States (assuming an ACTIVE-LOW relay).
  //   - Motor OFF => digitalWrite(RELAY_PIN, HIGH);
  //   - Motor ON  => digitalWrite(RELAY_PIN, LOW);
  // If your relay is ACTIVE-HIGH, you need to invert these signals.
  digitalWrite(RELAY_PIN, LOW);  // Start with motor ON
  digitalWrite(BUZZER_PIN, LOW); // Buzzer OFF

  Serial.println("Alcohol Detection System Initialized");
  delay(2000);
}

void loop() {
  // 1) Read MQ-3 sensor value (0-1023)
  int sensorValue = analogRead(GAS_SENSOR);

  // 2) Debug output
  Serial.print("Alcohol Sensor Value: ");
  Serial.println(sensorValue);

  // 3) Compare against threshold
  if (sensorValue > alcoholThreshold) {
    // ALCOHOL DETECTED
    // Motor OFF (if relay is active LOW)
    digitalWrite(RELAY_PIN, HIGH);
    // Buzzer ON
    digitalWrite(BUZZER_PIN, HIGH);

    Serial.println("ALCOHOL DETECTED -> Motor OFF, Buzzer ON");
  } else {
    // NO ALCOHOL
    // Motor ON (if relay is active LOW)
    digitalWrite(RELAY_PIN, LOW);
    // Buzzer OFF
    digitalWrite(BUZZER_PIN, LOW);

    Serial.println("No Alcohol -> Motor ON, Buzzer OFF");
  }

  delay(1000); // Wait 1 second before next read
}

