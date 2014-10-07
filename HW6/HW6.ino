/*
        RBE 2001 A14
        HW6 Solution
        
    Author: Christopher Bove
    Date Finished: 10/7/2014
    
    Description:
      This program receives a TTL (0-5V square) waveform and calculates the average frequency of the waveform
      over that period of time. The frequency is then printed on the first line of an LCD display.
      The period is selectable through a pull-down pin at either 500ms or 100ms.
      
      
      * Pins for the LCD are configured and defined as seen below the imported libraries.
      
    Dependencies:
      * LiquidCrystal
      * TimerOne
      * stdio
    
    
    ANSWER TO EXTRA CREDIT QUESTION: 
      The lowest frequency that can be reasonably detected in 500ms is roughly 2Hz. At that frequency,
    the chip recieves approximately 1 interrupt per period. This allows a rough approximation to be made,
    of 2Hz, for the frequency of that signal.
      The lowest frequency for the 100ms period is 10Hz. Again, this would be 1 click per time period. 
      
    For both of these tests, it was experimentally determined, and the results make sense due to the
    averaging nature of the calculation. The board received too many interrupts for frequencies around
    1MHz to show the calculated frequency, so the range is approximately 2Hz to 870kHz.
    
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
// interrupt pins
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
volatile int periodState = SHORT_PERIOD; // to store period
volatile bool isPeriodChanged = true;    // flag for period changes
volatile long unsigned int queuedFreqCount = 0; // count of frequency rises
volatile unsigned int timeCount = 0;  // flag to process frequency
volatile int subCount = 0;   // count for 500ms period option

// --------------------- SETUP ----------------------------
void setup() {
  // initialize lcd with 16 columns, 2 rows
  lcd.begin(16, 2);
  // set static label "Hz" to display
  lcd.setCursor(14,0);
  lcd.print("Hz");
  lcd.setCursor(0,0);
  
  // configure switch for period
  pinMode(periodSelectPin, INPUT_PULLUP);
  attachInterrupt(selectInt, selectPeriodISR, CHANGE);
  
  // configure input for frequency
  pinMode(inputPin, INPUT);
  attachInterrupt(freqInt, freqISR, RISING); // trigger on rising edge
  
  // initialize the period to start - otherwise starting it low won't do anything
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
  isPeriodChanged = true; // flag change
  if (digitalRead(periodSelectPin) == HIGH)
    periodState = SHORT_PERIOD; // set to short period if pin is high
  else
    periodState = LONG_PERIOD; // set to long period if pin is low
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
      timeCount ++; // its been 500ms, update count and reset subcount
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
  // grab the newest time count, freq count, and period w/o interrupts
  noInterrupts();
  // use doubles and floats to get unfloored math
  double tempFreqCount = queuedFreqCount;
  float tempPeriod = periodState;
  timeCount = 0; // reset time count - it has been serviced
  queuedFreqCount = 0; // reset frequency count
  interrupts();
  // calculate the frequency
  return (1000.0*tempFreqCount)/tempPeriod; 
}

// draws the passed frequency to line 1
void drawFrequency(float toWrite) {
  lcd.print(toWrite); // print float
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
