#define red    3
#define green  4
#define yellow 5
#define button 2
#define interruptNum 0

volatile bool state = false;
int color;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(interruptNum, buttonISR, CHANGE);
  
  color = red;
  
  // self test
  digitalWrite(red, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);              // wait for a second
  digitalWrite(green, HIGH);    // turn the LED off by making the voltage LOW
  delay(250);              // wait for a second
  digitalWrite(yellow, HIGH);    // turn the LED off by making the voltage LOW
  delay(250);              // wait for a second
  digitalWrite(red, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(250);              // wait for a second
  digitalWrite(green, LOW);    // turn the LED off by making the voltage LOW
  delay(250);              // wait for a second
  digitalWrite(yellow, LOW);    // turn the LED off by making the voltage LOW
  delay(250);              // wait for a second
  digitalWrite(red, HIGH);
}

void buttonISR() {
  switchColor();
  delay(250);
}

void switchColor() {
    switch(color)
    {
      case red:
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        color = green;
        break;
      case green:
        digitalWrite(yellow, HIGH);
        digitalWrite(green, LOW);
        color = yellow;
        break;
      case yellow:
        digitalWrite(red, HIGH);
        digitalWrite(yellow, LOW);
        color = red;
        break;
      default:
        color = green;
        digitalWrite(green,HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(red, LOW);
        break;
    }
}

void loop() {  
  // put your main code here, to run repeatedly:
}
