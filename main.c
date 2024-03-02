/************************************************************************
*	Program : 16F877A + I2C + HMC5883L									*
*	Version : 0.500														*
*	Author	: hmt2hwt                                                   *                                                        *
*   20Mhz                                                               *
************************************************************************/
#pragma warning push
#pragma warning disable 520     //function xxx is never called
#pragma warning disable 1498    //pointer (xxx@yyy) in expression may have no targets
                                
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "gpio.h"
#include "wait.h"
#include "usart.h"
#include "numtostr.h"
#include "HMC5883L.h"

#pragma warning pop

void main(void)
{
    uint8_t uptr[16]={0}, uptr_cnt=0, eol=13, spc=32;
    int16_t mgX=0, mgY=0, mgZ=0;
        
    GPIO_init();
    USART_init();

    if(!HMC5883L_init())    
    {
        uptr_cnt=mc_strcpy(uptr, (uint8_t *)"HMC5883L FOUND");
        USART_write(uptr,uptr_cnt);
        USART_write(&eol,1);
    }
    HMC5883L_set_config(HMC5883L_CONF_A_SET, HMC5883L_CONF_B_SET, HMC5883L_MODE_SET);
    while(true)
    {
        HMC5883L_read_axis_LSB(&mgX, &mgY, &mgZ);

        uptr_cnt=iToStr(mgX, uptr, 3);
        USART_write(uptr,uptr_cnt);
        USART_write(&spc,1);
        
        uptr_cnt=iToStr(mgY, uptr, 3);
        USART_write(uptr,uptr_cnt);
        USART_write(&spc,1);

        uptr_cnt=iToStr(mgZ, uptr, 3);
        USART_write(uptr,uptr_cnt);
        USART_write(&spc,1);

        USART_write(&eol,1); 

        TEST_LED = (~TEST_LED);
        delay_big_ms(500);
    }
}