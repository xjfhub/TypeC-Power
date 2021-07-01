/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-07-01 00:20:40
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-02 01:24:09
 */
#include "input.h"
#include "encoder.h"

#define QUADRUPLE 0 //AB上升下降都采集 四倍频

/**
 * @description: 获取按键状态
 * @param {KEY} num
 * @return {*}
 */
Key_type get_key(uint8_t num)
{
    static uint8_t new_state[KEY_NUM] = {0};
    static uint8_t last_state[KEY_NUM] = {0};
    static uint32_t press_time[KEY_NUM] = {0};
    static uint32_t last_press_time[KEY_NUM] = {0};
    Key_type key = {0};

    last_state[num] = new_state[num];
    switch (num)
    {
    case ON_OFF:
    {
        new_state[num] = !HAL_GPIO_ReadPin(ON_OFF_GPIO_Port, ON_OFF_Pin);
        break;
    }
    case SHUTDOWN:
    {
        new_state[num] = !HAL_GPIO_ReadPin(SHUTDOWN_GPIO_Port, SHUTDOWN_Pin);
        break;
    }
    case ENC0:
    {
        new_state[num] = !HAL_GPIO_ReadPin(S1_M_GPIO_Port, S1_M_Pin);
        break;
    }
    case ENC1:
    {
        new_state[num] = !HAL_GPIO_ReadPin(S2_M_GPIO_Port, S2_M_Pin);
        break;
    }
    default:
    {
        break;
    }
    }
    key.state = new_state[num];
    if(new_state[num] == 1)     
    {
        if ((last_state[num] == 0))//press
        {
            key.press = 1;
            last_press_time[num] = press_time[num];
            press_time[num] = sys_time_ms;
        }
        else
        {
            key.continual_time = sys_time_ms - press_time[num];
        }
    }
    else
    {
        if(last_state[num] == 1)     //release
        {
            key.release = 1;
        }
    }
    key.gap_time = press_time[num] - last_press_time[num];
    return key;
}
/**
 * @description: 
 * @param {uint16_t} *cnt
 * @return {*}
 */
#if QUADRUPLE
int8_t get_cnt(uint8_t num)
{
    static uint8_t last_A[2] = {1, 1}, last_B[2] = {1, 1};
    static uint8_t new_A[2], new_B[2];
    
    last_A[num] = new_A[num];
    last_B[num] = new_B[num];
    if (num == 0)
    {
     	new_A[0] = HAL_GPIO_ReadPin(S1_A_GPIO_Port, S1_A_Pin);
	    new_B[0] = HAL_GPIO_ReadPin(S1_B_GPIO_Port, S1_B_Pin);
    }
    if (num == 1)
    {
        new_A[1] = HAL_GPIO_ReadPin(S2_A_GPIO_Port, S2_A_Pin);
        new_B[1] = HAL_GPIO_ReadPin(S2_B_GPIO_Port, S2_B_Pin);  
    }

    if(new_A[num] != last_A[num])
    {
        if(new_A[num] != new_B[num])
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    if(new_B[num] != last_B[num])
    {
        if(new_A[num] != new_B[num])
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

#else
int8_t get_cnt(uint8_t num)
{
    static uint8_t last_A[2] = {1, 1}, last_B[2] = {1, 1};
    static uint8_t new_A[2], new_B[2];

    last_A[num] = new_A[num];
    last_B[num] = new_B[num];
    if (num == 0)
    {
     	new_A[0] = HAL_GPIO_ReadPin(S1_A_GPIO_Port, S1_A_Pin);
	    new_B[0] = HAL_GPIO_ReadPin(S1_B_GPIO_Port, S1_B_Pin);
    }
    if (num == 1)
    {
        new_A[1] = HAL_GPIO_ReadPin(S2_A_GPIO_Port, S2_A_Pin);
        new_B[1] = HAL_GPIO_ReadPin(S2_B_GPIO_Port, S2_B_Pin);
    }

    if((new_A[num] == GPIO_PIN_RESET) && (new_B[num] == GPIO_PIN_RESET))
    {
        if ((last_A[num] == GPIO_PIN_RESET) && (last_B[num] == GPIO_PIN_SET))
        {
            return 1;
        }
        if ((last_A[num] == GPIO_PIN_SET) && (last_B[num] == GPIO_PIN_RESET))
        {
            return -1;
        }
    }
    return 0;
}
#endif
