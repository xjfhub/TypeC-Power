/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-07-01 00:18:44
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-03 00:31:44
 */
#ifndef INPUT_H
#define INPUT_H
#include "main.h"

enum KEY{ON_OFF, SHUTDOWN, U_SET, I_SET, KEY_NUM};
enum KEY_STATE{OFF, PRESS, RELEASE, ON};

typedef struct{
    uint8_t state;              //����״̬  b00,
    uint32_t continual_time;    //���³���ʱ��  �����жϳ���
    uint32_t gap_time;          //���ΰ��¼��ʱ�� �����ж�����
}Key_type;

typedef struct
{
    Key_type key_switch;
    Key_type key_shutdown;
    Key_type key_U_set;
    Key_type key_I_set;
    int8_t ENC_U_adj;
    int8_t ENC_I_adj;
}Input_type;

extern Input_type g_input;

Key_type get_key(uint8_t num);
int8_t get_cnt(uint8_t num);

#endif
