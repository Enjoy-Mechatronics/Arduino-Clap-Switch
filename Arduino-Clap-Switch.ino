const int sensorPin = 7;
const int ledPin = 6;

String ledState = "off";

long lastEvent = 0;
long prevClapTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {

  // Read Sound Sensor data
  int sensorData = digitalRead(sensorPin);
  // If pin goes HIGH, sound is detected
  if (sensorData == HIGH) {

    // If 25ms have passed since last HIGH state, it means that
    // the clap is detected and not due to any spurious sounds
    if (millis() - lastEvent > 25) {
      Serial.println("Clap detected!");

      // If the Time between  two claps is greater than 600ms
      // Two consecutive Claps are Detected
      if(millis() - prevClapTime < 500){
        toggleState();
      }
      prevClapTime = millis();
    }

    // Remember when last event happened
    lastEvent = millis();
  }

}

void toggleState() {

  if (ledState == "off") {
    ledState = "on";
    digitalWrite(ledPin, HIGH);
  } else {
    ledState = "off";
    digitalWrite(ledPin, LOW);
  }
}
