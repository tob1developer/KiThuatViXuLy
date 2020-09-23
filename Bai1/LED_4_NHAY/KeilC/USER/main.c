#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
// 0 la sang 1 la tat
void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);

int main(void){
    Clock_Config(); // configuraion clock
    SystemCoreClockUpdate(); // update SystemCoreClock varibale
    GPIO_Config();
    
    uint16_t led_4_0 = 0xF0;
    uint16_t led_0_4 = 0x0F;

    while(1){

        GPIO_Write(GPIOA, led_4_0);
        Delay(100);
        GPIO_Write(GPIOA, led_0_4);
        Delay(100);
    }

    return 0;
}
/*Delay tuong doi*/
void Delay(uint32_t t){

    
    unsigned int i,j;

    for(i=0;i<t;i++){
        for(j=0;j< 0x2AFF; j++);
    }
}


void GPIO_Config(){
    GPIO_InitTypeDef GPIO_InitStructure;

    /*enble clock for GPIOA*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /*Configuration GPIO pin*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    
    /*mo cong de hoat dong */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
    GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    
    /*?*/
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    /*khoi tao cong A ( postA)*/
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Clock_Config(void){
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