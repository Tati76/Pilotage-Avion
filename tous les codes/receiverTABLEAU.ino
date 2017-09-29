// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
}

void loop() {
  int valeurs[6];
  byte taille_message = sizeof(valeurs);

  /* 
   La variable "taille_message" doit impérativement être remise à 
   la taille du tableau avant de pouvoir recevoir un message. 
   Le plus simple est d'utiliser une variable locale pour ne pas
   avoir à réassigner la valeur à chaque début de loop().
   */

  // On attend de recevoir un message
  vw_wait_rx();

  if (vw_get_message((byte *) &valeurs, &taille_message)) {
    // On copie le message, qu'il soit corrompu ou non

    Serial.print("valeurs[0]=");
    Serial.println(valeurs[0]); // Affiche le message
    Serial.print("valeurs[1]=");
    Serial.println(valeurs[1]); 
    Serial.print("valeurs[2]=");
    Serial.println(valeurs[2]); 
    Serial.print("valeurs[3]=");
    Serial.println(valeurs[3]); 
    Serial.print("valeurs[4]=");
    Serial.println(valeurs[4]);
  }
}
