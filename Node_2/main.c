/*
 * node_2.c
 *
 * Created: 07.10.2020 13:14:18
 * Author : andrschn
 */ 


#include "sam.h"
#include "uart.h"
#include "can_controller.h"
#include "timer.h"
//#include "can_interrupt.h"
#include "joystick.h"
#include "ir_signal.h"
#include "pingpong_states.h"
#include "motor_controller.h"
#include "pid.h"







int main(void)
{
	configure_uart();
	
    /* Initialize the SAM system */
    SystemInit();

	PIOA->PIO_OER = 0x1u <<20;
	
	PIOA->PIO_OER = 0x1u <<19;
	
	PIOA->PIO_PER = 0x1u<<0;
	PIOA->PIO_PER = 0x1u<<1;
	PIOA->PIO_SODR = 0x1u<<19;
	can_init_def_tx_rx_mb(0x00290561);
	pwm2_init();
	timer_init();
	adc_init();
	pid_init();
	//motor_init();
	
	//set_duty_cycle(7);
	CAN_MESSAGE m;
	
	
    while (1) 
    {	
		shoot(js_pos.shoot);
		pos_to_duty_cycle(-js_pos.y);
		//controller_speed(pid.u);
		printf("x: %d y: %d shoot:%d \n\r",js_pos.x,-js_pos.y,js_pos.shoot);
		printf("u: %d sum: %d last:%d \n\r",pid.u,pid.sum_error,pid.last_error);
		controller_speed(js_pos.x);
		printf("Encoder%d\n\r", read_encoder());
		count_score();
		
    }
}



