#include "lpc214x.h"

#define LED1 16
#define LED2 17
#define LED3 18
#define LED4 19

void led_on(int);
void led_off(int);
void delay_ms(unsigned char);
void gpio_init();

void led_on(int led)
{
	IO1SET |= (1<<led);
	return;
}

void led_off(int led)
{
	IO1CLR |= (1<<led);
	return;
}

void delay_ms(unsigned char j)
{
	unsigned int i;
	for(;j>0;j--)
		for(i = 0; i < 60000; i++);
	return;
}

void gpio_init()
{
	PINSEL0 = 0x00000000;
	PINSEL1 = 0x00000000;
	return;
}

int main()
{
	gpio_init();
	IO1DIR |= (1<<LED1) | (1<<LED2) | (1<<LED3) | (1<<LED4);

	while(1){
		led_on(LED1);
		delay_ms(10);
		led_off(LED1);
		led_on(LED2);
		delay_ms(10);
		led_off(LED2);
		led_on(LED3);
		delay_ms(10);
		led_off(LED3);
		led_on(LED4);
		delay_ms(10);
		led_off(LED4);
	}
	return 0;
}
