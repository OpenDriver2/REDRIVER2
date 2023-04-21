#ifndef REVERSING_H
#define REVERSING_H

// reverse engineering stuff
//----------------------------------------

// makes short out of two bytes
#define M_SHRT_2(a,b)	(((a) << 8) | (b))

// makes int out of two shorts
#define M_INT_2(a,b)	(((a) << 16) | (b))

// makes int out of four bytes
#define M_INT_4(a,b,c,d) (((a) << 24) | ((b) << 16) | ((c) << 8) | (d) )
#define M_INT_4R(a,b,c,d) M_INT_4(d, c, b, a)

#define M_BIT(x) (1 << (x))

// makes RGB int out of three bytes
#define M_INT_RGB(r,g,b) (((r) << 16) | ((g) << 8) | (b))

//---------------------------------------

#if !defined( __TYPEINFOGEN__ ) && !defined( _lint ) && defined(_WIN32)	// pcLint has problems with assert_offsetof()

template<bool> struct compile_time_assert_failed;
template<> struct compile_time_assert_failed<true> {};
template<int x> struct compile_time_assert_test {};
#define compile_time_assert_join2( a, b )	a##b
#define compile_time_assert_join( a, b )	compile_time_assert_join2(a,b)
#define compile_time_assert( x )			typedef compile_time_assert_test<sizeof(compile_time_assert_failed<(bool)(x)>)> compile_time_assert_join(compile_time_assert_typedef_, __LINE__)

#define assert_sizeof( type, size )						compile_time_assert( sizeof( type ) == size )
#define assert_sizeof_8_byte_multiple( type )			compile_time_assert( ( sizeof( type ) &  7 ) == 0 )
#define assert_sizeof_16_byte_multiple( type )			compile_time_assert( ( sizeof( type ) & 15 ) == 0 )
#define assert_offsetof( type, field, offset )			compile_time_assert( offsetof( type, field ) == offset )
#define assert_offsetof_8_byte_multiple( type, field )	compile_time_assert( ( offsetof( type, field ) & 7 ) == 0 )
#define assert_offsetof_16_byte_multiple( type, field )	compile_time_assert( ( offsetof( type, field ) & 15 ) == 0 )

#else

#define compile_time_assert( x )
#define assert_sizeof( type, size )
#define assert_sizeof_8_byte_multiple( type )
#define assert_sizeof_16_byte_multiple( type )
#define assert_offsetof( type, field, offset )
#define assert_offsetof_8_byte_multiple( type, field )
#define assert_offsetof_16_byte_multiple( type, field )

#endif

#ifdef _MSC_VER // maybe GCC?

#define forceinline __forceinline
#define _ALIGNED(x) __declspec(align(x))

#define ALIGNED_TYPE(s, a) typedef s _ALIGNED(a)

#else

#define forceinline inline
#define _ALIGNED(x) __attribute__ ((aligned(x)))

#define ALIGNED_TYPE(s, a) typedef struct s _ALIGNED(a)

#endif

#ifndef FUNCNAME

#ifdef _MSC_VER
#define FUNCNAME __FUNCTION__
#else
#define FUNCNAME __func__
#endif

#endif

#if defined(_DEBUG)
#define UNIMPLEMENTED()	{ static bool _stop = false; if(!_stop) printMsg("[GAME] %s - unimplemented!\n", FUNCNAME); _stop = true; }
#else
#define UNIMPLEMENTED()
#endif

//----------------------------------------


#endif // REVERSTING_H