/*
 * interrupt.c
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include "can_interrupt.h"

#include <stdio.h>
#include "sam.h"
#include "timer.h"
#include "printf-stdarg.h"
#include "pingpong_states.h"
#include "can_controller.h"
#include "joystick.h"
#include "motor_controller.h"
#define DEBUG_INTERRUPT 1

/**
 * \brief CAN0 Interrupt handler for RX, TX and bus error interrupts
 *
 * \param void
 *
 * \retval 
 */
void CAN0_Handler( void )
{
	if(DEBUG_INTERRUPT);//printf("CAN0 interrupt\n\r")
	char can_sr = CAN0->CAN_SR; 

	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2) )//Only mailbox 1 and 2 specified for receiving
	{
		CAN_MESSAGE message;
		if(can_sr & CAN_SR_MB1)  //Mailbox 1 event
		{	
			can_receive(&message,1);
			if(message.id==101){
				motor_init();
				init_ppstate();
				pid_error_init();
			}
			if(message.id==4){
				set_pid_difficulty(message.data[0]);
			}
			else{
				js_pos.x =message.data[0];
				js_pos.y = message.data[1];
				js_pos.shoot = message.data[2];
			}
		}
		else if(can_sr & CAN_SR_MB2) //Mailbox 2 event
		{	can_receive(&message,2);
			if(message.id==101){
				motor_init();
				init_ppstate();
				pid_error_init();
			}
			if(message.id==4){
				set_pid_difficulty(message.data[0]);
			}
			else{
				js_pos.x =message.data[0];
				js_pos.y = message.data[1];
				js_pos.shoot = message.data[2];
				
								
			}
			
		}
		else{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}
//
		//if(DEBUG_INTERRUPT);//printf("message id: %d\n\r", message.id)
		//if(DEBUG_INTERRUPT);//printf("message data length: %d\n\r", message.data_length)
		//for (int i = 0; i < message.data_length; i++)
		//{
			//if(DEBUG_INTERRUPT)printf("%d ", message.data[i]);
		
		//if(DEBUG_INTERRUPT)printf("\n\r");
	}
	
	if(can_sr & CAN_SR_MB0)
	{
		if(DEBUG_INTERRUPT) ;//printf("CAN0 MB0 ready to send \n\r")
		
	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;

	}

	if(can_sr & CAN_SR_ERRP)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}
	
	NVIC_ClearPendingIRQ(ID_CAN0);
	//sei();*/
}
