#include <Servo.h>
Servo servo[4];
byte sPins[4] = {3, 5, 6, 9};
byte adcPins[4] = {A1, A2, A3, A4};
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    servo[i].attach(sPins[i]);
  }
}
int adc[5] = {0, 0, 0, 0};
int lServo[4] = {45, 90, 90, 90};
int cServo[4] = {5, 5, 5, 5};
int cIR[4] = {0, 0, 0, 0};

void loop() {
  runServo();
  readServo();
  delay(100);
}



void mapServo() {
  int s[4];
  readIR();
  Serial.print("Servo Maped: ");
  for (int i = 0; i < 4; i++) {
    /* Hold Servo */
    if (i == 0) {
      cServo[i] = map(cIR[i], 0, 1024, 5, 90);
    }
    else {
      cServo[i] = map(cIR[i], 0, 1024, 5, 175);
    }
    Serial.print(cServo[i]);
    Serial.print(",");
  }
  Serial.println();
}




void runServo() {
  mapServo();
  for (int i = 0; i < 4; i++) {
    if (cIR[i] != 0) {
      if (cServo[i] > lServo[i]) {
        servo[i].write(lServo[i] + 1);
        delay(10);
      }
      else if (cServo[i] < lServo[i]) {
        servo[i].write(lServo[i] - 1);
        delay(10);
      }
    }
  }
  updateServo();
}

void updateServo() {
  for (int i = 0; i < 2; i++) {
    lServo[i] = cServo[i];
  }
}

void readIR() {
  for (int j = 0; j < 4; j++) {
    adc[j] = 0;
  }
  for (int i = 0; i < 20; i++) {
    for (int k = 0; k < 4; k++) {
      adc[k] += analogRead(adcPins[k]) / 20;

    }
  }

  for (int x = 0; x < 4; x++) {
    cIR[x] = adc[x];
  }
  /* Send IR values to Serial Monitor*/
  for (int i = 0; i < 4; i++) {
    Serial.print(adc[i]);
    Serial.print(",");
  }
  Serial.println();
}


void readServo() {
  int servoStatus[4];
  Serial.print("Servo Read : ");
  for (int i = 0; i < 4; i++) {
    servoStatus[i] = servo[i].read();
    Serial.print(servoStatus[i]);
    Serial.print(",");
  }
  Serial.println();
}
