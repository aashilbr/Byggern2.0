/*
 * external_memory.c
 *
 * Created: 02.09.2020 09:17:26
 * Author: andrschn
 */
#include "external_memory.h"
#include <avr/io.h>



#define MIN_DATA_NR 1
#define MAX_DATA_NR 2040

#define EXT_MEM ((volatile uint8_t *)(0x1800))
#define DATA_ADDRESS 0x1803

static uint16_t m_head = 3;
static uint16_t m_tail = 3;

void xmem_init(void){
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	m_head = 3;
	m_tail = 3;
}

void xmem_write(uint16_t addr, uint8_t data){
    EXT_MEM[addr] = data;
}


uint8_t xmem_read(uint16_t addr){
    return EXT_MEM[addr];
}

uint8_t xmem_save_movement(int8_t x_pos){
	if (m_head>=2048){
		return 1;
	}
	uint8_t data = (uint8_t)(x_pos);
	xmem_write(m_head++, data);
	return 0;
}

uint8_t xmem_load_movement(uint8_t *p_data){
	if (m_tail == m_head){
		return 1;
	}
	*p_data = xmem_read(m_tail++);
	return 0;
}

uint8_t xmem_check_storing_condition(uint32_t count, uint8_t sampling){
	if(count % sampling == 0
       && count / sampling < MAX_DATA_NR
       && count / sampling > MIN_DATA_NR
    ){
        return 1;
    }
	else {
        return 0;
    }
}
void xmem_reset_tail(void){
	m_tail = 3;
}