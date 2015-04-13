#include "MAVLinkFunctions.h"
#include "USBFunctions.h"

int DetectMAVLink(uint8_t *buffer, uint32_t bytes, mavlink_message_t *msgg) {

	mavlink_message_t msg;

	int i = 0;
	bool detected = false;
	
	while (i < bytes) {
		if(mavlink_parse_char(MAVLINK_COMM_0,buffer[i], &msg, &status))
		{
			printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d", msg.sysid, msg.compid, msg.len, msg.msgid);
			detected = true;
		} else {
			detected = false;
		}
		i++;
	}
	
	*msgg = msg;
	
	return detected;
};

int DecodeMAVLinkMsg(mavlink_message_t msg) {
	
	mavlink_heartbeat_t 	heart;
	mavlink_command_ack_t 	command_ack;
	mavlink_sys_status_t 	sys_status; 
	
	switch (msg.msgid) {
		case MAVLINK_MSG_ID_HEARTBEAT:
			//decode heartbeat
			mavlink_msg_heartbeat_decode(&msg, &heart);
			
			//show result
			printf("\n[%d] Heartbeat! [pilot:%d type:%d] mode:%d mavlink:%d status:%d\n", 	msg.msgid, heart.autopilot, 
																							heart.type, heart.base_mode, 
																							heart.mavlink_version, 
																							heart.system_status);
			break;
			
		case MAVLINK_MSG_ID_COMMAND_ACK:
			//decode acknowledge
			mavlink_msg_command_ack_decode(&msg, &command_ack);
			
			//show result
			printf("\n[%d] Acknowledge! command:%d result:%d\n", msg.msgid, command_ack.command, command_ack.result);
			break;
			
		case MAVLINK_MSG_ID_SYS_STATUS:
			//decode system status
			mavlink_msg_sys_status_decode(&msg, &sys_status);
			
			//show result
			printf("\n[%d] System Status!", msg.msgid);
			printf("\n\tSensors present: %d", sys_status.onboard_control_sensors_present);
			printf("\n\tSensors enabled: %d", sys_status.onboard_control_sensors_enabled);
			printf("\n\tSensors health: %d", sys_status.onboard_control_sensors_health);
			printf("\n\tLoad: %d", sys_status.load);
			printf("\n\tBattery voltage: %d", sys_status.voltage_battery);
			printf("\n\tBattery current: %d", sys_status.current_battery);
			printf("\n\tDrop rate communication: %d", sys_status.drop_rate_comm);
			printf("\n\tCommunication errors: %d", sys_status.errors_comm);
			printf("\n\tCounting errors 1: %d", sys_status.errors_count1);
			printf("\n\tCounting errors 2: %d", sys_status.errors_count2);
			printf("\n\tCounting errors 3: %d", sys_status.errors_count3);
			printf("\n\tCounting errors 4: %d", sys_status.errors_count4);
			printf("\n\tBattery remaining: %d", sys_status.battery_remaining);
			break;
			
		case MAVLINK_MSG_ID_STATUSTEXT: //253
			//decode status text
			mavlink_msg_statustext_decode(&msg, &statustext);
			
			//show result
			printf("\n[%d] Status text!", msg.msgid);
			
			printf("\n\tSeverity: %d", statustext.severity);
			printf("\n\tText: %s", statustext.text);
			
			break;
			
		default:
			printf("\n[%d] Not decoded... \n", msg.msgid);
			break;
	}
	return msg.msgid;
};

int SendHeartbeat(int fd) {
	mavlink_message_t msg;
	
	uint8_t heartbeat[17] = {0x00};		//hearbeat contains 17 bytes
	
	//create heartbeat message
	mavlink_msg_heartbeat_pack(	MAV_TYPE_GCS, MAV_AUTOPILOT_INVALID, &msg,
								MAV_TYPE_GCS, MAV_AUTOPILOT_INVALID,
								AIRSUPPORT_MAV_MODE, 0, AIRSUPPORT_MAV_STATE);
								
	//compress & copy to buffer
	uint16_t heartbeatlen = mavlink_msg_to_send_buffer(heartbeat, &msg);
	
	//send heartbeat
	SendData(fd, heartbeatlen, heartbeat);
	
	return 0;
};

int SendCommand(int fd, mavlink_command_long_t command) {
	mavlink_message_t msg;
	
	uint8_t sendbytes[MAVLINK_MAX_PACKET_LEN] = {0x00};
	
	//create message
	mavlink_msg_command_long_encode(MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_ARDUPILOTMEGA, &msg, &command);
	
	//compress & copy to buffer
	uint16_t packagelen = mavlink_msg_to_send_buffer(sendbytes, &msg);
	
	//send command
	SendData(fd, packagelen, sendbytes);
	
	return 0;
};
