int humidity;

void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  humidity = analogRead(A0);
  Serial.println(humidity);
}
