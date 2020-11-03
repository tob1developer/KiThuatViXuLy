#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

#define LED         GPIO_Pin_13
#define PORT_LED    GPIOC
#define RCC_LED     RCC_APB2Periph_GPIOC

void Clock_Config(void);
void GPIO_configuration(void);
void TIM3_configuration(void);
void NVIC_configuration(void);


int main(void)
{
    Clock_Config(); // configuraion clock
	SystemCoreClockUpdate(); // update SystemCoreClock varibale
    
    GPIO_configuration();
    TIM3_configuration();
    NVIC_configuration();
    
    GPIO_SetBits(PORT_LED, LED);
	while(1)
	{
//        GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(1^GPIO_ReadOutputDataBit(GPIOB, LED)));
//        Delay_t(100);
//        if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) // if update flag turn on
//        {
//            GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(1^GPIO_ReadOutputDataBit(GPIOB, LED)));
//            TIM_ClearFlag(TIM3, TIM_IT_Update); //clear update flag
//        }
	}
}


void Clock_Config(void)
{
    /* RCC system reset */
    RCC_DeInit();
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);
    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div1);
    /*enable HSI source clock*/
    RCC_HSICmd(ENABLE);	
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET){}
    /* Select HSI as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    /* Wait till HSI is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x00) {}    
}

void GPIO_configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_LED, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = LED;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_LED, &GPIO_InitStructure);
}

void TIM3_configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    
    /*
        Luu y: voi phien ban proteus 8.6, chung ta phai enable TIM1 thi moi co the dung TIMx.
        => bug cua phan men proteus.
    */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    TIM_TimeBaseStructInit(&TIM_InitStructure);
    TIM_Cmd(TIM1, ENABLE);
    
    /*configuration TIM3*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_InitStructure.TIM_Period = 7999;
    TIM_InitStructure.TIM_Prescaler = 999;    
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_RepetitionCounter = 0x00;    
    TIM_TimeBaseInit(TIM3, &TIM_InitStructure);

    TIM_TimeBaseInit(TIM3, &TIM_InitStructure);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //enable update interrup
    TIM_Cmd(TIM3, ENABLE);

}

void NVIC_configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //if update flag turn on
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //clear update flag
        GPIO_WriteBit(PORT_LED, LED, (BitAction)(1^GPIO_ReadOutputDataBit(PORT_LED, LED)));
    }
}



