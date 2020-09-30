#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

// bai 1 : hien thi so chan tang dan 0 -> 99
void SoChanTangDan(){
    uint8_t i = 0;
        for(i = 0; i < 100; i++){
            if(i == 0 || i%2 ==0) {
                uint8_t j = 0;
                for( j = 0; j < 24; j++){
                    // GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i/10]);
                    // GPIO_SetBits(PORT_LED, LED1); // LED1 = 1
                    // Delay(1);

                    // GPIO_ResetBits(PORT_LED, LED1); //LED1 = 0

                    // GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i%10]);
                    // GPIO_SetBits(PORT_LED, LED2); //LED2 = 1
                    // Delay(1);

                    // GPIO_ResetBits(PORT_LED, LED2); //L7S2 = 0
                }
            }
        }
}

// bai 2 : hien thi so chia het cho 3 tang dan 99 -> 0
void SoChanTangDan(){
    uint8_t i = 0;
        for(i = 99; i >= 0; i--){
            if(i%3 == 0 ) {
                uint8_t j = 0;
                for( j = 0; j < 24; j++){
                    // GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i/10]);
                    // GPIO_SetBits(PORT_LED, LED1); // LED1 = 1
                    // Delay(1);

                    // GPIO_ResetBits(PORT_LED, LED1); //LED1 = 0

                    // GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i%10]);
                    // GPIO_SetBits(PORT_LED, LED2); //LED2 = 1
                    // Delay(1);

                    // GPIO_ResetBits(PORT_LED, LED2); //L7S2 = 0
                }
            }
        }
}