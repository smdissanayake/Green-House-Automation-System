#define BLYNK_TEMPLATE_ID "TMPL691GFT2Fk"  // Replace with your Template ID
#define BLYNK_TEMPLATE_NAME "Smart Greenhouse"  // Replace with your Template Name
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi Credentials
const char* ssid = "Dialog 4G 068";         // Replace with your WiFi SSID
const char* password = "997402278S"; // Replace with your WiFi Password

// Blynk Auth Token
char auth[] = "MHDQwxdC6yUbLyfIlF_lH7vN5MzDng24";  // Replace with your Blynk Auth Token

// Sensor & Actuator Pin Definitions
#define DHTPIN 4          // DHT Sensor Pin
#define DHTTYPE DHT11     // DHT Sensor Type (DHT11 or DHT22)
#define SOIL_PIN 34       // Soil Moisture Sensor (Analog)
#define MOTOR_PIN 26      // Motor Relay
#define PIR_PIN 5         // PIR Motion Sensor Pin
#define FAN_PIN 27        // Fan Relay Pin
#define LDR_PIN 35        // LDR Sensor Pin (Analog)
#define BULB_PIN 25       // Bulb Relay Pin

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BULB_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(BULB_PIN, LOW);
  dht.begin();
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("📡 Connecting to WiFi");
  int timeout_counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    timeout_counter++;
    if (timeout_counter > 10) {
      Serial.println("\n❌ WiFi Connection Failed! Restarting...");
      ESP.restart();
    }
  }
  Serial.println("\n✅ WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Connect to Blynk
  Serial.println("🔗 Connecting to Blynk...");
  Blynk.begin(auth, ssid, password);
}

void loop() {
  Blynk.run();
  readSensors();
  delay(3000);
}

void readSensors() {
  int soilMoisture = analogRead(SOIL_PIN);
  Serial.print("🌱 Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.print(" / 4095  -> ");  
  Blynk.virtualWrite(V2, soilMoisture); // Send soil moisture data to Blynk (V2)
  
  if (soilMoisture > 2500) {
    digitalWrite(MOTOR_PIN, LOW);
    Serial.println("🚰 Motor OFF (Soil Dry)");
  } else {
    digitalWrite(MOTOR_PIN, HIGH);
    Serial.println("✅ Motor ON (Soil Wet)");
  }
  
  int motionState = digitalRead(PIR_PIN);
  if (motionState == HIGH) {
    Serial.println("🚶 Motion Detected!");
    Blynk.virtualWrite(V5, "🚨 Motion Detected!"); // Send motion alert to Blynk (V5)
  } else {
    Serial.println("🚫 No Motion.");
    Blynk.virtualWrite(V5, "✅ No Motion");
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h)  isnan(t)) {
    Serial.println("❌ DHT Sensor Read Error! Retrying...");
    return;
  }

  Serial.print("💧 Humidity: ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("🌡 Temperature: ");
  Serial.print(t);
  Serial.println("°C");

  Blynk.virtualWrite(V0, h); // Send humidity data to Blynk (V0)
  Blynk.virtualWrite(V1, t); // Send temperature data to Blynk (V1)

  if (t > 30.0  h > 70.0) {
    digitalWrite(FAN_PIN, HIGH);
    Serial.println("🌀 Fan ON (High Temp/Humidity)");
  } else {
    digitalWrite(FAN_PIN, LOW);
    Serial.println("🛑 Fan OFF (Normal Conditions)");
  }

  int ldrValue = analogRead(LDR_PIN);
  Serial.print("🔆 LDR Value: ");
  Serial.println(ldrValue);
  Blynk.virtualWrite(V10, ldrValue); // Send LDR data to Blynk (V10)

  if (ldrValue < 2000) {
    digitalWrite(BULB_PIN, HIGH);
    Serial.println("💡 Bulb ON (Low Light)");
  } else {
    digitalWrite(BULB_PIN, LOW);
    Serial.println("💡 Bulb OFF (Sufficient Light)");
  }
}
