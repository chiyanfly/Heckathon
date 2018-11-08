#include "CurieTimerOne.h"



#define ROTARY_ANGLE_SENSOR A0

 
#define TEMPS_D_OBSERVATION 600 // 10 minutes en secondes

const int uneSecondeEnMicroSec  = 1000000;

int nombre_d_ouverture;
int secondes;
bool etat_haut = false;


void setup()

{

    Serial.begin(9600);
    pinMode(ROTARY_ANGLE_SENSOR, INPUT);
 
    CurieTimerOne.start(uneSecondeEnMicroSec, &AddSeconde);

    nombre_d_ouverture = 0;
    secondes = 0;
    



}



void loop()

{   
    
    
    if(analogRead(ROTARY_ANGLE_SENSOR) > 100 && etat_haut == false )
    { 
      nombre_d_ouverture ++;
      etat_haut = true;
    }
    if(analogRead(ROTARY_ANGLE_SENSOR) == 0)
    {
      
      etat_haut = false;
    }
    

    delayMicroseconds(100);

    
    
    
    

}

void AddSeconde(){
  
  secondes ++;
  
  if(secondes == TEMPS_D_OBSERVATION ){
      
      nombre_d_ouverture = 0;
      secondes = 0;
      //Envoie LoRa
  }
}

