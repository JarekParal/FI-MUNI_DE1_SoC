/*
 * main.cpp
 *
 *  Created on: 6 Feb 2018
 *      Author: JarekParal
 */

#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h>
#include <stddef.h>
#include <unistd.h>  // usleep (unix standard?)
#include "sys/alt_flash.h"
#include "sys/alt_flash_types.h"
#include "io.h"
#include "alt_types.h"  // alt_u32
//#include "altera_avalon_pio_regs.h" //IOWR_ALTERA_AVALON_PIO_DATA
#include "sys/alt_irq.h"  // interrupt
#include "sys/alt_alarm.h" // time tick function (alt_nticks(), alt_ticks_per_second())
#include "sys/alt_timestamp.h"
#include "sys/alt_stdio.h"
#include "system.h"
#include <fcntl.h>
//#include "debug.h"



#include "altera_up_avalon_ps2.h"
#include "altera_up_ps2_keyboard.h"

#include "altera_up_avalon_video_character_buffer_with_dma.h"

#define DEBUG_DUMP  /*printf */

#include <iostream>
#include <vector>

KB_CODE_TYPE *decode_mode;
alt_u8 buf;
char ascii;
int result = -1;
int main()
{
	printf("===== Hello world =====\r\n");
	std::vector<int> vec{1,2,4,8,16,32};
	std::cout << "hello " << vec[0]  << std::endl;
	for(int i : vec) {
		std::cout << i << std::endl;
	}

	alt_up_ps2_dev *ps2;
	ps2 = alt_up_ps2_open_dev("/dev/ps2_0");
	//(*ps2).device_type = PS2_UNKNOWN;
	alt_up_ps2_init(ps2);
	printf("Detected device: %d\n",ps2->device_type);

	if((*ps2).device_type == PS2_MOUSE)
		std::cout << "PS2_MOUSE" << std::endl;
	else if((*ps2).device_type == PS2_KEYBOARD)
		std::cout << "PS2_KEYBOARD" << std::endl;
	else if((*ps2).device_type == PS2_UNKNOWN)
		std::cout << "PS2_UNKNOWN" << std::endl;
	else
		std::cout << "PS2 ERROR" << std::endl;

	alt_u8 Status,ButtonStatus;
	const alt_u8 ButtonMask = 0x0F; // 4 button

	alt_up_char_buffer_dev* char_buf;
	char_buf = alt_up_char_buffer_open_dev("/dev/video_character_buffer_with_dma_0");
	if(char_buf == NULL) {
		std::cout << "NULL" << std::endl;
	} else {
		std::cout << "NOT NULL" << std::endl;
		std::cout << "x_resolution: " << (char_buf)->x_resolution << std::endl;
		std::cout << "y_resolution: " << (char_buf)->y_resolution << std::endl;
		std::cout << "NOT NULL" << std::endl;
	}

	result = alt_up_char_buffer_clear(char_buf);
	std::cout << "char_buf: " << result << std::endl;

	result = alt_up_char_buffer_draw(char_buf, 'A', 0, 0);
	std::cout << "char_buf: " << result << std::endl;

	while (1)
    {
        usleep(1000*1000);
//		decode_scancode(ps2,decode_mode,static_cast<alt_u8 *>(&buf),&ascii);
//        if (*decode_mode != 6)
//            printf("Decode mode: %d Buffer: 0x%X ASCII: %c\n",*decode_mode,buf,ascii);

        ButtonStatus = IORD(KEY_BASE, 0);
        if ((ButtonStatus & 0x01) == 0x00){
        	std::cout << "KEY1 is pressed" << std::endl;
        } else {
        	std::cout << "KEY1 is not pressed" << std::endl;

        }

    }

	return 0;
}



