/*
  Esplora Software serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 8 (connect to TX of other device) (must be pins 8,9,10,11,14,15,16 for soft on Leos)
 * TX is digital pin 1 (connect to RX of other device)
 
 Not all pins on the Leonardo type Arduinos support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 Softserial example created back in the mists of time
 Based on Arduino SoftSerialExample by Tom Igoe
 which was based on Mikal Hart's example
 
 Modified for Esplora by M Barela  12/30/2012  http://21stdigitalhome.blogspot.com/
 
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8,1); // RX, TX Esplora Right Connector Pins 6 and 8 as 7 cannot receive via softserial)

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo/Esplora
  }


  Serial.println("Hello Monitor");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello Terminal");
}

void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
  delay(1);
}

