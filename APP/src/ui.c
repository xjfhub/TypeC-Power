/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-06-23 20:53:57
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-03 00:30:10
 */
#include "ui.h"
#include "oled.h"

#define FONT 8

void main_ui(Power_type set, Power_type atcual)
{
	uint8_t str[24] = {0};
    uint8_t current_x=0, current_y=0;
    uint8_t line;

    OLED_ShowString(0, 0, "  Type-C Power  ", 16, 1);
    
    line = 2;
    OLED_ShowString(0, (line++)*FONT, "       set   atcual ", FONT, 1);

    sprintf(str, "Uin :% 5.2fV % 5.2fV", set.Uin, atcual.Uin);
    OLED_ShowString(0, (line++)*FONT, str, FONT, 1);

    sprintf(str, "Iin :% 5.2fA % 5.2fA", set.Iin, atcual.Iin);
    OLED_ShowString(0, (line++)*FONT, str, FONT, 1);

    sprintf(str, "Umid:% 5.2fV % 5.2fV", set.Um, atcual.Um);
    OLED_ShowString(0, (line++)*FONT, str, FONT, 1);

    sprintf(str, "Uout:% 5.2fV % 5.2fV", set.Uout, atcual.Uout);
    OLED_ShowString(0, (line++)*FONT, str, FONT, 1);

    sprintf(str, "Iout:% 5.2fA % 5.2fA", set.Iout, atcual.Iout);
    OLED_ShowString(0, (line++)*FONT, str, FONT, 1);

    OLED_Refresh();
}
