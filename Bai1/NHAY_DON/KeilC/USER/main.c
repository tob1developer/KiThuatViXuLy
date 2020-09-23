//dieu khien 1 led
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


void GPIO_Config(void);
void Clock_Config(void);
void Delay(uint32_t);


//setting 1 den led A
void Single_Led_Port_A_Setting(GPIO_InitTypeDef GPIO_InitStructure);
void Single_Led_Port_A();

int main(void)
{
    Clock_Config();
    SystemCoreClockUpdate();
    GPIO_Config();
    // while (1)
    // {
    //     // GPIO_SetBits(GPIOC, GPIO_Pin_13);
    //     // Delay(100);
    //     // GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    //     // Delay(100);

    //     GPIO_SetBits(GPIOA, GPIO_Pin_13);
    //     Delay(100);
    //     GPIO_ResetBits(GPIOA, GPIO_Pin_13);
    //     Delay(100);
    // }
    Single_Led_Port_A();
		// VDDA vs VSSA la gi ?


    return 0;
}

void Single_Led_Port_A_Setting(GPIO_InitTypeDef GPIO_InitStructure){

    /*enble clock for GPIOA*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/*Configuration GPIO pin*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// nhay 1 den o port A - position 13
void Single_Led_Port_A(){
    while (1)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_13);
        Delay(100);
        GPIO_ResetBits(GPIOA, GPIO_Pin_13);
        Delay(100);
    }
}
/*Delay tuong doi*/

void Delay(uint32_t t){
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < 0x2AFF; j++);
        /**
         * 0xAFF = 2815^t -> big(n.t)
         * thuc ra ko phai la delay ma do minh tao for de no lap 1s -> cai duoi
         * 
        */
    
    }
    
}


void GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // // /*enble clock for GPIOC*/
	// // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    // /*enble clock for GPIOA*/
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	// /*Configuration GPIO pin*/
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	// GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	// // GPIO_Init(GPIOC, &GPIO_InitStructure);
    // GPIO_Init(GPIOA, &GPIO_InitStructure);

    Single_Led_Port_A_Setting(GPIO_InitStructure);
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

