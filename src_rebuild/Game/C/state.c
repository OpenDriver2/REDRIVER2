#include "driver2.h"
#include "state.h"
#include "main.h"
#include "glaunch.h"
#include "Frontend/FEmain.h"

//-------------------------------------------

typedef void (*StateFn)(void*);

StateFn gStates[] = {
	NULL,
	State_InitFrontEnd,
	State_FrontEnd,
	State_GameStart,
	State_LaunchGame,
	State_MissionLadder,
	State_GameInit,
	State_GameLoop,
	State_GameComplete,
	State_FMVPlay,
};

StateFn gCurrentState = NULL;
void* gCurrentStateParam = NULL;

#ifdef __EMSCRIPTEN__
void emStateFunc()
{
	StateFn stateFn = gCurrentState;

	if (!stateFn)
		return;

	stateFn(gCurrentStateParam);
}
#endif

// the main loop of the game
void DoStateLoop()
{
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(emStateFunc, 0, 1);
#else
	do
	{
		StateFn stateFn = gCurrentState;

		if (!stateFn)
			break;

		stateFn(gCurrentStateParam);
	} while (true);
#endif
}

void SetState(GameStates newState, void* param)
{
	gCurrentState = gStates[newState];
	gCurrentStateParam = param;
}