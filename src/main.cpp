#include <Wire.h>
#include <SSD1306Wire.h>  // Pour l'écran OLED
#include <ESP8266WiFi.h>  // Pour le Wi-Fi
#include "config.h"       // Inclure le fichier de configuration

// Initialisation de l'écran OLED
SSD1306Wire display(0x3C, D2, D1); // Adresse I2C, SDA, SCL

WiFiClient client;

// Fonction pour la connexion Wi-Fi
void connectToWiFi() {
  Serial.println("Connexion au Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Attente de connexion
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnecté au Wi-Fi !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

// Fonction pour afficher un message avec un balayage horizontal
void scrollText(String message, int y, int delayTime) {
  int messageWidth = message.length() * 8; // Largeur approximative du message (chaque caractère ~8px)
  int screenWidth = 128; // Largeur de l'écran OLED

  for (int x = screenWidth; x >= -messageWidth; x--) {
    display.clear(); // Efface l'écran
    display.drawString(x, y, message); // Dessine le texte à la position x
    display.display(); // Met à jour l'écran
    delay(delayTime); // Attente pour créer l'animation
  }
}

void setup() {
  // Initialisation du port série
  Serial.begin(115200);

  // Initialisation de l'écran OLED
  display.init();
  display.clear();
  display.flipScreenVertically(); // Optionnel
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  // Afficher un message initial
  display.drawString(0, 22, "Connexion WiFi...");
  display.display();

  // Connexion au Wi-Fi
  connectToWiFi();

  // Afficher l'état Wi-Fi sur l'écran
  display.clear();
  display.drawString(0, 22, "WiFi Connecte!");
  display.display();
  delay(1000);
}

void loop() {
  // Premier message avec balayage
  scrollText("WiFi Connecte !", 0, 30); // Texte à balayer à y=0 avec un délai de 50 ms

  // Adresse IP avec balayage
  String ipMessage = "Adresse IP : " + WiFi.localIP().toString();
  scrollText(ipMessage, 22, 30); // Texte à balayer à y=22 avec un délai de 50 ms

  // Pause avant de recommencer
  delay(1000);
}
