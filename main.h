#ifndef _MAIN_H_
	#define _MAIN_H_

	#include <wiringSerial.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <stdlib.h>
	
	#include "Dronard/MAVLink/ardupilotmega/mavlink.h"
	#include "Dronard/USBFunctions.h"
	#include "Dronard/MAVLinkFunctions.h"

	#define BAUDRATE 	115200
	#define APMDEVICE 	"/dev/ttyACM0"
					
	uint16_t packagesize 						= 0;			
	uint8_t readbytes[MAVLINK_MAX_PACKET_LEN] 	= {0x00};
	uint8_t heartbeat[17] 						= {0x00};
	
	mavlink_command_long_t command;

#endif //_MAIN_H_
