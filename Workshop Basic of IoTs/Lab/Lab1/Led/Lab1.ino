#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


char auth[] = "YourAuthToken";
char ssid[] = "CEIT-IoT";
char pass[] = "12345678";
//blynk

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

}

void loop() {
      Blynk.run();
}
