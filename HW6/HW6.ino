/*
        RBE 2001 A14
        HW3 Solution
        
    Author: Christopher Bove
    Date Finished: 9/19/2014
    
    Description:
      This program displays a clock using the Liquid Crystal Display library based on the
      internal Arduino timer. The format is hh:mm:ss
      
      * A NO pushbutton is used on pin 2 to ground to reset the system.
      
      * Pins for the LCD are configured and defined as seen below the imported libraries.
      
    Dependencies:
      * LiquidCrystal
      * TimerOne
      * stdio
    
    
*/


// *** IMPORT LIBRARIES ***
#include <LiquidCrystal.h>
#include <stdio.h>
#include <TimerOne.h>

// define pin configs
#define switchPin    2
#define LCD_REGSEL  12
#define LCD_EN      11
#define LCD_DATA4    10
#define LCD_DATA5    9
#define LCD_DATA6    8
#define LCD_DATA7    7
#define interruptNum 0
// call this a second
#define secondInMicros 1000000

// instantiate liquid crystal object using specified pins
LiquidCrystal lcd(LCD_REGSEL, LCD_EN, LCD_DATA4, LCD_DATA5, LCD_DATA6, LCD_DATA7);

// create variables used by the interrupts
volatile int resetTime = LOW;
volatile int queuedSeconds = 0;

// time data
int currentHours = 0;
int currentMinutes = 0;
int currentSeconds = 0;

// --------------------- SETUP ----------------------------
void setup() {
  // initialize lcd with 16 columns, 2 rows
  lcd.begin(16, 2);
  
  // configure switch
  pinMode(switchPin, INPUT_PULLUP);
  attachInterrupt(interruptNum, buttonISR, FALLING);
  
  Timer1.initialize(secondInMicros); // timer for 1 second
  Timer1.attachInterrupt(oneSecondISR);
}

// =================== SUPPORTING FUNCTIONS =====================

// ISR for reset button press, flags reset for high
void buttonISR() {
  resetTime = HIGH;
}

// service routine for the 1 second timer, adds a second to queue
void oneSecondISR() {
  queuedSeconds++;
}

// stuffs the time data into a string and refreshes the display with the time
void drawDisplay() {
  lcd.setCursor(0,0);
  char tempString[8];
  sprintf(tempString, "%02d:%02d:%02d", currentHours, currentMinutes, currentSeconds);
  lcd.print(tempString);
}

// adds seconds onto the current time data
// Assumption: it never gets passed more than 59 seconds. i.e. it only adds 1 minute tops
// NOTE: this functionality can be expanded if loop() ever gets really latent, but 
//   for now, it works just fine!
void addSeconds(int toAdd) {
  // if seconds buffer reached, add a minute and only add the remainder of seconds
  if ((currentSeconds + toAdd) > 59 ) {
    addMinutes(1);
    addSeconds(toAdd - 60); // recursive call
  }
  else // if this doesn't go over, just add it
    currentSeconds += toAdd;
}

// adds minutes to current time. assumes not more than an hour is passed
void addMinutes(int toAdd) {
  // if minutes buffer reached, add an hour and only add the remainder of minutes
  if ((currentMinutes + toAdd) > 59 ) {
    addHours(1);
    addMinutes(toAdd - 60);
  }
  else // otherwise, just add minutes on
    currentMinutes += toAdd;
}

// adds hours to current time
void addHours(int toAdd) {
  // if trying to add more than 23 hours, reset hours count
  if ((currentHours + toAdd) > 23 ) {
    currentHours = 0;
  }
  else
    currentHours += toAdd;
}

// --------------------------------- MAIN LOOP ---------------------------------
void loop() {
  // if a reset has happened, reset the clock
  if (resetTime == HIGH) {
    // reset all time data including the queue
    currentHours = 0;
    currentMinutes = 0;
    currentSeconds = 0;
    queuedSeconds = 0;
    // draw the display and reset the resetTime flag
    drawDisplay();
    resetTime = LOW;
  }
  else {
    // if we're not resetting this loop, check for new seconds
    if (queuedSeconds > 0) {
      // add new seconds onto the time
      addSeconds(queuedSeconds); // recursively adds additional minutes/hours
      queuedSeconds = 0; // reset the queued seconds
      drawDisplay();
    }
  }
  
}


