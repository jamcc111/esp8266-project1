#include <Wire.h>
#include <DHT.h>//温湿度
#include "Adafruit_SGP30.h"//SGP30空气检测

//*********DHT11*********//
#define DHTTYPE DHT11 //定义类型，DHT11
#define DHTPIN 2//定义D4的TXD1输入数据
DHT dht(DHTPIN, DHTTYPE);

Adafruit_SGP30 sgp;//SDA---D2和SLC-----D1

void setup() {
  Serial.begin(115200);               // 启动串口通讯

  dht.begin(); //DHT开始工作
  if (! sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
}
  void loop() {
float h = dht.readHumidity();//读湿度
 float t = dht.readTemperature();//读温度，默认为摄氏度
  Serial.print("Humidity: ");//湿度
  Serial.print(h);
  Serial.println(" %");
  Serial.print("Temperature: ");//温度
  Serial.print(t);
  Serial.println(" ℃ ");

  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }
  Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.println(" ppb\t");
  Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");
  Serial.println(); 

 delay(2000);//每2s打印
}