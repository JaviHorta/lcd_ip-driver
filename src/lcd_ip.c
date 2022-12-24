/*****************************************************************************
* Filename:          Y:\Custom_IP\MyProcessorIPLib/drivers/lcd_ip_v1_00_a/src/lcd_ip.c
* Version:           2.00.a
* Description:       lcd_ip Driver Source File
* Date:              Mon Dec 19 17:47:23 2022 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "lcd_ip.h"

/************************** Function Definitions ***************************/

void lcd_write_data(char data)
{
    while(LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1);      // Espera a que este lista la LCD
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, DATA | RW_ENABLE_MASK | data);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, DATA | data);
    return;
}

void lcd_write_cmd(char cmd)
{
    while(LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1);      // Espera a que este lista la LCD
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | cmd);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | cmd);
    return;
}

void lcd_CursorHome_cmd(void)
{
    while(LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1);      // Espera a que este lista la LCD
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x02);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x02);
    return;
}

void lcd_ClearDisplay_cmd(void)
{
    while(LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1);      // Espera a que este lista la LCD
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x01);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x01);
    return;
}

void lcd_SetAddress(char address)
{
    while(LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1);      // Espera a que este lista la LCD
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

void lcd_print_int(int number)
{
    int i = 0;
    int display[4];
    if(number > 10000)
    {
        number %= 10000;    // Si el numero tiene mas de 4 cifras, se toman las 4 cifras menos significativas
    }
    while (number != 0)     // Separar cada cifra del numero y colocarlas en el arreglo display
    {
        display[i] = (number % 10) + 0x30;
        number = number / 10;
        i++;
    }
    i--;
    while (i >= 0)
    {
        lcd_write_data(display[i]);      // Mandar a la LCD el codigo ASCII del digito
        i--;
    }
    return;
}

void lcd_send_to_frame(char data, char frame)
{
    char address;
    address = (frame >= 16) ? ((frame % 16) + 0x40) : frame;
    lcd_SetAddress(address);
    lcd_write_data(data);
    return;
}

void init_delay()
{
    volatile int i;
    do
    {
        for(i = 0; i < 100000; i++);
    } while (LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1);
    return;
}
