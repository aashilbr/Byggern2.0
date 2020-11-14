/*
 * CAN.h
 *
 * Created: 30.09.2020 14:00:55
 *  Author: andrschn
 */

#include "MCP2515_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>


#ifndef CAN_H_
#define CAN_H_
/**
* Message:
* @ID A message ID of 11 bits.
* @length The length of the message.
* @data An array of 8 elements, containing the message data.
*/
typedef struct Message_s{
	uint8_t ID;
	uint8_t length;
	int8_t data[8];
}Message;

/**
* @brief Initializes CAN.
* @param [in] mode Operation mode of the CAN controller.
* @details Sets the operation mode and configures the CAN bus.
*/
uint8_t CAN_init(uint8_t mode);

/**
* @brief Sends a message over the CAN bus.
* @param [in] message A pointer to a Message object.
*/
void CAN_send_message(Message *message);

/**
* @brief Checks if transmisson buffer 0 is pending transmission.
* @return Returns 1 if the buffer is pending transmission, 0 otherwise.
*/
uint8_t CAN_transmit_request(void);
/**
* @brief Receives a message over the CAN bus.
* @param [in] message A pointer to a Message object. 
*/
void CAN_receive_message(Message *message);

void oled_easy_pid(void);

void oled_hard_pid(void);

int check_CAN_interrupt(void);

CAN_send_pos(int8_t x, int8_t y,uint8_t button );

#endif /* CAN_H_ */
