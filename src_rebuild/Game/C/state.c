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

GameStates gCurrentState = STATE_NONE;
void* gCurrentStateParam = NULL;

// the main loop of the game
void DoStateLoop()
{
	do
	{
		StateFn stateFn = gStates[gCurrentState];

		if (!stateFn)
			break;

		stateFn(gCurrentStateParam);
	} while (true);
}

void SetState(GameStates newState, void* param)
{
	gCurrentState = newState;
	gCurrentStateParam = param;
}