#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "lcd16x2.h"
#include "delay.h"

int main(void)
{
	// Delay initialization
	DelayInit();
	// LCD initialization
	LCD_Init();

    while(1){
		LCD_Gotoxy(0,0);
		LCD_Puts("KY THUAT VI XU");
        LCD_Gotoxy(0,1);
		LCD_Puts("LY - PTIT");
		DelayMs(500);
    }       

}