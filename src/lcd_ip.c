/*****************************************************************************
* Filename:          Y:\Custom_IP\MyProcessorIPLib/drivers/lcd_ip_v1_00_a/src/lcd_ip.c
* Version:           1.00.a
* Description:       lcd_ip Driver Source File
* Date:              Mon Dec 19 17:47:23 2022 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "lcd_ip.h"

/************************** Function Definitions ***************************/

/*
* Funcion para mandar un dato imprimible a la LCD
* @param data codigo ASCII del caracter
*/
void lcd_write_data(char data)
{
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, DATA | RW_ENABLE_MASK | data);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, DATA | data);
    return;
}


/*
* Funcion para enviar un comando especifico a la LCD
* @param cmd comando a enviar
*/
void lcd_write_cmd(char cmd)
{
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | cmd);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | cmd);
    return;
}

/*
* Esta funcion envia el comando para retornar el cursor a la posicion inicial en el display
*/
void lcd_CursorHome_cmd(void)
{
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x02);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x02);
    return;
}

/*
* Esta funcion envia el comando limpiar el display
*/
void lcd_ClearDisplay_cmd(void)
{
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x01);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x01);
    return;
}

/*
* Establece el cursor en la direccion especificada
* @param address direccion especifica para colocar el cursor
*/
void lcd_SetAddress(char address)
{
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x80 | address);
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x80 | address);
    return;
}

/*
* Imprime una cadena de hasta 16 caracteres
* @param string puntero a la cadena de caracteres
*/
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
* Imprime un numero entero de hasta 4 cifras
* @param number numero a imprimir
*/
void lcd_print_int(int number)
{
    int remainder, i = 0;
    int display[4];
    if(number > 10000)
    {
        number %= 10000;    // Si el numero tiene mas de 4 cifras, se toman las 4 cifras menos significativas
    }
    while (number != 0)     // Separar cada cifra del numero y colocarlas en el arreglo display
    {
        display[i] = number % 10;
        number = number / 10;
        i++;
    }
    while (i >= 0)
    {
        lcd_write_data(display[i] + 0x30);      // Mandar a la LCD el codigo ASCII del digito
        i--;
    }
    return;
    
}

/*
* Envia un caracter ASCII al recuadro especificado en la LCD. Los recuadros se organizan de izquierda a derecha
* comenzando por el numero 0 en la primera linea hasta el 31 en la segunda.
* @param data caracter ASCII a enviar
* @param frame indice del recuadro (valor entre 0 - 32)
*/
void send_to_frame(char data, char frame)
{
    char address;
    address = (frame > 16) ? (address + 0x40) : frame;
    lcd_SetAddress(address);
    lcd_write_data(data);
    return;
}
