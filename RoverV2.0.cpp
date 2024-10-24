#include <Wire.h>
#include <VL53L0X.h>
#include <Motor_pwm_struct.h>
#include <sensor.h>


#define sensorRightX 23  // Højre sensor
#define sensorLeftX 4   // Venstre sensor
#define sensorFrontX 2  // Front sensor

VL53L0X sensorRight;  // sensor højre
VL53L0X sensorLeft;   //sensor Venstre
VL53L0X sensorFront;  // Front sensor


void setup() {

Serial.begin(115200); // åbner serial port

  Wire.begin(); // Initierer I2C


  pinMode(sensorRightX, OUTPUT);
  pinMode(sensorLeftX, OUTPUT);
  pinMode(sensorFrontX, OUTPUT);

    sensorRight = sensorStart(0x30, 23);
    Serial.println("sensor Right I2C address changed to 0x30");
    sensorLeft = sensorStart(0x31, 4);
    Serial.println("sensor Right I2C address changed to 0x31");
    sensorFront = sensorStart(0x32, 2);
    Serial.println("sensor Right I2C address changed to 0x32");

  // Indstil motorpins som output
  initMotors;
  steering;

//pinMode(A1, OUTPUT);
//pinMode(A2, OUTPUT);
//pinMode(B1, OUTPUT);
//pinMode(B2, OUTPUT);

  // Initialiser motorer til at være slukket
//analogWrite(A1, 0);
//analogWrite(A2, 0);
//analogWrite(B1, 0);
//analogWrite(B2, 0);
  

}

void loop() {


int distanceRight = sensorRight.readRangeSingleMillimeters(); // Læser højre sensor
int distanceLeft = sensorLeft.readRangeSingleMillimeters();   // Læser venstre sensor
int distanceFront = sensorFront.readRangeSingleMillimeters(); // læser front sensor


  if (sensorRight.timeoutOccurred()) {
        Serial.println("Sensor timeout-Right");
    } else {
          Serial.print("Afstand: ");
          Serial.print(distanceRight);
          Serial.print(" mm -Right\n");
  }
  if (sensorLeft.timeoutOccurred()) {
        Serial.println("Sensor timeout-Left");
    } else {
          Serial.print("Afstand: ");
          Serial.print(distanceLeft);
          Serial.print(" mm -Left\n");
    }
  if (sensorFront.timeoutOccurred()) {
        Serial.println("Sensor timeout-Front");
    } else {
          Serial.print("Afstand: ");
          Serial.print(distanceFront);
          Serial.print(" mm -Front\n");
    };

   if (distanceRight >= 500 && distanceLeft >= 500 && distanceFront >= 300) {
      moveForward(); // Kør fremad
      Serial.println("køre ligeud");
        delay (50);
      } 
    else if (distanceRight < 500)
      {
        
        turnRight ();
        Serial.println("Drej til højre");
        delay (50);
      }
    else if (distanceLeft < 500)
      {
        
        turnLeft ();
        Serial.println("Drej til venstre");
        delay(50);
      }
    else if (distanceFront < 400)
      {
        Back ();
        delay(200);
        turnRight();
        Serial.println("bak..!");
        
        //Buzzer();
        delay(50);
      }

      //delay(100); // Opdater motorer hver 100 ms
}
