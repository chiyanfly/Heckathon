#include <rn2xx3.h>
#include "SoftwareSerial.h"
#include "TimerOne.h"



#define ROTARY_ANGLE_SENSOR A0
 
#define TEMPS_D_OBSERVATION 60 // 1 minute en secondes

#define RESET_LORA_PIN 12

/* Déclaration */
const long uneSecondeEnMicroSec  = 1000000;
const char *appEui = "0004A30B002139AC";
const char *appKey = "00000000000000000000000000002018";



int nombre_d_ouverture;
int secondes;

bool etat_haut = false;


SoftwareSerial mySerial(11,10);
rn2xx3 myLora(mySerial);


void setup()

{

  
    while(!Serial){}
  
    
    Serial.begin(57600);
    mySerial.begin(9600);
    pinMode(ROTARY_ANGLE_SENSOR, INPUT);
    pinMode(RESET_LORA_PIN, OUTPUT);
 
    nombre_d_ouverture = 0;
    secondes = 0;
    Serial.println("Test");
    initialize_radio();
    Serial.println("Init OK ! ");


    delay(2000);
    Timer1.initialize(uneSecondeEnMicroSec);
    Timer1.attachInterrupt(addSeconde);
    Timer1.start();
    

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

void addSeconde(){
  
  secondes ++;
  if(secondes == TEMPS_D_OBSERVATION ){
      //Envoie LoRa par LoRa
      myLora.tx(String(nombre_d_ouverture));
      nombre_d_ouverture = 0;
      secondes = 0;
     
  }
}


void initialize_radio(){

  digitalWrite(RESET_LORA_PIN, LOW);
  delay(500);
  digitalWrite(RESET_LORA_PIN, HIGH);

  delay(100); //wait for the RN2xx3's startup message
  mySerial.flush();
  

  myLora.autobaud();

  bool join_result = false;
  /*
   * OTAA: initOTAA(String AppEUI, String AppKey);
   * If you are using OTAA, paste the example code from the TTN console here:
   */
  const char *appEui = "0004A30B002139AC";
  const char *appKey = "00000000000000000000000000002018";

  join_result = myLora.initOTAA(appEui, appKey);


  while(!join_result)
  {
    Serial.println("Unable to join. Are your keys correct, and do you have TTN coverage?");
    delay(60000); //delay a minute before retry
    join_result = myLora.init();
  }
  Serial.println("Successfully joined TTN");

}
  


