
#include <Arduino.h>
#include "syslog.h"
#include "A1333.h"
#include "SPI.h"
#include <stdio.h>
#include "board.h" 


#define A1333_CMD_NOP   (0x0000)
#define A1333_ANG15		(0x3200)

SPISettings settingsA(500000, MSBFIRST, SPI_MODE3);             ///400000, MSBFIRST, SPI_MODE1);

boolean A1333::begin(int csPin)
{

	digitalWrite(PIN_AS5047D_CS,LOW); //pull CS LOW by default (chip powered off)
	digitalWrite(PIN_MOSI,LOW);
	digitalWrite(PIN_SCK,LOW);
	digitalWrite(PIN_MISO,LOW);
	pinMode(PIN_MISO,OUTPUT);
	delay(1000);


	digitalWrite(PIN_AS5047D_CS,HIGH); //pull CS high

	pinMode(PIN_MISO,INPUT);


	chipSelectPin=csPin;

	LOG("csPin is %d",csPin);
	pinMode(chipSelectPin,OUTPUT);
	digitalWrite(chipSelectPin,HIGH); //pull CS high by default
	delay(1);

	SPI.begin();    //AS5047D SPI uses mode=1 (CPOL=0, CPHA=1)

	LOG("Begin A1333...");

	LOG("Address is 0x%04X",readAddress(A1333_ANG15));
}


//read the encoders
int16_t A1333::readAddress(uint16_t addr)
{
	uint16_t data;
	//make sure it is a write by setting bit 14
	//addr=addr | 0x4000;

	SPI.beginTransaction(settingsA);
	digitalWrite(chipSelectPin, LOW);
	delayMicroseconds(1);
	//clock out the address to read
	//LOG("address 0x%04X",addr);
	SPI.transfer16(addr);
	digitalWrite(chipSelectPin, HIGH);
	delayMicroseconds(1);
	digitalWrite(chipSelectPin, LOW);
	//clock out zeros to read in the data from address
	data=SPI.transfer16(0x00);

	digitalWrite(chipSelectPin, HIGH);
	SPI.endTransaction();

	return data;
}

//read the encoders
int16_t A1333::readEncoderAngle(void)
{

	return readAddress(A1333_ANG15)>>1;
}

int16_t A1333::readEncoderAnglePipeLineRead(void)
{
	static bool first=true;
	uint16_t addr = A1333_ANG15;
	uint16_t addr2;
	uint16_t data;

	if (first)
	{
		//make sure it is a write by setting bit 14
		//addr2=addr | 0x4000;
		SPI.beginTransaction(settingsA);
		digitalWrite(chipSelectPin, LOW);
		delayMicroseconds(1);
		//clock out the address to read
		SPI.transfer16(addr);
		digitalWrite(chipSelectPin, HIGH);
		delayMicroseconds(1);
		digitalWrite(chipSelectPin, LOW);
		delayMicroseconds(1);
		//clock out zeros to read in the data from address
		data=SPI.transfer16(addr);

		digitalWrite(chipSelectPin, HIGH);
		SPI.endTransaction();
		first=false;
		return data>>1;
	}

	SPI.beginTransaction(settingsA);
	digitalWrite(chipSelectPin, LOW);
	delayMicroseconds(1);
	//clock out zeros to read in the data from address
	data=SPI.transfer16(addr);

	digitalWrite(chipSelectPin, HIGH);
	SPI.endTransaction();
	return data>>1;
}
