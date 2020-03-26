#include <Arduino.h>

//Times to go from button to the optic
int Steps[6] = {80, 765, 1500, 2100, 2750, 3350};

//The below is for the contact switch.

const int buttonPin = 2; // the pin that the pushbutton is attached to
int buttonState = 0;     // current state of the button
int lastButtonState = 0; // previous state of the button

//----------------------

//The below is for the stepper motors

#include <AFMotor.h>
AF_Stepper motor1(48, 1);
AF_Stepper motor2(48, 2);

//---------------------

//The below are for running the machine:

int drinkRequested = true;

//---------------------

//Setup Keypad

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {9, 10, A0, A1};  //connect to the row pinouts of the keypad
byte colPins[COLS] = {A2, A3, A4, A5}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{

  // for the contact switch

  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);

  //--------------------------------

  //  For the stepper motors

  motor1.setSpeed(600);
  motor2.setSpeed(600);

  //-------------------------------
}

void pourDrink(int num) {

  for (int i = 0; i < num; i++)
  {
    delay(500);
    motor2.step(3100, BACKWARD, DOUBLE);
    motor2.release();
    delay(4000);
    motor2.step(3100, FORWARD, DOUBLE);
    motor2.release();
  }
}

void moveToBase() {

  buttonState = digitalRead(buttonPin);

  while (buttonState == LOW)
  {
    motor1.step(10, FORWARD, SINGLE);
    buttonState = digitalRead(buttonPin);
    motor1.release();
  }
}

void moveToDrink(int num) {

  if (num > 5)
  {
    Serial.println("No Such Drink Exists!!");
  }
  

  delay(500);
  motor1.step(Steps[num], BACKWARD, SINGLE);
  motor1.release();
}

void loop()
{
  char customKey = customKeypad.getKey();

  if (customKey == '1') //RonCola
  {
    Serial.println(customKey);
    moveToDrink(0);
    pourDrink(2);
    moveToBase();
    moveToDrink(1);
    pourDrink(5);
  }
  else if (customKey == '2') //Vodka with Lemon
  {
    Serial.println(customKey);
    moveToDrink(2);
    pourDrink(2);
    moveToBase();
    moveToDrink(3);
    pourDrink(5);
  }
  else if (customKey == '3') //Gin Tonic
  {
    Serial.println(customKey);
    moveToDrink(4);
    pourDrink(2);
    moveToBase();
    moveToDrink(5);
    pourDrink(5);
  }
  else if (customKey == '4')
  {
    Serial.println(customKey);
    for (int i = 0; i < 7; i++)
    {
      moveToDrink(i);
      pourDrink(1);
      moveToBase();
    } 
  }
  
    //Drink complete
    moveToBase();
    drinkRequested = false;
  }
