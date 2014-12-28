// new_roomba.cpp
//
// Modified from:
// Copyright (C) 2010 Mike McCauley
// $Id: Roomba.cpp,v 1.1 2010/09/27 21:58:32 mikem Exp mikem $

#include "new_roomba.h"

NewRoomba::NewRoomba(HardwareSerial* serial, Baud baud)
{
  _serial = serial;
  _baud = baudCodeToBaudRate(baud);
  _pollState = PollStateIdle;
}

// Resets the 
void NewRoomba::reset()
{
    _serial->write(7);
}

// Start OI
// Changes mode to passive
void NewRoomba::start()
{
    _serial->begin(_baud);
    passive();
}

uint32_t NewRoomba::baudCodeToBaudRate(Baud baud)
{
    switch (baud)
    {
	case Baud300:
	    return 300;
	case Baud600:
	    return 600;
	case Baud1200:
	    return 1200;
	case Baud2400:
	    return 2400;
	case Baud4800:
	    return 4800;
	case Baud9600:
	    return 9600;
	case Baud14400:
	    return 14400;
	case Baud19200:
	    return 19200;
	case Baud28800:
	    return 28800;
	case Baud38400:
	    return 38400;
	case Baud57600:
	    return 57600;
	case Baud115200:
	    return 115200;
	default:
	    return 57600;
    }
}

void NewRoomba::baud(Baud baud)
{
    _serial->write(129);
    _serial->write(baud);

    _baud = baudCodeToBaudRate(baud);
    _serial->begin(_baud);
}

// Changes mode to passive
void NewRoomba::passive()
{
    _serial->write(128); // same as starting
}

void NewRoomba::safeMode()
{
  _serial->write(131);
}

void NewRoomba::fullMode()
{
  _serial->write(132);
}

void NewRoomba::clean() {
  _serial->write(135);
}

void NewRoomba::maxClean() {
  _serial->write(136);
}

void NewRoomba::spotClean() {
  _serial->write(134);
}

void NewRoomba::dock()
{
  _serial->write(143);
}

// TODO implement scheduling, Opcode 167

// TODO implement date/time setting, Opcode 168

void NewRoomba::powerDown()
{
  _serial->write(133);
}

void NewRoomba::demo(Demo demo)
{
  _serial->write(136);
  _serial->write(demo);
}


void NewRoomba::drive(int16_t velocity, int16_t radius)
{
  _serial->write(137);
  _serial->write((velocity & 0xff00) >> 8);
  _serial->write(velocity & 0xff);
  _serial->write((radius & 0xff00) >> 8);
  _serial->write(radius & 0xff);
}

void NewRoomba::driveDirect(int16_t leftVelocity, int16_t rightVelocity)
{
  _serial->write(145);
  _serial->write((rightVelocity & 0xff00) >> 8);
  _serial->write(rightVelocity & 0xff);
  _serial->write((leftVelocity & 0xff00) >> 8);
  _serial->write(leftVelocity & 0xff);
}

// Sets PWM duty cycles on cleaning motors, see documentation
void NewRoomba::pwmCleaningMotors(uint8_t dutyCycle0, uint8_t dutyCycle1, uint8_t dutyCycle2)
{
  _serial->write(144);
  _serial->write(dutyCycle2);
  _serial->write(dutyCycle1);
  _serial->write(dutyCycle0);
}

// Sets cleaning motor outputs on or off, see documentation
void NewRoomba::cleaningMotors(uint8_t out)
{
  _serial->write(138);
  _serial->write(out);
}

void NewRoomba::leds(uint8_t leds, uint8_t powerColor, uint8_t powerIntensity)
{
  _serial->write(139);
  _serial->write(leds);
  _serial->write(powerColor);
  _serial->write(powerIntensity);
}


// TODO - SCHEDULING LEDS - OPCODE 162

// TODO - DIGIT LED'S RAW - OPCODE 163

// TODO - DIGIT LED'S ASCII - OPCODE 164

// TODO - BUTTONS - OPCODE 165, lets you push the buttons virtually


// Define a song
// Data is 2 bytes per note
void NewRoomba::song(uint8_t songNumber, const uint8_t* data, int len)
{
    _serial->write(140);
    _serial->write(songNumber);
    _serial->write(len >> 1); // 2 bytes per note
    _serial->write(data, len);
}

void NewRoomba::playSong(uint8_t songNumber)
{
  _serial->write(141);
  _serial->write(songNumber); 
}

// Start a stream of sensor data with the specified packet IDs in it
void NewRoomba::stream(const uint8_t* packetIDs, int len)
{
  _serial->write(148);
  _serial->write(packetIDs, len);
}

// One of StreamCommand*
void NewRoomba::streamCommand(StreamCommand command)
{
  _serial->write(150);
  _serial->write(command);
}


// Reads at most len bytes and stores them to dest
// If successful, returns true.
// If there is a timeout, returns false
// Blocks until all bytes are read
// Caller must ensure there is sufficient space in dest
bool NewRoomba::getData(uint8_t* dest, uint8_t len)
{
  while (len-- > 0)
  {
    unsigned long startTime = millis();
    while (!_serial->available())
    {
      // Look for a timeout
      if (millis() > startTime + ROOMBA_READ_TIMEOUT)
        return false; // Timed out
    }
    *dest++ = _serial->read();
  }
  return true;
}

bool NewRoomba::getSensors(uint8_t packetID, uint8_t* dest, uint8_t len)
{
  _serial->write(142);
  _serial->write(packetID);
  return getData(dest, len);
}

bool NewRoomba::getSensorsList(uint8_t* packetIDs, uint8_t numPacketIDs, uint8_t* dest, uint8_t len)
{
  _serial->write(149);
  _serial->write(numPacketIDs);
  _serial->write(packetIDs, numPacketIDs);
  return getData(dest, len);
}

// Simple state machine to read sensor data and discard everything else
bool NewRoomba::pollSensors(uint8_t* dest, uint8_t len)
{
    while (_serial->available())
    {
	uint8_t ch = _serial->read();
	switch (_pollState)
	{
	    case PollStateIdle:
		if (ch == 19)
		    _pollState = PollStateWaitCount;
		break;

	    case PollStateWaitCount:
		_pollChecksum = _pollSize = ch;
		_pollCount = 0;
		_pollState = PollStateWaitBytes;
		break;

	    case PollStateWaitBytes:
		_pollChecksum += ch;
		if (_pollCount < len)
		    dest[_pollCount] = ch;
		if (_pollCount++ >= _pollSize)
		    _pollState = PollStateWaitChecksum;
		break;

	    case PollStateWaitChecksum:
		_pollChecksum += ch;
		_pollState = PollStateIdle;
		return (_pollChecksum == 0);
		break;
	}
    }
    return false;
}
