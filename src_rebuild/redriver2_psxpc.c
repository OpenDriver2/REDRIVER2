// redriver2_psxpc.cpp
//

#include "GAME/C/MAIN.H"
#include "EMULATOR.H"
#include "EMULATOR_PRIVATE.H"

int(*GPU_printf)(const char *fmt, ...);

extern int g_texturelessMode;
extern int g_wireframeMode;

int main()
{
	//g_texturelessMode = 1;
	//g_wireframeMode = 1;

	GPU_printf = printf;

	Emulator_Initialise("REDRIVER2", 800, 600);

	redriver2_main();

	Emulator_ShutDown();
}
