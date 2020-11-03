#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "lcd16x2.h"
#include "delay.h"
#include "stdio.h"

void Clock_Config(void);
void ADC_configuration();

uint16_t raw_value, sum_adc, num_percent;
char str_percent[2];

int main(void)
{
	DelayInit();    // Delay initialization
	LCD_Init();     // LCD initialization
    ADC_configuration();
  
    while(1)
    {
        sum_adc = 0;
        //doc gia tri ADC 10 lan roi lay ket qua
        for(int i=0;i<10;i++)
        {
            
            raw_value = ADC_GetConversionValue(ADC1);
            sum_adc  += raw_value;
            DelayMs(1);
        }
        sum_adc /= 10;
        num_percent = (sum_adc*100)/4096;
        sprintf (str_percent, "%d *C", num_percent); 
		LCD_Gotoxy(0,0);
		LCD_Puts("PHAN TRAM BIEN TRO");
        LCD_Gotoxy(0,1);
		LCD_Puts(str_percent);
		DelayMs(500);
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

void ADC_configuration()
{
    //cau hinh cho chan GPIO va bo ADC hoat dong
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    
    /*cau hinh chan Input cua bo ADC1 la chan PA0*/
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //cau hinh ADC
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    
    /* Cau hinh chanel, rank, thoi gian lay mau */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    /* Cho phep bo ADC1 hoat dong */
    ADC_Cmd(ADC1, ENABLE);

    /* Bat dau chuyen doi ADC */ 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); 
}
