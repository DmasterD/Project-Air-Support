#include "USBFunctions.h"

int OpenAPM(void){
	int fd;
	fd = serialOpen(APMDEVICE, BAUDRATE);
	
	if(fd == -1) {
		printf("Couldn't open APM device.\nError: %d", fd);
		exit(fd);
	}
	
	printf("Succesfully opened APM device.\n");

	return fd;
};

void CloseAPM(int fd){
	serialClose(fd);
};

int ReadData(int fd, uint16_t *datalen, uint8_t *data) {
	int packagesize = 0;
	int i = 0;
	
	//check for bytes to be read
	packagesize = serialDataAvail(fd);
	
	if (packagesize > 0) {
		while (i<packagesize) {
			data[i] = serialGetchar(fd);
			i++;
		}
	}
	
	*datalen = i;
	return 0;
};

int SendData(int fd, uint16_t size, uint8_t *data) {
	int i = 0;
	for(i=0; i<size; i++) {
		serialPutchar(fd, *(data+i));
	}
	return 0;
};
