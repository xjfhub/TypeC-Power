/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-06-23 20:53:57
 * @LastEditors: Xjf
 * @LastEditTime: 2021-06-23 23:19:00
 */
#include "ui.h"
#include "oled.h"

void main_ui(void)
{
	uint8_t str[24] = {0};
    uint8_t current_x=0, current_y=0;

    OLED_ShowString(0, 0, "  Type-C Power  ", 16, 1);

    sprintf(str, "Vin:%4.1fV",adc_buff[0]/100.0);
    OLED_ShowString(0, 24, str, 8, 1);

    sprintf(str, "Iin:%4.1fA",adc_buff[1]/100.0-19.8);
    OLED_ShowString(0, 40, str, 8, 1);

    sprintf(str, "Vmid:%4.1fV",adc_buff[2]/100.0);
    OLED_ShowString(32, 56, str, 8, 1);

    sprintf(str, "Vout:%4.1fV",adc_buff[3]/100.0);
    OLED_ShowString(64, 24, str, 8, 1);

    sprintf(str, "Iout:%4.1fA",adc_buff[4]/100.0-19.8);
    OLED_ShowString(64, 40, str, 8, 1);

    // sprintf(str, "cnt1:%4d",cnt1);
    // OLED_ShowString(0, 56, str, 8, 1);

    // sprintf(str, "cnt2:%4d",cnt2);
    // OLED_ShowString(64, 56, str, 8, 1);

    OLED_Refresh();
}
