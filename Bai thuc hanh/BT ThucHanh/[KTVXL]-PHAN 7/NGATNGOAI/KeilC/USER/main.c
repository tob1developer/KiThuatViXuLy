#include "stm32f10x.h"

#define BUTTON_1        GPIO_Pin_8
#define PORT_BUTTON_1   GPIOA
#define RCC_BUTTON_1    RCC_APB2Periph_GPIOA

#define BUTTON_2        GPIO_Pin_13
#define PORT_BUTTON_2   GPIOC
#define RCC_BUTTON_2    RCC_APB2Periph_GPIOC

#define LED         GPIO_Pin_9
#define PORT_LED    GPIOB
#define RCC_LED     RCC_APB2Periph_GPIOB

void LED_Config(void);
void GPIO_EXTI_Config(void);
void EXTI_Config(void);
void NVIC_EXTI_Config(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

// cau hinh cho LED PB9
void LED_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_LED, ENABLE); //cap clock cho GPIOB

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_LED, &GPIO_InitStructure); //cai dat cac cau hinh tren cho GPIOB
}  
 
//cau hinh ngat ngoai cho 2 chan PA8 va PC13
/*
    B1:cap xung va cau hinh chan PA8 va PC13 nhan tin hieu ngat ngoai la input pull-up
*/
void GPIO_EXTI_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_BUTTON_1 | RCC_BUTTON_2 | RCC_APB2Periph_AFIO, ENABLE);
    //do ngat ngoai la chuc nang thay the nen phai bat AIFO

    //cau hinh chan PA8
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = BUTTON_1;
    GPIO_Init(PORT_BUTTON_1, &GPIO_InitStructure);

    //cau hinh chan PC13
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(PORT_BUTTON_2, &GPIO_InitStructure);

    //chon chan PA8 va PC13 la chan nhan tin hieu ngat ngoai
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);
}

/*
        B2:Cau hinh va cho phep ngat ngoai o EXTI
*/
void EXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line8 | EXTI_Line13; // chon kenh 8 va kenh 13 ung voi A8 va C13
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //chon che do ngat ngoai
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //chon canh tich cuc la canh xuong
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; //cho phep kenh ngat ngoai duoc cau hinh
    EXTI_Init(&EXTI_InitStructure); //lenh cau hinh cac thong so duoc luu trong EXTI_InitStructure
}

/*
        B3: cau hinh cap do uu tien va cho phep ngat ngoai o NVIC
*/
void NVIC_EXTI_Config()
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);   //0 cap PreemptionPriority va 16 cap SubPriority
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;  // chon cac kenh tu 5-9
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //chon thu tu uu tien
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // cho phep ngoai vi dang dc cau hinh o NVIC
    NVIC_Init(&NVIC_InitStructure); // lenh cau hinh cac thong so duoc luu trong NVIC_InitStructure cho NVIC

    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//chon kenh tu 10 den 15
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //chon muc uu tien
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
    B4: Viet chuong trinh con phuc vu ngat ngoai
*/
    
// chuong trinh con phuc vi ngat ngoai cho chan PA8
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_IMR_MR8) != RESET) //kiem tra co phai la kenh 8 ngat khong?
    {
        EXTI_ClearITPendingBit(EXTI_IMR_MR8); //xoa co ngat kenh 8
        GPIO_SetBits(PORT_LED, LED); //mo Led
    }
}

//chuong trinh con phuc vu ngat ngoai cho chanP C13
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_IMR_MR13) != RESET)//kiem tra co phai la kenh 13 ngat khong 
    {
        EXTI_ClearITPendingBit(EXTI_IMR_MR13); //xoa co ngat kenh 13
        GPIO_ResetBits(PORT_LED, LED); //tat Led
    }
}
    
int main(void)
{
    LED_Config();
    GPIO_EXTI_Config();
    EXTI_Config();
    NVIC_EXTI_Config();
    EXTI9_5_IRQHandler();
    EXTI15_10_IRQHandler();
    
    while(1);
}
