/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-07-01 00:20:40
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-02 18:39:43
 */
#include "input.h"
#include "encoder.h"

#define QUADRUPLE 0 //AB上升下降都采集 四倍频

/**
 * @description: 获取按键状态
 * @param {KEY} num  按键序号 一共四个按键
 * @return {*}按键状态，长按时间，间隔时间
 */
Key_type get_key(uint8_t num)
{
    static uint8_t new_state[KEY_NUM] = {0};
    static uint8_t last_state[KEY_NUM] = {0};
    static uint32_t press_time[KEY_NUM] = {0};
    static uint32_t last_press_time[KEY_NUM] = {0};
    Key_type key = {0};

    //更新按键状态
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
    //储存按键状态
    key.state = (last_state[num]<<1) | new_state[num];
    switch (key.state)
    {
        case PRESS:         //按下
        {
            last_press_time[num] = press_time[num];     //记录上次按下时间
            press_time[num] = HAL_GetTick();            //更新本次按下时间
            key.continual_time = 0;                     //开始计算长按时间
            key.gap_time = press_time[num] - last_press_time[num];  //计算两次按下间隔时间
            break;
        }
        case ON:            //打开
        {
            key.continual_time = HAL_GetTick(); - press_time[num];
            break;
        }
        case RELEASE:       //释放
        {
            break;
        }
        case OFF:           //关闭
        {
            break;
        }
        default:
        {
            break;
        }
    }
    return key;
}
/**
 * @description: 获取编码器旋转值
 * @param {uint8_t} num 编码器序号 一共两个编码器 
 * @return {*}  正转移位返回 1，反转一位返回 -1 ， 不转返回 0
 */
#if QUADRUPLE       //四倍频     AB上升下降沿都采集
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

<<<<<<< HEAD
#else               //不倍频
=======
#else
>>>>>>> 295d2e61a2435f767282dc710d06e418ab82284e
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
