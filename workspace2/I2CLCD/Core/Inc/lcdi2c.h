#ifndef LCDI2C_H
#define LCDI2C_H
//ALL ADDRESS
#define ADDRS_LCD_I2C 0x27
#define LCD_RS (1<<0)
#define LCD_RW (1<<1)
#define LCD_EN (1<<2)
#define LCD_BL (1<<3) //BACKLIGHT
#define LCD_D4 (1<<4)
#define LCD_D5 (1<<5)
#define LCD_D6 (1<<6)
#define LCD_D7 (1<<7)

//COMANDS

#define LCD_CLEAR (1<<0)
#define LCD_RET_H (1<<1)
#define LCD_ENTRY_M (1<<2)
#define LCD_DIS_ON (1<<3)
#define LCD_FUN_SET (1<<4)


///FLAGS PARA ENTRY MODE SET
#define LCD_EM_L (1<<1)
#define LCD_EM_R (0<<1)
//FLAGS FOR DISPLAY CONTROL
#define LCD_CTR_ON (1<<3)
#define LCD_CTR_OFF (0<<3)
#define LCD_CTR_CON (1<<1)
#define LCD_CTR_COF (0<<1)

#endif /* INC_LCDI2C_H_ */
