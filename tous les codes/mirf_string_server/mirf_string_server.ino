/**
 * Exemple de code pour la bibliothèque Mirf – Serveur d'envoi de texte
 */
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

#define TAILLE 4
 
long temps;
long compteur(0);
long ancienEtatCompteur(compteur);

void setup() {
  Serial.begin(9600);

  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = TAILLE; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf01"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf02"); // Adresse de réception

  Serial.println("Go !"); 
  temps = millis();
}

void loop() {
  byte message[TAILLE];

  if(Mirf.dataReady()){
    Mirf.getData(message); // Réception du paquet
    //Serial.println((char*) message); // Affiche le message
    //Serial.println("Got Message"); 
    
    compteur += 1;
  }
  

  if((millis() - temps) > 1000)
        {
            Serial.println(compteur -ancienEtatCompteur); 
            ancienEtatCompteur = compteur;
            temps = millis(); //on stocke la nouvelle heure
        }
}
