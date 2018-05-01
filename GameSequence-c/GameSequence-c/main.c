/*
 * GameSequence-c.c
 *
 * Created: 17-Apr-18 10:34:25
 * Author : Shishir
 */ 

#define F_CPU 10000000L
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <time.h>
#include "atmega2560_drivers.h"

#define value 300

int c, b;
int n, r,v;								//b = no. of sequence n = random number
int user = 255;								//user is used for user input
int s[8];									//array of size 8
int *po;									//po used as pointer for int

int main(void)
{
	init_stdio(0, 10000000L);
	sei();

	DDRA = 0xff;

	n = rand() % 7;								// rand % 7 to generate no. between 0 to 7
	printf("\n ");
	
	welcome();
	_delay_ms(200);
	
	po = s;
	
	for (b = 1; b <= 8; b++)
	{
		printf("\nLevel %d : ", b);
		po = s;
		for(c = 0; c < b; c++)
		{
			n = randomnum();
			if (n > 7)
			{
				n = n - 7;
			}
			v = generate_sequ(n);
			printf("%d ", n);
			*po = v;
			po++;
		}
					
		po = s;
		for(c = 0 ; c < b ; c++)
		{
			v = user_input(*po);
			if(v == 0)
			{
				wrong();
			}
			_delay_ms(300);
			po++;
		}
		correct();
	}
	_delay_ms(1000);
	end();
}

int randomnum(){
	r = rand() % 7;							// rand % 7 to generate no. between 0 to 7
	n = n + r;
	if(n == 7){
		n = n-7;
	}
	return n;
	
}

int user_input(int input)
{
	user = 255;
	while (user == 255)						//waits until user inputs
	{
		n++;								//counter to generate the random number
		if (n == 7)
		{
			n = 0;
		}
		user = PINB;
	}
		if	(user == input)						//compares the value
		{
			return 1;
		}
		else
		{
			return 0;
		}
}

int generate_sequ(int number){
	if(number == 0){
		PORTA = 254;
		_delay_ms(1000);
	}else if (number == 1)
	{
		PORTA = 253;
		_delay_ms(1000);
	}
	else if (number == 2)
	{
		PORTA = 251;
		_delay_ms(1000);
	}
	else if (number == 3)
	{
		PORTA = 247;
		_delay_ms(1000);
	}
	else if (number == 4)
	{
		PORTA = 239;
		_delay_ms(1000);
	}
	else if (number == 5)
	{
		PORTA = 223;
		_delay_ms(1000);
	}else if (number == 6)
	{
		PORTA = 191;
		_delay_ms(1000);
	}else if (number == 7)
	{
		PORTA = 127;
		_delay_ms(1000);
	}
	v = PORTA;
	PORTA = 255;
	_delay_ms(200);
	return v;
}

int welcome()
{
	PORTA = 0b11100111;
	_delay_ms(value);
	PORTA = 0b11011011;
	_delay_ms(value);
	PORTA = 0b10111101;
	_delay_ms(value);
	PORTA = 0b01111110;
	_delay_ms(value);
	PORTA = 255;
}

int correct()
{
	PORTA = 126;
	_delay_ms(200);
	PORTA = 255;
	_delay_ms(200);
	PORTA = 126;
	_delay_ms(200);
	PORTA = 255;
	_delay_ms(200);
	PORTA = 126;
	_delay_ms(200);
	PORTA = 255;
}

int wrong()
{
	PORTA = (~240);
	_delay_ms(200);
	PORTA = (~15);
	_delay_ms(200);
	PORTA = (~240);
	_delay_ms(200);
	PORTA = (~15);
	_delay_ms(200);
	PORTA = 255;
	main();
}

int end(){
	PORTA = 0b01111110;
	_delay_ms(value);
	PORTA = 0b10111101;
	_delay_ms(value);
	PORTA = 0b11011011;
	_delay_ms(value);	
	PORTA = 0b11100111;
	_delay_ms(value);
	PORTA = 255;
	
	while(0 == 0){
		PORTA = 255;
	}
}