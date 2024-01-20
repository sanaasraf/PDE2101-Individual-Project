//Code for finding designated hexacodes for buttons on the IR remote

#include <IRremote.h> //Version 3.5.2 included

IRrecv IR(3); //Pin for IR Reciever

void setup() { 

  IR.enableIRIn(); //Enables the receiver
  Serial.begin(9600); //Enables the start of serial communication at 9600 bps
}

void loop() { 
  
  if (IR.decode()) { //In the case that a signal has been recieved
    Serial.println(IR.decodedIRData.decodedRawData, HEX); //Prints the hexacode onto the serial monitor
    delay(1500); //A specified delay after the data is printed
    IR.resume(); //The receiver is free to receive the next signal
    }
 

}
