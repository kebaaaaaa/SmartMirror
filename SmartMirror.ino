#include "DHT.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define DHTPIN 2     

const int trigPin = 9;  
const int echoPin = 10;

#define time 7 

float duration, distance;

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  //Serial.println(F("DHTxx test!"));

  dht.begin();

  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  
  pinMode(time, OUTPUT);
  digitalWrite(time, LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
}

void loop() {

  delay(1000);
  
  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration*.0343)/2; 
  
  if(distance < 30) 
    {
      digitalWrite(time, HIGH);
      delay(30000);
    }
     else digitalWrite(time, LOW);

  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed 
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  lcd.setCursor(12, 0);  
  lcd.print(t);
  lcd.setCursor(10, 1); 
  lcd.print(h);
  lcd.setCursor(15, 1);  
  lcd.print('%');
  
}
