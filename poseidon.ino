int relayPin = 3;
int bluePin = 4;
int greenPin = 5;
int offPin = 6;
int waterPin = 9;
int sensePin = A0;
boolean running;
boolean pour = false; // If it should pour this loop
boolean fill = false; // If it's running a long fill
unsigned long time = 0;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(offPin, INPUT);
  pinMode(waterPin, INPUT);
  pinMode(sensePin, INPUT);
}

void loop() {
  pour = false;
  running = true;
  if (!digitalRead(offPin)) {
    // On
    digitalWrite(greenPin, HIGH);
  } else {
    // Off
    digitalWrite(greenPin, LOW);
    running = false;
  }
  if (digitalRead(waterPin)) {
    pour = true;
  }
  if (900 > analogRead(sensePin) && analogRead(sensePin) > 700) {
    fill = true;
  }
  if (fill) {
    int elapsed = millis() - time;
    if (time == 0) {
      time = millis();
    } else if (elapsed <= 2000) {
      pour = true;
    } else if (elapsed >= 2000) {
      time = 0;
      fill = false;
    }
  }
  water(pour);
}

void water(int status) {
  if (status && running) {
    digitalWrite(relayPin, HIGH);
    digitalWrite(bluePin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
    digitalWrite(bluePin, LOW);
  }
}
