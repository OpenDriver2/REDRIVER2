// redriver2_psxpc.cpp
//

#include "GAME/C/MAIN.H"
#include "EMULATOR.H"
#include "EMULATOR_PRIVATE.H"

int(*GPU_printf)(const char *fmt, ...);

int main()
{
	GPU_printf = printf;

	Emulator_Initialise("DRIVER 2", 800, 600);

	redriver2_main();

	Emulator_ShutDown();
}
