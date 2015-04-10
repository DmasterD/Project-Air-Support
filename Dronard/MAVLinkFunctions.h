#ifndef _MAVLINKFUNCTIONS_H_
	#define _MAVLINKFUNCTIONS_H_
	
	#include "MAVLink/ardupilotmega/mavlink.h"
	#include "USBFunctions.h"
	#include <stdio.h>
	#include <stdbool.h>
	
	mavlink_status_t status;
	
	uint8_t AIRSUPPORT_MAV_MODE 	= MAV_MODE_PREFLIGHT;
	uint8_t AIRSUPPORT_MAV_STATE 	= MAV_STATE_STANDBY;

	int DetectMAVLink(uint8_t *buffer, uint32_t bytes, mavlink_message_t *msg);
	int DecodeMAVLinkMsg(mavlink_message_t msg);
	int SendCommand(int fd, mavlink_command_long_t command);

#endif //_MAVLINKFUNCTIONS_H_
