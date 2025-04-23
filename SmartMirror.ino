#include "DHT.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define DHTPIN 2     

const int trigPin = 9;  
const int echoPin = 10;

#define time 7 

float duration, distance;

#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  dht.begin();

  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  
  pinMode(time, OUTPUT);
  digitalWrite(time, LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
}

void loop() {
  
  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration*.0343)/2; 
  
  if(distance < 70) 
    {
      digitalWrite(time, HIGH);
    }
     else digitalWrite(time, LOW);

  float h = dht.readHumidity();

  float t = dht.readTemperature();
 
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
 
  float hic = dht.computeHeatIndex(t, h, false);
  
  lcd.setCursor(12, 0);  
  lcd.print(t);
  lcd.setCursor(10, 1); 
  lcd.print(h);
  lcd.setCursor(15, 1);  
  lcd.print('%');
  delay(5000);
}
