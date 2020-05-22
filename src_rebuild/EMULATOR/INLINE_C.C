#include "INLINE_C.H"

#include "LIBGTE.H"
#include "GTEREG.H"

void gte_SetGeomScreen(int h)
{
	CTC2(*(uint*)&h, 26);
}

int gte_ldlzc(int input)
{
	int leadingZeroCount = 0;

	if (input > 0)
	{
		for (int i = (sizeof(int) * 8)-1; i >= 0 ; i--)
		{
			if (input & (1 << i))
			{
				break;
			}

			leadingZeroCount++;
		}
	}
	
	return leadingZeroCount;
}