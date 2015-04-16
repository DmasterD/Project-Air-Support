#ifndef _MAVLINKFUNCTIONS_H_
	#define _MAVLINKFUNCTIONS_H_
	
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <wiringSerial.h>
	
	int OpenAPM(void);
	void CloseAPM(int fd);
	int ReadData(int fd, uint16_t *datalen, uint8_t *data);
	//int SendData(int fd, uint16_t size, uint8_t *data);
	
#endif //_MAVLINKFUNCTIONS_H_

int SendData(int fd, uint16_t size, uint8_t *data);
