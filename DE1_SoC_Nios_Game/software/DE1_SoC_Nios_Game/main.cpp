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

#define DEBUG_DUMP  /*printf */

#include <iostream>
#include <vector>

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

	return 0;
}



