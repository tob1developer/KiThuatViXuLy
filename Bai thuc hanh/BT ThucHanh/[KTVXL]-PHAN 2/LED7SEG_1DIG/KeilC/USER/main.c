#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

uint16_t LED7SEG[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);

int main(void)
{
    Clock_Config(); // configuraion clock
	SystemCoreClockUpdate(); // update SystemCoreClock varibale
	GPIO_Config();
    
	while(1)
	{
        for(int i = 9; i >=0; i--){
            GPIO_Write(GPIOC, LED7SEG[i]);
            Delay(100);
        }
	}

}
/*Delay tuong doi*/
void Delay(uint32_t t)
{
    unsigned int i,j;
    
    for(i=0;i<t;i++){
        for(j=0;j< 0x2AFF; j++);
    }

}

void GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /*enble clock for GPIOC*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
	/*Configuration GPIO pin*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Clock_Config(void)
{
    /* RCC system reset */
    RCC_DeInit();
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div2);
    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);
    /*enable HSI source clock*/
    RCC_HSICmd(ENABLE);	
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET){}
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x00) {}    
}

