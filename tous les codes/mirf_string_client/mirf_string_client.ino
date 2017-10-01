/**
 * Exemple de code pour la bibliothèque Mirf – Client d'envoi de texte
 */
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

#define TAILLE 12

void setup() {
  Serial.begin(9600);
   
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = TAILLE; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf01"); // Adresse de réception
   
  Serial.println("Go !"); 
}

long compteur = 100000000000;
void loop() {
  compteur = compteur + 1;
  byte message[TAILLE];
  String mot("");
  mot = (String) compteur;
  for (int i(0) ; i<mot.length() ; i++)
  {
      message[i] = (byte) mot[i];
  }

  int len = mot.length();
  // Lit un message de maximum 32 caractères depuis le port série
  //int len = Serial.readBytesUntil('\n', (char*) message, TAILLE);
  Serial.println(len);
  if (!len) {
    return; // Pas de message
  }
  message[len] = '\0'; // Ferme la chaine de caractères
  
  Mirf.send(message); // On envoi le message
  while(Mirf.isSending()); // On attend la fin de l
}
