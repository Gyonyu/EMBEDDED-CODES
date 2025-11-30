#include "lcdi2c.h"
#include "i2c.h"
/*funciones propias o internas*/

static void LCD_SendCommand(uint8_t);
static void LCD_Write4Bits(uint8_t);
static void LCD_PulseEnable(uint8_t);

/*FUnciones propias*/

static void LCD_SendCommand(uint8_t data){
    uint8_t dataH=0xF0 & data;          // High nibble (upper 4 bits)
    uint8_t dataL=(data & 0x0F) << 4;   // Low nibble shifted to upper position

    
    LCD_Write4Bits(dataH|LCD_BACKLIGHT);
    LCD_Write4Bits(dataL|LCD_BACKLIGHT);
}
static void LCD_Write4Bits(uint8_t data){
    I2C_Write(ADDRS_LCD_I2C,data);
    LCD_PulseEnable(data);

}
static void LCD_PulseEnable(uint8_t data){
    I2C_Write(ADDRS_LCD_I2C,data|ENABLE_BIT);
    delay_ms(1);
    I2C_Write(ADDRS_LCD_I2C,data&~ENABLE_BIT);
}

void delay_ms(uint32_t ms){
    for(uint32_t i = 0; i < ms; i++){
        for(volatile uint32_t j = 0; j < 1067; j++);
    }
}

void LCD_Init(void){
    delay_ms(50);  // Wait for LCD power up
    
    LCD_Write4Bits(INTERFACE_8B| LCD_BACKLIGHT);  // 8-bit mode attempt 1
    delay_ms(5);
    LCD_Write4Bits(INTERFACE_8B | LCD_BACKLIGHT);  // 8-bit mode attempt 2
    delay_ms(1);
    LCD_Write4Bits(INTERFACE_8B | LCD_BACKLIGHT);  // 8-bit mode attempt 3
    delay_ms(1);
    LCD_Write4Bits(INTERFACE_4B | LCD_BACKLIGHT);  // Switch to 4-bit mode
    delay_ms(1);
    
    LCD_SendCommand(FUN_SET_4B);    // 0x28: 4-bit, 2 lines, 5x8 font
    LCD_SendCommand(DISPLAY_OFF);   // 0x08: Display off
    LCD_SendCommand(CLEAR_DISPLAY); // 0x01: Clear display
    delay_ms(2);
    LCD_SendCommand(ENTRY_MODE);    // 0x06: Entry mode set
    LCD_SendCommand(COMBINADO_FUNSET); // 0x0C: Display on, cursor off
}
void LCD_Clear(void){
    LCD_SendCommand(CLEAR_DISPLAY);
        delay_ms(2);
}

void LCD_ReturnHome(void){
    LCD_SendCommand(RET_HOME);
        delay_ms(2);
}


void LCD_ScrollLeft(uint8_t scrolls){
    for(uint8_t i=0; i<scrolls;i++){
        LCD_SendCommand(0x18);}
}


void LCD_ScrollRight(uint8_t scrolls){
     for(uint8_t i=0; i<scrolls;i++){
        LCD_SendCommand(0x1C);}
}

void LCD_SendChar(char c){
    uint8_t dataH=0xF0 & c;
    uint8_t dataL=(c & 0X0F)<<4;
    LCD_Write4Bits(dataH|REGISTER_SELECT|LCD_BACKLIGHT);
    LCD_Write4Bits(dataL|REGISTER_SELECT|LCD_BACKLIGHT);
}

void LCD_SendString(const char *str){
    while(*str){
        LCD_SendChar(*str++);
    }
    
}

void LCD_SetCursor(uint8_t row, uint8_t col){
    uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if(row > MAX_ROWS) row = MAX_ROWS - 1;
    LCD_SendCommand(SET_DD_RAM_ADDR | (col + row_offsets[row]));
}