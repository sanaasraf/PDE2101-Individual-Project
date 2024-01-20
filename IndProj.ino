//Kids WonderTech Dreamhouse Code- A smart dollhouse with features like: smart door, automatic doorbell, and IR controlled storytelling, interactive LCD screen and LED lights.

// different libraries- each fulfilling tasks for LCD, IR, Servo motor, etc.
#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo; //Declaration for servo motor

int pos = 0; //Inititalizing its position as '0'

//Defining designated pins for ultrasonic sensor related activities
int triggerPin = 9; //For ultrasonic sensor 1
int echoPin = 10; // For ultrasonic sensor 1
int triggerPin2 = 11; //For ultrasonic sensor 2
int echoPin2 = 6; //For ultrasonic sensor 2
long duration; //Stores time duration for distance measurement for ultrasonic sensor 1
int distance; //Stores calculated distance for ultrasonic sensor 1
long duration2; //Stores time duration for distance measurement for ultrasonic sensor 2
int distance2; //Stores calculated distance for ultrasonic sensor 2


// Defining Pins for the LED strip lights
int red = 8; 
int green = 6;
int blue = 7;

//Arrays representing icons with different number of elements (For LCD screen)
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t star[8] = {0x00,0x00,0x04,0x0E,0x1F,0x0E,0x04,0x00};
uint8_t smile[8] = {0x00,0x00,0x0A,0x0A,0x00,0x11,0x0E,0x00};

//Pin for IR Reciever 
IRrecv IR(3);

//Defining I2C address for LCD, along with number of rows and columns
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() { 

  IR.enableIRIn(); //Enabling the IR reviever

  //Setting input and output for LEDs and ultrasonic sensor and buzzer
  pinMode(12,OUTPUT); 
  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(triggerPin,OUTPUT);
  pinMode(triggerPin2,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(echoPin2,INPUT);
  
  Serial.begin(9600); //Serial communication is enabled at 9600 bps 
  lcd.begin(16, 2); // LCD has 16 rows and 2 columns
  lcd.backlight(); //Switching on backlight for LCD
  lcd.createChar(8,heart); //Creating a heart icon at position '8' on LCD
  lcd.createChar(5,star); //Creating a star icon at position '5' on LCD
  lcd.createChar(4,smile); // Creating a smile icon at position '4' on LCD
  myservo.attach(9); // Attaching servo motor to pin 9
       
}

void loop() { 

//Smart Door Code

    digitalWrite(triggerPin, HIGH); //Triggers the ultrasonic sensor
    delayMicroseconds(10); //Delay for a short duratiion
    digitalWrite(triggerPin, LOW); //End the trigger
    
    duration = pulseIn(echoPin, HIGH); //Measuring the distance of the echo pulse
    distance = (duration*.0343)/2; //Calculating distance based on the speed of sound
    Serial.print("Distance ="); // Defining the distance label on serial monitor
    Serial.print(distance); //Print the calculated distance on serial monitor
    Serial.print (" cm"); //Defining the units, cms.
    Serial.println (" "); //Specifying a new line
    
    if (distance <= 5){ //In the case that the distance in equal to or less than 5 cm
      for (pos = 0; pos <= 90; pos +=1) {
        myservo.write(pos); //Move position of servo from 0 to 90 degrees (opens door)
        delay(1000); //Waiting for servo to reach said position
    }
     
      delay(5000); // Delay for 5 seconds (For door to stay open)
      for (pos = 90; pos >= 0; pos -=1){
        myservo.write(pos); //Moving the servo back to 0 degrees (Closes door)
        delay(1000); //Waiting for servo to reach said positon

    }
    
  }
    
// Automatic Doorbell code

    digitalWrite(triggerPin2, HIGH); //Triggers the ultrasonic sensor
    delayMicroseconds(10); //Delay for a short duratiion
    digitalWrite(triggerPin2, LOW); //Ends the trigger
    
    duration2 = pulseIn(echoPin2, HIGH); //Measurement of the duration of echo pulse
    distance2 = (duration2*.0343)/2; //Calculation of distance based on the speed of sound
    Serial.print("Distance ="); //Defining and printing the label for calculated distance on serial monitor
    Serial.print(distance2); //Printing the distance
    Serial.print (" cm"); //Printing the units, cms.
    Serial.println (" "); //Next line
    
    if (distance <= 5){ //In the case that the distance is less than or equal to 5 cm
     digitalWrite(12,HIGH); //Ring buzzer (doorbell)
     
     }
     
    else {
      
      digitalWrite(12,LOW); //Else, don't ring the buzzer (doorbell)
      
     }
  
// Code for interactive IR controlled LCD screen
  
    if (IR.decode()) { //In the case that an IR signal has been recieved (if that particular button on the remote is clicked)
       Serial.println(IR.decodedIRData.decodedRawData, HEX); //Printing the hexadecimal on the serial monitor
       if(IR.decodedIRData.decodedRawData == 0xFE01BF00){ //In the case that this particular hexacode is recieved
        lcd.clear(); //Clearing the LCD Screen
        lcd.setCursor(3,0); //Setting the cursor for text alignment
        lcd.print("Hi, Barbie!"); //Displaying this message on the screen
        lcd.setCursor(7,1);  //Setting the cursor again for alignment 
        lcd.write(8); //Printing a heart icon as specified before
       
      }
      
       if(IR.decodedIRData.decodedRawData == 0xFD02BF00){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Time to eat,");
        lcd.setCursor(8,1);
        lcd.print(" Barbie!");
        
        
      }
      if(IR.decodedIRData.decodedRawData == 0xFC03BF00){
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("It's bedtime,");
        lcd.setCursor(3,1);
        lcd.print("good night");
        lcd.setCursor(14,1);
        lcd.write(5); //Printing a star icon as specified before
      }
      if(IR.decodedIRData.decodedRawData == 0xFB04BF00){
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("Hey Barbie!");
        lcd.setCursor(2,1);
        lcd.print("Lets have fun!");
        
      }
      if(IR.decodedIRData.decodedRawData == 0xFA05BF00){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("I love my Barbie!");
        lcd.setCursor(7,1);
        lcd.write(4); //Printing a smile-y face as specified before
      }

 //Code for interactive LED strip lights    
  
      if(IR.decodedIRData.decodedRawData == 0xF906BF00){ //If the particular hexacode is recieved (if that particular button is clicked)
        digitalWrite(red,HIGH); //Display red lights
        digitalWrite(green,LOW);
        digitalWrite(blue,LOW);
      }
      if(IR.decodedIRData.decodedRawData == 0xF807BF00){
        digitalWrite(red,LOW);
        digitalWrite(green,LOW);
        digitalWrite(blue,HIGH); //Display blue lights
      }
      if(IR.decodedIRData.decodedRawData == 0xF708BF00){
        digitalWrite(red,LOW);
        digitalWrite(green,HIGH); //DIsplay green lights
        digitalWrite(blue,LOW);
      }
       if(IR.decodedIRData.decodedRawData == 0xF609FF00){
        digitalWrite(red,HIGH);
        digitalWrite(green,LOW); //Display purple lights
        digitalWrite(blue,HIGH);
      }
      if(IR.decodedIRData.decodedRawData == 0xBC43FF00){
        digitalWrite(red,HIGH);
        digitalWrite(green,HIGH); //Display white lights
        digitalWrite(blue,HIGH);
      }
       if(IR.decodedIRData.decodedRawData == 0xBF40FF00){
        digitalWrite(red,LOW);
        digitalWrite(green,HIGH); //Display cyan lights
        digitalWrite(blue,HIGH);
      }
      if(IR.decodedIRData.decodedRawData == 0xE619FF00){
        digitalWrite(red,HIGH);
        digitalWrite(green,HIGH); //Display brown lights
        digitalWrite(blue,LOW);
      }
       if(IR.decodedIRData.decodedRawData == 0xE916FF00){ 
        digitalWrite(green,LOW);
        digitalWrite(blue,LOW);
        digitalWrite(green,LOW); //Switch lights off
      }
       if(IR.decodedIRData.decodedRawData == 0xE980FF00){ //If the particular hexacode is recieved
        digitalWrite(2,HIGH); // Switches on the pin for playing audio
        delay(10); //Waits for a short period
        digitalWrite(2,LOW); //Switches off the pin that plays audio
        delay(100); //Waits for a short period
      }
        delay(500); //After a short delay..
        IR.resume(); //Resumes the IR reciever so that another signal may be recieved
      } 

      //There are buttons on the module that have been rewired towards th front of the dollhouse that allow to skip to next audio, or swtich back to previous  audio. IR simply controls play and pause. 
 }
