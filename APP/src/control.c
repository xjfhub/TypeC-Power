/*
 * @Description: ��ѹ������Ҫ��س���
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-07-01 00:22:14
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-03 01:38:20
 */
#include "control.h"
#include "input.h"
#include "tim.h"

/**
 * @description: ��ȡʵ�ʵ�Դ��������AD�����ź�ת����ʵ���ź�
 * @param {uint32_t} adc adcת������
 * @param {Power_type} *atcual �����ʵ�ʵ�ѹ����
 * @return {*}
 */
static void get_atcual_power(uint32_t *adc, Power_type *atcual)
{
    atcual->Uin = adc[0]/105.0;
    atcual->Iin = (adc[1]-1980.0)/372.0;
    atcual->Um = adc[2]/105.0;
    atcual->Uout = adc[3]/105.0;
    atcual->Iout = (adc[4]-1980.0)/372.0;
}
/**
 * @description: ��ȡ�����ͱ�����������Ϣ
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
 * @param {Input_type} input ���������ź�
 * @param {Power_type} *set �趨��ѹ
 * @return {*}
 */
static void set_power(Input_type input, Power_type *set)
{
    set->Uin = 20;
    set->Iin = 1;
    set->Um = ((set->Uin > set->Uout)?set->Uin:set->Uout) + 1;
    set->Uout = set->Uout + 1*input.ENC_U_adj;
    set->Iout = set->Iout + 0.1*input.ENC_I_adj;
    set->enable = (input.key_switch.state == RELEASE)?(!set->enable):(set->enable);
}
static void pwm_control(Power_type set, Power_type atcual)
{
    uint16_t boost_pwm, buck_pwm;
    uint8_t boost_l_en, boost_h_en, buck_l_en, buck_h_en;
    
    /*��ѹ����*/
    /* �������Ϊ�������Ϲ�����Ч��*/
    if(atcual.Iin > set.Iin)    //�����������
    {
        boost_l_en = DISABLE;
        boost_h_en = DISABLE;
    }
    else
    {
        if (atcual.Um < set.Um)
        {
            boost_l_en = ENABLE;
        }
        else
        {
            boost_l_en = DISABLE;
        }
        if(atcual.Iin > 0.02)
        {
            boost_h_en = ENABLE;
        }
        else
        {
            boost_h_en = DISABLE;
        }
    }

    if (atcual.Um < set.Um)
    {
        boost_pwm = 500 - (set.Um - atcual.Um)*2;
    }
    else
    {
        boost_pwm = 500;
    }
    if(boost_l_en == ENABLE)
    {
        HAL_TIMEx_PWMN_Start(&htim16, TIM_CHANNEL_1);//TIM16_CH1N L
    }
    else
    {
        HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1); //TIM16_CH1N L
    }
    // if(boost_h_en == ENABLE)
    // {
    //     HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);//TIM16_CH1 H
    // }
    // else
    // {
        HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1); //TIM16_CH1 H
    // }
    __HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, boost_pwm);
//    if (g_adc_buff[2] < v_m_set)
//    {
//        __HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 200);
//        HAL_TIMEx_PWMN_Start(&htim16, TIM_CHANNEL_1); //TIM16_CH1N L
//    }
//    else
//    {
//        __HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 200);
//        HAL_TIMEx_PWMN_Stop(&htim16, TIM_CHANNEL_1); //TIM16_CH1N L
//    }
//    /*��ѹ����*/
//    if (g_adc_buff[3] < v_out_set)
//    {
//        __HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, ((float)v_out_set / v_m_set) * 200 + (v_out_set - g_adc_buff[3]) / 50);
//        HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);    //TIM17_CH1 L
//        HAL_TIMEx_PWMN_Start(&htim17, TIM_CHANNEL_1); //TIM17_CH1N H
//    }
//    else
//    {
//        __HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 0);
//        HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);    //TIM17_CH1 L
//        HAL_TIMEx_PWMN_Stop(&htim17, TIM_CHANNEL_1); //TIM17_CH1N H
//    }
}
void control(void)
{
    get_atcual_power(g_adc_buff, &g_power_atcual);
    get_input(&g_input);
    set_power(g_input, &g_power_set);
    pwm_control(g_power_set, g_power_atcual);
}
