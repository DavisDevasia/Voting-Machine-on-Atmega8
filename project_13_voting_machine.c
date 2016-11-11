/*
 * project_13_voting_machine.c
 *
 * Created: 02-06-2015 20:44:25
 *  Author: Davis
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <lcd/abc.h>
#include <lcd/abc.c>


int main(void)
{
    DDRD=0xff;
	DDRB=0xff;
	DDRC=0;
	char a=0,b=0,c=0,d=0;
	char w[]="WINNER";
	lcd_init(LCD_DISP_ON);
	while(1)
	{
		int s[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x58,0x5E,0x79,0x71,0x40};
		if(!(PINC&0x01)){PORTB=s[16];lcd_gotoxy(0,0);lcd_puts("Voting machine!");lcd_gotoxy(0,1);lcd_puts("Pls authenticate");}
		else
		{
			lcd_clrscr();
			while(PINC&0x01)
			{	
			PORTB=s[0];lcd_gotoxy(0,0);lcd_puts("Vote now....   ");lcd_gotoxy(0,1);lcd_puts("           ");
			if(PINC&0x02){a++;if(a>9)a=9;PORTB=s[a];lcd_clrscr();lcd_puts("You have voted!");lcd_gotoxy(0,1);lcd_puts("CANDIDATE A");PORTB=PORTB+0x80;_delay_ms(1000);}
			if(PINC&0x04){b++;if(b>9)b=9;PORTB=s[b];lcd_clrscr();lcd_puts("You have voted!");lcd_gotoxy(0,1);lcd_puts("CANDIDATE B");PORTB=PORTB+0x80;_delay_ms(1000);}
			if(PINC&0x08){c++;if(c>9)c=9;PORTB=s[c];lcd_clrscr();lcd_puts("You have voted!");lcd_gotoxy(0,1);lcd_puts("CANDIDATE C");PORTB=PORTB+0x80;_delay_ms(1000);}
			while(PINC&0x0E);
			if(PORTB&0x80)PORTB=PORTB-0x80;
			}
		}
		if(PINC&0x02 || PINC&0x04 || PINC&0x08)
		{
			lcd_clrscr();lcd_puts("Error!");lcd_gotoxy(0,1);lcd_puts("PCO not closed!!");
			while(PINC&0x0E);
			lcd_clrscr();
		}
		if(PINC&0x10)
		{
			if(a>b && a>c){strcpy(w,"A WINS!!!");d=a;}
			else if(b>a && b>c){strcpy(w,"B WINS!!!");d=b;}
			else if(c>a && c>b){strcpy(w,"C WINS!!!");d=c;}
			else if(a==b && a!=c){strcpy(w,"A and B TIE!!!");d=16;}
			else if(c==b && c!=a){strcpy(w,"B and C TIE!!!");d=16;}
			else if(a==c && c!=b){strcpy(w,"A and C TIE!!!");d=16;}
			else {strcpy(w,"A, B and C TIE!!");d=16;}
			lcd_clrscr();lcd_puts("Result:");lcd_gotoxy(0,1);lcd_puts(w);PORTB=s[d];
			_delay_ms(3000);
			while(PINC&0x10);
			a=b=c=0;
		}
	}
}