#include <ArcadeButton.h>
#include <LED.h>
#include <Keyboard.h>

//Set interrupt pin
byte interruptPin = 3;

// Construct the LEDs
const short numberOfLEDs = 4;
LED leds[numberOfLEDs] = {
  LED("Player 1 Start", 8 , true),
  LED("Player 2 Start", 9 , true),
  LED("Player 1 Coin" , 10, true),
  LED("Player 2 Coin" , 11, true)  
};

//Define keyboard buttons, find more keycodes here: http://keycode.info/
byte numberSevenAscii = 55;
byte numberEightAscii = 56;
byte numberNineAscii = 57;
byte numberZeroAscii = 48;

// Construct the arcade buttons
const short numberOfArcadeButtons = 4;
ArcadeButton arcadeButtons[numberOfArcadeButtons] = {
  ArcadeButton("Player 1 Start", 4, numberSevenAscii),
  ArcadeButton("Player 2 Start", 5, numberEightAscii),
  ArcadeButton("Player 1 Coin" , 6, numberNineAscii),
  ArcadeButton("Player 2 Coin" , 7, numberZeroAscii)
};

/**
 * Runs once, when Arduino first starts.
 */
void setup() {
  // Setup the button interrupts
  setupArcadeButtonsInterrupt();
}

/**
 * Repeatedly runs, speed is tied to the logic
 * that is completed within the function and the
 * onboard crystal oscillator.
 */
void loop() {
}

/*
 * Sets up the interrupt handler to listen for button presses.
 * 
 * The interrupt is setup for the Players 1 and 2 Start and
 * Coin buttons. The interrupt will be fired each time the 
 * button changes state. The button is connected to a RC 
 * network and a Schmitt Trigger so the debouncing will be 
 * handled by the hardware.
 * 
 * The Arduino Leonardo does not easily support using the 
 * five built-in digital pin interrupts, I have noticed a
 * lot of noise on the 0 and 1 digital pins. Due to this
 * I have the buttons triggering the same interrupt and
 * allow the handler to determine which button is currently
 * being pressed.
 */
void setupArcadeButtonsInterrupt() {
  attachInterrupt(
    digitalPinToInterrupt(interruptPin),
    [](){
      //Player 1 Start
      if(digitalRead(arcadeButtons[0].GetDigitalPin())) {
        leds[0].SetOff();
        Keyboard.begin();
        Keyboard.press(arcadeButtons[0].GetASCIIKeyCode());
      }
      else {
        leds[0].SetOn();
        Keyboard.release(arcadeButtons[0].GetASCIIKeyCode());
        Keyboard.end();
      }

      //Player 2 Start
      if(digitalRead(arcadeButtons[1].GetDigitalPin())) {
        leds[1].SetOff();
        Keyboard.begin();
        Keyboard.press(arcadeButtons[1].GetASCIIKeyCode());
      }
      else {
        leds[1].SetOn();
        Keyboard.release(arcadeButtons[1].GetASCIIKeyCode());
        Keyboard.end();
      }

      //Player 1 Coin
      if(digitalRead(arcadeButtons[2].GetDigitalPin())) {
        Keyboard.begin();
        Keyboard.press(arcadeButtons[2].GetASCIIKeyCode());
      }
      else {
        Keyboard.release(arcadeButtons[2].GetASCIIKeyCode());
        Keyboard.end();
      }

      //Player 2 Coin
      if(digitalRead(arcadeButtons[3].GetDigitalPin())) {
        Keyboard.begin();
        Keyboard.press(arcadeButtons[3].GetASCIIKeyCode());
      }
      else {
        Keyboard.release(arcadeButtons[3].GetASCIIKeyCode());
        Keyboard.end();
      }
    },
    CHANGE
  );
}
