#include <LWiFi.h>
#include "MCS.h"

char _lwifi_ssid[] = "Big";
char _lwifi_pass[] = "00000001";
MCSDevice mcs("DdE29yUT", "22T5qiRVb5UwsTjW");

MCSDisplayInteger  Temp("Temp");

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

  mcs.addChannel(Temp);
  pinMode(17,INPUT);
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

  int sensor = analogRead(17);
  
  Temp.set(sensor);
  Serial.println("Add sensor value.");
  Serial.println(sensor);
  delay(200);
}
