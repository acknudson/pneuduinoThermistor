/**********************************************************************************

    ____  ____     ___  __ __  ___    __ __  ____  ____    ___  
   |    \|    \   /  _]|  |  ||   \  |  |  ||    ||    \  /   \ 
   |  o  )  _  | /  [_ |  |  ||    \ |  |  | |  | |  _  ||     |
   |   _/|  |  ||    _]|  |  ||  D  ||  |  | |  | |  |  ||  O  |
   |  |  |  |  ||   [_ |  :  ||     ||  :  | |  | |  |  ||     |
   |  |  |  |  ||     ||     ||     ||     | |  | |  |  ||     |
   |__|  |__|__||_____| \__,_||_____| \__,_||____||__|__| \___/ 

   PneuDuino is a toolkit for controlling inflatable actuators
   and prototyping interactions with shape-changing systems.

   Every slave board has a RGB led on the top right corner that communicates
   the state of this board.

   GREEN - baord running and connecting
   RED - board running, but not connected
   BLUE - board not running yet (usually after reset or power) or broken :(

   The boards addresses range from 1-12. 12 is reserved for IO Boards.
   There can ONLY BE ONE IO BOARD per system.

   The library offers functions that allow for controlling the valves and 
   accessing the pressure sensor :

   begin() - should be called at the beginning of setup()
   update() - should be called at the beginning of loop()

   void in(address, side) - inflates bag of board with defined address
   void out(address, side) - deflates bag of board with defined address
   int readPressure(address) - returns pressure of bag at defined address. 
                              Notice that a non-deflated bag still experiences 
                              athmospheric pressure and thus does not return 0.
   bool readButton(side) - returns button state of IO Board. 0 is top, 1 is bottom.
   int readPot() - returns potentiometer value of IO Board. 0 - 15.

**********************************************************************************/

#include <Wire.h>
#include <PneuDuino.h>
#include <avr/pgmspace.h>

#define THERM_PIN   0  // 10ktherm & 10k resistor as divider.

PneuDuino air = PneuDuino();

/* sample code: http://playground.arduino.cc/ComponentLib/Thermistor */

void setup() {
  pinMode(13, OUTPUT); //sets pin 13 as output
  Serial.begin(9600);
  air.begin(); // initialize the pneuDuino library. DON'T MOVE THIS!
  time = millis(); //the number of milliseconds since the Arduino board began running the current program
  Serial.println("Ready!")
  
}

void loop() {
  air.update(); // update the pneuduino library. DONT MOVE THIS!
  

  Serial.println(therm, DEC);
  //add checks for the thermometer temp. 

  if (millis() - time >10000){ //check every 10 seconds
    //or take out of if and use delay(10000); 
    time=millis();
    int therm;   
    therm=analogRead(THERM_PIN)-238; //subtract 238 from ADC reading to start at 0*C
    //the thermistors we have may not read below 0*C... what should we do???
    therm=pgm_read_word(&temps[therm]);
  }
}
