// ESP8266 core
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Depuración remota sobre telnet
#include <RemoteDebug.h>
RemoteDebug Debug;

// Configuraciones y utilidades
#include "config.h"
#include "utils.h"

// Dependencias para Sensor DHT22
#include <DHT.h>
#define DHTTYPE DHT22
DHT dht(placa_pin_dht22, DHTTYPE);

void setup() {
  Serial.begin(115200);
  connectWIFI();

  Debug.begin(placa_name);
  Debug.setResetCmdEnabled(true);

  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  Debug.handle();

  if (currentMillis - previousMillis > _5_SEGUNDOS) {
    previousMillis = currentMillis;
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Debug.println("Fail!");
      return;
    }

    Debug.print("Humedad -> ");
    Debug.println(h);
    Debug.print("Temperatura -> ");
    Debug.println(t);
  }
}
