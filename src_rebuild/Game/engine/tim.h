#ifndef TIM_H
#define TIM_H

struct TIMHDR
{
	int magic;
	int flags;
};

struct TIMIMAGEHDR
{
	int len;
	short origin_x;
	short origin_y;
	short width;
	short height;
};

#endif // TIM_H