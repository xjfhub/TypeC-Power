/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-07-01 00:22:14
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-02 01:27:20
 */
#include "control.h"
#include "tim.h"

/**
 * @description: 获取实际电源参数，降AD采样信号转换成实际信号
 * @param {uint32_t} adc
 * @param {Power_type} *atcual
 * @return {*}
 */
static void get_atcual_power(uint32_t adc[], Power_type *atcual)
{
    atcual->Uin = adc[0]/105;
    atcual->Iin = adc[1]/105;
    atcual->Um = adc[2]/105;
    atcual->Uout = adc[3]/105;
    atcual->Iout = adc[4]/105;
}
/**
 * @description: 
 * @param {Input_type} *input
 * @return {*}
 */
static void get_input(Input_type *input)
{
    input.key_on_off = get_key(ON_OFF);
    input.key_shutdown = get_key(SHUTDOWN);
    input.key_U_set = get_key(U_SET);
    input.key_I_set = get_key(I_SET);
    input.ENC_U_adj = get_cnt(0);
    input.ENC_I_adj = get_cnt(1);
}
/**
 * @description: 
 * @param {Input_type} input
 * @param {Power_type} *set
 * @return {*}
 */
static void set_power(Input_type input, Power_type *set)
{
    atcual->Uin = adc[0]/105;
    atcual->Iin = adc[1]/105;
    atcual->Um = adc[2]/105;
    atcual->Uout = adc[3]/105;
    atcual->Iout = adc[4]/105;
}
static void pwm_control(Power_type set, Power_type atcual)
{
    /*升压控制*/
    if (g_adc_buff[2] < v_m_set)
    {
        __HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 200);
        HAL_TIMEx_PWMN_Start(&htim16, TIM_CHANNEL_1); //TIM16_CH1N L
    }
    else
    {
        __HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 200);
        HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1); //TIM16_CH1N L
    }
    /*降压控制*/
    if (g_adc_buff[3] < v_out_set)
    {
        __HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, ((float)v_out_set / v_m_set) * 200 + (v_out_set - g_adc_buff[3]) / 50);
        HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);    //TIM17_CH1 L
        HAL_TIMEx_PWMN_Start(&htim17, TIM_CHANNEL_1); //TIM17_CH1N H
    }
    else
    {
        __HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 0);
        HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);    //TIM17_CH1 L
        HAL_TIMEx_PWMN_Stop(&htim17, TIM_CHANNEL_1); //TIM17_CH1N H
    }
}
void control(void)
{
    get_atcual_power();
    get_input();
    set_power();
    pwm_control();
}
