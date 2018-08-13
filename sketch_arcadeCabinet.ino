#include <Keyboard.h>

/*
  ToDo: create a class that will serve as a button object.
  This button object will contain a variable for the button's
  state and which keyboard key it should be assigned to.
  
  ToDo: create a class that will contain the 
  ToDo: the buttons should be controlled by a State Machine
    States
    ButtonNotPressed -> ButtonPressed
    ButtonPressed    -> ButtonNotPressed
    ButtonPressed    -> ButtonHeld
    ButtonHeld       -> ButtonNotPressed
    
    Then when processing the button inputs we can just check
    to see what state the button is currently in. If in state
    `ButtonNotPressed` send Keyboard.Release() command for the
    associated key.
    
    If button is in state ButtonPressed I will use
    Keyboard.write(), which simulates pressing a releasing a
    keyboard key, this will then need to transition the state
    to then return to ButtonNotPressed
*/

//find more keycodes here: http://keycode.info/
int pageUpASCII = 33;
int pageDownASCII = 34;

bool isButton1Pressed;
bool isButton2Pressed;
bool isButton1Held;
bool isButton2Held;

bool isKeyboardButton1Released;
bool isKeyboardButton2Released;

bool isPlayer1CoinLEDLit;
bool isPlayer1StartLEDLit;
bool isPlayer2CoinLEDLit;
bool isPlayer2StartLEDLit;

/*
  Developer's Note: The Arduino Uno defaults to using a 16Mhz
  crystal. This means that the microcontroller can execute up
  to 16 million instructions per second. Therefore, setting the
  skipLEDDelay to 10 million will cause the LEDs to remain in a
  state for just under one second.
  
  Reference: https://stackabuse.com/speeding-up-arduino/
*/
int skipLEDDelay = 10000000; //10 million
int skipLED      = skipLEDDelay;

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps: //https://www.arduino.cc/reference/en/language/functions/communication/serial/print/
  //Keyboard.begin();
  
  isButton1Pressed = false;
  isButton2Pressed = false;
  isButton1Held    = false;
  isButton2Held    = false;

  isKeyboardButton1Released = true;
  isKeyboardButton2Released = true;

  isPlayer1CoinLEDLit  = true;
  isPlayer1StartLEDLit = false;
  isPlayer2CoinLEDLit  = true;
  isPlayer2StartLEDLit = false;

  #define inputPinsLength 2
  int inputPins[inputPinsLength]  = { 2, 3 };  
  setInputPins(inputPins, inputPinsLength, true);  
  
  #define outPinsLength 4
  int outputPins[outPinsLength] = { 4, 5, 6, 7 };  
  setInputPins(outputPins, outPinsLength, false);  
}

void loop() {
  readInputPins();
  printButtonPress();
  //sendToKeyboard();
  
  setLEDState();
  displayLEDState();
}

void displayLEDState() {
  //Serial.println((String)"is player 1 start LED lit? " + isPlayer1StartLEDLit);
  //Serial.println((String)"skipLED: " + skipLED);
  
  if(skipLED == skipLEDDelay) {
    isPlayer1CoinLEDLit  ? digitalWrite(7, HIGH) : digitalWrite(7, LOW);
    isPlayer1StartLEDLit ? digitalWrite(6, HIGH) : digitalWrite(6, LOW);
    isPlayer2CoinLEDLit  ? digitalWrite(5, HIGH) : digitalWrite(5, LOW);
    isPlayer2StartLEDLit ? digitalWrite(4, HIGH) : digitalWrite(4, LOW);        
  }
  else if(skipLED == 0) {
      skipLED = skipLEDDelay;
      return;
  }
  
  skipLED--;
}

void setLEDState() {
  //ToDo: figure out a nicer LED strategy, for now just blink ON | OFF  
  if(isPlayer1StartLEDLit) {
    isPlayer1StartLEDLit = false;
    isPlayer2StartLEDLit = false;
  }
  else {
    isPlayer1StartLEDLit = true;
    isPlayer2StartLEDLit = true;
  }
}

/*
  Reads the current value of the pins and sets their variables.
  
  When the button is pressed its corresponding isButton*Pressed variable
  
  When the button is held down then we will set a isButton*Held variable to true,
  while the button is held down we do not process the digital signal as the button
  being repeatedly pressed, this is because we will send the keyboard.Release()
  command when the button is no longer being held.
  
  In a case where the button was not being held we will immediately send the keyboard.Release()
*/
void readInputPins() {  
  //Check if the buttons are pressed
  if(digitalRead(2) != 0) {
    //Was the button held since the last loop?
    if(isButton1Pressed || isButton1Held)
    {
      isButton1Held = true;
      isButton1Pressed = false;
    }    
    else {
      isButton1Pressed = true;  
    }
  }
  else {
    isButton1Pressed = false;
    isButton1Held    = false;
  }
  
  if(digitalRead(3) != 0) {
    //Was the button held since the last loop?
    if(isButton2Pressed || isButton2Held)
    {
      isButton2Held = true;
      isButton2Pressed = false;
    }    
    else {
      isButton2Pressed = true;  
    }
  }
  else {
    isButton2Pressed = false;
    isButton2Held    = false;
  }

  //Short-circuit the loop if no buttons are pressed
  //Arduino will start the loop again
  if((!isButton1Pressed and !isButton2Pressed) || isButton1Held || isButton2Held) 
  {
    return;
  }
  
  delay(100);
  
  //Check if the buttons are being held
  //Should not switch off button pressed yet, 
  //so that the pressing of the button can be processed
  if(digitalRead(2)) {
    if(isButton1Pressed) { isButton1Held = true;  }
    else                 { isButton1Held = false; }
  }
  else
  {
    isButton1Held = false;
  }
  
  if(digitalRead(3)) {
    if(isButton2Pressed) { isButton2Held = true;  }
    else                 { isButton2Held = false; }
  }
  else
  {
    isButton2Held = false;
  }
}

/*
Cannot use Keyboard.begin() and Keyboard.end() within this method. If I did
I would be unable to hold the keys down.
*/
void sendToKeyboard() {
  /* The Arduino UNO does not support Keyboard. Ordered a Leonardo to use this code.
  // Button 1
  if(isButton1Pressed) {
    if(isButton1Held) {
      Keyboard.press(pageUpASCII);
      isKeyboardButton1Released = false;
    }
    
    Keyboard.write(pageUpASCII);
    isKeyboardButton1Released = true;
  }
  else if(isButton1Held) {
    isKeyboardButton1Released = false;
  }
  else if(!isKeyboardButton1Released) {
    Keyboard.release(pageUpASCII);
    isKeyboardButton1Released = true;
  }
  
  // Button 2
  if(isButton2Pressed) {
    if(isButton2Held) {
      Keyboard.press(pageDownASCII);
      isKeyboardButton2Released = false;
    }
    
    Keyboard.write(pageDownASCII);
    isKeyboardButton2Released = true;
  }
  else if(isButton2Held) {
    isKeyboardButton2Released = false;
  }
  else if(!isKeyboardButton2Released) {
    Keyboard.release(pageDownASCII);
    isKeyboardButton2Released = true;
  } 
  */
}  

/*
  Sets the specified pins to either INPUT or OUTPUT
  
  param pin Array representing a list of pins.
  param isInput Boolean representing if pins should be set to INPUT or OUTPUT
*/
void setInputPins(int pin[], int numberOfPins, bool isInput) {
  int i;

  for(i = 0; i < numberOfPins; i++) {      
    pinMode(pin[i], isInput ? INPUT : OUTPUT);
  }
}

/*
  Uses Serial.println to inform the user which buttons are currently displayed.
*/
void printButtonPress() {
  if(isButton1Pressed == 1) { Serial.println("Button 1 is pressed."); }
  if(isButton2Pressed == 1) { Serial.println("Button 2 is pressed."); }
  
  if(isButton1Held == 1) { Serial.println("Button 1 is held."); }
  if(isButton2Held == 1) { Serial.println("Button 2 is held."); }
}
