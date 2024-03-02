/************************************************************************
*	Program : HMC5883L.h											    *
*	Version : 0.500														*
*	Author	: hmt2hwt                                                   *
*	Date	:                                                           *
*   Modified:                                                           *
*	Function:                                                           *
*                                                                       *
*   Earth mag. Field -> 25uT (0.25G) and 65uT (0.65G)                   *
*   https://www.magnetic-declination.com/                               *
************************************************************************/

#ifndef HMC5883L_H
#define	HMC5883L_H

#include <xc.h>
#include "i2c.h"
                                    
#define HMC5883L_I2C_ADR_WR         0x3C    
#define HMC5883L_I2C_ADR_RD         0x3D

#define HMC5883L_CONFIG_A_REG       0x00    //RW        
#define HMC5883L_CONFIG_B_REG       0x01    //RW
#define HMC5883L_MODE_REG           0x02    //RW

#define EMC5883L_DATA_OUT_X_MSB_REG 0x03    //Read only
#define EMC5883L_DATA_OUT_X_LSB_REG 0x04    //Read only

#define EMC5883L_DATA_OUT_Z_MSB_REG 0x05    //Read only
#define EMC5883L_DATA_OUT_Z_LSB_REG 0x06    //Read only

#define EMC5883L_DATA_OUT_Y_MSB_REG 0x07    //Read only
#define EMC5883L_DATA_OUT_Y_LSB_REG 0x08    //Read only

#define EMC5883L_STATUS_REG         0x09    //Read only
//----------------------------------------------------------------
#define EMC5883L_IDENT_A_REG        0x0A    //Read only
#define EMC5883L_IDENT_B_REG        0x0B    //Read only
#define EMC5883L_IDENT_C_REG        0x0C    //Read only

//HMC5883L_CONFIG_A_REG BIT DEFINITIONS
//MEASUREMENT MODE -> BIT1-BIT0
#define HMC5883L_CONFIG_MODE_NORMAL				(0x00 << 0)    /* DEFAULT*/
#define HMC5883L_CONFIG_MODE_POS_BIAS			(0x01 << 0)
#define HMC5883L_CONFIG_MODE_NEG_BIAS			(0x02 << 0)
//DATA OUTPUT RATE -> BIT4-BIT3-BIT2
#define HMC5883L_DATA_OUT_RATE_0_75_HZ          (0x00 << 2)	/* 0.75 Hz */
#define HMC5883L_DATA_OUT_RATE_1_5_HZ			(0x01 << 2)	/* 1.5 Hz */
#define HMC5883L_DATA_OUT_RATE_3_HZ				(0x02 << 2)	/* 3 Hz */
#define HMC5883L_DATA_OUT_RATE_7_5_HZ			(0x03 << 2)	/* 7.5 Hz */
#define HMC5883L_DATA_OUT_RATE_15_HZ			(0x04 << 2)	/* 15 Hz   DEFAULT*/
#define HMC5883L_DATA_OUT_RATE_30_HZ			(0x05 << 2)	/* 30 Hz */
#define HMC5883L_DATA_OUT_RATE_75_HZ			(0x06 << 2)	/* 75 Hz */
//SAMPLE AVERAGED PER MEASUREMENT OUTPUT -> BIT6-BIT5
#define HMC5883L_SAMPLE_AVG_1					(0x00 << 5)	/* No averaging */
#define HMC5883L_SAMPLE_AVG_2					(0x01 << 5)	/* Average 2 samples */
#define HMC5883L_SAMPLE_AVG_4					(0x02 << 5)	/* Average 4 samples */
#define HMC5883L_SAMPLE_AVG_8					(0x03 << 5)	/* Average 8 samples     DEFAULT */ 
//HMC5883L_CONFIG_B_REG BIT DEFINITIONS
// GAIN CONFIGURATION -> BIT7-BIT6-BIT5                    LSB/Gauss  mG/LSB
#define HMC5883L_RESOLUTION_0_73				(0x00 << 5) /* 1370 - 0.73 Sensor Field range: +/- 0.88 Gauss */
#define HMC5883L_RESOLUTION_0_92				(0x01 << 5) /* 1090 - 0.92 Sensor Field range: +/- 1.3  Gauss DEFAULT */
#define HMC5883L_RESOLUTION_1_22				(0x02 << 5) /*  820 - 1.22 Sensor Field range: +/- 1.9  Gauss */
#define HMC5883L_RESOLUTION_1_52				(0x03 << 5) /*  660 - 1.52 Sensor Field range: +/- 2.5  Gauss */
#define HMC5883L_RESOLUTION_2_27				(0x04 << 5) /*  440 - 2.27 Sensor Field range: +/- 4.0  Gauss */
#define HMC5883L_RESOLUTION_2_56				(0x05 << 5) /*  390 - 2.56 Sensor Field range: +/- 4.7  Gauss */
#define HMC5883L_RESOLUTION_3_03				(0x06 << 5) /*  330 - 3.03 Sensor Field range: +/- 5.6  Gauss */
#define HMC5883L_RESOLUTION_4_35				(0x07 << 5) /*  230 - 4.35 Sensor Field range: +/- 8.1  Gauss */
//HMC5883L_MODE_REG BIT DEFINITIONS -> BIT1-BIT0
#define HMC5883L_MODE_CONTINUOUS                (0x00 << 0) /* Continuous measurement mode */
#define HMC5883L_MODE_SINGLE                    (0x01 << 0) /* Single measurement mode DEFAULT*/
#define HMC5883_MODE_IDLE                       (0x02 << 0) /* Idle mode and (3 << 0) idle mode*/

//---------------------------------------------------------------------------------------------------------

#define HMC5883L_CONF_A_SET                     HMC5883L_CONFIG_MODE_NORMAL | HMC5883L_DATA_OUT_RATE_15_HZ | HMC5883L_SAMPLE_AVG_8
#define HMC5883L_CONF_B_SET                     HMC5883L_RESOLUTION_0_92
#define HMC5883L_MODE_SET                       HMC5883L_MODE_CONTINUOUS

#define HMC5883L_SELF_TEST_CONF_A_SET           HMC5883L_CONFIG_MODE_POS_BIAS | HMC5883L_DATA_OUT_RATE_15_HZ | HMC5883L_SAMPLE_AVG_8
#define HMC5883L_SELF_TEST_CONF_B_SET           HMC5883L_RESOLUTION_2_56
#define HMC5883L_SELF_TEST_MODE_SET             HMC5883L_MODE_CONTINUOUS

uint8_t HMC5883L_init(void);
void HMC5883L_write(uint8_t hmc5883l_reg, uint8_t data);
uint8_t HMC5883L_read(uint8_t hmc5883l_reg);
void HMC5883L_set_config(uint8_t configA, uint8_t configB, uint8_t mode);
void HMC5883L_read_axis_LSB(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis);

#endif	/* HMC5883L_H */

