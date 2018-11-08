#define ROTARY_ANGLE_SENSOR A0


#define ADC_REF 5 //reference voltage of ADC is 5v.If the Vcc switch on the seeeduino

                    //board switches to 3V3, the ADC_REF should be 3.3


#define FULL_ANGLE 300 //full value of the rotary angle is 300 degrees



void setup()

{

    Serial.begin(9600);
    pinMode(ROTARY_ANGLE_SENSOR, INPUT);
  
}



void loop()

{   

    float voltage;
    int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
    voltage = (float)sensor_value*ADC_REF/1023;
    float degrees = (voltage*FULL_ANGLE)/GROVE_VCC;
    Serial.println("The angle between the mark and the starting position:");
    Serial.println(degrees);



    delay(500);

}
