#ifndef _MAVLINKFUNCTIONS_H_
	#define _MAVLINKFUNCTIONS_H_
	
	#include "MAVLink/pixhawk/mavlink.h"
	#include "USBFunctions.h"
	#include <stdio.h>
	#include <stdbool.h>
	
	mavlink_status_t status;
	
	uint8_t AIRSUPPORT_MAV_MODE 	= MAV_MODE_PREFLIGHT;
	uint8_t AIRSUPPORT_MAV_STATE 	= MAV_STATE_STANDBY;

	int DetectMAVLink(int fd, uint8_t *buffer, uint32_t bytes, mavlink_message_t *msg);
	int DecodeMAVLinkMsg(mavlink_message_t msg);
	int ReqDatastream(int fd, int streamid);
	int SetMode(int fd, uint8_t mode);
	int TakeOffTest(int fd);

#endif //_MAVLINKFUNCTIONS_H_
