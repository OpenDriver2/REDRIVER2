// WARNING: This file's extension ('.S') indicates that it may not have been a C or C++ file.
// It should contain Ghidra's best effort at decompiling the machine language to C, 
// but TDR does not currently attempt to handle assembly language or other non-C/C++ code differently, 
// so any decompiled code below may not reflect the original project source code for this file.
// If the source file is from a library, you should replace it with the original library version of the file.
// Otherwise, manual reconstruction of the code may be required, 
// Especially if the original source code was assembly language which used hardware features inaccessible to C.
#include "THISDUST.H"
#include "FONT2.H"


// decompiled code
// original method signature: 
// void add_prim() /* add_prim method signature is not contained in the debug symbol data. This is likely either a library function or the game was compiled without debug symbols. Please refer to the TDR documentation for additional guidance. */
 // line 246, offset 0x0010eb20
	/* begin block 1 */
		// Start line: 493
	/* end block 1 */
	// End Line: 494

void FUN_MCARD__0010eb20(undefined4 *param_1,undefined2 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = *param_1;
  *(short *)param_1 = (short)param_2;
  *param_2 = (short)uVar1;
  *(char *)(param_2 + 1) = (char)((uint)uVar1 >> 0x10);
  *(char *)((int)param_1 + 2) = (char)((uint)param_2 >> 0x10);
  return;
}





