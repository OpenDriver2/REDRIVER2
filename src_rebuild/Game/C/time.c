#include "driver2.h"
#include "time.h"

// [F]
void GetTimeStamp(char *buffer)
{
	if (buffer)
		sprintf(buffer, "%s %s", __DATE__, __TIME__);
}





