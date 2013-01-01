/*
  Esplora Wireless Slave

  This sketch allows to test all the Esplora's peripherals over an Xbee connected to the hardware serial (Serial1).
  It also outputs button and joystick state like a game  controller (rudimentary)
  
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
  

  Created on January 1, 2013 M Barela http://21stdigitalhome.blogspot.com/
  Based on EsploraRemote example code by Enrico Gueli <enrico.gueli@gmail.com>
*/

#include <Esplora.h>

/*
  You're going to handle eight different buttons. You'll use arrays, 
  which are ordered lists of variables with a fixed size. Each array 
  has an index (counting from 0) to keep track of the position
  you're reading in the array, and each position can contain a number.
 
  This code uses three different arrays: one for the buttons you'll read;
  a second to hold the current states of those buttons; and a third to hold
  the keystrokes associated with each button.
 */

/*
  This array holds the last sensed state of each of the buttons
  you're reading.
  Later in the code, you'll read the button states, and compare them
  to the previous states that are stored in this array. If the two
  states are different, it means that the button was either
  pressed or released.
 */
boolean buttonStates[8];

/*
  This array holds the names of the buttons being read.
  Later in the sketch, you'll use these names with
  the method Esplora.readButton(x), where x
  is one of these buttons.
 */
const byte buttons[] = {
  JOYSTICK_DOWN,
  JOYSTICK_LEFT,
  JOYSTICK_UP,
  JOYSTICK_RIGHT,
  SWITCH_RIGHT, // fire
  SWITCH_LEFT, // bend
  SWITCH_UP, // nitro
  SWITCH_DOWN, // look back
};

/*
  This array tells what keystroke to send to the PC when a
  button is pressed.
  If you look at this array and the above one, you can see that
  the "D" keystroke is sent when the joystick is moved
  down, the "U" keystroke when the joystick is moved up
  and so on.
*/
const char keystrokes[] = {
  'D',
  'L',
  'U',
  'R',
  'G',
  'V',
  'N',
  'B'
};


void setup() {
  // while(!Serial); // needed for Leonardo-based board like Esplora
  Serial1.begin(9600);
}

void loop() {
  if (Serial1.available()) // if any incoming serial commands, handle them 
    parseCommand();        // this code may be removed if you want an output controller only
    
  // for controller output, Iterate through all the buttons:
  for (byte thisButton=0; thisButton<8; thisButton++) {
    boolean lastState = buttonStates[thisButton];
    boolean newState = Esplora.readButton(buttons[thisButton]);
    if (lastState != newState) { // Something changed!
      Serial1.println(keystrokes[thisButton]); // output code to Xbee on Serial1
    }

    // Store the new button state, so you can sense a difference later:
    buttonStates[thisButton] = newState;
  }
  
  /*
    Wait a little bit (50ms) between one button check and another.
    When a mechanical switch is pressed or released, the
    contacts may bounce very rapidly. If the check is done too
    fast, these bounces may be confused as multiple presses and
    may lead to unexpected behaviour.
   */
  delay(50);
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
