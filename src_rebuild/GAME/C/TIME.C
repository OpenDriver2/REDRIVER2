#include "DRIVER2.H"
#include "TIME.H"

// [F]
void GetTimeStamp(char *buffer)
{
	if (buffer)
		sprintf(buffer, "%s %s", __DATE__, __TIME__);
}





