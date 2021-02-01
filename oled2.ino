#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ESP8266WiFi.h"
#include "font.h"
WiFiClient client;

char buffer[20];                
char bufrssi[4];                
char* ssid     = "Wifi";      
char* password = "clave";
bool Connecte = false;          
bool affiche = false;           


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_ADDR 0x3C   // Address may be different for your module, also try with 0x3D if this doesn't work

// Declaration for an SSD1306 display connected to I2C (SDA d2, SCL pins d1)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Heap: "); Serial.println(system_get_free_heap_size());
  Serial.print("Boot Vers: "); Serial.println(system_get_boot_version());
  Serial.print("CPU: "); Serial.println(system_get_cpu_freq());
  Serial.println();
  Serial.println("Init OLED...");
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();           // Required to clear display
  display.display();
  
  display.setTextColor(WHITE);
  display.setTextSize(1);           // Set text size
  display.print("Hola mundo!...");

  display.setTextSize(2);
  display.setCursor(0, 15);         // Set cursor
  display.print("Hello"); 
  display.setCursor(1, 32);
  display.print("World!");


  display.display();                // Always required when changes are made and when you have to display them

}
void Connexion()                   
{
  affiche = false;
  if (WiFi.status() != WL_CONNECTED) {
     WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) {  
         Serial.print(".");
         delay(1000);
     }
  }
}

void loop() {
  Serial.println("Connected");
  Connexion();
  if (!client.connected()) {
    
    if (!affiche) { 
        affiche = true;
        
        IPAddress ip = WiFi.localIP();   
        String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
        ipStr.toCharArray(buffer, 20);

        long rssi = WiFi.RSSI();
        String strRssi;
        strRssi=String(rssi);
        strRssi.toCharArray(bufrssi,4);
        Serial.println(rssi);
        display.clearDisplay();
        display.display();
        display.setTextColor(WHITE);
        display.setTextSize(1);         // Set text size
        display.setCursor(0, 0);        // Set cursor
        display.print(ssid);
        display.setCursor(0, 15);       // Set cursor
        display.print(bufrssi); 
        display.setCursor(0, 32);
        display.print(buffer);
        display.display();
    }
  } 
   delay(1000);   
}
