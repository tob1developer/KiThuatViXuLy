#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

#define PWM         GPIO_Pin_2
#define PORT_PWM    GPIOA
#define RCC_PWM     RCC_APB2Periph_GPIOA

void Clock_Config(void);
void GPIO_configuration(void);
void TIM2_PWM_CH3_configuration(void);


int main(void)
{
    Clock_Config(); // configuraion clock
	SystemCoreClockUpdate(); // update SystemCoreClock varibale
    
    GPIO_configuration();
    TIM2_PWM_CH3_configuration();

	while(1)
	{

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
    RCC_APB2PeriphClockCmd(RCC_PWM, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = PWM;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_PWM, &GPIO_InitStructure);
}

void TIM2_PWM_CH3_configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    
    /*
        Luu y: voi phien ban proteus 8.6, chung ta phai enable TIM1 thi moi co the dung TIMx.
        => bug cua phan men proteus.
    */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    TIM_TimeBaseStructInit(&TIM_InitStructure);
    TIM_Cmd(TIM1, ENABLE);
    
    /*configuration TIM2*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_InitStructure.TIM_Period = 7999;
    TIM_InitStructure.TIM_Prescaler = 999;    
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_RepetitionCounter = 0x00;    
    TIM_TimeBaseInit(TIM2, &TIM_InitStructure);

    TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //enable update interrup
    TIM_Cmd(TIM2, ENABLE);

    //cau hinh TIM2 channel 3 xuat PWM
    TIM_OCInitTypeDef TIM_OCInitStructure;

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //che do tao xung PWM o ngo ra loai 1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //cho phep output compare xuat tin bieu ra o Channel 3
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //cau hinh muc tich cuc
    TIM_OCInitStructure.TIM_Pulse = 3999; //cau hinh gia tri so sanh cho output compare
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    
    TIM_CtrlPWMOutputs(TIM2, ENABLE); //cho phep xuat tin hieu ra o TIM2 
    TIM_Cmd(TIM2, ENABLE);
}



