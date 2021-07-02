/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-07-02 11:33:38
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-03 00:32:23
 */
#include "screen_printf.h"
#include "stdarg.h"	 

#define FONT 8
#define ROW 8
#define LIST 21

void screen_printf(char *String, ...)
{
    static char buff[8][21] = {0};
    static char str[21*8] = {0};
    static uint8_t pos_list = 0, pos_row = 0;
    uint8_t *pos;


	va_list argptr;
	va_start(argptr, String);
	(void)vsprintf(str, String, argptr);
	va_end(argptr);

    pos = str;
    while(*pos != '\0')
    {
        if((*pos >= ' ') && (*pos <= '~'))
        {
            OLED_ShowChar(pos_list, pos_row, *pos, FONT, 1);
            pos++;
            pos_row = pos_row + (pos_list + 1)/LIST;
            pos_list = (pos_list+1)%LIST;
        }

    }
}