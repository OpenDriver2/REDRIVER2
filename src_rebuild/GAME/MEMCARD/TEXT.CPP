#include "THISDUST.H"
#include "TEXT.H"


// decompiled code
// original method signature: 
// int /*$ra*/ ParseLanguageFile__FPci(char *textBuffer /*$a0*/, int language /*$a1*/)
 // line 16, offset 0x001004c8
	/* begin block 1 */
		// Start line: 17
		// Start offset: 0x001004C8
		// Variables:
	// 		int m; // $t0
	// 		char *textPtr; // $a0
	/* end block 1 */
	// End offset: 0x001005D8
	// End Line: 172

	/* begin block 2 */
		// Start line: 32
	/* end block 2 */
	// End Line: 33

	/* begin block 3 */
		// Start line: 34
	/* end block 3 */
	// End Line: 35

void FUN_MCARD__001004c8(char *param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  char **ppcVar3;
  int iVar4;
  
  iVar4 = 0;
  ppcVar3 = (char **)&DAT_MCARD__0010ece0;
  DAT_MCARD__0010ee04 = param_1;
  do {
    cVar1 = *param_1;
    if (cVar1 != '\n') {
      if (cVar1 == -1) {
        return;
      }
      do {
        param_1 = param_1 + 1;
        cVar1 = *param_1;
        if (cVar1 == '\n') goto LAB_MCARD__00100528;
      } while (cVar1 != -1);
      cVar1 = *param_1;
    }
LAB_MCARD__00100528:
    if (cVar1 == -1) {
      return;
    }
    *param_1 = -1;
    pcVar2 = param_1 + 1;
    if ((param_2 == 9) && (((uint)pcVar2 & 1) != 0)) {
      *ppcVar3 = param_1;
      cVar1 = param_1[1];
      *param_1 = cVar1;
      while (param_1 = param_1 + 1, cVar1 != '\n') {
        cVar1 = param_1[1];
        *param_1 = cVar1;
      }
      param_1[-1] = '\0';
      *param_1 = '\0';
      param_1 = param_1 + 1;
    }
    else {
      *ppcVar3 = pcVar2;
      cVar1 = *pcVar2;
      param_1 = param_1 + 2;
      while (cVar1 != '\n') {
        cVar1 = *param_1;
        param_1 = param_1 + 1;
      }
    }
    iVar4 = iVar4 + 1;
    ppcVar3 = ppcVar3 + 1;
    param_1[-1] = '\0';
    *param_1 = '\0';
    param_1 = param_1 + 1;
    if (0x48 < iVar4) {
      return;
    }
  } while( true );
}





