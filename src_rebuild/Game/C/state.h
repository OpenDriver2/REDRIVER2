enum GameStates
{
	STATE_NONE = 0,
	STATE_INITFRONTEND,
	STATE_FRONTEND,
	STATE_GAMESTART,
	STATE_GAMELAUNCH,		// launch single game
	STATE_LADDER,			// launch a mission ladder
	STATE_GAMEINIT,
	STATE_GAMELOOP,
	STATE_GAMECOMPLETE,
	STATE_FMVPLAY,
};

// changes the state
extern void SetState(GameStates newState, void* param = NULL);

// does the state loop
extern void DoStateLoop();