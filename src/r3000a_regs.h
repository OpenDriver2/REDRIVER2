#ifndef R300A_REGS_H
#define R300A_REGS_H

typedef unsigned int uint32;
typedef unsigned char ubyte;

typedef enum ERegVar
{
	_zero = 0,					//	Always returns 0

	_at = 1,																		//	Reserved for use by assembler
	_v0 = 2, _v1 = 3,																//	Value returned by subroutine
	_a0 = 4, _a1 = 5, _a2 = 6, _a3 = 7,												//	First four parameters (arguments) for a subroutine
	_t0 = 8, _t1 = 9, _t2 = 10, _t3 = 11, _t4 = 12, _t5 = 13, _t6 = 14, _t7 = 15,	//	temporary, subroutines can use without saving
	_t8 = 24, _t9 = 25,																//	Subroutines can use without saving
	_s0 = 16, _s1 = 17, _s2 = 18, _s3 = 19, _s4 = 20, _s5 = 21, _s6 = 22, _s7 = 23,		//	Subroutine register variables, must be restored before returning
	_k0 = 26, _k1 = 27,																//	Reserved for use by interrupt / trap handler; may change under your feet
	_gp = 28,																		//	Global pointer; used to access "static" or "extern" variables
	_sp = 29,																		//	Stack pointer
	_s8 = 30, // fp																	//	Frame pointer or ninth subroutine variable
	_ra = 31,																		//	Return address for subroutine

	_LO,
	_HI,

	allregs,
} RegVar_t;

extern uint32 _registers[allregs];

#endif // R300A_REGS_H