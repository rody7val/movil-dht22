// Ayudas de tiempo
long _5_SEGUNDOS = 5 * 1000;
unsigned long previousMillis = 0;

// WiFi config
IPAddress ip(192, 168, 43, 4);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 43, 1);
IPAddress dns(192, 168, 43, 1);
const char * ssid = "new";
const char * password = "12345678";

// Sector
const String placa_name = "Placa_A";
const int placa_pin_dht22 = 2;
