#define BLYNK_TEMPLATE_ID "TMPL3RO-XTxyY"
#define BLYNK_TEMPLATE_NAME "BATTERY"
#define BLYNK_AUTH_TOKEN "90V_JQMUEymEiRCqmvz3SjSeRP_NKAgU"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// -------------------- Hardware Setup --------------------
#define RELAY_PIN 25
#define BUZZER_PIN 4
#define FAULT_BTN 27
#define OVERRIDE_BTN 14

// 4 potentiometers simulate 4 battery cells
int cellPins[4] = {34, 35, 32, 33};

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------------------- Blynk Setup --------------------
char auth[] = "90V_JQMUEymEiRCqmvz3SjSeRP_NKAgU";
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// -------------------- State Variables --------------------
float cellVolt[4];
float avgVolt = 0;
float imbalance = 0;
int weakestCell = 0, strongestCell = 0;

enum BatteryState { HEALTHY, MINOR_IMBALANCE, CRITICAL_IMBALANCE, PACK_FAILURE };
BatteryState battState = HEALTHY;

enum RuntimeMode { NORMAL, DEGRADED, FAILSAFE, SHUTDOWN };
RuntimeMode runMode = NORMAL;

unsigned long lastLCDUpdate = 0;
unsigned long lastSafetyCheck = 0;
unsigned long lastTelemetry = 0;

// -------------------- Functions --------------------

// 1. Adaptive Multi-Cell Battery Intelligence Engine
void readCells() {
  avgVolt = 0;
  float minV = 100, maxV = 0;
  for (int i = 0; i < 4; i++) {
    cellVolt[i] = analogRead(cellPins[i]) * (3.3 / 4095.0) * 2; // scale for divider
    avgVolt += cellVolt[i];
    if (cellVolt[i] < minV) { minV = cellVolt[i]; weakestCell = i; }
    if (cellVolt[i] > maxV) { maxV = cellVolt[i]; strongestCell = i; }
  }
  avgVolt /= 4;
  imbalance = ((maxV - minV) / avgVolt) * 100;

  if (imbalance < 5) battState = HEALTHY;
  else if (imbalance < 10) battState = MINOR_IMBALANCE;
  else if (imbalance < 20) battState = CRITICAL_IMBALANCE;
  else battState = PACK_FAILURE;
}

// 2. Event-Driven Safety Protection Kernel
void safetyKernel() {
  if (millis() - lastSafetyCheck > 200) {
    lastSafetyCheck = millis();

    if (battState == PACK_FAILURE || avgVolt < 3.0) {
      digitalWrite(RELAY_PIN, LOW); // cutoff
      tone(BUZZER_PIN, 1000, 200);
      runMode = FAILSAFE;
    } else {
      digitalWrite(RELAY_PIN, HIGH);
      noTone(BUZZER_PIN);
      runMode = NORMAL;
    }
  }
}

// 3. Intelligent Embedded HMI & Diagnostic Interface
void updateLCD() {
  if (millis() - lastLCDUpdate > 1000) {
    lastLCDUpdate = millis();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Avg:");
    lcd.print(avgVolt,2);
    lcd.print("V Imb:");
    lcd.print(imbalance,1);

    lcd.setCursor(0,1);
    switch(battState) {
      case HEALTHY: lcd.print("Healthy"); break;
      case MINOR_IMBALANCE: lcd.print("Minor Imb"); break;
      case CRITICAL_IMBALANCE: lcd.print("Critical"); break;
      case PACK_FAILURE: lcd.print("Pack Fail"); break;
    }
  }
}

// 4. Fault-Tolerant Embedded Runtime System
void runtimeCheck() {
  for (int i=0; i<4; i++) {
    if (cellVolt[i] < 0.1) runMode = DEGRADED;
  }
  // Add more fault checks here
}

// 5. Intelligent Cloud Telemetry Architecture
void telemetry() {
  if (millis() - lastTelemetry > 5000) {
    lastTelemetry = millis();

    Serial.print("AVG_VOLTAGE -> ");
    Serial.println(avgVolt);
    Blynk.virtualWrite(V1, avgVolt);

    Serial.print("IMBALANCE -> ");
     Serial.println(imbalance);
    Blynk.virtualWrite(V2, imbalance);

    Serial.print("PACK_STATUS -> ");
    switch(battState) {
      case HEALTHY: Serial.println("Healthy"); break;
      case MINOR_IMBALANCE: Serial.println("Minor Imbalance"); break;
      case CRITICAL_IMBALANCE: Serial.println("Critical Imbalance"); break;
      case PACK_FAILURE: Serial.println("Pack Failure"); break;
    }
    Blynk.virtualWrite(V3, battState);
  }
}

// -------------------- Setup --------------------
void setup() {
  Serial.begin(115200);
  Serial.println();
  lcd.init(); lcd.backlight();
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FAULT_BTN, INPUT_PULLUP);
  pinMode(OVERRIDE_BTN, INPUT_PULLUP);

  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);
}

// -------------------- Loop --------------------
void loop() {
  Blynk.run();
  readCells();
  safetyKernel();
  runtimeCheck();
  updateLCD();
  telemetry();

Blynk.virtualWrite(V1, avgVolt);
    Blynk.virtualWrite(V2, imbalance);
    Blynk.virtualWrite(V3, battState);
}     