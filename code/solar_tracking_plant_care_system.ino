#include <Servo.h>
#include <dht11.h>

#define MIST_PIN A0
#define DHT11_PIN A1
#define LDR_1_PIN A2
#define LDR_2_PIN A3

#define TEMP_LOWEST 20
#define LDR_THRESHOLD 20
#define INITIAL_POS 90
#define MIN_POS 0
#define MAX_POS 180

int pos = INITIAL_POS;

Servo solarServo;
dht11 DHT11;

void setup() {
  Serial.begin(9600);
  solarServo.attach(9);
  solarServo.write(90);
  pinMode(MIST_PIN, OUTPUT);
  pinMode(LDR_1_PIN, INPUT);
  pinMode(LDR_2_PIN, INPUT);
  digitalWrite(MIST_PIN, HIGH);
}

void loop() {
  // Serial.println(readTemp());
  DHT11.read(DHT11_PIN);
  float temp = DHT11.read(DHT11_PIN);
  int leftLDR = analogRead(LDR_1_PIN);
  int rightLDR = analogRead(LDR_2_PIN);

  Serial.print("LDR Left: ");
  Serial.print(leftLDR);
  Serial.print("\t\tLDR Right: ");
  Serial.print(rightLDR);
  Serial.print("\t\tTemp: ");
  Serial.print(temp);
  Serial.print("\t\tPos: ");
  Serial.println(pos);

  if (abs(leftLDR - rightLDR) > LDR_THRESHOLD) {
    if (leftLDR > rightLDR && pos < MAX_POS) {
      pos += 2;
    } else if (rightLDR > leftLDR && pos > MIN_POS) {
      pos -= 2;
    }
    solarServo.write(pos);
  }

  if (temp < TEMP_LOWEST) {
    digitalWrite(MIST_PIN, LOW);
  } else {
    digitalWrite(MIST_PIN, HIGH);
  }

  delay(200);
}
