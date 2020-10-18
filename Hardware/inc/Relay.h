#ifndef __relay_H
#define __relay_H	

void relay_init(void);
void relay_on(void);
void relay_off(void);
void relay_on2(void);
void relay_off2(void);


typedef enum
{

	OFF = 0,
	ON = 1

} RELAY_ENUM;

void relay_set(RELAY_ENUM status);
void Pin_value(void);
#endif
