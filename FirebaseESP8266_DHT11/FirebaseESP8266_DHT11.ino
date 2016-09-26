#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT11

// Set these to run example.
#define FIREBASE_HOST "gdg-iot-demo-app.firebaseio.com"
#define FIREBASE_AUTH "*"
#define WIFI_SSID "*"
#define WIFI_PASSWORD "*"

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  Serial.begin(115200);

  // Init DHT
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void updateData() {
  bool okToSend = true;

  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& jsonResult = jsonBuffer.createObject();

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
    okToSend = false;
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");

    jsonResult["temperature"] = event.temperature;
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
    okToSend = false;
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");

    jsonResult["humidity"] = event.relative_humidity;
  }

  if (okToSend) {
    Firebase.set("sensors/" + WiFi.macAddress(), jsonResult);
    // handle error
    if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());
      return;
    }
  }
}

void loop() {
  delay(delayMS);
  updateData();
}
