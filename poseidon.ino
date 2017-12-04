int relayPin = 3;
int bluePin = 4;
int greenPin = 5;
int offPin = 6;
int waterPin = 9;
int sensePin = A0;
boolean running;
boolean pour = false; // If it should pour this loop
boolean fill = false; // If it's running a long fill
boolean failsafe = false; // If there is a problem with the watering
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
  // Serial.println(analogRead(sensePin));
  pour = false;
  running = true;
  if (!digitalRead(offPin)) {
    // On
    digitalWrite(greenPin, HIGH);
  } else {
    // Off
    digitalWrite(greenPin, LOW);
    running = false;
    failsafe = false;
  }
  if (digitalRead(waterPin)) {
    pour = true;
  }
  if (900 > analogRead(sensePin) && analogRead(sensePin) > 700) {
    fill = true;
  }
  if (fill && !failsafe) {
    int elapsed = millis() - time;
    if (time == 0) {
      time = millis();
    } else if (elapsed <= 3000) {
      pour = true;
    } else if (elapsed >= 3000) {
      if (900 > analogRead(sensePin) && analogRead(sensePin) > 700) {
        // Enter failsafe!
        failsafe = true;
      }
      time = 0;
      fill = false;
    }
  }
  if (failsafe) {
    int elapsed = millis() - time;
    if (time == 0) {
      time = millis();
    } else if (elapsed <= 1000) {
      digitalWrite(bluePin, HIGH);
    } else if (1000 <= elapsed && elapsed <= 2000) {
      digitalWrite(bluePin, LOW);
    } else {
      time = millis();
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
