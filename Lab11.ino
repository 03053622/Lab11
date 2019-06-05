#include <LWiFi.h>
#include "MCS.h"

char _lwifi_ssid[] = "Big";
char _lwifi_pass[] = "00000001";
MCSDevice mcs("DdE29yUT", "22T5qiRVb5UwsTjW");

MCSControllerOnOff led("LED");
MCSDisplayOnOff remote("LED1");

void setup()
{
  Serial.begin(9600);

  Serial.println("Connect to Wifi");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    Serial.println("Wifi Reconnecting..");
    delay(1000);
  }

  Serial.println("Connect to MCS...");
  while (!mcs.connected()) {
    Serial.println("MCS Reconnecting..");
    mcs.connect();
  }
  Serial.println("MCS Connected!");
  mcs.addChannel(led);
  mcs.addChannel(remote);

  pinMode(7, OUTPUT);

}


void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) {
      Serial.println("MCS Reconnect");
    }
  }
  mcs.process(1000);
while(!led.valid())
{
    Serial.println("read LED value from MCS...");
    led.value();
}
Serial.print("done, LED value = ");
Serial.println(led.value());  
digitalWrite(7, led.value() ? HIGH : LOW);
if(!remote.set(led.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(remote.value());
    }

  if (led.value() == 1) {
    digitalWrite(7, HIGH);

  } else {
    digitalWrite(7, LOW);

  }

  delay(200);
}
