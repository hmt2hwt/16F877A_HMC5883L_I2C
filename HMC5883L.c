/************************************************************************
*	Program : HMC5883L.c											    *
************************************************************************/
#include "HMC5883L.h"

uint8_t HMC5883L_init(void)
{
    uint8_t identA=0, identB=0, identC=0;
    
    I2C_init();
    
    identA = HMC5883L_read(EMC5883L_IDENT_A_REG);
    identB = HMC5883L_read(EMC5883L_IDENT_B_REG);
    identC = HMC5883L_read(EMC5883L_IDENT_C_REG);
    
    if((identA == 0x48) && (identB == 0x34) && (identC == 0x33))    //H43
        return 0;
    else
        return 1;
}

void HMC5883L_write(uint8_t hmc5883l_reg, uint8_t data)
{
	I2C_start();
    I2C_write(HMC5883L_I2C_ADR_WR);
    I2C_write(hmc5883l_reg);
    I2C_write(data);
    I2C_stop();
}

uint8_t HMC5883L_read(uint8_t hmc5883l_reg)
{
    uint8_t tmp=0;
    
    I2C_start();
    I2C_write(HMC5883L_I2C_ADR_WR);
    I2C_write(hmc5883l_reg);
    I2C_restart();
    I2C_write(HMC5883L_I2C_ADR_RD);
    tmp=I2C_read();
    I2C_stop();
    
	return tmp;
}

void HMC5883L_set_config(uint8_t configA, uint8_t configB, uint8_t mode)
{
    HMC5883L_write(HMC5883L_CONFIG_A_REG, configA);
    HMC5883L_write(HMC5883L_CONFIG_B_REG, configB);
    HMC5883L_write(HMC5883L_MODE_REG, mode);
}
// --- output range  -2048LSB   2047LSB   ----------------
void HMC5883L_read_axis_LSB(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis)
{
    uint8_t val[6]={0};
    
    val[0]=HMC5883L_read(EMC5883L_DATA_OUT_X_LSB_REG);
    val[1]=HMC5883L_read(EMC5883L_DATA_OUT_X_MSB_REG);
    val[2]=HMC5883L_read(EMC5883L_DATA_OUT_Y_LSB_REG);
    val[3]=HMC5883L_read(EMC5883L_DATA_OUT_Y_MSB_REG);
    val[4]=HMC5883L_read(EMC5883L_DATA_OUT_Z_LSB_REG);
    val[5]=HMC5883L_read(EMC5883L_DATA_OUT_Z_MSB_REG);
        
    *x_axis=(val[1] << 8) | val[0];     
    *y_axis=(val[3] << 8) | val[2];
    *z_axis=(val[5] << 8) | val[4];
}