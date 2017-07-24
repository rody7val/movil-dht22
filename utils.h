void connectWIFI() {
  WiFi.config(ip, gateway, subnet, dns);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
}
