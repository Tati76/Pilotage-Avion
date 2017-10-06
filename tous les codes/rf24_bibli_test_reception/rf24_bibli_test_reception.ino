// ************* La Radio *************
#include <SPI.h>
#include <RF24.h> // voir http://tmrh20.github.io/RF24/

// Configurer vos radio nRF24L01+ sur le bus SPI et mettre  CE sur D7 et CSN sur D8
RF24 radio(7, 8);

// Le nom des "pipes" de communication, un en lecture, un en écriture
const byte adresses[][6] = {"0pipe", "1pipe"}; // Pipes 1-5 should share the same address, except the first byte. Only the first byte in the array should be unique

// A CONFIGURER sur la pin A0
// si A0 est à GND alors rôle = 0 --> le premier Arduino
// si A0 est à  3.3V ou 5V alors rôle = 1 --> pour le second
const byte configurationPin = A0;
uint8_t role;

// *************  Deux Leds avec résitances de limiation de courant *************
const byte pinLed0 = 9;
const byte pinLed1 = 10;


// ----------------------------------------------------------------------------------------
// envoi d'un octet vers l'autre radio
// ----------------------------------------------------------------------------------------
long compteur(0);
void envoyerMessage(uint8_t nombre)
{
  radio.stopListening();   // On arrête d'écouter pour qu'on puisse émettre

  if (!radio.write( &nombre, sizeof(nombre) )) {
    Serial.println(F("erreur d'envoi"));
  }
  radio.startListening(); // On se remet en mode écoute
}

// ----------------------------------------------------------------------------------------
// vérifie si on a reçu une commande de la part de l'autre radio (1 octet)
// ----------------------------------------------------------------------------------------
uint8_t ecouterRadio()
{
  uint8_t message; // 0 = pas de commande

  if ( radio.available()) {
    while (radio.available()) {
      radio.read( &message, sizeof(message) );  // on lit l'octet reçu (si plusieurs messages on ne conserve que le dernier)
    }
    //Serial.print(F("J'ai recu "));   Serial.println(message);
    compteur++;
  }
  return message;
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------
// ------------------------------------------------------------------

long temps;

void setup() {


  Serial.begin(115200);

  role =  1 ;
  Serial.print(F("\nMon Role = ")); Serial.println(role);

  // On configure la radio
  radio.begin();
  // pour le test on règle le niveau d'énergie à RF24_PA_LOW pour éviter les interférences
  // mettre à RF24_PA_MAX si on veut la puissance d'émission max
  radio.setPALevel(RF24_PA_LOW);

  // On ouvre un pipe de lecture et un d'écriture avec des noms opposés en fonction du rôle
  // comme ça un parle sur "pipe0" et l'autre écoute sur "pipe0"
  // et l'autre parle sur "pipe1" tandisque Le premier écoute sur "pipe1"

  radio.openWritingPipe(adresses[role]); // role doit être 0 ou 1
  radio.openReadingPipe(1, adresses[1 - role]); // 1 - role = l'autre adresse

  // Start the radio listening for data
  radio.startListening();

  temps = millis();
}

// ------------------------------------------------------------------


void loop() {
    ecouterRadio();

    if ((millis()-temps) > 1000)
    {
      Serial.println(compteur);
      compteur = 0;
      temps = millis();
    }
}
