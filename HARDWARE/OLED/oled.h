/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2020-11-03 12:13:37
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-03 00:31:02
 */
#ifndef __OLED_H
#define __OLED_H 

#include "stdlib.h"	
#include "main.h"
#define u8 unsigned char
#define u16 unsigned short int
#define u32 unsigned long int

//-----------------OLED??????---------------- 

#define OLED_SCL_Clr() HAL_GPIO_WritePin(OLED_D0_GPIO_Port, OLED_D0_Pin, GPIO_PIN_RESET)//SCL
#define OLED_SCL_Set() HAL_GPIO_WritePin(OLED_D0_GPIO_Port, OLED_D0_Pin, GPIO_PIN_SET)

#define OLED_SDA_Clr() HAL_GPIO_WritePin(OLED_D1_GPIO_Port, OLED_D1_Pin, GPIO_PIN_RESET)//SDA
#define OLED_SDA_Set() HAL_GPIO_WritePin(OLED_D1_GPIO_Port, OLED_D1_Pin, GPIO_PIN_SET)

#define OLED_RES_Clr() HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, GPIO_PIN_RESET)//RES
#define OLED_RES_Set() HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, GPIO_PIN_SET)

#define OLED_DC_Clr()  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET)//DC
#define OLED_DC_Set()  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET)

#define OLED_CMD  0	
#define OLED_DATA 1	

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_Init(void);

#endif

