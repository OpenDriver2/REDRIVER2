#include "driver2.h"
#include "roadbits.h"

char ROADS_GetRouteData(int x, int z, ROUTE_DATA *pRouteData)
{
	// Driver 2 roads don't support model numbers. Driver 1 does.
	pRouteData->type = 0;
	return 1;
}





