#include <DHT.h>


#define DHT11_PIN 7
#define DTTYPE DHT11

DHT dht(DHT11_PIN, DTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int temp = dht.readTemperature(true);
  int humidity = dht.readHumidity();

  if (isnan(temp) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Temperature = ");
  Serial.println(temp);

  Serial.print("Humidity = ");
  Serial.println(humidity);

  delay(5000);
}
