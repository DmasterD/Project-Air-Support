#ifndef _USBFUNCTIONS_H_
	#define _USBFUNCTIONS_H_
	
	#define BAUDRATE 	57600
	#define APMDEVICE 	"/dev/ttyUSB0"
	
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <wiringSerial.h>
	
	int OpenAPM(void);
	void CloseAPM(int fd);
	int ReadData(int fd, uint16_t *datalen, uint8_t *data);
	int SendData(int fd, uint16_t size, uint8_t *data);
	
#endif //_USBFUNCTIONS_H_
