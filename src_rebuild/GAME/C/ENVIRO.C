#include "THISDUST.H"
#include "ENVIRO.H"

#include "STRINGS.H"

short gPlayerCar0ShinyFaces[38];

// decompiled code
// original method signature: 
// void /*$ra*/ Env_MakeColourAddTable(short *shinysrc /*$s0*/, char *polytable /*$s1*/, int length /*$a2*/)
 // line 46, offset 0x00044e88
	/* begin block 1 */
		// Start line: 47
		// Start offset: 0x00044E88
		// Variables:
	// 		short addval; // $a0
	// 		short polynum; // $v1
	/* end block 1 */
	// End offset: 0x00044F08
	// End Line: 67

	/* begin block 2 */
		// Start line: 92
	/* end block 2 */
	// End Line: 93

// [A] - this code is not needed
void Env_MakeColourAddTable(short *shinysrc, char *polytable, int length)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	int iVar2;
	short sVar3;

	memset(polytable, 0xe, length);
	sVar3 = *shinysrc;
	sVar1 = shinysrc[1];
	shinysrc = shinysrc + 2;
	while (iVar2 = (int)sVar1, iVar2 != -1) {
		if (iVar2 == -2) {
			sVar3 = *shinysrc;
			shinysrc = shinysrc + 1;
		}
		else {
			polytable[iVar2] = (char)sVar3;
		}
		sVar1 = *shinysrc;
		shinysrc = shinysrc + 1;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ Init_Reflection_Mapping()
 // line 72, offset 0x00044f08
	/* begin block 1 */
		// Start line: 74
		// Start offset: 0x00044F08
		// Variables:
	// 		struct TPAN pos; // stack offset -16
	// 		int count; // $v1
	/* end block 1 */
	// End offset: 0x00044F60
	// End Line: 89

	/* begin block 2 */
		// Start line: 142
	/* end block 2 */
	// End Line: 143

	/* begin block 3 */
		// Start line: 148
	/* end block 3 */
	// End Line: 149

	/* begin block 4 */
		// Start line: 149
	/* end block 4 */
	// End Line: 150

	/* begin block 5 */
		// Start line: 151
	/* end block 5 */
	// End Line: 152

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [A] - this code is not needed
void Init_Reflection_Mapping(void)
{
	UNIMPLEMENTED();
	/*
	char *pcVar1;
	int iVar2;

	iVar2 = 0xff;
	pcVar1 = &CHAR____000cdb4f;
	do {
		*pcVar1 = '0';
		iVar2 = iVar2 + -1;
		pcVar1 = pcVar1 + -1;
	} while (-1 < iVar2);
	ShinyTextureNum = 0;
	Env_MakeColourAddTable(gPlayerCar0ShinyFaces, Car0_ShinyTable, 0x100);
	return;
	*/
}





