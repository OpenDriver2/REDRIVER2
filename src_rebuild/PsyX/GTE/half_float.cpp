#include "half_float.h"

half::half(const float x)
{
	union
	{
		float floatI;
		unsigned int i;
	};

	floatI = x;

	//	unsigned int i = *((unsigned int *) &x);
	int e = ((i >> 23) & 0xFF) - 112;
	int m = i & 0x007FFFFF;

	sh = (i >> 16) & 0x8000;
	if (e <= 0)
	{
		// Denorm
		m = ((m | 0x00800000) >> (1 - e)) + 0x1000;
		sh |= (m >> 13);
	}
	else if (e == 143)
	{
		sh |= 0x7C00;
		if (m != 0)
		{
			// NAN
			m >>= 13;
			sh |= m | (m == 0);
		}
	}
	else
	{
		m += 0x1000;
		if (m & 0x00800000)
		{
			// Mantissa overflow
			m = 0;
			e++;
		}
		if (e >= 31)
		{
			// Exponent overflow
			sh |= 0x7C00;
		}
		else
		{
			sh |= (e << 10) | (m >> 13);
		}
	}
}

half::half(const half& other)
{
	sh = other.sh;
}

half::operator float() const
{
	union
	{
		unsigned int s;
		float result;
	};

	s = (sh & 0x8000) << 16;
	unsigned int e = (sh >> 10) & 0x1F;
	unsigned int m = sh & 0x03FF;

	if (e == 0)
	{
		// +/- 0
		if (m == 0) return result;

		// Denorm
		while ((m & 0x0400) == 0)
		{
			m += m;
			e--;
		}
		e++;
		m &= ~0x0400;
	}
	else if (e == 31)
	{
		// INF / NAN
		s |= 0x7F800000 | (m << 13);
		return result;
	}

	s |= ((e + 112) << 23) | (m << 13);

	return result;
}
