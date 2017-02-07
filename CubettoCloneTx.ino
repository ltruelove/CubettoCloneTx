/* 
 *  
  Lots of help referenced here:
  http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
  
  and here:
  http://shanes.net/another-nrf24l01-sketch-string-sendreceive/
  
  Uses the RF24 Library by TMRH2o here:
  https://github.com/TMRh20/RF24
 */
  
#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)

// (Create an instance of a radio, specifying the CE and CS pins. )
RF24 myRadio (9, 10); // "myRadio" is the identifier you will use in following methods

byte addresses[][6] = {"CNode"}; // Create address for 1 pipe.
String commandSet = "";
int commandPosition = 0;
int myInit = 1;

void setup()
{
  // Use the serial Monitor (Symbol on far right). Set speed to 9600 (Bottom Right)
  Serial.begin(9600);
  delay(1000);
  
  myRadio.begin();  // Start up the physical nRF24L01 Radio
  myRadio.setChannel(108);  // Above most Wifi Channels
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  myRadio.setPALevel(RF24_PA_MIN);
  //  myRadio.setPALevel(RF24_PA_MAX);  // Uncomment for more power
  myRadio.openWritingPipe( addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  
  delay(1000);
}//--(end setup )---


void loop()
{ 
  // listen for commands coming in over serial
  if (Serial.available() > 0) {
    commandSet = Serial.readString();
    commandPosition = 0;

    //iterate over each character received and send it to the other transceiver
    for(int i = 0; i < commandSet.length(); i++){
      char charToSend[1];
      charToSend[0] = commandSet.charAt(i);
      myRadio.write(charToSend, 1);
    }

    //send the 1 character as a terminating char
    myRadio.write("1",1);

    //currently, we're not listening for a response. In the future it may be a good idea to do so
    
    delay(500);
  }

}
