#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "lcd16x2.h"
#include "delay.h"

void resetLEDSau(int postion);
void resetLEDTruoc(int postion);

int main(void)
{
	// Delay initialization
	DelayInit();
	// LCD initialization
	LCD_Init();
		int i = 5;
    while(1){
			while(i){
				LCD_Gotoxy(i,0);
			LCD_Puts("KIET");
			resetLEDSau(i);
			i--;
			DelayMs(1);
			}
			while(i < 12){
				
				LCD_Gotoxy(i,0);
				LCD_Puts("KIET");
				resetLEDTruoc(i);
				DelayMs(1);
				i++;
			}
		//	LCD_Cmd(0x84);
    }       

}

void resetLEDSau(int postion){
	LCD_Gotoxy(postion + 4, 0);
	LCD_Puts(" ");
}

void resetLEDTruoc(int postion){
	if(postion != 0){
		LCD_Gotoxy(postion -1 , 0);
		LCD_Puts("  ");
	}
	if(postion==0){
		LCD_Gotoxy(0 , 0);
		LCD_Puts("  ");
		
	}
	
}