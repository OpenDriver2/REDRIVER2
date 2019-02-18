#ifndef MIPS_HW_INTPRET_H
#define MIPS_HW_INTPRET_H

#include "r3000a_regs.h"

#ifndef __cplusplus

typedef int bool;

#endif // __cplusplus

//-------------------------------------------------------------
// Helpers
//-------------------------------------------------------------

inline int sregv(RegVar_t r)		// returns signed register value
{
	return *(int*)&_registers[r];
}

inline uint32 uregv(RegVar_t r)		// returns unsigned register value
{
	return *(uint32*)&_registers[r];
}

inline void stores(RegVar_t r, int v)	// stores signed register value
{
	int* regVal = (int*)&_registers[r];
	*regVal = v;
}

inline void storeu(RegVar_t r, uint32 v)	// stores unsigned register value
{
	_registers[r] = v;
}

//-------------------------------------------------------------
// operations
//-------------------------------------------------------------

inline void add(RegVar_t d, RegVar_t s, RegVar_t t)
{
	_registers[d] = sregv(s) + sregv(t);
}

inline void addi(RegVar_t d, RegVar_t s, int imm)
{
	_registers[d] = sregv(s) + imm;
}

inline void addiu(RegVar_t d, RegVar_t s, uint32 imm)
{
	_registers[d] = _registers[s] + imm;
}

inline void addu(RegVar_t d, RegVar_t s, RegVar_t t)
{
	_registers[d] = _registers[s] + _registers[t];
}

inline void and(RegVar_t d, RegVar_t s, RegVar_t t)
{
	_registers[d] = _registers[s] & _registers[t];
}

inline void andi(RegVar_t d, RegVar_t s, uint32 imm)
{
	_registers[d] = _registers[s] & imm;
}

inline void sub(RegVar_t d, RegVar_t s, RegVar_t t)
{
	_registers[d] = sregv(s) - sregv(t);
}

inline void subu(RegVar_t d, RegVar_t s, RegVar_t t)
{
	_registers[d] = _registers[s] - _registers[t];
}

inline void or(RegVar_t d, RegVar_t s, RegVar_t t)
{
	_registers[d] = _registers[s] | _registers[t];
}

inline void ori(RegVar_t d, RegVar_t s, uint32 imm)
{
	_registers[d] = _registers[s] | imm;
}

inline void xor (RegVar_t d, RegVar_t s, RegVar_t t)
{
	_registers[d] = _registers[s] ^ _registers[t];
}

inline void xori(RegVar_t d, RegVar_t s, uint32 imm)
{
	_registers[d] = _registers[s] ^ imm;
}

//-------------

inline bool beq(RegVar_t s, RegVar_t t)
{
	return (_registers[s] == _registers[t]);
}

inline bool beqz(RegVar_t s)
{
	return (_registers[s] == 0);
}

//---

inline bool bgez(RegVar_t s)
{
	return (_registers[s] >= 0);
}

inline bool bgtz(RegVar_t s)
{
	return (_registers[s] > 0);
}

//---

inline bool blez(RegVar_t s)
{
	return (_registers[s] <= 0);
}

inline bool bltz(RegVar_t s)
{
	return (_registers[s] < 0);
}

//---

inline bool bne(RegVar_t s, RegVar_t t)
{
	return (_registers[s] != _registers[t]);
}

inline bool bnez(RegVar_t s)
{
	return (_registers[s] != 0);
}

//-------------

inline void lb(RegVar_t s, ubyte byteimm)
{
	_registers[s] = byteimm;
}

//---

inline void li(RegVar_t s, uint32 imm)
{
	_registers[s] = imm;
}

inline void lui(RegVar_t s, uint32 imm)
{
	_registers[s] = (imm << 16);
}

inline void lw(RegVar_t s, uint32* w)
{
	_registers[s] = *w;
}

//---

inline void mfhi(RegVar_t s)
{
	_registers[s] = _registers[_HI];
}

inline void mflo(RegVar_t s)
{
	_registers[s] = _registers[_LO];
}

inline void div(RegVar_t s, RegVar_t t)
{
	_registers[_LO] = sregv(s) / sregv(t); 
	_registers[_HI] = sregv(s) % sregv(t);
}

inline void divu(RegVar_t s, RegVar_t t)
{
	_registers[_LO] = _registers[s] / _registers[t];
	_registers[_HI] = _registers[s] % _registers[t];
}

inline void mult(RegVar_t s, RegVar_t t)
{
	unsigned __int64* result = (__int64*)&_registers[_LO];
	*result = (__int64)sregv(s) * (__int64)sregv(t);
}

inline void multu(RegVar_t s, RegVar_t t)
{
	unsigned __int64* result = (__int64*)&_registers[_LO];
	*result = (__int64)_registers[s] * (__int64)_registers[t];
}

//---

inline void sb(RegVar_t t, char* b)
{
	*b = 0xff & _registers[t];
}

inline void sw(RegVar_t t, int* w)
{
	*w = _registers[t];
}

inline void sll(RegVar_t d, RegVar_t t, uint32 h)
{
	_registers[d] = _registers[t] << h;
}

inline void sllv(RegVar_t d, RegVar_t t, RegVar_t s)
{
	_registers[d] = _registers[t] << _registers[s];
}

inline void sra(RegVar_t d, RegVar_t t, int h)
{
	_registers[d] = sregv(t) >> h;
}

inline void srl(RegVar_t d, RegVar_t t, uint32 h)
{
	_registers[d] = _registers[t] >> h;
}

inline void srlv(RegVar_t d, RegVar_t t, RegVar_t s)
{
	_registers[d] = _registers[t] >> _registers[s];
}

inline void slt(RegVar_t d, RegVar_t s, RegVar_t t)
{
	if (sregv(s) < sregv(t))
		_registers[d] = 1;
	else
		_registers[d] = 0;
}

inline void sltu(RegVar_t d, RegVar_t s, RegVar_t t)
{
	if(_registers[s] < _registers[t])
		_registers[d] = 1;
	else 
		_registers[d] = 0;
}

inline void slti(RegVar_t d, RegVar_t s, int imm)
{
	if (sregv(s) < imm)
		_registers[d] = 1;
	else
		_registers[d] = 0;
}

inline void sltiu(RegVar_t d, RegVar_t s, uint32 imm)
{
	if (_registers[s] < imm)
		_registers[d] = 1;
	else
		_registers[d] = 0;
}

#define move(a,b) add(a,b,_zero)
#define la(a,b) li(a,(uint32)b)

#endif // MIPS_HW_INTPRET_H