#include <ArcadeButton.h>
#include <LED.h>
#include <Timer.h>

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

bool isKeyboardButton1Released;
bool isKeyboardButton2Released;

// Construct the arcade buttons
//ToDO: add support to ArcadeButton to push in an LED object
//ToDo: find out ASCII key code for Player 1 and Player 2 Start button, find more keycodes here: http://keycode.info/
ArcadeButton player1Start(1, "Player 1 Start", 2);
ArcadeButton player2Start(2, "Player 2 Start", 3);
ArcadeButton player1Coin(3, "Player 1 Coin", 4, 33); // 33 is ASCII for PageUp Key Code
ArcadeButton player2Coin(4, "Player 2 Coin", 5, 34); // 34 is ASCII for PageDown Key Code

/*
  Developer's Note: The Arduino Uno defaults to using a 16Mhz
  crystal. This means that the microcontroller can execute up
  to 16 million instructions per second. Therefore, setting the
  skipLEDDelay to 10 million will cause the LEDs to remain in a
  state for just under one second.
  
  Reference: https://stackabuse.com/speeding-up-arduino/
*/
//ToDo: Add ability to determine the clock speed for the board,
//this will enable this sketch to be operate as expected regardless
//of its deployment

/*
 * //was 10 million when running on the UNO. Now 3000 for the Leonardo. Need to work out something that uses the actual clock speed. It is now 30000 since I have removed some of the Serial.println code
 * I think this shows that a cycle counter will need to be adjusted not just on the clock speed, but how
 * long it takes the loop operation to cycle when compared to a second.
 */
const long skipLEDDelay = 30000L; 
//int skipLED      = skipLEDDelay;

// Construct the LEDs
LED player1StartLED("Player 1 Start", 8 , false, skipLEDDelay);
LED player2StartLED("Player 2 Start", 9 , false, skipLEDDelay);
LED player1CoinLED("Player 1 Coin"  , 10, false, skipLEDDelay);
LED player2CoinLED("Player 2 Coin"  , 11, false, skipLEDDelay);

Timer ledBlinkTimer(millis(), Timer::TimeUnit::Second, 1, true);

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps: //https://www.arduino.cc/reference/en/language/functions/communication/serial/print/
  
  //Keyboard.begin();
  isKeyboardButton1Released = true;
  isKeyboardButton2Released = true;

  player1CoinLED.SetLEDOn();
  player2CoinLED.SetLEDOn();
}

void loop() {
  readInputPins();
  printButtonPress();
  //sendToKeyboard();

  //Serial.println(skipLEDDelay);
  //Serial.println(player1StartLED.GetLEDBlinkSpeed());
  
  if(player1StartLED.UpdateCyclesTilLEDBlink() == 0){
   player1StartLED.ToggleLED(); 
  }

  if(player2StartLED.UpdateCyclesTilLEDBlink() == 0){
   player2StartLED.ToggleLED(); 
  }

  Serial.print("Remaining time: ");
  Serial.println(ledBlinkTimer.GetRemainingTime());
  ledBlinkTimer.UpdateTimer();
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
  player1Coin.SetButtonStatePressed();
  player1Start.SetButtonStatePressed();
  
  player2Coin.SetButtonStatePressed();
  player2Start.SetButtonStatePressed();
  
  //Short-circuit the loop if no buttons are pressed
  //Arduino will start the loop again
  
  if(
    player1Coin.GetButtonState()  == ArcadeButton::States::UnPressed &&
    player1Start.GetButtonState() == ArcadeButton::States::UnPressed &&
    player2Coin.GetButtonState()  == ArcadeButton::States::UnPressed &&
    player2Start.GetButtonState() == ArcadeButton::States::UnPressed
  ) {
    return;
  }
  
  delay(100);
  
  //Check if the buttons are being held
  //Should not switch off button pressed yet, 
  //so that the pressing of the button can be processed

  player1Coin.SetButtonStateHeld();
  player1Start.SetButtonStateHeld();
  
  player2Coin.SetButtonStateHeld();
  player2Start.SetButtonStateHeld();
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
  if(player1Coin.GetButtonState() == ArcadeButton::States::Pressed  ) { Serial.println("Player 1 Coin is pressed."); }
  if(player1Coin.GetButtonState() == ArcadeButton::States::Held     ) { Serial.println("Player 1 Coin is held."   ); }
  
  if(player1Start.GetButtonState() == ArcadeButton::States::Pressed  ) { Serial.println("Player 1 Start is pressed."); }
  if(player1Start.GetButtonState() == ArcadeButton::States::Held     ) { Serial.println("Player 1 Start is held."   ); }

  if(player2Coin.GetButtonState() == ArcadeButton::States::Pressed  ) { Serial.println("Player 2 Coin is pressed."); }
  if(player2Coin.GetButtonState() == ArcadeButton::States::Held     ) { Serial.println("Player 2 Coin is held."   ); }
  
  if(player2Start.GetButtonState() == ArcadeButton::States::Pressed  ) { Serial.println("Player 2 Start is pressed."); }
  if(player2Start.GetButtonState() == ArcadeButton::States::Held     ) { Serial.println("Player 2 Start is held."   ); }
}
