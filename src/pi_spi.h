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
    void pic_open_grabber();
    void pic_close_grabber();
	uint16_t pic_read_grabber();
            
//motor-----------------------------------------------------------------------

	typedef enum {
		MOT_REV = 0x00, MOT_FWD = 0x01
	} motor_direction_t;

    //Motor Commands
    void pic_set_left_motor_speed(uint16_t speed, motor_direction_t direction);
    void pic_set_right_motor_speed(uint16_t speed, motor_direction_t direction);
    int32_t pic_read_left_motor_speed();
	int32_t pic_read_right_motor_speed();

//encoder----------------------------------------------------------------------

	int32_t pic_read_encoder_left(uint16_t Reset);
	int32_t pic_read_encoder_right(uint16_t Reset);

//compass----------------------------------------------------------------------

	float pic_read_compass();

//photosensors-----------------------------------------------------------------

	void pic_read_photosense1(uint16_t* buffer, uint16_t length, uint16_t clear);
	void pic_read_photosense2(uint16_t* buffer, uint16_t length, uint16_t clear);
	void pic_read_photosense3(float* buffer, uint16_t length, uint16_t clear);
	void pic_read_photosense4(float* buffer, uint16_t length, uint16_t clear);
	void pic_read_photosense5(float* buffer, uint16_t length, uint16_t clear);
	void pic_read_photosense6(float* buffer, uint16_t length, uint16_t clear);
	void pic_read_photosensecube(uint16_t* buffer, uint16_t length, uint16_t clear);
	void pic_read_photosensefront(uint16_t* buffer, uint16_t length, uint16_t clear);

//LED------------------------------------------------------------------------

	typedef enum {
		RED = 0x00, GREEN = 0x01, BLUE = 0x02, 
		FLASH_RED = 0x03, FLASH_GREEN = 0x04, FLASH_BLUE = 0x05,
		OFF = 0x06
	} led_t;

	void pic_write_led(led_t mode, uint16_t period);

//Rooms----------------------------------------------------------------------

	ERoom pic_read_roomtype();

//STATES---------------------------------------------------------------------

	void pic_write_state(state_t state, condition_t termination, uint16_t termination_val, char stall);
	void Wait_Done();
#endif