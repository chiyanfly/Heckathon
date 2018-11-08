#include "CurieTimerOne.h"



#define ROTARY_ANGLE_SENSOR A0

#define SORTIE A1;


#define ADC_REF 5 //reference voltage of ADC is 5v.If the Vcc switch on the seeeduino

                    //board switches to 3V3, the ADC_REF should be 3.3


#define FULL_ANGLE 300 //full value of the rotary angle is 300 degrees

#define GROVE_VCC 5 //VCC of the grove interface is normally 5v

 
#define TEMPS_D_OBSERVATION 600 // En seconde

const int uneSecondeEnMicroSec  = 2000000;

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
  Serial.print("Bonjour depuis l'interruption :");
  secondes ++;
  Serial.println(secondes);
  if(secondes == 5 ){
      Serial.print("ça fait 10 secondes, on a eu ");
      Serial.println(nombre_d_ouverture);
      nombre_d_ouverture = 0;
      secondes = 0;
  }
}

