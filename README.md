# gdg-iot-apps

## Настройка окружения
1. Установите Arduino IDE: http://www.arduino.cc/en/main/software
2. Зайдите в меню File -> Preferences
3. Введите в поле Additional Boards Manager URL адрес: http://arduino.esp8266.com/stable/package_esp8266com_index.json
4. Зайдите в меню Tools -> Boards -> Boards manager
5. В поиске введите esp8266
6. Установите последнюю версию библиотек

## Необходимые библиотеки
* Adafruit Sensor: https://github.com/adafruit/Adafruit_Sensor
* Adafruit DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
* Adafruit DHT Unified: https://github.com/adafruit/Adafruit_DHT_Unified (можно установить через Library manager)
* Firebase Arduino: https://github.com/googlesamples/firebase-arduino

## Данные для проекта Firebase
ID:  gdg-iot-demo-app

```C
#define FIREBASE_HOST "gdg-iot-demo-app.firebaseio.com"
#define FIREBASE_AUTH "ut8LWhCawBW8tE7nTARkBZHbudcGcU1GPQtVxbB-"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "KEY"
```

## Распиновка NodeMCU
![NodeMCU](https://raw.githubusercontent.com/nodemcu/nodemcu-devkit-v1.0/master/Documents/NODEMCU_DEVKIT_V1.0_PINMAP.png)

## Подключение датчика DHT11
![NodeMCUDHT](http://www.seeedstudio.com/recipe/img/recipe/2015-05/5555de22a4b2a.jpg)
