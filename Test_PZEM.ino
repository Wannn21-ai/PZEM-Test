#include <PZEM004Tv30.h>

// ========================================
// PZEM UART2 ESP32
// RX2 = GPIO16
// TX2 = GPIO17
// ========================================

HardwareSerial pzemSerial(2);
PZEM004Tv30 pzem(pzemSerial, 16, 17);

// ========================================
// Tarif listrik PLN
// ========================================

float tarifPLN = 1444.70;

void setup() {

  Serial.begin(115200);

  // Start UART2
  pzemSerial.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println();
  Serial.println("===== PZEM START =====");
}

void loop() {

  // ========================================
  // Baca data dari PZEM
  // ========================================

  float voltage = pzem.voltage();
  float current = pzem.current();
  float power   = pzem.power();
  float energy  = pzem.energy();
  float freq    = pzem.frequency();
  float pf      = pzem.pf();

  // ========================================
  // Validasi data
  // ========================================

  if (isnan(voltage)) voltage = 0;
  if (isnan(current)) current = 0;
  if (isnan(power))   power   = 0;
  if (isnan(energy))  energy  = 0;
  if (isnan(freq))    freq    = 0;
  if (isnan(pf))      pf      = 0;

  // ========================================
  // Hitung estimasi biaya
  // ========================================

  float biaya = energy * tarifPLN;

  // ========================================
  // Tampilkan data
  // ========================================

  Serial.println("========== DATA PZEM ==========");

  Serial.print("Voltage     : ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("Current     : ");
  Serial.print(current);
  Serial.println(" A");

  Serial.print("Power       : ");
  Serial.print(power);
  Serial.println(" W");

  Serial.print("Energy      : ");
  Serial.print(energy);
  Serial.println(" kWh");

  Serial.print("Frequency   : ");
  Serial.print(freq);
  Serial.println(" Hz");

  Serial.print("Power Factor: ");
  Serial.println(pf);

  Serial.print("Estimasi Rp : Rp ");
  Serial.println(biaya);

  Serial.println("================================");
  Serial.println();

  delay(2000);
}