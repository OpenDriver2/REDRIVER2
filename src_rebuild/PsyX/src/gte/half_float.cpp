#include "PsyX/common/half_float.h"
#include "psx/types.h"

// see https://gist.github.com/rygorous/2156668

union FP32
{
	uint u;
	float f;
	struct
	{
		uint Mantissa : 23;
		uint Exponent : 8;
		uint Sign : 1;
	};
};

union FP16
{
	unsigned short u;
	struct
	{
		uint Mantissa : 10;
		uint Exponent : 5;
		uint Sign : 1;
	};
};

half::half(const float x)
{
	// this is a approximate solution
	FP32 f = *(FP32*)&x;
	FP32 f32infty = { 255 << 23 };
	FP32 f16max = { (127 + 16) << 23 };
	FP32 magic = { 15 << 23 };
	FP32 expinf = { (255 ^ 31) << 23 };
	uint sign_mask = 0x80000000u;
	FP16 o = { 0 };

	uint sign = f.u & sign_mask;
	f.u ^= sign;

	if (!(f.f < f32infty.u)) // Inf or NaN
		o.u = f.u ^ expinf.u;
	else
	{
		if (f.f > f16max.f) f.f = f16max.f;
		f.f *= magic.f;
	}

	o.u = f.u >> 13; // Take the mantissa bits
	o.u |= sign >> 16;
	sh = o.u;
}

half::half(const half& other)
{
	sh = other.sh;
}

half::operator float() const
{
	FP16 h = { sh };

	static const FP32 magic = { 113 << 23 };
	static const uint shifted_exp = 0x7c00 << 13; // exponent mask after shift
	FP32 o;

	o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
	uint exp = shifted_exp & o.u;   // just the exponent
	o.u += (127 - 15) << 23;        // exponent adjust

	// handle exponent special cases
	if (exp == shifted_exp) // Inf/NaN?
		o.u += (128 - 16) << 23;    // extra exp adjust
	else if (exp == 0) // Zero/Denormal?
	{
		o.u += 1 << 23;             // extra exp adjust
		o.f -= magic.f;             // renormalize
	}

	o.u |= (h.u & 0x8000) << 16;    // sign bit
	return o.f;
}
