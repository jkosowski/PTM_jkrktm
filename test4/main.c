 /*    Keil project example for HD44780 LCD driver
 *
 *    @author     Tilen Majerle
 *    @email        tilen@majerle.eu
 *    @website    http://stm32f4-discovery.com
 *    @ide        Keil uVision 5
 */
#include "tm_stm32f4_button.h"
#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"
#include "tm_stm32f4_hcsr04.h"
#include "string.h"

//#include "stdio.h"
#include "math.h"

void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}
int poww(int x, unsigned int y)
{
  if (y == 0) return 1;
  if (y == 1) return x;
  int a = y / 2;
  int xa = poww(x, a);
  if (a + a == y) // y even
    return xa * xa;
  else
    return xa * xa * x;
}

void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * poww(afterpoint,10);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

void BUTTON1_EventHandler(TM_BUTTON_PressType_t type);


int opcja=0;
int main(void) {

    SystemInit();

    //Initialize LCD 20 cols x 4 rows
    TM_HD44780_Init(16, 2);
    TM_HD44780_Clear();

    TM_BUTTON_Init(GPIOA, GPIO_Pin_0, 1, BUTTON1_EventHandler);


    //TM_GPIO_Init(GPIOA,GPIO_PIN_0, GPIO_Mode_IN, GPIO_OType_PP,GPIO_PuPd_DOWN, GPIO_Speed_50MHz);
    TM_HD44780_Puts(5,0,"WITAM!");
    Delayms(1000);
    TM_HD44780_Clear();

    int czekaj = 1500;

	TM_HCSR04_t HCSR2;

	    char res[20];
	    float n = 0;
	    int i =0;

    while (1) {/*
    	opcja = 1;
    	TM_HD44780_Puts(0,0, "1. Zmierz odleglosc.");
    	while(czekaj){
    		TM_BUTTON_Update();
    		czekaj--;
    		Delayms(1);
    	}
    	TM_HD44780_Clear();
    	TM_BUTTON_Update();
    	czekaj = 1500;
    	opcja = 2;
    	TM_HD44780_Puts(0,0, "2. Zlicz.");
    	while(czekaj){
    	    TM_BUTTON_Update();
    	    czekaj--;
    	    Delayms(1);
    	}
    	czekaj = 1500;
    	TM_HD44780_Clear();
    	TM_BUTTON_Update();
*/
    	//distance(5,1);


    	    TM_HCSR04_Init(&HCSR2,GPIOC,GPIO_PIN_15,GPIOC,GPIO_PIN_14);

    	    n = TM_HCSR04_Read(&HCSR2);
    	    	ftoa(n, res, 2);

    	    	TM_HD44780_Clear();
    	    	TM_HD44780_Puts(0,0,res);


    	    	Delayms(500);

    }
}

void BUTTON1_EventHandler(TM_BUTTON_PressType_t type) {

		if (type == TM_BUTTON_PressType_OnPressed) {

		} else if (type == TM_BUTTON_PressType_Normal) {
			 if(opcja =1)
				 distance(10,1);
			 else if(opcja=2)
				 counter();
		} else {
			 main();
		}
}
void counter(){

    TM_HD44780_Puts(5,0,"counter!");
}
void distance(int samples, int precision)
{
	//while(1){
	//TM_BUTTON_Update();
	//TM_HCSR04_t HCSR;
	TM_HCSR04_t HCSR2;

	    char res[20];
	    float n = 0;
	    int i =0;
	    TM_HCSR04_Init(&HCSR2,GPIOC,GPIO_PIN_15,GPIOC,GPIO_PIN_14);
while(1){
	n=0;
for( i= 0; i<samples; i++)
	{

		n = n + TM_HCSR04_Read(&HCSR2);
	}

	n = n / (float)samples;

	ftoa(n, res, precision);

	TM_HD44780_Clear();
	TM_HD44780_Puts(0,0,res);


	Delayms(500);
}
//	}
}
