#include <ArcadeButton.h>
#include <LED.h>
#include <Keyboard.h>

// Construct the LEDs
const short numberOfLEDs = 4;
LED leds[numberOfLEDs] = {
  LED("Player 1 Start", 8 , true),
  LED("Player 2 Start", 9 , true),
  LED("Player 1 Coin" , 10, true),
  LED("Player 2 Coin" , 11, true)  
};

//Define keyboard buttons, find more keycodes here: http://keycode.info/
byte numberOneASCII   = 49;
byte numberTwoASCII   = 50;
byte numberThreeASCII = 51;
byte numberFourASCII  = 52;

// Construct the arcade buttons
const short numberOfArcadeButtons = 4;
ArcadeButton arcadeButtons[numberOfArcadeButtons] = {
  ArcadeButton("Player 1 Start", 2, numberOneASCII  ),
  ArcadeButton("Player 2 Start", 3, numberTwoASCII  ),
  ArcadeButton("Player 1 Coin" , 4, numberThreeASCII),
  ArcadeButton("Player 2 Coin" , 5, numberFourASCII )
};

/**
 * Runs once, when Arduino first starts.
 */
void setup() {
  // Setup the button interrupts
  setupPlayer1StartInterrupt();
  setupPlayer2StartInterrupt();
  setupPlayer1CoinInterrupt();
  setupPlayer2CoinInterrupt(); 
}

/**
 * Repeatedly runs, speed is tied to the logic
 * that is completed within the function and the
 * onboard crystal oscillator.
 */
void loop() {  
}

/**
 * The interrupt for Player 1 Start button.
 * 
 * This will be fired each time the button
 * changes state. The button is connected to
 * a RC network and a Schmitt Trigger so the
 * debouncing will be handled by the hardware.
 */
void setupPlayer1StartInterrupt() {
  attachInterrupt(
    digitalPinToInterrupt(arcadeButtons[0].GetDigitalPin()),
    []() {
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
    },
    CHANGE
  );
}

/**
 * The interrupt for Player 2 Start button.
 * 
 * This will be fired each time the button
 * changes state. The button is connected to
 * a RC network and a Schmitt Trigger so the
 * debouncing will be handled by the hardware.
 */
void setupPlayer2StartInterrupt() {
  attachInterrupt(
    digitalPinToInterrupt(arcadeButtons[1].GetDigitalPin()),
    []() {
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
    },
    CHANGE
  );
}

/**
 * The interrupt for Player 1 Coin button.
 * 
 * This will be fired each time the button
 * changes state. The button is connected to
 * a RC network and a Schmitt Trigger so the
 * debouncing will be handled by the hardware.
 * 
 */
void setupPlayer1CoinInterrupt() {
  attachInterrupt(
    digitalPinToInterrupt(arcadeButtons[2].GetDigitalPin()),
    []() {
      if(digitalRead(arcadeButtons[2].GetDigitalPin())) {
        leds[2].SetOff();
        Keyboard.begin();
        Keyboard.press(arcadeButtons[2].GetASCIIKeyCode());
      }
      else {
        leds[2].SetOn();
        Keyboard.release(arcadeButtons[2].GetASCIIKeyCode());
        Keyboard.end();
      }
    },
    CHANGE
  );
}

/**
 * The interrupt for Player 2 Coin button.
 * 
 * This will be fired each time the button
 * changes state. The button is connected to
 * a RC network and a Schmitt Trigger so the
 * debouncing will be handled by the hardware.
 * 
 */
void setupPlayer2CoinInterrupt() {
  attachInterrupt(
    digitalPinToInterrupt(arcadeButtons[3].GetDigitalPin()),
    []() {       
      if(digitalRead(arcadeButtons[3].GetDigitalPin())) {
        leds[3].SetOff();
        Keyboard.begin();
        Keyboard.press(arcadeButtons[3].GetASCIIKeyCode());
      }
      else {
        leds[3].SetOn();
        Keyboard.release(arcadeButtons[3].GetASCIIKeyCode());
        Keyboard.end();
      }        
    },
    CHANGE
  );
}
