#include "DRIVER2.H"
#include "TIME.H"


// decompiled code
// original method signature: 
// void /*$ra*/ GetTimeStamp(char *buffer /*$a0*/)
 // line 5, offset 0x00081140
	/* begin block 1 */
		// Start line: 10
	/* end block 1 */
	// End Line: 11

	/* begin block 2 */
		// Start line: 11
	/* end block 2 */
	// End Line: 12

// [F]
void GetTimeStamp(char *buffer)
{
	if (buffer)
		sprintf(buffer, "%s %s", __DATE__, __TIME__);
}





