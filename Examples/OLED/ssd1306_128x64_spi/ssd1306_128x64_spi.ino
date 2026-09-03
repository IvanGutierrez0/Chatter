#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LoRa.h>


// Incluye la fuente personalizada
#include <Fonts/Picopixel_custom.h> 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// --- CONFIGURACIÓN DE PINES SPI PARA ESP32 ---
#define OLED_MOSI   13  // Pin D1 / MOSI / SDA
#define OLED_CLK    14  // Pin D0 / SCK / SCLK
#define OLED_DC     27  // Pin DC / A0
#define OLED_CS     15  // Pin CS
#define OLED_RESET  26  // Pin RES / RST


int counter = 0;


// Constructor para SPI Hardware
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// Mapeo Hexadecimal de Iconos
enum CustomIcons {
  // Batería
  ICON_BAT_FULL = 0x7F,
  ICON_BAT_MID_FULL = 0x80,
  ICON_BAT_MID_EMPT = 0x81,
  ICON_BAT_EMPT = 0x82,
  ICON_NET_MAX = 0x83,
  ICON_NET_MID = 0x84,
  ICON_NET_MIN = 0x85
};

void setup() {
  Serial.begin(115200);

  LoRa.setPins(5, 21, 2);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("Error al iniciar pantalla OLED SPI SSD1306"));
    for(;;);
  }

  display.setFont(&Picopixel_custom);
  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(true);

  // --- PRUEBA 1: Muestra de Iconos ---
  display.clearDisplay();

  display.setCursor(0, 6);

  display.write(ICON_BAT_FULL);
  display.write(ICON_BAT_MID_FULL);
  display.write(ICON_BAT_MID_EMPT);
  display.write(ICON_BAT_EMPT);
  display.write(ICON_NET_MAX);
  display.write(ICON_NET_MID);
  display.write(ICON_NET_MIN);
  display.display();
  delay(3000);
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("qh");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(1000);
}