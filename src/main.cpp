#include <Wire.h>
#include <SSD1306Wire.h> // Inclure la bibliothèque SSD1306Wire

// Initialisation de l'écran OLED
SSD1306Wire display(0x3C, D2, D1); // Adresse I2C, SDA, SCL

// Variables pour l'animation
int xPosition = 0;   // Position X initiale
int direction = 1;   // Direction de déplacement (1 = droite, -1 = gauche)
const int yPosition = 22; // Position Y fixe pour le texte

void setup() {
  // Initialisation du port série pour le débogage
  Serial.begin(115200);
  Serial.println("Initialisation de l'écran OLED...");

  // Initialisation de l'écran
  display.init();
  display.clear();
  display.flipScreenVertically(); // Optionnel : inverser l'écran si nécessaire

  // Configuration de la police
  display.setFont(ArialMT_Plain_16); // Police de taille 16
}

void loop() {
  // Effacer l'écran
  display.clear();

  // Dessiner le texte "Hello" à la position actuelle
  display.setTextAlignment(TEXT_ALIGN_LEFT); // Aligner à gauche
  display.drawString(xPosition, yPosition, "Hello");

  // Mettre à jour l'écran pour afficher le texte
  display.display();

  // Mettre à jour la position X
  xPosition += direction;

  // Inverser la direction si le texte atteint les bords de l'écran
  if (xPosition <= 0 || xPosition >= 128 - 50) { // 128 est la largeur de l'écran, 50 est la largeur approximative de "Hello"
    direction *= -1; // Inverser la direction
  }

  // Ajouter un petit délai pour ralentir l'animation
  delay(30);
}
