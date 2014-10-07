/*
        RBE 2001 A14
        HW6 Solution
        
    Author: Christopher Bove
    Date Finished: 10/6/2014
    
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
#define periodSelectPin  3
#define inputPin     2
#define LCD_REGSEL   12
#define LCD_EN       11
#define LCD_DATA4    10
#define LCD_DATA5    9
#define LCD_DATA6    8
#define LCD_DATA7    7
#define freqInt      0
#define selectInt    1

// this is 100ms in microseconds
#define timerTime 100000
// this is for defining period in ms
#define SHORT_PERIOD  100
#define LONG_PERIOD   500

// instantiate liquid crystal object using specified pins
LiquidCrystal lcd(LCD_REGSEL, LCD_EN, LCD_DATA4, LCD_DATA5, LCD_DATA6, LCD_DATA7);

// create variables used by the interrupts
volatile int periodState = SHORT_PERIOD;
volatile bool isPeriodChanged = true;
volatile long unsigned int queuedFreqCount = 0;
volatile unsigned int timeCount = 0;
volatile int subCount = 0;

// --------------------- SETUP ----------------------------
void setup() {
  // initialize lcd with 16 columns, 2 rows
  lcd.begin(16, 2);
  
  // configure switch
  pinMode(periodSelectPin, INPUT_PULLUP);
  attachInterrupt(selectInt, selectPeriodISR, CHANGE);
  
  // configure input
  pinMode(inputPin, INPUT);
  attachInterrupt(freqInt, freqISR, RISING);
  
  // initialize period to start
  selectPeriodISR();
  
  // configure timer
  Timer1.initialize(timerTime); // timer for 100msecond
  Timer1.attachInterrupt(timerISR);
}

// =================== INTERRUPT SERVICE ROUTINES =====================

// ISR for frequency inputs, increases queued frquencies
void freqISR() {
  queuedFreqCount ++;
}

// ISR for switching the period
void selectPeriodISR() {
  isPeriodChanged = true;
  if (digitalRead(periodSelectPin) == HIGH)
    periodState = SHORT_PERIOD;
  else
    periodState = LONG_PERIOD;
}

// service routine for the 100msecond timer
void timerISR() {
  // if we're counting short 100ms periods, count each callback
  if (periodState == SHORT_PERIOD) {
    timeCount ++;
  }
  else { // 100, 200, 300, 400, 500
    // otherwise, just count every five to get 500ms counts
    if(subCount >= 4) {
      timeCount ++;
      subCount = 0;
    }
    else
      subCount ++;
  }
}

// ----------------------- SUPPORTING FUNCTIONS ---------------------------

// stuffs the period into a string and refreshes the displaye
void drawPeriodStats() {
  lcd.setCursor(0,1);      // put cursor on second line
  char tempString[15];
  // quickly save the current period w/o getting interrupted
  noInterrupts();
  int temp = periodState;
  interrupts();
  // convert to a nice string
  sprintf(tempString, "Period: %3d ms", temp);
  lcd.print(tempString); // print string
  lcd.setCursor(0,0);    // return cursor to first line
}

// returns float of the calculated frequency of the signal
float calcFreq() {
  // grab the newest time count, freq count, and period
  noInterrupts();
  float tempTimeCount = timeCount;
  double tempFreqCount = queuedFreqCount;
  float tempPeriod = periodState;
  timeCount = 0; // reset time count - it has been serviced
  queuedFreqCount = 0; // reset frequency count
  interrupts();
  // period = counts/1000, avgT = counts/period, f = 1/T
  return (1000.0*tempFreqCount)/tempPeriod; //1.0/(tempTimeCount/(1000*tempPeriod)); 
}

// draws the passed frequency to line 1
void drawFrequency(float toWrite) {
  char tempString[17];
  // convert to a nice string
  sprintf(tempString, "Hz: %1.2f", toWrite);//toWrite);
  lcd.print(toWrite); // print string
  lcd.setCursor(14,0);
  lcd.print("Hz");
  lcd.setCursor(0,0);
}

// checks if the period stats need to be refreshed
void checkPeriodSelect() {
  if (isPeriodChanged)
    drawPeriodStats();
}

// checks if timer events have occurred
void checkTimerCount() {
  // if any time has passed, its time to calculate the frequency for this run
  if(timeCount > 0){
    drawFrequency(calcFreq());
  }
}

// --------------------------------- MAIN LOOP ---------------------------------
void loop() {
  // check if the period has changed, and if so update display
  checkPeriodSelect();
  // check if we have new ms, and if so calc freq. and update display
  checkTimerCount();

}
