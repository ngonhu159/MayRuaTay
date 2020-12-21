#include "Function.h"

/*---------------------------------------------- GY 960 -------------------------------------------*/
Adafruit_MLX90614 gy960 = Adafruit_MLX90614();

int PinIC7447[4] = {2, 3, 4, 5};
int PinLedIC7447[4] = {9, 8, 7, 6};

void initial_GY960() {
  gy960.begin();
}

float body_temperature() {
  return gy960.readObjectTempC();
}

void initial_sensor() {
  pinMode(PinSignalHead, INPUT);
  pinMode(PinSignalHand, INPUT);
}

bool is_head_sensor() {
  if (!digitalRead(PinSignalHead)) {
    unsigned long long start = millis();
    while (millis() - start <= 1500) {
      if (digitalRead(PinSignalHead)) {
        return false;
      }
    }
    return true;
  } else return false;
}

bool is_hand_sensor() {
  if (!digitalRead(PinSignalHand)) {
    unsigned long long start = millis();
    while (millis() - start <= 1500) {
      if (digitalRead(PinSignalHand)) {
        return false;
      }
    }
    return true;
  } else return false;
}

void inital_IC7447() {
  for (int implement = 0; implement < 4; implement++) {
    pinMode(PinIC7447[implement], OUTPUT);
    digitalWrite(PinIC7447[implement], LOW);
    pinMode(PinLedIC7447[implement], OUTPUT);
    digitalWrite(PinLedIC7447[implement], LOW);
  }
  pinMode(PinLedHead, OUTPUT);
  digitalWrite(PinLedHead, HIGH);
  pinMode(PinH, OUTPUT);
  digitalWrite(PinLedHead, HIGH);
}

void display_IC7447(float val) {
  int temporary = val * 100;
  int load_ic7447[4] = {0, 0, 0, 0};
  int number[4] = {0, 0 , 0, 0};
  number[3] = temporary / 1000;
  number[2] = (temporary % 1000) / 100;
  number[1] = (temporary % 100) / 10;
  number[0] = temporary % 10;
  Serial.println((String)number[3] + "  " + (String)number[2] + "  " + (String)number[1] + "  " + (String)number[0]);
  for (int implement = 0; implement < 4; implement++) {
    switch (number[implement]) {
      case 0:
        load_ic7447[3] = 0; load_ic7447[2] = 0; load_ic7447[1] = 0; load_ic7447[0] = 0;
        break;
      case 1:
        load_ic7447[3] = 0; load_ic7447[2] = 0; load_ic7447[1] = 0; load_ic7447[0] = 1;
        break;
      case 2:
        load_ic7447[3] = 0; load_ic7447[2] = 0; load_ic7447[1] = 1; load_ic7447[0] = 0;
        break;
      case 3:
        load_ic7447[3] = 0; load_ic7447[2] = 0; load_ic7447[1] = 1; load_ic7447[0] = 1;
        break;
      case 4:
        load_ic7447[3] = 0; load_ic7447[2] = 1; load_ic7447[1] = 0; load_ic7447[0] = 0;
        break;
      case 5:
        load_ic7447[3] = 0; load_ic7447[2] = 1; load_ic7447[1] = 0; load_ic7447[0] = 1;
        break;
      case 6:
        load_ic7447[3] = 0; load_ic7447[2] = 1; load_ic7447[1] = 1; load_ic7447[0] = 0;
        break;
      case 7:
        load_ic7447[3] = 0; load_ic7447[2] = 1; load_ic7447[1] = 1; load_ic7447[0] = 1;
        break;
      case 8:
        load_ic7447[3] = 1; load_ic7447[2] = 0; load_ic7447[1] = 0; load_ic7447[0] = 0;
        break;
      case 9:
        load_ic7447[3] = 1; load_ic7447[2] = 0; load_ic7447[1] = 0; load_ic7447[0] = 1;
        break;
      default:
        load_ic7447[3] = 0; load_ic7447[2] = 0; load_ic7447[1] = 0; load_ic7447[0] = 0;
        break;
    }
 
    for (int imp = 0; imp < 4; imp++) {
      digitalWrite(PinIC7447[imp], load_ic7447[imp]);
    }
    if (implement == 1) {
      digitalWrite(PinH, LOW);
    } else digitalWrite(PinH, HIGH);
    if (implement == 0) {
      digitalWrite(PinLedIC7447[implement + 3], LOW);
      digitalWrite(PinLedIC7447[implement], HIGH);
    } else {
      digitalWrite(PinLedIC7447[implement - 1], LOW);
      digitalWrite(PinLedIC7447[implement], HIGH);
    }
    delay(5);
    if (implement == 3) {
      digitalWrite(PinLedIC7447[implement], LOW);
    }
  }
}

void inital_handle(){
  pinMode(PinRelay, OUTPUT);
  pinMode(PinBuzzer, OUTPUT);
}

void hand_washing(String state){
  if (state == "ON"){
    digitalWrite(PinRelay, HIGH);
  } else if (state == "OFF"){
    digitalWrite(PinRelay, LOW);
  }
}

void warning(String state){
  if (state == "ON"){
    digitalWrite(PinBuzzer, HIGH);
  } else if (state == "OFF"){
    digitalWrite(PinBuzzer, LOW);
  }
}
