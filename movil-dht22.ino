// ESP8266 core
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// JSON encoder/decoder
#include <ArduinoJson.h>
DynamicJsonBuffer jsonBuffer;

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
    
    vcc = ESP.getVcc();
    h = dht.readHumidity();
    t = dht.readTemperature();
    if (isnan(h) || isnan(t)) { Debug.println("Fail!"); return; }
    
    Debug.print("Temperatura -> "); Debug.print(t);
    Debug.print(", Humedad -> "); Debug.println(h);

    String url;
    JsonObject& json = jsonBuffer.createObject();
    json_stringify = "";
    
    // Middleware controler
    if (!logged) {
      // JSON user, ej:
      // {"email":"MI@EMAIL.COM","password":"PASSWORD"}
      json["email"] = api_user_email;
      json["password"] = api_user_pass;
      
      // Obtener Token
      url = api_protocol + "://" + api_host + ":" + api_port + api_path_login;
      promesa(url, json, Auth);
      return;
    }

    // JSON sensor, ej:
    // {"temp":[18.3],"hr":[54.6],"prefix":["PREFIX_NAME"],"placa":"PLACA_NAME", ... }
    json["placa"] = placa_name;
    json["sector"] = sector;
    json["pin"] = placa_pin_dht22;
    json["vcc"] = vcc;
    JsonArray& temp = json.createNestedArray("temp");
    JsonArray& hr = json.createNestedArray("hr");
    JsonArray& pr = json.createNestedArray("prefix");
    temp.add(t); hr.add(h); pr.add(prefix);

    // Guardar Temperatura y Humedad
    url = api_protocol + "://" + api_host + ":" + api_port + api_path_newSensor;
    promesa(url, json, Save);
  }
}
