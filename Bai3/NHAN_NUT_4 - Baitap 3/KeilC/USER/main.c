#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

uint16_t LED7SEG[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

#define BUTTON1              GPIO_Pin_0 // +1
#define BUTTON2              GPIO_Pin_1 // -1 

#define PORT_BUTTON         GPIOB                
#define PORT_BUTTON_CLOCK   RCC_APB2Periph_GPIOB // open chan B
#define LED                 0x007f          // open 8 chan dau 0 _> 6
#define PORT_LED            GPIOC
#define PORT_LED_CLOCK      RCC_APB2Periph_GPIOC // open chan C 

#define LED_ON              GPIO_ResetBits(PORT_LED, LED);
#define LED_OFF             GPIO_SetBits(PORT_LED, LED);

void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);

int main(void)
{
    Clock_Config(); // configuraion clock
    SystemCoreClockUpdate(); // update SystemCoreClock varibale
    GPIO_Config();

    int tmp = 0;

    while(1){
        int status1 = GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON1); 
        int status2 = GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON2); 

        if( status1 == 0) tmp++;
        if( status2 == 0) tmp--;

        GPIO_SetBits(PORT_LED, LED7SEG[tmp - 1]);
        GPIO_ResetBits(PORT_LED, LED7SEG[tmp]);
    }
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

    /*enble clock for GPIOC*/
    RCC_APB2PeriphClockCmd(PORT_BUTTON_CLOCK|PORT_LED_CLOCK, ENABLE);

    /*Configuration GPIO pin*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = BUTTON1;
    GPIO_Init(PORT_BUTTON,&GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = BUTTON2;
    GPIO_Init(PORT_BUTTON,&GPIO_InitStructure);

	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(PORT_LED, &GPIO_InitStructure);
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
