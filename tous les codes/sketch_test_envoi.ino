/**
 * Exemple de code pour la bibliothèque VirtualWire – Client d'envoi de variable
 */
 
#include <VirtualWire.h>

void setup() {
  Serial.begin(9600);

  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
  
  Serial.println("Go !"); 
}
 
void loop() {
  
  // Lit un nombre depuis le port série
  float valeur = Serial.parseFloat();
  
  vw_send((byte *) &valeur, sizeof(valeur)); // On envoie le message
  vw_wait_tx(); // On attend la fin de l'envoi
  Serial.print("valeur envoyée : ");
  Serial.print(valeur);
  Serial.println("      ");
  delay(2000);
}
