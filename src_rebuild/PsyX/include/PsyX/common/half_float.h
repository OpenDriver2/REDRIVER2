#ifndef HALF_FLOAT
#define HALF_FLOAT


typedef struct half
{
	unsigned short sh;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
	half() {};
	half(const float x);
	half(const half& other);
	operator float() const;

	half& operator=(const half& other)
	{
		sh = other.sh;
		return *this;
	}
#endif

} half;


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern short to_half_float(const float x);
extern float from_half_float(const short x);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif // HALF_FLOAT