#ifndef HALF_FLOAT
#define HALF_FLOAT

struct half
{
	unsigned short sh;

	half() {};
	half(const float x);
	half(const half& other);
	operator float() const;

	half& operator=(const half& other)
	{
		sh = other.sh;
		return *this;
	}
};

#endif // HALF_FLOAT