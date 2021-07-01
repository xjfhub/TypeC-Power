/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-06-23 20:53:57
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-02 00:40:27
 */
#include "ui.h"

#define FONT 8

void main_ui(Power_type set, Power_type atcual)
{
	uint8_t str[24] = {0};
    uint8_t current_x=0, current_y=0;
    uint8_t line;

    OLED_ShowString(0, 0, "  Type-C Power  ", 16, 1);
    line = 3;
    sprintf(str, "Uin : %4.1fV 4.1fV", set.Uin, atcual.Uin);
    OLED_ShowString(0, (line++)*FONT, str, FONT, 1);

    sprintf(str, "Iin : %4.1fA %4.1fA", set.Iin, atcual.Iin);
    OLED_ShowString(0, (line++)*FONT, str, FONT, 1);

    sprintf(str, "Umid: %4.1fV 4.1fV", set.Um, atcual.Um);
    OLED_ShowString(0, (line++)*FONT, str, FONT, 1);

    sprintf(str, "Uout: %4.1fV 4.1fV", set.Uout, atcual.Uout);
    OLED_ShowString(0, (line++)*FONT, str, FONT, 1);

    sprintf(str, "Iout: %4.1fV 4.1fV", set.Iout, atcual.Iout);
    OLED_ShowString(0, (line++)*FONT, str, FONT, 1);

    OLED_Refresh();
}
