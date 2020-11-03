#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

uint16_t LED_6[7]={ 0x03F0, 0x03E1, 0x03C3,  0x0387, 0x030F,  0x021F, 0x003F};

#define BUTTON1              GPIO_Pin_0
#define BUTTON2              GPIO_Pin_1

#define PORT_BUTTON         GPIOB                
#define PORT_BUTTON_CLOCK   RCC_APB2Periph_GPIOB // open chan B
#define LED                 0x03FF          
#define PORT_LED            GPIOC
#define PORT_LED_CLOCK      RCC_APB2Periph_GPIOC // open chan C 

#define LED_OFF            GPIO_SetBits(PORT_LED, LED);

void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);

int main(void)
{
		int tmp = 0;
	
    Clock_Config(); // configuraion clock
    SystemCoreClockUpdate(); // update SystemCoreClock varibale
    GPIO_Config();
		
		//trang thai ban dau
		LED_OFF
	
    while(1){
        GPIO_Write(PORT_LED, LED_6[tmp]);
				Delay(15);
			
        if( GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON1) == 0 ) tmp++;
        if( GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON2) == 0 ) tmp--;
					
				if(tmp > 6) tmp = 6;
				if(tmp < 0) tmp = 0;
				
       // if(status2 == 0) LED_ON
       // else LED_OFF
    }
}
/*Delay tuong doi*/
void Delay(uint32_t t){
    unsigned int i,j;

    for(i=0;i<t;i++){
    for(j=0;j< +0x2AFF; j++);
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
