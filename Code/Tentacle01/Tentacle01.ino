#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

Servo servo4;
Servo servo5;
Servo servo6;

Servo servo7;
Servo servo8;
Servo servo9;

Servo servo10;
Servo servo11;
Servo servo12;

Servo servo13;
Servo servo14;
Servo servo15;

Servo servo16;
Servo servo17;
Servo servo18;

// back and front legs

float pos1;
float pos1Filtered;
float pos2;
float pos2Filtered;
float pos3;
float pos3Filtered;

float pos1a;
float pos1aFiltered;
float pos2a;
float pos2aFiltered;
float pos3a;
float pos3aFiltered;

// mid legs

float pos4;
float pos4Filtered;
float pos5;
float pos5Filtered;
float pos6;
float pos6Filtered;

float pos4a;
float pos4aFiltered;
float pos5a;
float pos5aFiltered;
float pos6a;
float pos6aFiltered;

unsigned long currentMillis;
long previousMillis = 0;    // set up timers
long interval = 10;        // time constant for timer

int stepFlag = 0;
long previousStepMillis = 0;

void setup() {

Serial.begin(115200);

servo1.attach(22);    // front right
servo2.attach(24); 
servo3.attach(26); 

servo4.attach(28);    // front left
servo5.attach(30); 
servo6.attach(32);

servo7.attach(34);    // mid left
servo8.attach(36); 
servo9.attach(38);

servo10.attach(40);    // mid right
servo11.attach(42); 
servo12.attach(44);

servo13.attach(46);    // back right
servo14.attach(48); 
servo15.attach(50);

servo16.attach(52);    // back left
servo17.attach(3); 
servo18.attach(4);

}

void loop() {

  currentMillis = millis();
  if (currentMillis - previousMillis >= 10) {  // start timed event    
      previousMillis = currentMillis;

      if (stepFlag == 0 && currentMillis - previousStepMillis > 500) {
        //position 1 - primary
        pos1 = 1650;
        pos2 = 1050;
        pos3 = 1050;
        //position 3 - opposite
        pos1a = 1650;
        pos2a = 1050;
        pos3a = 2400; 

        //position 3 - mid/opposite
        pos4 = 1250;
        pos5 = 1850;
        pos6 = 1850;

        pos4a = 1250;
        pos5a = 1850;
        pos6a = 550;

        
        stepFlag = 1;           
        previousStepMillis = currentMillis;
      }

      else if (stepFlag == 1 && currentMillis - previousStepMillis > 500) {
        //position 2 - primary
        pos1 = 1250;
        pos2 = 1850;
        pos3 = 1850;
        //position 4 - opposite
        pos1a = 1250;
        pos2a = 1850;
        pos3a = 2400;  

       //position 4 - mid/opposite
        pos4 = 1650;
        pos5 = 1050;
        pos6 = 1050; 

        pos4a = 1650;
        pos5a = 1050;
        pos6a = 550; 


                
        stepFlag = 2;           
        previousStepMillis = currentMillis;
      }

      else if (stepFlag == 2 && currentMillis - previousStepMillis > 500) {
        //position 3 - primary
        pos1 = 1250;
        pos2 = 1850;
        pos3 = 550;
        //position 1 - opposite
        pos1a = 1250;
        pos2a = 1850;
        pos3a = 1850;

        //position 1 - mid/opposite
        pos4 = 1650;
        pos5 = 1050;
        pos6 = 2400;

        pos4a = 1650;
        pos5a = 1050;
        pos6a = 1050;

        
        stepFlag = 3;           
        previousStepMillis = currentMillis;
      }


      else if (stepFlag == 3 && currentMillis - previousStepMillis > 500) {
        //position 4 - primary
        pos1 = 1650;
        pos2 = 1050;
        pos3 = 550;
        //position 2 - opposite
        pos1a = 1650;
        pos2a = 1050;
        pos3a = 1050; 

        //position 2 - mid/opposite
        pos4 = 1250;
        pos5 = 1850;
        pos6 = 2400; 

        pos4a = 1250;
        pos5a = 1850;
        pos6a = 1850;


        
        stepFlag = 0;           
        previousStepMillis = currentMillis;
      }

     
        pos1Filtered = filter(pos1, pos1Filtered, 20);
        pos2Filtered = filter(pos2, pos2Filtered, 20);
        pos3Filtered = filter(pos3, pos3Filtered, 20);

        pos1aFiltered = filter(pos1a, pos1aFiltered, 20);
        pos2aFiltered = filter(pos2a, pos2aFiltered, 20);
        pos3aFiltered = filter(pos3a, pos3aFiltered, 20);

        pos4Filtered = filter(pos4, pos4Filtered, 20);
        pos5Filtered = filter(pos5, pos5Filtered, 20);
        pos6Filtered = filter(pos6, pos6Filtered, 20);

        pos4aFiltered = filter(pos4a, pos4aFiltered, 20);
        pos5aFiltered = filter(pos5a, pos5aFiltered, 20);
        pos6aFiltered = filter(pos6a, pos6aFiltered, 20);
        
        servo1.writeMicroseconds(pos1Filtered);   // front right
        servo2.writeMicroseconds(pos2Filtered);
        servo3.writeMicroseconds(pos3Filtered);

        servo13.writeMicroseconds(pos1Filtered);   // back right
        servo14.writeMicroseconds(pos2Filtered);
        servo15.writeMicroseconds(pos3Filtered);

        servo4.writeMicroseconds(pos1aFiltered);  // front left
        servo5.writeMicroseconds(pos2aFiltered);
        servo6.writeMicroseconds(pos3aFiltered);

        servo16.writeMicroseconds(pos1aFiltered);  // back left
        servo17.writeMicroseconds(pos2aFiltered);
        servo18.writeMicroseconds(pos3aFiltered);

        servo10.writeMicroseconds(pos4Filtered);   // mid left
        servo11.writeMicroseconds(pos5Filtered);
        servo12.writeMicroseconds(pos6Filtered);

        servo7.writeMicroseconds(pos4aFiltered);   // mid right
        servo8.writeMicroseconds(pos5aFiltered);
        servo9.writeMicroseconds(pos6aFiltered);

        

  }   // end of timed loop




}


// motion filter to filter motions and compliance

float filter(float prevValue, float currentValue, int filter) {  
  float lengthFiltered =  (prevValue + (currentValue * filter)) / (filter + 1);  
  return lengthFiltered;  
}
