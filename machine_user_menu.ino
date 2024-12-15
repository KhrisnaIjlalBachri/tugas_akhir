// WiFi
#include <WiFi.h>
#include <HTTPClient.h>
#include <EEPROM.h>

const char* ssid = "@wifi.id";              // Ubah nama WiFi
const char* password = "sakarepmu";        // Ubah password WiFi
String serverName = "http://172.20.10.13/websiteprojekalat/";

// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// // Servo
// #include <ESP32Servo.h>
// const int pin_servo = 12;
// Servo servo;

// HX711
#include <HX711_ADC.h>
#define DO 13
#define SCK 14
float calibration = 0.0;
float weight = 0.0;
char value[20];
const int calVal_eepromAdress = 0;
HX711_ADC LoadCell(DO, SCK);

// RFID
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 5
#define RST_PIN 4
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Tombol pin
const int BTN_UP = 33;
const int BTN_DOWN = 25;
const int BTN_ENTER = 32;
const int BTN_BACK = 27;

// Set batas berat maksimal timbangan
const int gram_maks = 2500;

// Deklarasi
float gram = 0;
int halaman = 1;
String serverPath, payload;
int httpResponseCode, payload_int;

// Modbus
#include <ModbusRTUSlave.h>
#define MODBUS_SLAVE_ID 1  // ID dari slave Modbus
const byte dePin = 2;
ModbusRTUSlave modbusSlave(Serial2, dePin);
uint16_t inputRegisters[1];
uint8_t servoval = 0;

void modbus();

void setup() {
  // Serial
  Serial.begin(115200);

  // WiFi
  WiFi.begin(ssid, password);
  Serial.println("Menyambungkan");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nBerhasil Tersambung!");

  // HX711
  EEPROM.begin(512);
  EEPROM.get(calVal_eepromAdress, calibration);
  delay(500);
  LoadCell.begin();
  LoadCell.start(2000);
  LoadCell.setCalFactor(calibration);

  // RFID
  SPI.begin();
  mfrc522.PCD_Init();

  // Set pin tombol sebagai input pull-up
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_ENTER, INPUT_PULLUP);
  pinMode(BTN_BACK, INPUT_PULLUP);

  // Servo
  // servo.attach(pin_servo, 500, 2400);
  servoval = 0;

  // Modbus
  modbusSlave.configureInputRegisters(inputRegisters, 1);
  modbusSlave.begin(MODBUS_SLAVE_ID, 9600, SERIAL_8N1);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("By Khrisna");
  lcd.setCursor(2, 1);
  lcd.print("2123640004");
  delay(4000);
  lcd.clear();
}

void loop() {
  // Modbus
  modbus();

  // Cek Koneksi WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WIFI TERPUTUS");
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("WIFI TERPUTUS");
    lcd.setCursor(1, 1);
    lcd.print("MOHON PERIKSA");
    delay(1000);
    lcd.clear();
  }

  // Baca HX711
  LoadCell.update();
  weight = LoadCell.getData();
  sprintf(value, "%.1f", weight);
  Serial.println("Sent: " + String(value) + " gram");
  delay(50);

  // Baca RFID
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Tampilkan UID kartu
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      if (mfrc522.uid.uidByte[i] < 0x10) {
        uid.concat("0");  // Tambahkan 0 di depan jika kurang dari 0x10
      }
      uid.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    uid.toUpperCase();  // Ubah huruf menjadi kapital
    Serial.println("UID dari kartu KTP:");
    Serial.println(uid);

    if (halaman == 1) {
      // Server
      serverPath = serverName + "fc_cek_uid.php?uid=" + String(uid);
      Serial.print("Serial Path: ");
      Serial.println(serverPath);

      HTTPClient http;
      http.begin(serverPath.c_str());
      httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.print("Respon: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
        payload_int = payload.toInt();
        Serial.println(payload_int);

        if (payload_int == 1) {  // Terdaftar
          lcd.clear();
          halaman = 2;
        } else if (payload_int == 2) {  // Sudah Ambil
          lcd.clear();
          halaman = 2;
        } else if (payload_int == 0) {  // Tidak Terdaftar
          lcd.clear();
          halaman = 3;
        }
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
  }

  switch (halaman) {
    case 1:  // Standby
      lcd.setCursor(2, 0);
      lcd.print("SILAHKAN TAP");
      lcd.setCursor(4, 1);
      lcd.print("KTP ANDA");
      break;

    case 2:  // KTP Terdaftar
      lcd.setCursor(6, 0);
      lcd.print("KTP");
      lcd.setCursor(3, 1);
      lcd.print("TERDAFTAR");
      delay(2000);
      lcd.clear();
      halaman = 5;
      break;

    case 3:  // KTP Tidak Terdaftar
      lcd.setCursor(3, 0);
      lcd.print("KTP TIDAK");
      lcd.setCursor(3, 1);
      lcd.print("TERDAFTAR");
      delay(2000);
      lcd.clear();
      halaman = 1;
      break;

    case 5:  // Proses Pengisian
      lcd.setCursor(4, 0);
      lcd.print("PROSES");
      lcd.setCursor(3, 1);
      lcd.print("PENGISIAN");
      lcd.setCursor(5, 2);
      lcd.print(String(value) + " gram");

      if (weight <= gram_maks) {
        servoval = 1;
      } else if (weight >= gram_maks) {
        servoval = 0;
        Serial.println("Pengisian Selesai");
        halaman = 6;
      }
      Serial.println(servoval);
      break;

    case 6:  // Selesai
      lcd.setCursor(4, 0);
      lcd.print("SELESAI");
      lcd.setCursor(2, 1);
      lcd.print("TERIMAKASIH");
      servoval = 0;
      delay(2000);
      lcd.clear();
      halaman = 1;
      break;

    case 7:  // Sudah Mengambil
      lcd.setCursor(5, 0);
      lcd.print("SUDAH");
      lcd.setCursor(4, 1);
      lcd.print("DIAMBIL");
      delay(2000);
      lcd.clear();
      halaman = 1;
      break;
  }
}

void modbus() {
  inputRegisters[0] = servoval;
  modbusSlave.poll();
}
