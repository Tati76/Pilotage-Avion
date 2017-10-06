/*
 Example sketch for the PS4 USB library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

/*#include <PS4USB.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif*/

#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

#define TAILLE 4

//USB Usb;
//PS4USB PS4(&Usb);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

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




  /*// INIT Manette
  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif
  if (Usb.Init() == -1) {
    Serial.println(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.println(F("\r\nPS4 USB Library Started"));*/

}



void loop() {
 
  //Usb.Task();
  
  //if (PS4.connected()) {
  
    // ACCELERATEUR
    //valeurAccelerateurs = PS4.getAnalogButton(R2) ;
   
    

    String motATransmettre("1234\0");
    byte message[TAILLE];
    int len = motATransmettre.length();
    
    for (int i(0) ; i<4; i++)
    {
        message[i] = motATransmettre[i];
    }
    
    
    
    message[len] = '\0'; // Ferme la chaine de caractères
    
    Mirf.send(message); // On envoie le message
    while(Mirf.isSending());// On attend la fin de l'envoi
    /*{
      Serial.println("Bloqué");
      //delay(100);
    }*/
    
  //}

}

