// KY-039 Heartbeat Sensor - BPM Monitor
// Connect Signal pin to A0
// Connect VCC to 5V
// Connect GND to GND

const int sensorPin = A0;
const int ledPin = 13;

// Variables for BPM calculation
int signal;
int threshold = 550;  // Adjust based on your sensor readings
unsigned long lastBeatTime = 0;
unsigned long currentTime = 0;
int bpm = 0;
int beatCount = 0;
unsigned long startTime = 0;
const int avgPeriod = 10000;  // 10 seconds averaging period

// Signal processing variables
int readings[10];
int readIndex = 0;
int total = 0;
int average = 0;
bool beatDetected = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 300;  // Minimum 300ms between beats

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  
  // Initialize readings array
  for (int i = 0; i < 10; i++) {
    readings[i] = 0;
  }
  
  startTime = millis();
  Serial.println("KY-039 Heartbeat Sensor - BPM Monitor");
  Serial.println("Place your finger on the sensor...");
  Serial.println("-----------------------------------");
}

void loop() {
  // Read sensor value
  signal = analogRead(sensorPin);
  
  // Moving average filter to smooth signal
  total = total - readings[readIndex];
  readings[readIndex] = signal;
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % 10;
  average = total / 10;
  
  currentTime = millis();
  
  // Beat detection
  if (average > threshold && !beatDetected && 
      (currentTime - lastDebounceTime) > debounceDelay) {
    
    beatDetected = true;
    lastDebounceTime = currentTime;
    
    // Calculate time between beats
    unsigned long timeBetweenBeats = currentTime - lastBeatTime;
    
    if (lastBeatTime != 0 && timeBetweenBeats > 300 && timeBetweenBeats < 2000) {
      // Calculate instantaneous BPM
      int instantBpm = 60000 / timeBetweenBeats;
      
      // Only accept realistic heart rates (40-200 BPM)
      if (instantBpm >= 40 && instantBpm <= 200) {
        beatCount++;
        digitalWrite(ledPin, HIGH);
        
        Serial.print("Beat detected! Instant BPM: ");
        Serial.println(instantBpm);
      }
    }
    
    lastBeatTime = currentTime;
  }
  
  // Reset beat detection when signal drops
  if (average < threshold - 50) {
    beatDetected = false;
    digitalWrite(ledPin, LOW);
  }
  
  // Calculate average BPM every 10 seconds
  if (currentTime - startTime >= avgPeriod) {
    if (beatCount > 0) {
      bpm = (beatCount * 60000) / avgPeriod;
      
      Serial.println("===========================");
      Serial.print("Average BPM: ");
      Serial.println(bpm);
      Serial.print("Beats detected: ");
      Serial.println(beatCount);
      Serial.println("===========================");
    } else {
      Serial.println("No beats detected. Check sensor placement.");
    }
    
    // Reset for next measurement period
    beatCount = 0;
    startTime = currentTime;
  }
  
  // Optional: Print raw sensor value for calibration
  // Uncomment the lines below to see sensor readings
  /*
  Serial.print("Raw: ");
  Serial.print(signal);
  Serial.print(" | Avg: ");
  Serial.println(average);
  */
  
  delay(20);  // Small delay for stability
}

// Additional function to auto-calibrate threshold
void calibrateThreshold() {
  Serial.println("Calibrating... Keep finger still on sensor");
  int minVal = 1023;
  int maxVal = 0;
  
  for (int i = 0; i < 100; i++) {
    int val = analogRead(sensorPin);
    if (val < minVal) minVal = val;
    if (val > maxVal) maxVal = val;
    delay(50);
  }
  
  threshold = (minVal + maxVal) / 2;
  Serial.print("Threshold set to: ");
  Serial.println(threshold);
}