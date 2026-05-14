#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PZEM004Tv30.h>

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ================= PZEM =================
// RX2 = GPIO16
// TX2 = GPIO17

HardwareSerial pzemSerial(2);
PZEM004Tv30 pzem(pzemSerial, 16, 17);

void setup() {

  Serial.begin(115200);

  // ================= OLED =================
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED gagal");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);

  // ================= UART PZEM =================
  pzemSerial.begin(9600, SERIAL_8N1, 16, 17);

  // Tampilan awal
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("PZEM OK");
  display.display();

  delay(2000);
}

void loop() {

  // ================= BACA DATA =================
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power   = pzem.power();
  float energy  = pzem.energy();

  // ================= SERIAL MONITOR =================
  Serial.println("===== DATA PZEM =====");

  Serial.print("Tegangan : ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("Arus     : ");
  Serial.print(current);
  Serial.println(" A");

  Serial.print("Daya     : ");
  Serial.print(power);
  Serial.println(" W");

  Serial.print("Energi   : ");
  Serial.print(energy);
  Serial.println(" kWh");

  Serial.println("=====================");
  Serial.println();

  // ================= OLED =================
  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0,0);
  display.print("Volt : ");
  display.print(voltage);
  display.println(" V");

  display.setCursor(0,16);
  display.print("Arus : ");
  display.print(current);
  display.println(" A");

  display.setCursor(0,32);
  display.print("Daya : ");
  display.print(power);
  display.println(" W");

  display.setCursor(0,48);
  display.print("Ener : ");
  display.print(energy);
  display.println(" kWh");

  display.display();

  delay(2000);
}