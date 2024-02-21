#include "AdafruitIO_WiFi.h"
#include "config.h"
#include "DHT.h"

#define DHTPIN 14
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// set up feed
AdafruitIO_Feed *temp = io.feed("temp");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.println(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  dht.begin();

}

void loop() {

  io.run();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

  String temp_info = "Temp: " + String(temperature) + "C, Humidity: " + String(humidity) + "%, Heat index: " + String(heatIndex) + "C";

  Serial.print("sending -> ");
  Serial.println(temp_info);
  temp->save(temp_info);

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.print("°C  Heat index: ");
  Serial.print(heatIndex);
  Serial.println("°C");

  delay(3000);
}
