/*********************************************************************************
 ** Project:			Air Support												**
 ** File:				main.c													**
 ** Version:			0.2														**
 ** 																			**
 ** Author:				David Meijer											**
 ** Date of creation:	08 Apr 2015	15:15										**
 ** Last modification:	16 Apr 2015	10:36										**
 **																				**
 ** Contents:	Main function for:												**
 ** 			- Sending commands to the APM 2.5 with the MAVLink protocol		**
 **				- Deciding what the APM 2.5 needs to execute					**
 ** 																			**
 **	Building:	gcc -Wall -o "%e" "%f" "Dronard/USBFunctions.c" 				**
 **				"Dronard/MAVLinkFunctions.c" -lwiringPi							**
 *********************************************************************************/

#include "main.h"

//Function prototypes that couldn't be put in the header file for some unknown reason
int DetectMAVLink(uint8_t *buffer, uint32_t bytes, mavlink_message_t *msg);
int DecodeMAVLinkMsg(mavlink_message_t msg);
int SendHeartbeat(int fd);
int SendCommand(int fd, mavlink_command_long_t command);

int main(void) {
	
	int APMdesc = 0; 				//File descriptor for APM
	uint8_t data[MAVLINK_MAX_PACKET_LEN] = {0x00};	//Data buffer for all MAVLink messages
	uint16_t datalen = 0;				//Stores length of data
	mavlink_message_t msg;				//The MAVLink message structure
	
	mavlink_command_long_t command;			//The MAVLink command structure
	command.param1 = 0; 				//Setting param1 to 0 to disarm
	
	uint16_t idmsg = 0;				//Will contain MAVLink msg ID

	//Opening APM and applying file descriptor to APMdesc
	APMdesc = OpenAPM();
	
	int i = 0;
	while(1){
		//Read buffer from USB port
		ReadData(APMdesc, &datalen, data);
		
		//Checking if a MAVLink package is complete and putting it into the message structure
		if (DetectMAVLink(data, datalen, &msg)) {
			
			//Decode MAVLink message and applying the message ID to idmsg
			idmsg = DecodeMAVLinkMsg(msg);
			
			//Send heartbeat back if heartbeat was received
			if (idmsg == MAVLINK_MSG_ID_HEARTBEAT) {
				SendHeartbeat(APMdesc);
				
				//Send arm or disarm command after 10 heartbeats
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
