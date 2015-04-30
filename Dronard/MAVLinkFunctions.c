#include "MAVLinkFunctions.h"
#include "USBFunctions.h"

int DecodeMAVLinkMsg(mavlink_message_t msg) {
	
	mavlink_heartbeat_t 					heart;
	mavlink_command_ack_t 					command_ack;
	mavlink_sys_status_t 					sys_status;
	mavlink_statustext_t					statustext;
	mavlink_vfr_hud_t						vfr_hud;
	mavlink_attitude_target_t 				attitude_target;
	mavlink_position_target_global_int_t 	position_target_global_int;
	mavlink_local_position_ned_t			local_position_ned;
	mavlink_highres_imu_t					highres_imu;
	mavlink_rc_channels_t					rc_channels;
	
	printf("[%03d]", msg.msgid);
	//Only show the following messages
	switch (msg.msgid) {
		case MAVLINK_MSG_ID_HEARTBEAT:
			break;
		case MAVLINK_MSG_ID_STATUSTEXT:
			break;
		case MAVLINK_MSG_ID_RC_CHANNELS:
			break;
		case MAVLINK_MSG_ID_HIGHRES_IMU:
			break;
		case MAVLINK_MSG_ID_SYS_STATUS:
			break;
			
		default:
			msg.msgid = -1;
			break;
	}
	
	switch (msg.msgid) {
		case MAVLINK_MSG_ID_HEARTBEAT: //0
			//decode heartbeat
			mavlink_msg_heartbeat_decode(&msg, &heart);
			
			//show result
			printf("\tHeartbeat! [pilot:%d type:%d] mode:%d mavlink:%d status:%d", 	heart.autopilot, 
																						heart.type, heart.base_mode, 
																						heart.mavlink_version, 
																						heart.system_status);
																							
			break;
			
		case MAVLINK_MSG_ID_COMMAND_ACK: //77
			//decode acknowledge
			mavlink_msg_command_ack_decode(&msg, &command_ack);
			
			//show result
			printf("\tAcknowledge! command:%d result:%d", command_ack.command, command_ack.result);
			break;
			
		case MAVLINK_MSG_ID_SYS_STATUS: //1
			//decode system status
			mavlink_msg_sys_status_decode(&msg, &sys_status);
			
			//show result
			printf("\tSystem Status!");
			
			printf("\n\t-Sensors present (bitmask): 0x%#04x", sys_status.onboard_control_sensors_present);
			printf("\n\t-Sensors enabled (bitmask): 0x%#04x", sys_status.onboard_control_sensors_enabled);
			printf("\n\t-Sensors health	(bitmask): 0x%#04x", sys_status.onboard_control_sensors_health);
			printf("\n\t-Load (0,1%%): %d", sys_status.load);
			printf("\n\t-Battery voltage (mV): %d", sys_status.voltage_battery);
			printf("\n\t-Battery current (10mA): %d", sys_status.current_battery);
			printf("\n\t-Drop rate communication (0,01%%): %d", sys_status.drop_rate_comm);
			printf("\n\t-Communication errors: %d", sys_status.errors_comm);
			printf("\n\t-Counting errors 1: %d", sys_status.errors_count1);
			printf("\n\t-Counting errors 2: %d", sys_status.errors_count2);
			printf("\n\t-Counting errors 3: %d", sys_status.errors_count3);
			printf("\n\t-Counting errors 4: %d", sys_status.errors_count4);
			printf("\n\t-Battery remaining (%%): %d", sys_status.battery_remaining);
			break;
			
		case MAVLINK_MSG_ID_STATUSTEXT: //253
			//decode status text
			mavlink_msg_statustext_decode(&msg, &statustext);
			
			//show result
			printf("\tStatus text!");
			
			printf("\n\t-Severity: %d", statustext.severity);
			printf("\n\t-Text: %s", statustext.text);
			break;
			
		case MAVLINK_MSG_ID_VFR_HUD: //74
			//decode visual flight rules hud
			mavlink_msg_vfr_hud_decode(&msg, &vfr_hud);
			
			//show result
			printf("\tVisual flight rules hud!");
			
			printf("\n\t-Airspeed: %f", vfr_hud.airspeed);
			printf("\n\t-Groundspeed: %f", vfr_hud.groundspeed);
			printf("\n\t-Altitude: %f", vfr_hud.alt);
			printf("\n\t-Climb: %f", vfr_hud.climb);
			printf("\n\t-Heading (deg): %d", vfr_hud.heading);
			printf("\n\t-Throttle (%%): %d", vfr_hud.throttle);
			break;
			
		case MAVLINK_MSG_ID_ATTITUDE_TARGET: //83 
			//decode attitude of target
			mavlink_msg_attitude_target_decode(&msg, &attitude_target);
			
			//show result
			printf("\tAttitude of target!");
			
			printf("\n\t-Time boot (ms): %d", attitude_target.time_boot_ms);
			printf("\n\t-Attitude quaternion w, x, y, z: %f %f %f %f", attitude_target.q[0], attitude_target.q[1], attitude_target.q[2], attitude_target.q[3]);
			printf("\n\t-Body roll rate (rad/s): %f", attitude_target.body_roll_rate);
			printf("\n\t-Body pitch rate (rad/s): %f", attitude_target.body_pitch_rate);
			printf("\n\t-Body yaw rate (rad/s): %f", attitude_target.body_yaw_rate);
			printf("\n\t-Thrust: %f", attitude_target.thrust);
			printf("\n\t-Type mask: %d", attitude_target.type_mask);
			break;
			
		case MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT: //87
			//decode position of target ???
			mavlink_msg_position_target_global_int_decode(&msg, &position_target_global_int);
			
			//show result
			printf("\tPosition of target!");
			
			printf("\n\t-Time boot (ms): %d", position_target_global_int.time_boot_ms);
			printf("\n\t-X position (1e7m): %d", position_target_global_int.lat_int);
			printf("\n\t-Y position (1e7m): %d", position_target_global_int.lon_int);
			printf("\n\t-Altitude: %f", position_target_global_int.alt);
			printf("\n\t-X velocity (m/s): %f", position_target_global_int.vx);
			printf("\n\t-Y velocity (m/s): %f", position_target_global_int.vy);
			printf("\n\t-Z velocity (m/s): %f", position_target_global_int.vz);
			printf("\n\t-X acceleration force (N): %f", position_target_global_int.afx);
			printf("\n\t-Y acceleration force (N): %f", position_target_global_int.afy);
			printf("\n\t-Z acceleration force (N): %f", position_target_global_int.afz);
			printf("\n\t-Yaw (rad): %f", position_target_global_int.yaw);
			printf("\n\t-Yaw rate (rad/s): %f", position_target_global_int.yaw_rate);
			printf("\n\t-Type mask: %d", position_target_global_int.type_mask);
			printf("\n\t-Coordinate frame: %d", position_target_global_int.coordinate_frame);
			break;
			
		case MAVLINK_MSG_ID_LOCAL_POSITION_NED: //32
			//decode local position
			mavlink_msg_local_position_ned_decode(&msg, &local_position_ned);
			
			//show result
			printf("\tLocal position!");
			
			printf("\n\t-Time boot (ms): %d", local_position_ned.time_boot_ms);
			printf("\n\t-X position: %f", local_position_ned.x);
			printf("\n\t-Y position: %f", local_position_ned.y);
			printf("\n\t-Z position: %f", local_position_ned.z);
			printf("\n\t-X speed: %f", local_position_ned.vx);
			printf("\n\t-Y speed: %f", local_position_ned.vy);
			printf("\n\t-Z speed: %f", local_position_ned.vz);
			break;
			
		case MAVLINK_MSG_ID_HIGHRES_IMU: //105
			//decode high resolution inertional measurement unit
			mavlink_msg_highres_imu_decode(&msg, &highres_imu);
			
			//show result
			printf("\tHigh resolution inertional measurement unit!");
			
			printf("\n\t-Timestamp (us): %lld", highres_imu.time_usec);
			printf("\n\t-X acceleration (m/ss): %f", highres_imu.xacc);
			printf("\n\t-Y acceleration (m/ss): %f", highres_imu.yacc);
			printf("\n\t-Z acceleration (m/ss): %f", highres_imu.zacc);
			printf("\n\t-Angular speed around X axis (rad/s): %f", highres_imu.xgyro);
			printf("\n\t-Angular speed around Y axis (rad/s): %f", highres_imu.ygyro);
			printf("\n\t-Angular speed around Z axis (rad/s): %f", highres_imu.zgyro);
			printf("\n\t-X magnetic field (1e-4T): %f", highres_imu.xmag);
			printf("\n\t-Y magnetic field (1e-4T): %f", highres_imu.ymag);
			printf("\n\t-Z magnetic field (1e-4T): %f", highres_imu.zmag);
			printf("\n\t-Absolute pressure (mbar): %f", highres_imu.abs_pressure);
			printf("\n\t-Differential pressure (mbar): %f", highres_imu.diff_pressure);
			printf("\n\t-Altitude from pressure (m?): %f", highres_imu.pressure_alt);
			printf("\n\t-Temperature (C): %f", highres_imu.temperature);
			printf("\n\t-Fields updated: 0x%#04x", highres_imu.fields_updated);
			break;
			
		case MAVLINK_MSG_ID_RC_CHANNELS: //65
			//decode RC channels message
			mavlink_msg_rc_channels_decode(&msg, &rc_channels);
			
			//show result
			printf("\tRC channels!");
			
			printf("\n\t-RC channel 5: %d", rc_channels.chan5_raw);
			printf("\n\t-RC channel 6: %d", rc_channels.chan6_raw);
			break;
			
		default:
			break;
	}
	printf("\n");
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

int SetMode(int fd, uint8_t mode) {
	mavlink_message_t msg;

	//create message
	mavlink_msg_set_mode_pack(	MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_PIXHAWK, &msg,
								1, mode, 0);
	
	uint8_t sendbytes[MAVLINK_MAX_PACKET_LEN] = {0x00};
	
	//compress & copy to buffer
	uint16_t packagelen = mavlink_msg_to_send_buffer(sendbytes, &msg);
	
	//send set mode
	SendData(fd, packagelen, sendbytes);
	
	return 0;
};

int ReqDatastream(int fd, int streamid) {
	mavlink_message_t msg;	
	mavlink_data_stream_t data_stream;
	
	data_stream.message_rate = 1; //1 Hz
	data_stream.stream_id = streamid;
	data_stream.on_off = 1;
	
	//create message
	mavlink_msg_data_stream_encode(MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_PIXHAWK, &msg, &data_stream);
	
	uint8_t sendbytes[MAVLINK_MAX_PACKET_LEN] = {0x00};
	
	//compress & copy to buffer
	uint16_t packagelen = mavlink_msg_to_send_buffer(sendbytes, &msg);
	
	//send heartbeat
	SendData(fd, packagelen, sendbytes);
	
	return 0;
};

int TakeOffTest(int fd) {
	mavlink_message_t msg;
	mavlink_command_long_t command_long;
	
	command_long.param1 = 0.1; 	//Minimum pitch in m/s
	command_long.param5 = 0;	//Latitude
	command_long.param6 = 0;	//Longitude
	command_long.param7 = 1;	//Altitude
	
	uint8_t sendbytes[MAVLINK_MAX_PACKET_LEN] = {0x00};
	
	//create message
	mavlink_msg_command_long_encode(MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_PIXHAWK, &msg, &command_long);
	
	//compress & copy to buffer
	uint16_t packagelen = mavlink_msg_to_send_buffer(sendbytes, &msg);
	
	//send heartbeat
	SendData(fd, packagelen, sendbytes);
	
	return 0;
};

int DetectMAVLink(int fd, uint8_t *buffer, uint32_t bytes, mavlink_message_t *p_msg) {

	mavlink_message_t msg;
	int idmsg = -1;

	int i = 0;
	bool detected = false;
	
	while (i < bytes) {
		if(mavlink_parse_char(MAVLINK_COMM_0,buffer[i], &msg, &status))
		{
			//printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d", msg.sysid, msg.compid, msg.len, msg.msgid);
			idmsg = DecodeMAVLinkMsg(msg);
			
			if (idmsg == MAVLINK_MSG_ID_HEARTBEAT) {
				SendHeartbeat(fd);
			}
			
			detected = true;
		} else {
			detected = false;
		}
		i++;
	}
	
	*p_msg = msg;
	
	return detected;
};
