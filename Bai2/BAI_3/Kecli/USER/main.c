#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define LED7SEG_A GPIO_Pin_0
#define LED7SEG_B GPIO_Pin_1
#define LED7SEG_C GPIO_Pin_2
#define LED7SEG_D GPIO_Pin_3
#define LED7SEG_E GPIO_Pin_4
#define LED7SEG_F GPIO_Pin_5
#define LED7SEG_G GPIO_Pin_6

#define LED7SEG_DP GPIO_Pin_7
#define LED1       GPIO_Pin_1
#define LED2       GPIO_Pin_2

#define PORT_LED7SEG_CODE GPIOC
#define PORT_LED          GPIOA

#define PORT_LED7SEG_CODE_CLOCK RCC_APB2Periph_GPIOC
#define PORT_LED_CLOCK          RCC_APB2Periph_GPIOA

uint16_t LED7SEG[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80,0x90};
uint16_t CHAN = 0x2AA;
uint16_t LE = 0x0555;
void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);


int main(void)
    {
    Clock_Config(); // configuraion clock
    SystemCoreClockUpdate(); // update SystemCoreClock varibale
    GPIO_Config();

    GPIO_ResetBits(PORT_LED, LED1); //LED1 = 0;
    GPIO_ResetBits(PORT_LED, LED2); //LED2 = 0;

    while(1){
		uint8_t i = 0;
        for(i = 0; i < 96; i++){
           uint8_t j = 0;
					if(i%5 ==0 ){
						if(i%10 == 0) {
							GPIO_Write(GPIOB, CHAN);
							Delay(10);
						}
						else {
							GPIO_Write(GPIOB, LE);
							Delay(10);
						}
            for( j = 0; j < 24; j++){
                GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i/10]);
                GPIO_SetBits(PORT_LED, LED1); // LED1 = 1
                Delay(1);

                GPIO_ResetBits(PORT_LED, LED1); //LED1 = 0

                GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i%10]);
                GPIO_SetBits(PORT_LED, LED2); //LED2 = 1
                Delay(1);

                GPIO_ResetBits(PORT_LED, LED2); //L7S2 = 0
            }
					}
        }
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
		GPIO_InitTypeDef GPIO_InitStructure_SINGLE;
    /*enble clock for GPIOC*/
    RCC_APB2PeriphClockCmd(PORT_LED7SEG_CODE_CLOCK|PORT_LED_CLOCK, ENABLE);

    /*Configuration GPIO pin*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Pin =
    LED7SEG_A|LED7SEG_B|LED7SEG_C|LED7SEG_D|LED7SEG_E|LED7SEG_F|LED7SEG_G|LED7SEG_A|LED7SEG_DP;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(PORT_LED7SEG_CODE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LED1|LED2;
    
    GPIO_Init(PORT_LED, &GPIO_InitStructure);
	
		
	
		/*enble clock for GPIOC*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /*Configuration GPIO pin*/
    GPIO_InitStructure_SINGLE.GPIO_Mode = GPIO_Mode_Out_PP;
    
    /*mo cong de hoat dong */
    GPIO_InitStructure_SINGLE.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
    GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    
    /*?*/
    GPIO_InitStructure_SINGLE.GPIO_Speed = GPIO_Speed_2MHz;

    /*khoi tao cong C ( postC)*/
    GPIO_Init(GPIOB, &GPIO_InitStructure_SINGLE);
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