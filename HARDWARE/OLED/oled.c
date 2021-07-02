#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"

u8 OLED_GRAM[144][8];
void delay(void)
{
	u8 t = 3;
	while (t--);
}
void OLED_WR_Byte(u8 dat, u8 cmd)
{
	u8 i;
	if (cmd)
		OLED_DC_Set();
	else
		OLED_DC_Clr();
	for (i = 0; i < 8; i++)
	{
		OLED_SCL_Clr();

		delay();
		if (dat & 0x80)
			OLED_SDA_Set();
		else
			OLED_SDA_Clr();
		delay();
		OLED_SCL_Set();
		delay();
		dat <<= 1;
	}
	OLED_DC_Set();
}
void OLED_ColorTurn(u8 i)
{
	if (i == 0)
	{
		OLED_WR_Byte(0xA6, OLED_CMD); //������ʾ
	}
	if (i == 1)
	{
		OLED_WR_Byte(0xA7, OLED_CMD); //��ɫ��ʾ
	}
}
void OLED_DisplayTurn(u8 i)
{
	if (i == 0)
	{
		OLED_WR_Byte(0xC8, OLED_CMD); //������ʾ
		OLED_WR_Byte(0xA1, OLED_CMD);
	}
	if (i == 1)
	{
		OLED_WR_Byte(0xC0, OLED_CMD); //��ת��ʾ
		OLED_WR_Byte(0xA0, OLED_CMD);
	}
}

void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D, OLED_CMD); //��ɱ�ʹ��?
	OLED_WR_Byte(0x14, OLED_CMD); //������ɱ�?
	OLED_WR_Byte(0xAF, OLED_CMD); //������Ļ
}

void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D, OLED_CMD); //��ɱ�ʹ��?
	OLED_WR_Byte(0x10, OLED_CMD); //�رյ�ɱ�?
	OLED_WR_Byte(0xAE, OLED_CMD); //�ر���Ļ
}

void OLED_Refresh(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD); //��������ʼ��ַ
		OLED_WR_Byte(0x02, OLED_CMD);	  //���õ�����ʼ��ַ
		OLED_WR_Byte(0x10, OLED_CMD);	  //���ø�����ʼ��ַ
		for (n = 0; n < 128; n++)
			OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);
	}
}

void OLED_Clear(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		for (n = 0; n < 128; n++)
		{
			OLED_GRAM[n][i] = 0; //�����������?
		}
	}
	OLED_Refresh(); //������ʾ
}

void OLED_DrawPoint(u8 x, u8 y, u8 t)
{
	u8 i, j;
	i = y / 8;
	j = y % 8;
	if (t)
	{
		OLED_GRAM[x][i] |= 1 << j;
	}
	else
	{
		OLED_GRAM[x][i] &= ~(1 << j);
	}
}

void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2, u8 mode)
{
	u16 t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1; //������������
	delta_y = y2 - y1;
	uRow = x1; //�����������?
	uCol = y1;
	if (delta_x > 0)
		incx = 1; //���õ�������
	else if (delta_x == 0)
		incx = 0; //��ֱ��
	else
	{
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0; //ˮƽ��
	else
	{
		incy = -1;
		delta_y = -delta_x;
	}
	if (delta_x > delta_y)
		distance = delta_x; //ѡȡ��������������
	else
		distance = delta_y;
	for (t = 0; t < distance + 1; t++)
	{
		OLED_DrawPoint(uRow, uCol, mode); //����
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
}

void OLED_DrawCircle(u8 x, u8 y, u8 r)
{
	int a, b, num;
	a = 0;
	b = r;
	while (2 * b * b >= r * r)
	{
		OLED_DrawPoint(x + a, y - b, 1);
		OLED_DrawPoint(x - a, y - b, 1);
		OLED_DrawPoint(x - a, y + b, 1);
		OLED_DrawPoint(x + a, y + b, 1);

		OLED_DrawPoint(x + b, y + a, 1);
		OLED_DrawPoint(x + b, y - a, 1);
		OLED_DrawPoint(x - b, y - a, 1);
		OLED_DrawPoint(x - b, y + a, 1);

		a++;
		num = (a * a + b * b) - r * r; //���㻭�ĵ���Բ�ĵľ���
		if (num > 0)
		{
			b--;
			a--;
		}
	}
}

void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size1, u8 mode)
{
	u8 i, m, temp, size2, chr1;
	u8 x0 = x, y0 = y;
	if (size1 == 8)
		size2 = 6;
	else
		size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2); 
	chr1 = chr - ' ';											   
	for (i = 0; i < size2; i++)
	{
		if (size1 == 8)
		{
			temp = asc2_0806[chr1][i];
		} 
		else if (size1 == 12)
		{
			temp = asc2_1206[chr1][i];
		} 
		else if (size1 == 16)
		{
			temp = asc2_1608[chr1][i];
		} 
		else
			return;
		for (m = 0; m < 8; m++)
		{
			if (temp & 0x01)
				OLED_DrawPoint(x, y, mode);
			else
				OLED_DrawPoint(x, y, !mode);
			temp >>= 1;
			y++;
		}
		x++;
		if ((size1 != 8) && ((x - x0) == size1 / 2))
		{
			x = x0;
			y0 = y0 + 8;
		}
		y = y0;
	}
}

void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 size1, u8 mode)
{
	while ((*chr >= ' ') && (*chr <= '~')) 
	{
		OLED_ShowChar(x, y, *chr, size1, mode);
		if (size1 == 8)
			x += 6;
		else
			x += size1 / 2;
		chr++;
	}
}

//m^n
u32 OLED_Pow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--)
	{
		result *= m;
	}
	return result;
}

void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size1, u8 mode)
{
	u8 t, temp, m = 0;
	if (size1 == 8)
		m = 2;
	for (t = 0; t < len; t++)
	{
		temp = (num / OLED_Pow(10, len - t - 1)) % 10;
		if (temp == 0)
		{
			OLED_ShowChar(x + (size1 / 2 + m) * t, y, '0', size1, mode);
		}
		else
		{
			OLED_ShowChar(x + (size1 / 2 + m) * t, y, temp + '0', size1, mode);
		}
	}
}
//OLED�ĳ�ʼ��
void OLED_Init(void)
{
	OLED_RES_Clr();
	HAL_Delay(200);
	OLED_RES_Set();

	OLED_WR_Byte(0xAE, OLED_CMD); /*display off*/
	OLED_WR_Byte(0x02, OLED_CMD); /*set lower column address*/
	OLED_WR_Byte(0x10, OLED_CMD); /*set higher column address*/
	OLED_WR_Byte(0x40, OLED_CMD); /*set display start line*/
	OLED_WR_Byte(0xB0, OLED_CMD); /*set page address*/
	OLED_WR_Byte(0x81, OLED_CMD); /*contract control*/
	OLED_WR_Byte(0xcf, OLED_CMD); /*128*/
	OLED_WR_Byte(0xA1, OLED_CMD); /*set segment remap*/
	OLED_WR_Byte(0xA6, OLED_CMD); /*normal / reverse*/
	OLED_WR_Byte(0xA8, OLED_CMD); /*multiplex ratio*/
	OLED_WR_Byte(0x3F, OLED_CMD); /*duty = 1/64*/
	OLED_WR_Byte(0xad, OLED_CMD); /*set charge pump enable*/
	OLED_WR_Byte(0x8b, OLED_CMD); /* 0x8B �ڹ� VCC */
	OLED_WR_Byte(0x33, OLED_CMD); /*0X30---0X33 set VPP 9V */
	OLED_WR_Byte(0xC8, OLED_CMD); /*Com scan direction*/
	OLED_WR_Byte(0xD3, OLED_CMD); /*set display offset*/
	OLED_WR_Byte(0x00, OLED_CMD); /* 0x20 */
	OLED_WR_Byte(0xD5, OLED_CMD); /*set osc division*/
	OLED_WR_Byte(0x80, OLED_CMD);
	OLED_WR_Byte(0xD9, OLED_CMD); /*set pre-charge period*/
	OLED_WR_Byte(0x1f, OLED_CMD); /*0x22*/
	OLED_WR_Byte(0xDA, OLED_CMD); /*set COM pins*/
	OLED_WR_Byte(0x12, OLED_CMD);
	OLED_WR_Byte(0xdb, OLED_CMD); /*set vcomh*/
	OLED_WR_Byte(0x40, OLED_CMD);
	OLED_Clear();
	OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
}
