#include <Arduino.h>
#include <ESC.h>

int max_value = 1600; //change this if your ESC's max value is different or leave it be
int min_value = 1400; //change this if your ESC's min value is different or leave it be
int arm_value = 1500;
int speed = arm_value -100;
#define control_pin 4
ESC myESC(control_pin, min_value, max_value, arm_value);

int brightness = 0; // how bright the LED is
int fadeAmount = 5; // how many points to fade the LED by
void setup()
{
  // put your setup code here, to run once:
  //In Setup, let´s do the calibration, before we enter loop.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(control_pin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Starting....");
  while (!Serial.available())
  {
    Serial.println("Connect the battery and press a button.");
  }
  Serial.println("Calibrating...");
  myESC.calib();
  Serial.println("Calib done, stopping..");
  myESC.stop();
  digitalWrite(2, HIGH);
  pinMode(control_pin, OUTPUT);
  delay(1000);
  Serial.println("Arming!");
  myESC.arm();
}
bool golow = false;
bool LED = 0;
void loop()
{
  if (speed == max_value)
  {
    golow = true;
  }
  else if (speed == min_value)
  {
    golow = false;
  }
  if (golow)
  {
    speed-=50;
  }
  else
  {
    speed+=50;
  }
  LED = !LED;
  Serial.println(speed);
  myESC.speed(speed);
  digitalWrite(2, LED);
  delay(2000);
}