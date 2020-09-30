// FIle luu lai bai tap
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

uint16_t LED7SEG[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80,0x90};
                    //  0    1     2      3    4     5     6      7    8    9

// cau 1:
/********************************************************/
uint16_t LED7CHAN[10]={0xC0, 0xA4, 0x99, 0x82, 0x80};  
void NhayChan(){     
    int i = 0;
    for ( i = 0; i < 5; i++)
    {
        GPIO_Write(GPIOC, LED7CHAN[i]);
		Delay(100);
    }
}


uint16_t LED7LE[10]={0xF9, 0xB0, 0x92, 0xF8, 0x90};
void NhayLe(){
    int i = 0;
    for ( i = 0; i < 5; i++)
    {
        GPIO_Write(GPIOC, LED7LE[i]);
		Delay(100);
    }
}
/********************************************************/

//cau 2:
/********************************************************/
void DemNguoc(){
    int i = 0;
    for(i = 9; i >= 0; i--){
        GPIO_Write(GPIOC, LED7SEG[i]);
        Delay(100);
}
/********************************************************/
