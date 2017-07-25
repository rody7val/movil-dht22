# movil-dht22

Registrador móvil de temperatura y humedad relativa con sensor DHT22 en una placa ESP8266

### Requerimientos:

 * [IDE de Arduino](https://www.arduino.cc/en/Main/Software).
 * [ESP8266 package](https://github.com/esp8266/Arduino).
 * [ArduinoJson](https://github.com/bblanchon/ArduinoJson).
 * [RemoteDebug](https://github.com/JoaoLopesF/ESP8266-RemoteDebug-Telnet).
 * [DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library).
 * Telnet para el reporte de mensajes
   * Para activar telnet en Windows presiona las teclas *WIN+R* y ejecuta el siguiente comando:
      ```
      pkgmgr /iu:TelnetClient
      ```
   * Reiniciar.
   * Una vez conectada la placa esp8266 a una red wifi utilizar telnet para visualizar los mensajes en consola, por ejemplo:
      ```
        telnet 192.168.0.101
      ```

