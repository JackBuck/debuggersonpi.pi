/////////////////////////////////////////
//
// pi_spi.cpp
// Author: Luke Walker
//
/////////////////////////////////////////

#include "wiringPiSPI.h"
#include "pic_enums.h"
#include "pi_spi.h"
#include <cstdint>

/* For reference:
    int wiringPiSPISetup (int channel, int speed) ;
    int wiringPiSPIDataRW (int channel, unsigned char *data, int len) ;
*/

#define SPI_CHANNEL 0
#define SPI_TIMEOUT 100000

const uint16_t DONE = 0xFFFE;
const uint16_t DATA = 0xFFFD;
const uint16_t ERROR= 0xFFFC;

void init_spi() {
	//initialises channel 0 of spi with clock speed = 1MHz
	wiringPiSPISetupMode(SPI_CHANNEL, 1000000, 1);
}

EPicErr write_SPI_stall_DONE(uint8_t* send_buffer) {
        //Send command
        wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) send_buffer, 16); 

        //Wait for response
        EPicErr err = PIC_NONE;
        while(1) {
            //Read from SPI_LINK
            uint16_t receive_buffer;
            receive_buffer = 0;
            wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) &receive_buffer, 2);
                
            //If receive DONE, then respond with DONE, ending SPI comms
            if(receive_buffer == DONE) {
                send_buffer[0] = (uint8_t) (((uint16_t) DONE) >> 8);
                send_buffer[1] = (uint8_t) (((uint16_t) DONE) & 0x00FF);
                wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) send_buffer, 2);
                break;
            }
            if(receive_buffer == ERROR) {
                err = PIC_ERROR;
                break;
            }
        }       

    return err;
}

void write_SPI(uint8_t* send_buffer) {
        //Send command
        wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) send_buffer, 16);     
}

EPicErr Wait_Done() {
    
    EPicErr err = PIC_NONE;

        //Wait for response
        while(1) {
            //Read from SPI_LINK
            uint16_t receive_buffer;
            receive_buffer = 0;
            wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) &receive_buffer, 2);
                
            //If receive DONE, then respond with DONE, ending SPI comms
            if(receive_buffer == DONE) {
                uint8_t send_buffer[16];

                send_buffer[0] = (uint8_t) (((uint16_t) DONE) >> 8);
                send_buffer[1] = (uint8_t) (((uint16_t) DONE) & 0x00FF);
                wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) send_buffer, 2);
                break;
            }
            if(receive_buffer == ERROR) {
                err = PIC_ERROR;
                break;
            }
        }   

    return err;
}

EPicErr write_SPI_wait_DONE(uint8_t* send_buffer) {
        //Send command
        wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) send_buffer, 16); 

        //Wait for response
        uint32_t n = 0;
        EPicErr err = PIC_NONE;
        while(/*n++ < SPI_TIMEOUT*/1) {
            //Read from SPI_LINK
            uint16_t receive_buffer;
            receive_buffer = 0;
            wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) &receive_buffer, 2);
                
            //If receive DONE, then respond with DONE, ending SPI comms
            if(receive_buffer == DONE) {
                send_buffer[0] = (uint8_t) (((uint16_t) DONE) >> 8);
                send_buffer[1] = (uint8_t) (((uint16_t) DONE) & 0x00FF);
                wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) send_buffer, 2);
                break;
            }
            if(receive_buffer == ERROR) {
                err = PIC_ERROR;
                break;
            }
        }   

    return err;
}

EPicErr write_SPI_read_wait_DONE(uint8_t* send_buffer, uint16_t* receive_buffer, uint32_t length) {
        //Send command
        wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) send_buffer, 16); 

        //Wait for response
        uint32_t n = 0;
        uint16_t result = 0;
        EPicErr err = PIC_NONE;
        while(/*n++ < SPI_TIMEOUT*/1) {
            //Read from SPI_LINK
            uint16_t receive_value;
            receive_value = 0;
            wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) &receive_value, 2);
            
            //If receive DONE, then respond with DONE, ending SPI comms
            if(receive_value == DATA) {
                receive_value = 0;
                wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) &receive_buffer[0], length*2);
            }
            if(receive_value == DONE) {
                send_buffer[0] = (uint8_t) (((uint16_t) DONE) >> 8);
                send_buffer[1] = (uint8_t) (((uint16_t) DONE) & 0x00FF);
                wiringPiSPIDataRW(SPI_CHANNEL, (uint8_t*) send_buffer, 2);
                break;
            }
            if(receive_value == ERROR) {
                err = PIC_ERROR;
                break;
            }
        }     

    return err;
}

//helper function to fill up send buffer
void fill_buffer(uint8_t* buffer, uint16_t val0, uint16_t val1,uint16_t val2, uint16_t val3) {
    //Change orientation of bytes (MSB - LSB)
    buffer[0] = (uint8_t) (((uint16_t) val0) >> 8);
    buffer[1] = (uint8_t) (((uint16_t) val0) & 0x00FF);
    buffer[2] = (uint8_t) (((uint16_t) val1) >> 8);
    buffer[3] = (uint8_t) (((uint16_t) val1) & 0x00FF);
    buffer[4] = (uint8_t) (((uint16_t) val2) >> 8);
    buffer[5] = (uint8_t) (((uint16_t) val2) & 0x00FF);
    buffer[6] = (uint8_t) (((uint16_t) val3) >> 8);
    buffer[7] = (uint8_t) (((uint16_t) val3) & 0x00FF);
    for(int i=8;i<16;i++) buffer[i] = 0;
}

//GRABBER---------------------------------------------------------------------

    //Grabber commands
    EPicErr pic_open_grabber() {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) OPEN_GRABBER, 0, 0,0);

        //write command
        return write_SPI_wait_DONE(&send_buffer[0]);      
    }
    EPicErr pic_close_grabber() {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) CLOSE_GRABBER, 0, 0,0);

        //write command
        return write_SPI_wait_DONE(&send_buffer[0]);         
    }
	EPicErr pic_read_grabber(uint16_t* Result) {
    	uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
    	fill_buffer(&send_buffer[0], (uint16_t) READ_GRABBER, 1, 0,0);

        return write_SPI_read_wait_DONE(&send_buffer[0], Result, 1);
	}
            
//motor-----------------------------------------------------------------------

    //Motor Commands
    EPicErr pic_set_left_motor_speed(uint16_t speed, motor_direction_t direction) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        if(direction == MOT_FWD) fill_buffer(&send_buffer[0], (uint16_t) WRITE_MOTOR_LEFT_FWD, speed, 0,0);
        else                     fill_buffer(&send_buffer[0], (uint16_t) WRITE_MOTOR_LEFT_REV, speed, 0,0);       
        //write command
        return write_SPI_wait_DONE(&send_buffer[0]);      
    }
    EPicErr pic_set_right_motor_speed(uint16_t speed, motor_direction_t direction) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        if(direction == MOT_FWD) fill_buffer(&send_buffer[0], (uint16_t) WRITE_MOTOR_RIGHT_FWD, speed, 0,0);
        else                     fill_buffer(&send_buffer[0], (uint16_t) WRITE_MOTOR_RIGHT_REV, speed, 0,0);  

        //write command
        return write_SPI_wait_DONE(&send_buffer[0]);      
    }

//encoder----------------------------------------------------------------------

	EPicErr pic_read_encoder_left(uint16_t Reset, int32_t* Result) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_ECDR1_SUM, Reset, 0,0);

        int16_t result;
        EPicErr err = PIC_NONE;
        err = write_SPI_read_wait_DONE(&send_buffer[0], (uint16_t*) &result, 1);
        *Result = (int32_t) result;

        return err;
	}
	EPicErr pic_read_encoder_right(uint16_t Reset, int32_t* Result) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_ECDR2_SUM, Reset, 0,0);

        int16_t result;
        EPicErr err = PIC_NONE;
        err = write_SPI_read_wait_DONE(&send_buffer[0], (uint16_t*) &result, 1);
        *Result = (int32_t) result;

        return err;
	}

//compass----------------------------------------------------------------------

	EPicErr pic_read_compass(float* Result) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_COMP, 0, 0,0);

        uint16_t result;
        EPicErr err = PIC_NONE;
        err = write_SPI_read_wait_DONE(&send_buffer[0], &result, 1);
        *Result = (float) result;

        return err;
	}

//photosensors-----------------------------------------------------------------

	EPicErr pic_read_photosense1(uint16_t* buffer, uint16_t length, uint16_t clear) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_PSNS1, length, clear,0);

        return write_SPI_read_wait_DONE(&send_buffer[0], &buffer[0], length);
    }
	EPicErr pic_read_photosense2(uint16_t* buffer, uint16_t length, uint16_t clear) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_PSNS2, length, clear,0);

        return write_SPI_read_wait_DONE(&send_buffer[0], &buffer[0], length);
    }
	EPicErr pic_read_photosense3(float* buffer, uint16_t length, uint16_t clear) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_PSNS3, length, clear,0);

        //create receive buffer of uint16 values
        uint16_t* recbuf;
        recbuf = new uint16_t [length];

        if (write_SPI_read_wait_DONE(&send_buffer[0], (uint16_t*) &recbuf[0], length) == PIC_ERROR) return PIC_ERROR;

        //Fill float buffer with converted uint16_t buffer
        for(int i=0;i<length;i++) {
            buffer[i] = ((float) recbuf[i]) / 1024; //2^10 - max value of ADCs
        }

        //remove temporary buffer
        delete[] recbuf;

        return PIC_NONE;
    }
	EPicErr pic_read_photosense4(float* buffer, uint16_t length, uint16_t clear) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_PSNS4, length, clear,0);

        //create receive buffer of uint16 values
        uint16_t* recbuf;
        recbuf = new uint16_t [length];

        if(write_SPI_read_wait_DONE(&send_buffer[0], (uint16_t*) &recbuf[0], length) == PIC_ERROR) return PIC_ERROR;

        //Fill float buffer with converted uint16_t buffer
        for(int i=0;i<length;i++) {
            buffer[i] = ((float) recbuf[i]) / 1024; //2^10 - max value of ADCs
        }

        //remove temporary buffer
        delete[] recbuf;

        return PIC_NONE;
    }
	EPicErr pic_read_photosense5(float* buffer, uint16_t length, uint16_t clear) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_PSNS5, length, clear,0);

        //create receive buffer of uint16 values
        uint16_t* recbuf;
        recbuf = new uint16_t [length];

        if(write_SPI_read_wait_DONE(&send_buffer[0], (uint16_t*) &recbuf[0], length) == PIC_ERROR) return PIC_ERROR;

        //Fill float buffer with converted uint16_t buffer
        for(int i=0;i<length;i++) {
            buffer[i] = ((float) recbuf[i]) / 1024; //2^10 - max value of ADCs
        }

        //remove temporary buffer
        delete[] recbuf;

        return PIC_NONE;
    }
	EPicErr pic_read_photosense6(float* buffer, uint16_t length, uint16_t clear) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_PSNS6, length, clear,0);

        //create receive buffer of uint16 values
        uint16_t* recbuf;
        recbuf = new uint16_t [length];

        if(write_SPI_read_wait_DONE(&send_buffer[0], (uint16_t*) &recbuf[0], length) == PIC_ERROR) return PIC_ERROR;

        //Fill float buffer with converted uint16_t buffer
        for(int i=0;i<length;i++) {
            buffer[i] = ((float) recbuf[i]) / 1024; //2^10 - max value of ADCs
        }

        //remove temporary buffer
        delete[] recbuf;

        return PIC_NONE;
    }
	EPicErr pic_read_photosensecube(uint16_t* buffer, uint16_t length, uint16_t clear) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_PSNSCBE, length, clear,0);

        return write_SPI_read_wait_DONE(&send_buffer[0], &buffer[0], length);
    }
	EPicErr pic_read_photosensefront(uint16_t* buffer, uint16_t length, uint16_t clear) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_PSNSFNT, length, clear,0);

        return write_SPI_read_wait_DONE(&send_buffer[0], &buffer[0], length);
    }

//LED------------------------------------------------------------------------

	EPicErr pic_write_led(led_t mode, uint16_t period) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) WRITE_LED, (uint16_t) mode, period,0);

        //write command
        return write_SPI_wait_DONE(&send_buffer[0]); 	
	}

//Rooms-------------------------------------------------------------------------


    EPicErr pic_read_roomtype(ERoom* Result) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) READ_ROOM, 0, 0,0);

        uint16_t result;
        EPicErr err = PIC_NONE;
        err = write_SPI_read_wait_DONE(&send_buffer[0], &result, 1);
        *Result = (ERoom) result;

        return err;   
    }


//STATES--------------------------------------------------------------------------

    EPicErr pic_write_state(state_t state, condition_t termination, uint16_t termination_val, char stall) {
        uint8_t send_buffer[16]; //for 16-bits = 8 bytes

        //command word first
        fill_buffer(&send_buffer[0], (uint16_t) state, (uint16_t) termination, termination_val,0);

        if(stall) {
            return write_SPI_stall_DONE(&send_buffer[0]);
        } else {
            write_SPI(&send_buffer[0]);
            return PIC_NONE;
        }
    }