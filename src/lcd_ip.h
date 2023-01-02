/*****************************************************************************
* Filename:          Y:\Custom_IP\MyProcessorIPLib/drivers/lcd_ip_v2_00_a/src/lcd_ip.h
* Version:           2.00.a
* Description:       lcd_ip Driver Header File
* Date:              Fri Dec 23 19:55:53 2022 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef LCD_IP_H
#define LCD_IP_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"
#include "xparameters.h"

/************************** Constant Definitions ***************************/
#define COMMAND 0x000
#define DATA 0x100
#define RW_ENABLE_MASK 0x200
#define RIGTH 0x04
#define LEFT 0x00

/**
 * User Logic Slave Space Offsets
 * -- SLV_REG0 : user logic slave module register 0
 * -- SLV_REG1 : user logic slave module register 1
 */
#define LCD_IP_USER_SLV_SPACE_OFFSET (0x00000000)
#define LCD_IP_SLV_REG0_OFFSET (LCD_IP_USER_SLV_SPACE_OFFSET + 0x00000000)
#define LCD_IP_SLV_REG1_OFFSET (LCD_IP_USER_SLV_SPACE_OFFSET + 0x00000004)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/


/**
 *
 * Write a value to a LCD_IP register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the LCD_IP device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void LCD_IP_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define LCD_IP_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a LCD_IP register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the LCD_IP device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 LCD_IP_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define LCD_IP_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Write/Read 32 bit value to/from LCD_IP user logic slave registers.
 *
 * @param   BaseAddress is the base address of the LCD_IP device.
 * @param   RegOffset is the offset from the slave register to write to or read from.
 * @param   Value is the data written to the register.
 *
 * @return  Data is the data from the user logic slave register.
 *
 * @note
 * C-style signature:
 * 	void LCD_IP_mWriteSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Value)
 * 	Xuint32 LCD_IP_mReadSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define LCD_IP_mWriteSlaveReg0(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (LCD_IP_SLV_REG0_OFFSET) + (RegOffset), (Xuint32)(Value))
#define LCD_IP_mWriteSlaveReg1(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (LCD_IP_SLV_REG1_OFFSET) + (RegOffset), (Xuint32)(Value))

#define LCD_IP_mReadSlaveReg0(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (LCD_IP_SLV_REG0_OFFSET) + (RegOffset))
#define LCD_IP_mReadSlaveReg1(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (LCD_IP_SLV_REG1_OFFSET) + (RegOffset))

/**
 * 
 * Macro para mandar un dato imprimible a la LCD.
 * @param 	data codigo ASCII del caracter
 * 
 */
#define lcd_write_data(data) \
	while(LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1); \
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, DATA | RW_ENABLE_MASK | data); \
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, DATA | data)

/**
 * 
 * Macro para enviar un comando especifico a la LCD.
 * @param 	cmd comando a enviar
 * 
 */
#define lcd_write_cmd(cmd) \
	while(LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1); \
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | cmd); \
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | cmd)

/**
 * 
 * Macro para enviar el comando de retorno del cursor de la LCD a la primera posicion (linea 1, casilla 1)
 * 
*/
#define lcd_CursorHome_cmd() \
	while(LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1); \
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x02); \
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x02)

/**
 * 
 * Macro para enviar el comando de borrar el display LCD
 * 
*/
#define lcd_ClearDisplay_cmd() \
	while(LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1); \
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x01); \
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x01)

/**
 * 
 * Comando para mover el cursor una posición a la izquierda o a la derecha según se indique.
 * @param  	direction indica el sentido del movimiento del cursor (RIGTH o LEFT). 
 * @note	Solo puede tomar los valores definidos como RIGTH o LEFT. Si se pasa cualquier otro valor, el resultado puede que no sea el esperado.
 * 
*/
#define lcd_MoveCursor_cmd(direction) \
	lcd_write_cmd(0x10 | direction) \

/**
 * Establece el cursor de la LCD en la direccion especificada.
 * @param 	address direccion especifica para colocar el cursor
*/
#define lcd_SetAddress(address) \
	while(LCD_IP_mReadReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG1_OFFSET) != 1); \
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | RW_ENABLE_MASK | 0x80 | address); \
    LCD_IP_mWriteReg(XPAR_LCD_IP_0_BASEADDR, LCD_IP_SLV_REG0_OFFSET, COMMAND | 0x80 | address) \

/************************** Function Prototypes ****************************/

/**
 * Imprime una cadena de hasta 16 caracteres.
 * @param string puntero a la cadena de caracteres
*/
void lcd_print_string(char* string);

/**
 * Imprime un numero entero de hasta 4 cifras.
 * @param number numero a imprimir
*/
void lcd_print_int(int number);

/**
 * Envia un caracter ASCII a la casilla especificada en la LCD. Las casillas se organizan de izquierda a derecha
 * comenzando por el numero 0 en la primera linea hasta el 31 en la segunda.
 * @param data caracter ASCII a enviar.
 * @param frame indice de la casilla (valor entre 0 - 31)
*/
void lcd_send_to_frame(char data, char frame);

/**
 * Realiza una espera para permitir la inicializacion de la LCD cuando se inicia o se resetea el sistema. Esta
 * funcion siempre debe invocarse al inicio de cualquier programa, de lo contrario no se garantiza un correcto
 * funcionamiento.
*/
void lcd_init_delay();

/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the LCD_IP instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus LCD_IP_SelfTest(void * baseaddr_p);

#endif /** LCD_IP_H */
