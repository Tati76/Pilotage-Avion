// ************* La Radio *************
#include <SPI.h>
#include <RF24.h> // voir http://tmrh20.github.io/RF24/
#include <Servo.h>



// Variables pour les angles des ailettes
#define ANGLE_MAX_AILETTE_AILE_GAUCHE 60
#define ANGLE_MIN_AILETTE_AILE_GAUCHE -60
#define ANGLE_MAX_AILETTE_AILE_DROITE 60
#define ANGLE_MIN_AILETTE_AILE_DROITE -60
#define ANGLE_MAX_AIDE_DECOLLAGE 30
#define ANGLE_MAX_LACET 50 //R1 | L1
#define ANGLE_MIN_LACET -50 //R1 | L1
#define ANGLE_MAX_ROULIS 50 // angle vertical joystick
#define ANGLE_MIN_ROULIS -50 // angle vertical joystick
#define ACC_MAX_MOTEUR 2000
#define ACC_MIN_MOTEUR 1050
#define ANGLE_MAX_TRAIN_ATTERISSAGE 180
#define ANGLE_MIN_TRAIN_ATTERISSAGE 0



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

typedef struct{
  uint8_t Acc; //moteur
  uint8_t LUn; // servoEmpLacet 
  uint8_t RUn; // servoEmpLacet 
  uint8_t XRoulis; // servoAileGauche et servoAileDroite
  uint8_t YRoulis; // servoAileGauche et servoAileDroite
  bool trainAtterissage; // si train d'atterissage alors aide à l'atterissage/decollage
  
} Donnees;

unsigned long temps;


Servo servoEmpLacet;
Servo servoAileDroite;
Servo servoAileGauche;
Servo servoAideDecollageGauche;
Servo servoAideDecollageDroite;
Servo moteur;
Servo servoRoulis; // angle vertical joystick
Servo trainAtterissage;

// ----------------------------------------------------------------------------------------
// envoi d'un octet vers l'autre radio
// ----------------------------------------------------------------------------------------
long compteur(0);
/*void envoyerMessage(uint8_t nombre)
{
  radio.stopListening();   // On arrête d'écouter pour qu'on puisse émettre

  if (!radio.write( &nombre, sizeof(nombre) )) {
    Serial.println(F("erreur d'envoi"));
  }
  radio.startListening(); // On se remet en mode écoute
}*/



// ----------------------------------------------------------------------------------------
// vérifie si on a reçu une commande de la part de l'autre radio (1 octet)
// ----------------------------------------------------------------------------------------
Donnees ecouterRadio()
{
  Donnees message; // 0 = pas de commande

  if ( radio.available()) {
    while (radio.available()) {
      radio.read( &message, sizeof(Donnees) );  // on lit l'octet reçu (si plusieurs messages on ne conserve que le dernier)
    }
  /*Serial.print("[");
	Serial.print(message.Acc);
  Serial.print(",");
  Serial.print(message.LUn);
  Serial.print(",");
  Serial.print(message.RUn);
  Serial.print(",");
  Serial.print(message.XRoulis);
  Serial.print(",");
  Serial.print(message.YRoulis);
  Serial.print(",");
  Serial.print(message.trainAtterissage);
  Serial.print(",");
  Serial.println("]");*/
  
    //SERVO ANGLE LACET
	if (message.LUn == 0 && message.RUn == 255 )
	{
		servoEmpLacet.write(90+ANGLE_MAX_LACET); 
	}
	else if (message.LUn == 255 && message.RUn == 0 )
	{
		servoEmpLacet.write(90+ANGLE_MIN_LACET);
	}
	else 
	{
		servoEmpLacet.write(90); 
	}
  
	
	//SERVO AILE DROITE
	  servoAileDroite.write(map(255-message.XRoulis, 0, 255, ANGLE_MIN_AILETTE_AILE_DROITE + 90, ANGLE_MAX_AILETTE_AILE_DROITE + 90)); 
	
	//SERVO AILE GAUCHE
    servoAileGauche.write(map(255-message.XRoulis, 0, 255, ANGLE_MIN_AILETTE_AILE_GAUCHE + 90, ANGLE_MAX_AILETTE_AILE_GAUCHE + 90)); 
	
	//MOTEUR
    moteur.write(map(message.Acc, 0, 255, ACC_MIN_MOTEUR, ACC_MAX_MOTEUR)); 
	
	//SERVO ROULIS angle vertical joystick
    servoRoulis.write(map(message.YRoulis, 0, 255, ANGLE_MIN_ROULIS+90, ANGLE_MAX_ROULIS+90)); 
	
	//Train d'atterissage
	if (message.trainAtterissage)
	{
		trainAtterissage.write(ANGLE_MAX_TRAIN_ATTERISSAGE); // ON ABAISSE LE TRAIN D'ATTERISSAGE
		servoAideDecollageGauche.write(60 + ANGLE_MAX_AIDE_DECOLLAGE); // ON ABAISSE LES VOLETS POUR AUGMENTER LA PORTANCE
		servoAideDecollageDroite.write(60 - ANGLE_MAX_AIDE_DECOLLAGE);
	}
	else
	{
		trainAtterissage.write(ANGLE_MIN_TRAIN_ATTERISSAGE); // ON REMONTE LE TRAIN D'ATTERISSAGE
		servoAideDecollageGauche.write(60); // ON REMONTE LES VOLETS POUR AUGMENTER LA PORTANCE 
		servoAideDecollageDroite.write(60);
	}
    
    
	temps = millis();
	
  }
  return message;
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------
// ------------------------------------------------------------------


void arretUrgence()
{
	miseAZeroMoteurEtServos();
}


void miseAZeroMoteurEtServos() {
	
	servoEmpLacet.write(90); 	
	servoAileDroite.write(90); 	
	servoAileGauche.write(90); 	
	servoAideDecollageGauche.write(90); 
	servoAideDecollageDroite.write(90);     
	moteur.write(0); 	
	servoRoulis.write(90); 	
	trainAtterissage.write(0); 
	
}

void setup() {


  Serial.begin(115200);
  
  // PIN POUR LES SERVOS ET LES MOTEURS
  servoEmpLacet.attach(2);
  servoAileDroite.attach(A2);
  servoAileGauche.attach(A5);
  servoAideDecollageGauche.attach(A4);
  servoAideDecollageDroite.attach(A3);
  moteur.attach(9);
  servoRoulis.attach(A0);
  trainAtterissage.attach(A1);

  // INITIALISATION DES MODULES nrf24l01+
  role =  1 ;
  Serial.print(F("\nMon Role = ")); Serial.println(role);

  // CONFIGURATION DE LA RADIO
  radio.begin();
  // pour le test on règle le niveau d'énergie à RF24_PA_LOW pour éviter les interférences
  // mettre à RF24_PA_MAX si on veut la puissance d'émission max
  radio.setPALevel(RF24_PA_MIN);
  //radio.setDataRate(RF24_250KBPS);
  // On ouvre un pipe de lecture et un d'écriture avec des noms opposés en fonction du rôle
  // comme ça un parle sur "pipe0" et l'autre écoute sur "pipe0"
  // et l'autre parle sur "pipe1" tandisque Le premier écoute sur "pipe1"
  radio.openWritingPipe(adresses[role]); // role doit être 0 ou 1
  radio.openReadingPipe(1, adresses[1 - role]); // 1 - role = l'autre adresse
  // Start the radio listening for data
  radio.startListening();

  // INITIALISATION DU COMPTEUR DE TEMPS
  temps = millis();
  moteur.writeMicroseconds(ACC_MIN_MOTEUR);
  delay(4000);
}

// ------------------------------------------------------------------


void loop() {
    ecouterRadio();
      
    if ((millis()-temps) > 3000)
    {
		arretUrgence();
		Serial.println("AU");
      /*Serial.println(compteur);
      compteur = 0;
      temps = millis();*/
    }
}
