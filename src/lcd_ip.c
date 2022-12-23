/*****************************************************************************
* Filename:          Y:\Custom_IP\MyProcessorIPLib/drivers/lcd_ip_v1_00_a/src/lcd_ip.c
* Version:           1.00.a
* Description:       lcd_ip Driver Source File
* Date:              Mon Dec 19 17:47:23 2022 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "lcd_ip.h"

/************************** Function Definitions ***************************/

void lcd_write_data(char data)
{
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, DATA | RW_ENABLE_MASK | data);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, DATA | data);
    return;
}

void lcd_write_cmd(char cmd)
{
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | cmd);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | cmd);
    return;
}

void lcd_CursorHome_cmd(void)
{
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x02);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x02);
    return;
}

void lcd_ClearDisplay_cmd(void)
{
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x01);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x01);
    return;
}

void lcd_SetAddress(char address)
{
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x80 | address);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x80 | address);
    return;
}

void lcd_print_string(char* string)
{
    char i = 0;
    while (string[i] != '\0')
    {
        lcd_write_data(string[i]);
        i++;
        if(i > 15)
            break;
    }
    return;
}
/*
void lcd_print_int(int number)
{
    int remainder, i = 0;
    int display[4];
    while (number != 0)
    {
        display[i] = number % 10;
        number = number / 10;
        i++;
    }
    
}
*/
