#define GAS_SENSOR A0
#define BUZZER     7
#define RELAY      6

int alc = 0; // Will store the digital reading from the sensor

void setup() {
  Serial.begin(9600);
  pinMode(GAS_SENSOR, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Initial states
  digitalWrite(RELAY, HIGH);   // Relay HIGH (motor off if your relay is active-low)
  digitalWrite(BUZZER, LOW);   // Buzzer off

  Serial.println("Alcohol Detection System Initialized");
  delay(2000);
}

void loop() {
  // Read the sensor as a digital input
  alc = digitalRead(GAS_SENSOR);

  if (alc == HIGH) {
    // No alcohol detected
    digitalWrite(BUZZER, LOW);   // Buzzer off
    digitalWrite(RELAY, LOW);    // Relay low (motor on if active-low relay)
    Serial.println("No Alcohol Detected -> Motor ON");
    
  } else {
    // Alcohol detected
    digitalWrite(BUZZER, HIGH);  // Buzzer on
    digitalWrite(RELAY, HIGH);   // Relay high (motor off if active-low relay)
    Serial.println("ALCOHOL DETECTED -> Motor OFF");
  }

  delay(1000); // Small delay between readings
}


#define MQ3_PIN    A0   // MQ-3 sensor analog output
#define RELAY_PIN  6
#define BUZZER_PIN 7

// Adjust this threshold to match the typical reading that indicates "alcohol detected."
// Higher threshold => sensor needs a higher voltage to decide "alcohol is present."
int threshold = 400;  

void setup() {
  Serial.begin(9600);

  pinMode(MQ3_PIN, INPUT);       // Reading analog sensor
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initial states: turn motor OFF (relay not energized) and buzzer OFF.
  // If your relay is active HIGH, swap these two lines (HIGH <-> LOW).
  digitalWrite(RELAY_PIN, HIGH); 
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("MQ-3 Alcohol Detection System Initialized");
  delay(3000);
}

void loop() {
  // 1) Read from MQ3 sensor
  int sensorValue = analogRead(MQ3_PIN);

  // 2) Print sensor value for debugging
  Serial.print("MQ-3 reading: ");
  Serial.println(sensorValue);

  // 3) Compare against threshold
  if (sensorValue > threshold) {
    // Alcohol detected
    digitalWrite(RELAY_PIN, HIGH);  // Motor OFF if relay is active LOW
    digitalWrite(BUZZER_PIN, HIGH); // Buzzer ON
    Serial.println("ALCOHOL DETECTED -> Motor OFF, Buzzer ON");
  }
  else {
    // No alcohol
    digitalWrite(RELAY_PIN, LOW);   // Motor ON if relay is active LOW
    digitalWrite(BUZZER_PIN, LOW);  // Buzzer OFF
    Serial.println("No Alcohol -> Motor ON, Buzzer OFF");
  }

  delay(1000); // 1 second delay between reads
}
