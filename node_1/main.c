 #include <avr/io.h>
 #include "uart.h"
 #include "external_memory.h"
 #include <stdio.h>
 #include "sram_test.h"
 #include "pwm_clock.h"

#include "adc.h"
#include "oled.h"
#include "mcu.h"
#include "menu.h"
#include "tictactoe.h"
#include "SPI.h"
#include "MCP2515_driver.h"
#include "CAN.h"
#include "pingpong.h"
#include "timer.h"

#define F_CPU 4915200
#include <util/delay.h>

#include <avr/pgmspace.h>



Grid_state game_board[]={NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE};


int main(void){
	UART_Init(MYUBRR);
	xmem_init();
	pwm_init();
	mcu_init();
	oled_init();
	SPI_master_init();
	CAN_init(MODE_NORMAL);
	timer_init();
	printf("Heidu");
	//SRAM_test();
	oled_clear_all();
	adc_calibrate_joystick(&joystick);
	state current_state;
	current_state.current_node=menu_root_node();
	menu_init(&current_state);
	adc_calibrate_joystick(&joystick);

	while(1){

		adc_joystick_pos(&joystick);
		oled_navigate(adc_joystick_dir(&joystick), &current_state);

	}
 	return 0;
}
