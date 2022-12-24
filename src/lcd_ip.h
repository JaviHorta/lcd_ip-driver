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

/************************** Function Prototypes ****************************/
void lcd_write_data(char data);
void lcd_write_cmd(char cmd);
void lcd_CursorHome_cmd(void);
void lcd_ClearDisplay_cmd(void);
void lcd_SetAddress(char address);
void lcd_print_string(char* string);
void lcd_print_int(int number);
void send_to_frame(char data, char frame);

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
