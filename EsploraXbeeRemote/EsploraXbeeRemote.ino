/*
  Esplora Wireless Slave

  This sketch allows to test all the Esplora's peripherals over an Xbee connected to the hardware serial (Serial1).
  
  When uploaded, you can open a PuTTY Serial monitor and write one of
  the following commands (without quotes) to get an answer:
  
  "D": prints the current value of all sensors, separated by a comma.
       See the dumpInputs() function below to get the meaning of
       each value.
       
  "Rxxx"
  "Gxxx"
  "Bxxx": set the color of the RGB led. For example, write "R255"
          to turn on the red to full brightness, "G128" to turn
          the green to half brightness, or "G0" to turn off
          the green channel.
  
  "Txxxx": play a tone with the buzzer. The number is the
           frequency, e.g. "T440" plays the central A note.
           Write "T0" to turn off the buzzer.
  

  Created on 31 December 2012 Anne Barela http://21stdigitalhome.blogspot.com/
  Based on EsploraRemote example code by Enrico Gueli <enrico.gueli@gmail.com>
*/

#include <Esplora.h>

void setup() {
  // while(!Serial); // needed for Leonardo-based board like Esplora
  Serial1.begin(9600);
}

void loop() {
  if (Serial1.available())
    parseCommand();
}

/*
 * This function reads a character from the serial line and
 * decide what to do next. The "what to do" part is given by
 * function it calls (e.g. dumpInputs(), setRed() and so on).
 */
void parseCommand() {
  char cmd = Serial1.read();
  switch(cmd) {
    case 'D': dumpInputs(); break;
    case 'R': setRed(); break;
    case 'G': setGreen(); break;
    case 'B': setBlue(); break;
    case 'T': setTone(); break;
  }
}

void dumpInputs() {  
  /*
   * please note: a single row contains two instructions.
   * one is to print the sensor value, the other to print the
   * comma symbol.
   */
  Serial1.print(Esplora.readButton(SWITCH_1)); Serial1.print(',');
  Serial1.print(Esplora.readButton(SWITCH_2)); Serial1.print(',');
  Serial1.print(Esplora.readButton(SWITCH_3)); Serial1.print(',');
  Serial1.print(Esplora.readButton(SWITCH_4)); Serial1.print(',');
  Serial1.print(Esplora.readSlider());         Serial1.print(',');
  Serial1.print(Esplora.readLightSensor());    Serial1.print(',');
  Serial1.print(Esplora.readTemperature(DEGREES_C)); Serial1.print(',');
  Serial1.print(Esplora.readMicrophone());     Serial1.print(',');
  Serial1.print(Esplora.readJoystickSwitch()); Serial1.print(',');
  Serial1.print(Esplora.readJoystickX());      Serial1.print(',');
  Serial1.print(Esplora.readJoystickY());      Serial1.print(',');
  Serial1.print(Esplora.readAccelerometer(X_AXIS)); Serial1.print(',');
  Serial1.print(Esplora.readAccelerometer(Y_AXIS)); Serial1.print(',');
  Serial1.print(Esplora.readAccelerometer(Z_AXIS)); Serial1.println();
}

void setRed() {
  Esplora.writeRed(Serial1.parseInt());
}

void setGreen() {
  Esplora.writeGreen(Serial1.parseInt());
}

void setBlue() {
  Esplora.writeBlue(Serial1.parseInt());
}

void setTone() {
  Esplora.tone(Serial1.parseInt());
}
