// 匯入程式庫標頭檔 
#include <OneWire.h>
#include <DallasTemperature.h>

#define FAN_SPEED_LEVEL1 10
#define FAN_SPEED_LEVEL2 128
#define FAN_SPEED_LEVEL3 254

// pin 12 is 1-Wire device, temperature sensor is connected in here
#define ONE_WIRE_BUS 12
int PWM_PIN = 3;
float temp_val = 0;


// 運用程式庫建立物件
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void)
{
  Serial.begin(9600);
  // PWM pin number is 3
  pinMode(PWM_PIN, OUTPUT);
  // Serial.println("Temperature Sensor");
  // init. temperature sensor
  sensors.begin();
}

void loop(void)
{
  // request sensor 
  sensors.requestTemperatures();
  // read 1-Wire device 0 value (should temperature sensor) 
  temp_val = sensors.getTempCByIndex(0);
  Serial.println(temp_val);

  if (temp_val < 33)
  {
    set_fan_speed(FAN_SPEED_LEVEL1);
    Serial.println("fan speed is low");
  }
  else if (temp_val >= 33 && temp_val <= 40)
  {
    set_fan_speed(FAN_SPEED_LEVEL2);
    Serial.println("fan speed is med");
  }
  else
  {
    set_fan_speed(FAN_SPEED_LEVEL3);
    Serial.println("fan speed is high");
  }

  delay(1000);
}

void set_fan_speed(int speed)
{
  //analogWrite(PWM_PIN, speed);
  
  static int prv_speed = 0;
  if (prv_speed != speed)
  {
    analogWrite(PWM_PIN, speed);
    prv_speed = speed;
    Serial.print("***renew fan speed to: ");
    Serial.println(speed);
  }

}
