/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-06-23 20:54:05
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-02 18:44:54
 */
#ifndef UI_H
#define UI_H
#include "main.h"

typedef struct
{
    uint8_t menu;
}Menu_type;

void main_ui(Power_type set, Power_type atcual);

#endif
