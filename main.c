/*********************************************************************************
 ** Project:			Air Support												**
 ** File:				main.c													**
 ** Version:			0.2														**
 ** 																			**
 ** Author:				David Meijer											**
 ** Date of creation:	08 Apr 2015	15:15										**
 ** Last modification:	09 Apr 2015	10:14										**
 **																				**
 ** Contents:	Main function for:												**
 ** 			- Sending commands to the APM 2.5 with the MAVLink protocol		**
 **				- Deciding what the APM 2.5 needs to execute					**
 ** 																			**
 **	Building:	gcc -Wall -o "%e" "%f" "Dronard/USBFunctions.c" 				**
 **				"Dronard/MAVLinkFunctions.c" -lwiringPi							**
 *********************************************************************************/

#include "main.h"

int DetectMAVLink(uint8_t *buffer, uint32_t bytes, mavlink_message_t *msg);
int DecodeMAVLinkMsg(mavlink_message_t msg);

int SendHeartbeat(int fd);
int SendCommand(int fd, mavlink_command_long_t command);

int main(void) {
	
	int APMdesc = 0;
	uint8_t data[MAVLINK_MAX_PACKET_LEN] = {0x00};
	uint16_t datalen = 0;
	mavlink_message_t msg;
	
	mavlink_command_long_t command;
	command.param1 = 0; //0 to disarm
	
	uint16_t idmsg = 0;

	APMdesc = OpenAPM();
	
	int i = 0;
	while(1){
		ReadData(APMdesc, &datalen, data);
		if (DetectMAVLink(data, datalen, &msg)) {
			idmsg = DecodeMAVLinkMsg(msg);
			if (idmsg == MAVLINK_MSG_ID_HEARTBEAT) {
				SendHeartbeat(APMdesc);
				if (i >= 10) {
					
					command.command			 = MAV_CMD_COMPONENT_ARM_DISARM;
					command.confirmation 	 = 0;
					command.target_component = MAV_COMP_ID_SYSTEM_CONTROL;
					command.target_system	 = 1;
					
					if(command.param1 == 0) {
						command.param1 = 1;
						printf("\nSending arm command...");
					} else {
						command.param1 = 0;
						printf("\nSending disarm command...");
					}
	
					SendCommand(APMdesc, command);
					i = 0;
				}
				i++;
			}
		}
	}
	 
	//Never reaches this
	CloseAPM(APMdesc);
	return 0;
}
