This software establishes either a hardware serial or software serial connection 
using the right expansion header on the Arduino Esplora (the left connector appears
unused).

ExploraXbeeRemote is a fork of the example EsploraRemote but it uses Serial1 (the
hardware serial pins D0 and D1 which are on the expansion header at Pins 7 and 8.
This is useful for making a wireless esplora controller.  

EsploraXbeeController melds EsploraXbeeRemote with the EsploraKart controller software,
making the Esplora responsive to input and outputing command when the buttons and
joystick press/move making the Esplora a wireless controller. A cell phone emergency
charge battery is strapped onto the Esplora with Xbee making it a truly wireless controller. 

See http://21stdigitalhome.blogspot.com/ - keyword "Arduino Esplora" for all
Esplora related articles which may use this code.

This code is Open Software, Creative Commons 3.0 attribute.
If you use this code, please keep in the header that it is based on code
by Mike Barela dated 12/2012 and 1/2013

Good luck and please post your derivatives.