#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define Red_Pin 13 // 1s
#define Yellow_Pin 12 // 2s
#define Green_Pin 11 // 3s

// bool Red_State = LOW;

// unsigned long Red_Prev_Millis = 0;
// const unsigned long Red_Interval = 1000;

// bool Yellow_State = LOW;

// unsigned long Yellow_Prev_Millis = 0;
// const unsigned long Yellow_Interval = 2000;

void RedLedControllerTask(void *pvParameters);
void YellowLedControllerTask(void *pvParameters);
void GreenLedControllerTask(void *pvParameters);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  xTaskCreate(RedLedControllerTask, "Red Led Task", 128, NULL, 1, NULL);
  xTaskCreate(YellowLedControllerTask, "Yellow Led Task", 128, NULL, 1, NULL);
  xTaskCreate(GreenLedControllerTask, "Green Led Task", 128, NULL, 1, NULL);
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(Red_Pin, digitalRead(Red_Pin)^1);
  // delay(1000);
  // digitalWrite(Yellow_Pin, digitalRead(Yellow_Pin)^1);
  // delay(2000);
}

void RedLedControllerTask(void *pvParameters){
  pinMode(Red_Pin,OUTPUT);

  while(1){
    digitalWrite(Red_Pin, digitalRead(Red_Pin)^1);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.println("Red Task");
  }
}
void YellowLedControllerTask(void *pvParameters){
  pinMode(Yellow_Pin,OUTPUT);

  while(1){
    digitalWrite(Yellow_Pin, digitalRead(Yellow_Pin)^1);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    Serial.println("Yellow Task");
  }
}
void GreenLedControllerTask(void *pvParameters){
  pinMode(Green_Pin,OUTPUT);

  while(1){
    digitalWrite(Green_Pin, digitalRead(Green_Pin)^1);
    vTaskDelay(3000/portTICK_PERIOD_MS);
    Serial.println("Green Task");
  }
}