#ifndef REVERSING_H
#define REVERSING_H

// reverse engineering stuff

// Ghidra stuff
#define _CopReg0 gteRegs.CP0
#define _CopReg2 gteRegs.CP2D

#define copReg(n, reg) _CopReg##n.p[reg]

#define getCopReg(n, reg) copReg(n, reg).d
#define setCopReg(n, reg, value) (copReg(n, reg).d = value)

#define _CopControlWord2 gteRegs.CP2C

#define copControlWord(n, reg) _CopControlWord##n.p[reg]

#define getCopControlWord(n, reg) copControlWord(n, reg).d
#define setCopControlWord(n, reg, value) (copControlWord(n, reg).d = value)

#define _CopFunc2 docop2

#define copFunction(n, op) _CopFunc##n(op)


//----------------------------------------

// byte swapped short
#define SW_SHORT(a,b) (((a) << 8) | (b))

// byte swapped int
#define SW_INT(a,b) (((a) << 16) | (b))

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

#undef eprintf
#define eprintf(fmt, ...) printMsg("[GAME] " fmt, ##__VA_ARGS__)

#define UNIMPLEMENTED_PRINTONCE() { static bool _stop = false; if(!_stop) eprinterr("Unimplemented!\n"); _stop = true; }

#ifdef UNIMPLEMENTED
#undef UNIMPLEMENTED
#define UNIMPLEMENTED() UNIMPLEMENTED_PRINTONCE() //eprinterr("Unimplemented!\n");
#endif // UNIMPLEMENTED

//----------------------------------------


#endif // REVERSTING_H