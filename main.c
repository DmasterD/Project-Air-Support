/*********************************************************************************
 ** Project:			Air Support												**
 ** File:				main.c													**
 ** Version:			0.2														**
 ** 																			**
 ** Author:				David Meijer											**
 ** Date of creation:	23 Apr 2015	13:45										**
 ** Last modification:	23 Apr 2015	13:47										**
 **																				**
 ** Contents:	Main function for:												**
 ** 			- Sending commands to the APM 2.5 with the MAVLink protocol		**
 **				- More to come...												**
 ** 																			**
 **	Building:	gcc -Wall -o "%e" "%f" "Dronard/USBFunctions.c" 				**
 **				"Dronard/MAVLinkFunctions.c" -lwiringPi							**
 *********************************************************************************/

#include "main.h"

int DetectMAVLink(int fd, uint8_t *buffer, uint32_t bytes, mavlink_message_t *msg);
int DecodeMAVLinkMsg(mavlink_message_t msg);

int SetMode(int fd, uint8_t mode);
int ReqDatastream(int fd, int streamid);
int TakeOffTest(int fd);

int main(void) {
	int APMdesc = 0;
	uint8_t data[MAVLINK_MAX_PACKET_LEN] = {0x00};
	uint16_t datalen = 0;
	mavlink_message_t msg;

	APMdesc = OpenAPM();
	
	int i = 0;
	while(1){
		ReadData(APMdesc, &datalen, data);
		if (DetectMAVLink(APMdesc, data, datalen, &msg)) {
			if (i == 40) {
				printf("\tSending data stream request from RC channels...\n");	
				ReqDatastream(APMdesc, MAVLINK_MSG_ID_RC_CHANNELS);
			}
			if (i == 50) {
				printf("\tSending arm command...\n");	
				SetMode(APMdesc, MAV_MODE_STABILIZE_ARMED);
			}
			if (i == 150) {
				printf("\tSending takeoff command...\n");
				TakeOffTest(APMdesc);	
			}
			if (i == 350) {
				printf("\tSending disarm command...\n");
				SetMode(APMdesc, MAV_MODE_STABILIZE_DISARMED);	
				break;
			}
			i++;
		}
	}
	 
	CloseAPM(APMdesc);
	return 0;
}
 
