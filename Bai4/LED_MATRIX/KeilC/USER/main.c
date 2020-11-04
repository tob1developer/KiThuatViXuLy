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
unsigned int chuH[8]={0x3C00,0x3C00,0x3C00,0x0000,0x0000,0x3C00,0x3C00,0x3C00};
unsigned int chuA[8]={0x8100,0x8100,0x3C00,0x3C00,0x0000,0x0000,0x3C00,0x3C00};
unsigned int chuB[8]={0x0300,0x3c00,0x3C00,0x0300,0x0300,0x3C00,0x3C00,0x0300};
unsigned int chuC[8]={0xC300,0x3C00,0x3C00,0x3700,0x3C00,0x3900,0x8100,0x8300}; // bi loi
unsigned int chuD[8]={0x0100,0x3800,0x3C00,0x3C00,0x3C00,0x3C00,0x3800,0x0100};
unsigned int chuE[8]={0x8000,0x8000,0xFC00,0x8000,0x8000,0xFC00,0x8000,0x8000}; // bi loi
unsigned int chuF[8]={0x0000,0x0000,0xC000,0xFC00,0xFC00,0xC000,0xC000,0xC000}; // bi loi
unsigned int chuG[8]={0x8100,0x0000,0x3C00,0x3F00,0x3000,0x3C00,0x0000,0x8200};
unsigned int chuI[8]={0x0000,0xE700,0xE700,0xE700,0xE700,0xE700,0xE700,0x0000};
unsigned int chuJ[8]={0x0000,0xF900,0xF900,0xF900,0xF900,0x3900,0x8100,0xC700};
unsigned int chuK[8]={0x3C00,0x3900,0x3300,0x0700,0x1300,0x3900,0x3C00,0x3E00};
unsigned int chuL[8]={0x3F00,0x3F00,0x3F00,0x3F00,0x3F00,0x3F00,0x0000,0x0000};
unsigned int chuM[8]={0x3C00,0x1800,0x0000,0x2400,0x2400,0x3C00,0x3C00,0x3C00};
unsigned int chuN[8]={0x3800,0x3000,0x2400,0x2400,0x1200,0x3400,0x3C00,0x3C00}; // bi loi
unsigned int chuO[8]={0xC300,0x8100,0x1800,0x3C00,0x3C00,0x1800,0x8100,0xC300};
unsigned int chuP[8]={0x0100,0x0000,0x3C00,0x3C00,0x0100,0x0300,0x3F00,0x3F00};
unsigned int chuQ[8]={0xC300,0x8100,0x1800,0x3C00,0x3400,0x1900,0x8000,0xC200};
unsigned int chuR[8]={0x0100,0x0000,0x3C00,0x3C00,0x0100,0x3300,0x3900,0x3C00};
unsigned int chuS[8]={0x8100,0x3C00,0x3F00,0x8100,0x0300,0x3C00,0x0100,0x8300}; // bi loi
unsigned int chuT[8]={0x0000,0x0000,0xE700,0xE700,0xE700,0xE700,0xE700,0xE700};
unsigned int chuU[8]={0x3C00,0x3C00,0x3C00,0x3C00,0x3C00,0x1800,0x0000,0xC300};
unsigned int chuV[8]={0x7E00,0x3C00,0x9900,0x9900,0xDB00,0xC300,0xE700,0xE700};
unsigned int chuX[8]={0x3C00,0x9900,0xC300,0xE700,0xE700,0xC300,0x9900,0x3C00};
unsigned int chuY[8]={0x3C00,0x9900,0xc300,0xE700,0xE700,0xE700,0xE700,0xE700};

unsigned int Reset = 0xFF00;



void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);
void ResetLed(void);
void RunChuCai(int ArrChuCai[]);

int main(void){
	Clock_Config(); // configuraion clock
	SystemCoreClockUpdate(); // update SystemCoreClock varibale
	GPIO_Config();

	while(1){
		RunChuCai(chuA);
		ResetLed();
		RunChuCai(chuB);
		ResetLed();
		RunChuCai(chuC);
		ResetLed();
		RunChuCai(chuD);
		ResetLed();
		RunChuCai(chuE);
		ResetLed();
		RunChuCai(chuF);
		ResetLed();
		RunChuCai(chuG);
		ResetLed();
		RunChuCai(chuI);
		ResetLed();
		RunChuCai(chuJ);
		ResetLed();
		RunChuCai(chuK);
		ResetLed();
		RunChuCai(chuL);
		ResetLed();
		RunChuCai(chuM);
		ResetLed();
		RunChuCai(chuN);
		ResetLed();
		RunChuCai(chuO);
		ResetLed();
		RunChuCai(chuP);
		ResetLed();
		RunChuCai(chuQ);
		ResetLed();
		RunChuCai(chuR);
		ResetLed();
		RunChuCai(chuS);
		ResetLed();
		RunChuCai(chuT);
		ResetLed();
		RunChuCai(chuU);
		ResetLed();
		RunChuCai(chuV);
		ResetLed();
		RunChuCai(chuX);
		ResetLed();
		RunChuCai(chuY);
		ResetLed();

	}
	
	return 0;

}
void RunChuCai(int ArrChuCai[]){
	int tmp = 50;
	while (tmp)
	{
		uint8_t i = 0;
		for(i = 0; i < 8; i++){
            GPIO_Write(GPIO_ROW, 0x01 << i); //tu tren xuong duoi
            GPIO_Write(GPIO_COL, ArrChuCai[i]); // tu trai qua phai hay tu phai qua trai
            Delay(1);            
        }  
		tmp--;
	}
}

void ResetLed(){
	uint8_t i = 0;
	for(i =0; i < 8; i++){
		GPIO_Write(GPIO_ROW, 0x01 << i);
		GPIO_Write(GPIO_COL, Reset);
		Delay(1);
	}
	Delay(100);
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