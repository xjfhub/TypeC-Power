/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-07-01 00:18:44
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-02 01:16:46
 */
#ifndef INPUT_H
#define INPUT_H
#include "main.h"

enum KEY{ON_OFF, SHUTDOWN, U_SET, I_SET, KEY_NUM};
typedef struct{
    uint8_t state;              //按键状态
    uint8_t press;              //按下
    uint8_t release;            //释放
    uint32_t continual_time;    //按下持续时间
    uint32_t gap_time;          //两次按下间隔时间
}Key_type;

typedef struct
{
    Key_type key_on_off;
    Key_type key_shutdown;
    Key_type key_U_set;
    Key_type key_I_set;
    int8_t ENC_U_adj;
    int8_t ENC_I_adj;
}Input_type;

Key_type get_key(uint8_t num)
int8_t get_cnt(uint8_t num);

#endif