/*
  Esplora Wireless Controller
  
  This program outputs ASCII characters over the Serial1 hardware connection to an XBee radio
  in response to joystick movements and button presses like a commercial game controller

  This version is customized to outut commands to another Xbee connected to an
  Arduino Uno and an Adafruit Motorshield connected to a Robotic Head.  Independent
  control of the neck, chin, eyes, and mouth are possible using 2 servos and 2 DC motors.

  Updated on January 3, 2013 Anne Barela http://21stdigitalhome.blogspot.com/
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
  SWITCH_RIGHT, 
  SWITCH_LEFT, 
  SWITCH_UP, 
  SWITCH_DOWN, 
};

/*
  This array tells what keystroke to send to the receiving XBee when a
  button is pressed.
  If you look at this array and the above one, you can see that
  the "D" keystroke is sent when the joystick is moved
  down, the "U" keystroke when the joystick is moved up
  and so on.
*/
const char keystrokes[] = {
  'U',
  'R',
  'D',
  'L',
  '2',
  '1',
  '4',
  '3'
};


void setup() {
  Serial1.begin(9600);  // begin serial comms on XBee hardwired to D0/D1 hardware Serial1
}

void loop() {
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
  if(Esplora.readJoystickButton()==LOW)  // If joystick pressed down (button)
      Serial1.println("0");             //   then output eyes/outh home comand
  /*
    Wait a little bit (50ms) between one button check and another.
    When a mechanical switch is pressed or released, the
    contacts may bounce very rapidly. If the check is done too
    fast, these bounces may be confused as multiple presses and
    may lead to unexpected behaviour.
   */
  delay(50);
}

