/////////////////////////////////////////
//
// pi_spi.h
// Author: Luke Walker
//
/////////////////////////////////////////

#ifndef PI_SPI_H
#define PI_SPI_H

#include <cstdint>
#include "EnumsHeader.h"

//SPI-------------------------------------------------------------------------

void init_spi();

//GRABBER---------------------------------------------------------------------

	typedef enum {
		GRAB_ERR = 0x00, GRAB_OPEN =0x01, GRAB_CLOSE =0x02, GRAB_UNKNOWN = 0x03 
	} grab_t;

    //Grabber commands
    EPicErr pic_open_grabber();
    EPicErr pic_close_grabber();
	EPicErr pic_read_grabber(uint16_t* Result);
            
//motor-----------------------------------------------------------------------

	typedef enum {
		MOT_REV = 0x00, MOT_FWD = 0x01
	} motor_direction_t;

    //Motor Commands
    EPicErr pic_set_left_motor_speed(uint16_t speed, motor_direction_t direction);
    EPicErr pic_set_right_motor_speed(uint16_t speed, motor_direction_t direction);

//encoder----------------------------------------------------------------------

	EPicErr pic_read_encoder_left(uint16_t Reset, int32_t* Result);
	EPicErr pic_read_encoder_right(uint16_t Reset, int32_t* Result);

//compass----------------------------------------------------------------------

	EPicErr pic_read_compass(float* Result);

//photosensors-----------------------------------------------------------------

	EPicErr pic_read_photosense1(uint16_t* buffer, uint16_t length, uint16_t clear);
	EPicErr pic_read_photosense2(uint16_t* buffer, uint16_t length, uint16_t clear);
	EPicErr pic_read_photosense3(float* buffer, uint16_t length, uint16_t clear);
	EPicErr pic_read_photosense4(float* buffer, uint16_t length, uint16_t clear);
	EPicErr pic_read_photosense5(float* buffer, uint16_t length, uint16_t clear);
	EPicErr pic_read_photosense6(float* buffer, uint16_t length, uint16_t clear);
	EPicErr pic_read_photosensecube(uint16_t* buffer, uint16_t length, uint16_t clear);
	EPicErr pic_read_photosensefront(uint16_t* buffer, uint16_t length, uint16_t clear);

//LED------------------------------------------------------------------------

	typedef enum {
		RED = 0x00, GREEN = 0x01, BLUE = 0x02, 
		FLASH_RED = 0x03, FLASH_GREEN = 0x04, FLASH_BLUE = 0x05,
		OFF = 0x06
	} led_t;

	EPicErr pic_write_led(led_t mode, uint16_t period);

//Rooms----------------------------------------------------------------------

	EPicErr pic_read_roomtype(ERoom* Result);

//STATES---------------------------------------------------------------------

	EPicErr pic_write_state(state_t state, condition_t termination, uint16_t termination_val, char stall);
	EPicErr Wait_Done();
#endif