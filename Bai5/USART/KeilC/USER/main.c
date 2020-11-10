#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stdio.h"

void Clock_Config(void);
void UART_configuration(void);
void UART_SendChar(USART_TypeDef *USART, char data);
void UART_SendString(USART_TypeDef *USART, char *Str);
void Delay_t(uint32_t t);

struct __FILE {
    int dummy;
};
FILE __stdout;

int fputc(int ch, FILE *f){
    /* Send your custom byte */
    USART_SendData(USART1, ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){};
    /* If everything is OK, you have to return character written */
    return ch;
}

int main(void)
{
    Clock_Config(); // configuraion clock
	SystemCoreClockUpdate(); // update SystemCoreClock varibale
    UART_configuration();
    
	while(1)
	{
        printf("Ky Thuat Vi Xu Ly PTIT");
        Delay_t(100);
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

/*Delay tuong doi*/
void Delay_t(uint32_t t)
{
    unsigned int i,j;
    
    for(i=0;i<t;i++){
        for(j=0;j< 0x2AFF; j++);
    }

}

void UART_SendChar(USART_TypeDef *USARTx, char data){
	
	USARTx->DR = 0x00;
	USART_SendData(USARTx, data);
	//TxE = 1: Data is transferred to the shift register)
	//TxE = 0; Data is not transferred to the shift register
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}

void UART_SendString(USART_TypeDef *USARTx,char *Str)
{
    while(*Str){
        UART_SendChar(USARTx, *Str);
        Str++;
    }
}

void UART_configuration(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;
    USART_InitTypeDef   USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE ); /*enable clock*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );
    /* 
        USART1_Rx : PA10  input floating 
        USART1_Tx : PA9  alternate function push-pull
    */	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure );

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE); //kich hoat usart1
}


