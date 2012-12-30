/*
  Esplora expansion hardware serial test
 
 Receives from the USB serial, sends to hardware serial (Serial1)
 Receives from hardware (Serial1) serial, sends to USB serial.
 Per Leonardo docs, Serial One (Serial1) is hardware pin 0/1 serial port
 
 The circuit: 
 * RX is digital pin 0 / Esplora right expansion pin 7 (connect to TX of other device) 
 * TX is digital pin 1 / Esplora right expansion pin 8 (connect to RX of other device)
 
By M Barela  12/30/2012  http://21stdigitalhome.blogspot.com/
 
 */

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo/Esplora
  }


  Serial.println("Hello IDE Serial Monitor");

  // set the data rate for the SoftwareSerial port
  Serial1.begin(4800);
  Serial1.println("Hello PuTTY Terminal");
}

void loop() // run over and over
{
  if (Serial1.available())
    Serial.write(Serial1.read());
  if (Serial.available())
    Serial1.write(Serial.read());
  delay(1);
}

