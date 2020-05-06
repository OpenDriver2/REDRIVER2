// redriver2_psxpc.cpp
//

#include "GAME/C/MAIN.H"
#include "EMULATOR.H"
#include "EMULATOR_PRIVATE.H"

#include <SDL_scancode.h>

int(*GPU_printf)(const char *fmt, ...);

extern int g_texturelessMode;
extern int g_wireframeMode;
int gShowCollisionDebug = 0;
extern int gDrawDistance;
extern int gDisplayPosition;
extern int gDisplayDrawStats;


void GameDebugKeys(int nKey, bool down)
{

	if (!down)
		return;

	if (nKey == SDL_SCANCODE_F1)
	{
		gDrawDistance -= 100;

		if (gDrawDistance < 441)
			gDrawDistance = 441;

		printf("gDrawDistance = %d\n", gDrawDistance);

	}
	else if (nKey == SDL_SCANCODE_F2)
	{
		gDrawDistance += 100;

		if (gDrawDistance > 6000)
			gDrawDistance = 6000;

		printf("gDrawDistance = %d\n", gDrawDistance);
	}
	else if (nKey == SDL_SCANCODE_F3)
	{
		gDisplayPosition ^= 1;
		printf("Position display %s\n", gDisplayPosition ? "ON" : "OFF");
	}
	else if (nKey == SDL_SCANCODE_F4)
	{
		gShowCollisionDebug ^= 1;
		printf("Collision debug %s\n", gShowCollisionDebug ? "ON" : "OFF");
	}
	else if (nKey == SDL_SCANCODE_F5)
	{
		gDisplayDrawStats ^= 1;
		printf("Stats %s\n", gDisplayDrawStats ? "ON" : "OFF");
	}
}

int main()
{
	//g_texturelessMode = 1;
	//g_wireframeMode = 1;
	gameDebugKeys = GameDebugKeys;
	gDrawDistance = 1300;		// best distance

	GPU_printf = printf;

	Emulator_Initialise("REDRIVER2", 800, 600);

	redriver2_main();

	Emulator_ShutDown();
}
