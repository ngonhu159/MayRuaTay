#ifndef __Function__H_
#define __Function__H_
#include <Wire.h>
#include <Adafruit_MLX90614.h>
 
#define PinH A6
#define PinLedHead 13
#define PinButtonHead A1
#define PinButtonHand A2
#define PinSignalHead 11
#define PinSignalHand 10
#define PinRelay 12
#define PinBuzzer A3

void initial_GY960();
float body_temperature();

/*---------------------------------------------- Sensor -------------------------------------------*/
void initial_sensor();
bool is_head_sensor();
bool is_hand_sensor();

/*---------------------------------------------- Display -------------------------------------------*/
void inital_IC7447();
void display_IC7447(float val);

/*---------------------------------------------- Display -------------------------------------------*/
void inital_handle();
void warning(String state);
void hand_washing(String state);


#endif
