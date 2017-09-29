#include <SoftwareServo.h>

/**
 * Exemple de code pour la bibliothèque VirtualWire – Serveur d'envoi de tableau de valeurs
 */

#include <VirtualWire.h>

SoftwareServo aileDroite;  
SoftwareServo aileGauche;
SoftwareServo empenage;
int servoAileDroite;
int servoAileGauche;
int servoEmpenage;
int moteurs;

void setup() {
  Serial.begin(9600);
  aileDroite.attach(6);  // attaches the servo on pin 9 to the servo object
  aileGauche.attach(5);  // attaches the servo on pin 9 to the servo object
  empenage.attach(2);  // attaches the servo on pin 9 to the servo object
  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
  vw_rx_start(); // On peut maintenant recevoir des messages

  Serial.println("Go !"); 
}

void loop() {
  int valeur;
  byte taille_message = sizeof(int);

  // On attend de recevoir un message
  vw_wait_rx();

  if (vw_get_message((byte *) &valeur, &taille_message)) {
    // On copie le message, qu'il soit corrompu ou non

    Serial.println(valeur); // Affiche le message

    if(aucuneErreur(valeur)) // si pas d'erreurs
    {
      servoAileDroite = (valeur % 100 ) - 18;
      servoAileGauche = (((valeur %10000) - (valeur %100)) / 100) - 18;
      servoEmpenage = ((valeur % 1000000) /10000 ) - 18;
      moteurs = valeur/1000000;

      aileDroite.write(servoAileDroite+90); // offset de 90° pour eviter les angles negatifs
      aileGauche.write(servoAileGauche+90); // offset de 90° pour eviter les angles negatifs
      empenage.write(servoEmpenage+90); // offset de 90° pour eviter les angles negatifs
    }
    
  }
}

bool aucuneErreur(int message)
{
  int receptionServoAileDroite = (message % 100 ) - 18;
  int receptionServoAileGauche = (((message %10000) - (message %100)) / 100) - 18;
  int receptionServoEmpenage = ((message % 1000000) /10000 ) - 18;
  int receptionMoteurs = message/1000000;

  if ((receptionServoAileDroite < -18 || receptionServoAileDroite > 18) || 
  (receptionServoAileGauche < -18 || receptionServoAileGauche > 18) || 
  (receptionServoEmpenage < -18 || receptionServoEmpenage > 18) || 
  (receptionMoteurs < 0 || receptionMoteurs > 2000 )) // erreurs
  {
    return false;
  }
  else
  {
    return true;
  }
}

