#define red    2
#define green  3
#define yellow 4
#define button 0

bool is_pressed;
int color;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  is_pressed = false;
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

void loop() {
  is_pressed = digitalRead(button);
  if(is_pressed == HIGH)
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
  delay(100);
  
  // put your main code here, to run repeatedly:
}
