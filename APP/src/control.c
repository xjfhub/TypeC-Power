/*
 * @Description: 电压控制主要相关程序
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-07-01 00:22:14
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-02 18:37:31
 */
#include "control.h"
#include "input.h"
#include "tim.h"

/**
 * @description: 获取实际电源参数，降AD采样信号转换成实际信号
 * @param {uint32_t} adc adc转换数组
 * @param {Power_type} *atcual 计算的实际电压电流
 * @return {*}
 */
static void get_atcual_power(uint32_t *adc, Power_type *atcual)
{
    atcual->Uin = adc[0]/105;
    atcual->Iin = adc[1]/105;
    atcual->Um = adc[2]/105;
    atcual->Uout = adc[3]/105;
    atcual->Iout = adc[4]/105;
}
/**
 * @description: 获取按键和编码器控制信息
 * @param {Input_type} *input
 * @return {*}
 */
static void get_input(Input_type *input)
{
    input->key_switch = get_key(ON_OFF);
    input->key_shutdown = get_key(SHUTDOWN);
    input->key_U_set = get_key(U_SET);
    input->key_I_set = get_key(I_SET);
    input->ENC_U_adj = get_cnt(0);
    input->ENC_I_adj = get_cnt(1);
}
/**
 * @description: 
 * @param {Input_type} input 按键输入信号
 * @param {Power_type} *set 设定电压
 * @return {*}
 */
static void set_power(Input_type input, Power_type *set)
{
    set->Uin = 20;
    set->Iin = 1;
    set->Um = ((set->Uin > set->Uout)?set->Uin:set->Uout) + 1;
    set->Uout = set->Uout + 0.1*input.ENC_U_adj;
    set->Iout = set->Iout + 0.1*input.ENC_I_adj;
    set->enable = (input.key_switch.state == RELEASE)?(!set->enable):(set->enable);
}
static void pwm_control(Power_type set, Power_type atcual)
{
    uint16_t boost_pwm, buck_pwm;
    uint8_t boost_l_en, boost_h_en, buck_l_en, buck_h_en;
    
    /*升压控制*/
    /* 如果输入电流为正，打开上管提升效率*/
    if(atcual.Iin > 0.02)
    {
        boost_h_en = ENABLE;
    }
    else
    {
        boost_h_en = DISABLE;
    }
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
    get_atcual_power(g_adc_buff, &g_power_atcual);
    get_input(&g_input);
    set_power(g_input, &g_power_set);
    pwm_control(g_power_set, g_power_atcual);
}
