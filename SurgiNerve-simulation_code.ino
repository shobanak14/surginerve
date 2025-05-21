#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define trigPin 7
#define echoPin 6
#define buzzer 8
#define vibPin 9
#define tempPin A0

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(vibPin, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  // Ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // Temperature
  int tempValue = analogRead(tempPin);
  float voltage = tempValue * 5.0 / 1023;
  float temperatureC = voltage * 100;

  // Vibration
  int vibState = digitalRead(vibPin);

  // LCD Display
  lcd.setCursor(0, 0);
  lcd.print("Dis:");
  lcd.print(distance);
  lcd.print("cm");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temperatureC);
  lcd.print("C");

  // Buzzer action
  if (vibState == HIGH || distance < 10) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(500);
}
