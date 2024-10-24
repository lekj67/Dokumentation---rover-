#include <Wire.h>
#include <VL53L0X.h>

#define A1 17  // Motor A pins
#define A2 16
#define B1 23 // Motor B pins
#define B2 19


#define sensorRightX 18 // Højre sensor
#define sensorLeftX 19 // Venstre sensor
#define sensorFrontX 5 // Front sensor

VL53L0X sensorRight;  // sensor højre
VL53L0X sensorLeft;   //sensor Venstre
VL53L0X sensorFront;  // Front sensor


// Funktion til at køre fremad
void moveForward() {
  analogWrite(A1, 0); // A1 - Venstre side kører baglæns
  analogWrite(A2, 200); //A2 - Venstre side kører fremad
  analogWrite(B1, 0);   //B1 - Højre side kører baglæns
  analogWrite(B2, 200);   //B2 - Høre side kører fremad
}

// Funktion til at dreje lidt til venstre
void turnLeft() {
  analogWrite(A1, 150); //A1 - Venstre side kører baglæns
  analogWrite(A2, 0);   //A2 - Venstre side kører fremad
  analogWrite(B1, 0);   //B1 - Højre side kører baglæns
  analogWrite(B2, 200); //B2 - Høre side kører fremad
}

// Funktion til at dreje til højre
void turnRight() {
  analogWrite(A1, 0);   //A1 - Venstre side kører baglæns
  analogWrite(A2, 200); //A2 - Venstre side kører fremad
  analogWrite(B1, 150); //B1 - Højre side kører baglæns
  analogWrite(B2, 0);   //B2 - Høre side kører fremad
}

void reverse () {
  analogWrite(A1, 250);   //A1 - Venstre side kører baglæns
  analogWrite(A2, 0);   //A2 - Venstre side kører fremad
  analogWrite(B1, 150); //B1 - Højre side kører baglæns
  analogWrite(B2, 0);   //B2 - Høre side kører fremad
}

void stopMe() {
  analogWrite(A1, 0);   //A1 - Venstre side kører baglæns
  analogWrite(A2, 0);   //A2 - Venstre side kører fremad
  analogWrite(B1, 0);   //B1 - Højre side kører baglæns
  analogWrite(B2, 0);   //B2 - Høre side kører fremad
}



void setup() {

  Serial.begin(115200); // åbner serial port

  Wire.begin(); // Initierer I2C


pinMode(sensorRightX, OUTPUT);
pinMode(sensorLeftX, OUTPUT);
pinMode(sensorFrontX, OUTPUT);

digitalWrite (sensorRightX, LOW); //sætter sensor til slukket
digitalWrite (sensorLeftX, LOW); //sætter sensor til slukket
digitalWrite (sensorFrontX, LOW); //sætter sensor til slukket

digitalWrite (sensorLeftX, HIGH);  //aktivere sensor
delay(10);

sensorLeft.setAddress(0x30);
  Serial.println("Venstre sensor I2C address changed to 0x30");

  // Initialiser sensor
  if (!sensorLeft.init()) { // Sender en fejl i monitor, hvis den fejler.
    Serial.println("Failed to detect and initialize sensorVenstre!");
    while (1); // Stop programmet, hvis sensoren ikke kan initialiseres
  }

digitalWrite (sensorRightX, HIGH);
delay(10);

sensorRight.setAddress(0x31);
 Serial.println("Højre sensor is using I2C address 0x31");

  if (!sensorRight.init()) { // Sender en fejl i monitor, hvis den fejler.
    Serial.println("Failed to detect and initialize sensorHøjre!");
    while (1); // Stop programmet, hvis sensoren ikke kan initialiseres
  }

digitalWrite (sensorFrontX, HIGH);
delay(10);

sensorFront.setAddress(0x32);
  Serial.println("Front sensor is Using I2C adress 0x32");

  if (!sensorFront.init()) { // Sender en fejl i monitor, hvis den fejler.
    Serial.println("Failed to detect and initialize sensorFront!");
    while (1); // Stop programmet, hvis sensoren ikke kan initialiseres
  }
  



  // Indstil motorpins som output
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);

  // Initialiser motorer til at være slukket
  analogWrite(A1, 0);
  analogWrite(A2, 0);
  analogWrite(B1, 0);
  analogWrite(B2, 0);

  sensorRight.setTimeout(200); // Timeout indstilling for sensoren
  sensorLeft.setTimeout(200); //Timeout indstilling for sensoren
  sensorFront.setTimeout(200); //Timeout indstilling for sensoren
  
  // sensor.startContinuous(); // Start kontinuerlig afstandsmåling
  // sensorVenstre.startContinuous(); // Start kontinuerlig afstandsmåling
}

void loop() {
  // Læs sensor afstand
  int distanceRight = sensorRight.readRangeSingleMillimeters(); // Læser højre sensor
  int distanceLeft = sensorLeft.readRangeSingleMillimeters();   // Læser venstre sensor
  int distanceFront = sensorFront.readRangeSingleMillimeters(); // læser front sensor

  // Tjek for timeout
  if (sensorRight.timeoutOccurred()) {
    Serial.println("Sensor timeout-Right");
  } else {
    Serial.print("Afstand: ");
    Serial.print(distanceRight);
    Serial.print(" mm\n");
  }
  if (sensorLeft.timeoutOccurred()) {
    Serial.println("Sensor timeout-Left");
  } else {
    Serial.print("Afstand: ");
    Serial.print(distanceLeft);
    Serial.print(" mm\n");
  }
  if (sensorFront.timeoutOccurred()) {
    Serial.println("Sensor timeout-Front");
  } else {
    Serial.print("Afstand: ");
    Serial.print(distanceFront);
    Serial.print(" mm\n");
  }

  // Hvis afstanden til højre og ventre er større end 600, kør fremad. ((distanceRight >= 600 && distanceLeft >= 600))
   if (distanceRight >= 300 && distanceLeft >= 300 && distanceFront >= 350) {
    moveForward(); // Kør fremad
    Serial.println("køre ligeud");
  } 
  if (distanceFront < 350)
  {
    turnLeft ();
    delay(20);
  }
  
  if (distanceRight < 300)
  {
    turnLeft ();
    //delay (30);
  }

  if (distanceLeft < 300)
  {
    turnRight ();
    //delay(30);
  }

  delay(100); // Opdater motorer hver 100 ms
}
