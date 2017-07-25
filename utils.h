void connectWIFI() {
  WiFi.config(ip, gateway, subnet, dns);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
}

// Prototype
typedef void (*Function) ();
void promesa(String url, JsonObject& json, Function next);

// Servicio http
void promesa(String url, JsonObject& json, Function next) {
  // Instancia cliente
  HTTPClient http;

  // Request
  http.begin(url);
  http.addHeader("Authorization", String("token ") + api_user_token);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Cache-Control", "no-cache");
  json.printTo(json_stringify);
  Debug.println(json_stringify);

  // Enviar json!
  int httpCode = http.POST(json_stringify);

  // Response
  if (httpCode == 200) {

    // Manejo de next() para ejecutar callback
    response = http.getString();
    http.end();
    next();
    return;

  } else if (httpCode == 403) {

    Debug.println("Token expirado!");
    logged = false;
    http.end();
    return;
  }

  Debug.println("Error server ->");
  Debug.println(http.getString());
  http.end();
}

// Callback Guardar Temperatura y Humedad Relativa
void Save() {
  // Cazar Objeto JSON
  JsonObject& sensor = jsonBuffer.parseObject(response);
  sensor_saved_id = sensor["sensor"]["_id"];

  // Si falla
  if (!sensor.success()) {
    Debug.printf("Falló la decodificación");
    sensor.printTo(Debug);
    return;
  }

  // Registro del Sensor Guardado!
  Debug.print("ID de Registro -> ");
  Debug.println(sensor_saved_id);

  // Dormir
  // Debug.println("A dormir 5 segundos ...");
  // ESP.deepSleep(_5_SEGUNDOS);
}

// Callback Obtener Token
void Auth() {
  // Cazar Objeto JSON
  JsonObject& user = jsonBuffer.parseObject(response);
  api_user_token = user["token"];

  // Si falla
  if (!user.success()) {
    Debug.printf("Fallo la decodificacion");
    user.printTo(Debug);
    return;
  }
  
  // Token!
  Debug.print("Token -> ");
  Debug.println(api_user_token);
  logged = true;
}
