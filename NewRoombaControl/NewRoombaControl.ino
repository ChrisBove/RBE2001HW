#include "new_roomba.h"

NewRoomba roomba(&Serial1, NewRoomba::Baud115200);

unsigned int errors = 0;

void error(const char *m)
{
  Serial.print("Error: ");
  Serial.println(m);
  errors++;
}

void check(boolean t, const char *m)
{
  if (!t)
    error(m);
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  roomba.start();
  roomba.fullMode();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
