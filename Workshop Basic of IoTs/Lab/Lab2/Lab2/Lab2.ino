#define BLYNK_PRINT Serial 
#include <Wire.h>
#include <WiFiClient.h> 
#include <BlynkSimpleEsp32.h>  

char auth[] = "YourAuthToken";
char ssid[] = "CEIT-IoT";
char pass[] = "12345678";

#define LM73_ADDR 0x4D

double temp=0;

float readTemperature() {
  Wire1.beginTransmission(LM73_ADDR);
  Wire1.write(0x00); // Temperature Data Register
  Wire1.endTransmission();
 
  uint8_t count = Wire1.requestFrom(LM73_ADDR, 2);
  float temp = 0.0;
  if (count == 2) {
    byte buff[2];
    buff[0] = Wire1.read();
    buff[1] = Wire1.read();
    temp += (int)(buff[0]<<1);
    if (buff[1]&0b10000000) temp += 1.0;
    if (buff[1]&0b01000000) temp += 0.5;
    if (buff[1]&0b00100000) temp += 0.25;
    if (buff[0]&0b10000000) temp *= -1.0;
  }
  return temp;
}

void setup() {
  Serial.begin(9600);
  Wire1.begin(4, 5);

  Blynk.begin(auth, ssid, pass);

}

void loop() {
      Blynk.run();

      temp = readTemperature();
      Serial.print("Temp:");Serial.println(temp);

      Blynk.virtualWrite(V1, temp);
      delay(2000);

      if( temp > 28 ){
        Blynk.notify("Temperature over 28");
      }
}
