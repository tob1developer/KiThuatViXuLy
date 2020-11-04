#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#define RCC_GPIO_ROW RCC_APB2Periph_GPIOA
#define RCC_GPIO_COL RCC_APB2Periph_GPIOB
#define GPIO_ROW GPIOA
#define GPIO_COL GPIOB
#define GPIO_PIN_ROW_1 GPIO_Pin_0 // khai bao hang 1
#define GPIO_PIN_ROW_2 GPIO_Pin_1 // khai bao hang 2
#define GPIO_PIN_ROW_3 GPIO_Pin_2 // khai bao hang 3
#define GPIO_PIN_ROW_4 GPIO_Pin_3 // khai bao hang 4
#define GPIO_PIN_ROW_5 GPIO_Pin_4 // khai bao hang 5
#define GPIO_PIN_ROW_6 GPIO_Pin_5 // khai bao hang 6
#define GPIO_PIN_ROW_7 GPIO_Pin_6 // khai bao hang 7
#define GPIO_PIN_ROW_8 GPIO_Pin_7 // khai bao hang 8
#define GPIO_PIN_COL_1 GPIO_Pin_8 // khai bao cot 1
#define GPIO_PIN_COL_2 GPIO_Pin_9 // khai bao cot 2
#define GPIO_PIN_COL_3 GPIO_Pin_10 // khai bao cot 3
#define GPIO_PIN_COL_4 GPIO_Pin_11 // khai bao cot 4
#define GPIO_PIN_COL_5 GPIO_Pin_12 // khai bao cot 5
#define GPIO_PIN_COL_6 GPIO_Pin_13 // khai bao cot 6
#define GPIO_PIN_COL_7 GPIO_Pin_14 // khai bao cot 7
#define GPIO_PIN_COL_8 GPIO_Pin_15 // khai bao cot 8
unsigned int chuH[]={0x3C00,0x3C00,0x3C00,0x0000,0x0000,0x3C00,0x3C00,0x3C00};

unsigned int chuA[8]={0x8100,0x8100,0x3C00,0x3C00,0x0000,0x0000,0x3C00,0x3C00};
unsigned int chuB[8]={0x0300,0x3c00,0x3C00,0x0300,0x0300,0x3C00,0x3C00,0x0300};
unsigned int chuC[8]={0xC300,0x3C00,0x3C00,0x3700,0x3C00,0x3900,0x8100,0x8300};


void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);
int main(void)
{
 Clock_Config(); // configuraion clock
 SystemCoreClockUpdate(); // update SystemCoreClock varibale
 GPIO_Config();

 while(1){
	 int dem = 4;
	 while(dem){
				uint8_t i = 0;
				 for(i =0; i < 8; i++){
					 GPIO_Write(GPIO_ROW, 0x01 << i);
					 GPIO_Write(GPIO_COL, chuH[i]);
					 Delay(1);
					}
		 
		 	 Delay(1000);
        //Chu A
        for(uint8_t i = 0; i < 8; i++){
            GPIO_Write(GPIO_ROW, 0x01 << i); //tu tren xuong duoi
            GPIO_Write(GPIO_COL, chuA[i]); // tu trai qua phai hay tu phai qua trai
            Delay(1);            
        }  
        Delay(1000);
        // Chu B
        for(uint8_t i = 0; i < 8; i++){
            GPIO_Write(GPIO_ROW, 0x01 << i); //tu tren xuong duoi
            GPIO_Write(GPIO_COL, chuB[i]); // tu trai qua phai hay tu phai qua trai
            Delay(1);            
        }  
        Delay(1000);
        // Chu C
        for(uint8_t i = 0; i < 8; i++){
            GPIO_Write(GPIO_ROW, 0x01 << i); //tu tren xuong duoi
            GPIO_Write(GPIO_COL, chuC[i]); // tu trai qua phai hay tu phai qua trai
            Delay(1);            
        }  
        Delay(1000);
				dem--;
	 }
	 }
}

void Delay(uint32_t t)
{
 unsigned int i,j;

 for(i=0;i<t;i++){
 for(j=0;j< 0x2AFF/4; j++);
 }
}
void GPIO_Config()
{
 GPIO_InitTypeDef GPIO_InitStructure;

 /*enble clock for GPIOC*/
 RCC_APB2PeriphClockCmd(RCC_GPIO_ROW|RCC_GPIO_COL, ENABLE);

 /*Configuration GPIO pin*/
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Pin =
GPIO_PIN_ROW_1|GPIO_PIN_ROW_2|GPIO_PIN_ROW_3|GPIO_PIN_ROW_4|GPIO_PIN_ROW_5|
GPIO_PIN_ROW_6|GPIO_PIN_ROW_7|GPIO_PIN_ROW_8;;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 GPIO_Init(GPIO_ROW, &GPIO_InitStructure);

 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Pin =
GPIO_PIN_COL_1|GPIO_PIN_COL_2|GPIO_PIN_COL_3|GPIO_PIN_COL_4|GPIO_PIN_COL_5|
GPIO_PIN_COL_6|GPIO_PIN_COL_7|GPIO_PIN_COL_8;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 GPIO_Init(GPIO_COL, &GPIO_InitStructure);
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