#include "Function.h"

#define TemperatureThreshold 36.5
float Temperature = 0;
bool flag = false;
void setup() {
  Serial.begin(9600);
  initial_GY960();
  initial_sensor();
  inital_IC7447();
  inital_handle();
}

void loop() {
  Serial.println(is_head_sensor());
  if (is_head_sensor()){
    while (!digitalRead(PinButtonHand));
    Temperature = body_temperature();
    unsigned long long start = millis();
    while(millis() - start <= 3000) {
      if (body_temperature() > Temperature){
        Temperature = body_temperature();
      }
      if (Temperature > TemperatureThreshold){
        warning("ON");
      } 
      display_IC7447(Temperature);
      digitalWrite(PinLedHead, LOW);
      if (!digitalRead(PinButtonHand)){
        while (!digitalRead(PinButtonHand));
        hand_washing("ON");
        delay(3000);
      }
      if (is_hand_sensor() && !flag){
        flag = true;
        hand_washing("ON");
        delay(1000);
      }
    }
    digitalWrite(PinLedHead, HIGH);
    warning("OFF");
    hand_washing("OFF");
    Temperature = 0;
  }
  if (!digitalRead(PinButtonHand)){
    while (!digitalRead(PinButtonHand));
    hand_washing("ON");
    delay(1000);
    hand_washing("OFF");
  }
  if (is_hand_sensor() && !flag){
    flag = true;
    hand_washing("ON");
    delay(1000);
    hand_washing("OFF");
  } else if (!is_hand_sensor() && flag) {
    flag = false;
  }
  Serial.println(flag);
}
