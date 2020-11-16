
/**
* @file node_1/CAN.h
* @author andrschn
* @date 30.09.2020 14:00:55
* @brief For CAN communication
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


/**
* @brief Setting the pid factors to the best tuning -->easy mode
* @details Sends a CAN message with the
* specified message content for the easy pid setting
*/
void oled_easy_pid(void);

/**
* @brief Setting the pid factors to the best tuning -->hard mode
* @details Sends a CAN message with the
* specified message content for the hard pid setting
*/
void oled_hard_pid(void);

/**
* @brief Checks if the CAN interrupt flag is set
* @return Returns 1 if the flag is set and 0 if not
*/
int check_CAN_interrupt(void);

/**
* @brief Sends a position and button information over the CAN bus
* @param [in] x x-position
* @param [in] y y-position
* @param [in] button the button state, 1 for pressed
*/
void CAN_send_pos(int8_t x, int8_t y,uint8_t button );

#endif /* CAN_H_ */
