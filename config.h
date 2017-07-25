// Ayudas de tiempo
long _5_SEGUNDOS = 5 * 1000;
unsigned long previousMillis = 0;

// WiFi config
IPAddress ip(192, 168, 43, 4);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 43, 1);
IPAddress dns(192, 168, 43, 1);
const char * ssid = "TU-LOCAL-SSID-WIFI";
const char * password = "TU-LOCAL-PASSWORD-WIFI";

// Node.js api server
const String api_protocol = "http"; // o https
const String api_host = "TU-API-HOST";
const String api_port = "TU-API-PORT";
const String api_path_login = "/PATH/A/TU/API/LOGIN";
const String api_path_newSensor = "/PATH/A/TU/API/SENSOR/SAVE";

// user api:
const String api_user_email = "TU@EMAIL-USER.API";
const String api_user_pass = "TU-API-USER-PASSWORD";

// Dinamic
const char * api_user_token;
const char * sensor_saved_id;
String response;
String json_stringify;
bool logged = false;

// Sector
const String placa_name = "ESP_1";
const String sector = "DHT_MOVIL";
const String prefix = "M01";
const int placa_pin_dht22 = 2;

// Sensores
float t;
float h;
int vcc;