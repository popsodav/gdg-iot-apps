#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "gdg-iot-demo-app.firebaseio.com"
#define WIFI_SSID "AndroidAP"
#define WIFI_PASSWORD "q1w2e3r4"

#define RELAY_PIN 5
bool pinState = false;

void setup() {
  Serial.begin(115200);

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

  Firebase.begin(FIREBASE_HOST);
  Firebase.stream("/switch/" + WiFi.macAddress());

  pinMode(RELAY_PIN, OUTPUT);
}


void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }

  if (Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    eventType.toLowerCase();

    Serial.print("event: ");
    Serial.println(eventType);
    if (eventType == "put") {
      pinState = event.getBool("data");

      Serial.print("path: ");
      Serial.print(event.getString("path"));
      Serial.print(", data: ");
      Serial.println(pinState);
    }
  }

  digitalWrite(RELAY_PIN, !pinState);
}
