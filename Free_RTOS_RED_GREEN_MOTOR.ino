#include <Arduino_FreeRTOS.h>
#include <Servo.h>
Servo ServoMotor;

#define RED    6
#define GREEN 7
int servoPin = 8;

typedef int TaskProfiler;

TaskProfiler  RedLEDProfiler;
TaskProfiler  GreenLEDProfiler;

const TickType_t _10ms = pdMS_TO_TICKS(10);
const TickType_t _150ms = pdMS_TO_TICKS(150);
const TickType_t _500ms = pdMS_TO_TICKS(500);
const TickType_t _1000ms = pdMS_TO_TICKS(1000);

void setup()
{
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,
              "Red LED Task",
              100,
              NULL,
              1,
              NULL
             );
  xTaskCreate(greenLedControllerTask,
              "Green LED Task",
              100,
              NULL,
              1,
              NULL);
  xTaskCreate(ServoMotorControllerTask,
              "Servo Motor Task",
              100,
              NULL,
              1,
              NULL
             );
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED, OUTPUT);

  while (1)
  {
    // Serial.println("This is RED");
    digitalWrite(RED, HIGH);
    vTaskDelay(_500ms);
    digitalWrite(RED, LOW);
    vTaskDelay(_500ms);
  }
}

void greenLedControllerTask(void *pvParameters)
{
  pinMode(GREEN, OUTPUT);
  while (1)
  {
    digitalWrite(GREEN, HIGH);
    vTaskDelay(_1000ms);
    digitalWrite(GREEN, LOW);
    vTaskDelay(_1000ms);
    //  Serial.print("This is GREEN");
  }
}

void ServoMotorControllerTask(void *pvParameters)
{ 
  int angle = 10;
  ServoMotor.attach(servoPin);
  ServoMotor.write(angle);
  
  while (1)
  {
    // scan from 0 to 170 degrees
    for (angle = 10; angle < 170; angle++)
    {
      ServoMotor.write(angle);
      vTaskDelay(_150ms);
    }
    // now scan back from 170 to 10 degrees
    for (angle = 170; angle > 10; angle--)
    {
      ServoMotor.write(angle);
      vTaskDelay(_150ms);
    }
   
  }
}

void loop()
{}
