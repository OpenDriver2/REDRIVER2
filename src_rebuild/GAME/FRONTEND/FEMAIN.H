#ifndef FEMAIN_H
#define FEMAIN_H

struct PSXBUTTON // hashcode: 0x41BD456C (dec: 1102923116)
{
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short w; // size=0, offset=4
	short h; // size=0, offset=6
	unsigned char l; // size=0, offset=8
	unsigned char r; // size=0, offset=9
	unsigned char u; // size=0, offset=10
	unsigned char d; // size=0, offset=11
	int userDrawFunctionNum; // size=0, offset=12
	short s_x; // size=0, offset=16
	short s_y; // size=0, offset=18
	int action; // size=0, offset=20
	int var; // size=0, offset=24
	char Name[32]; // size=32, offset=28
};

struct PSXSCREEN // hashcode: 0x9E392939 (dec: -1640421063)
{
	unsigned char index; // size=0, offset=0
	unsigned char numButtons; // size=0, offset=1
	unsigned char userFunctionNum; // size=0, offset=2
	PSXBUTTON buttons[8]; // size=480, offset=4
};

extern int gInFrontend;
extern int bRedrawFrontend;

extern void SetVariable(int var); // 0x001C0974

extern void LoadFrontendScreens(); // 0x001C0C1C

extern void LoadBackgroundFile(char *name); // 0x001C0F24

extern void SetupBackgroundPolys(); // 0x001C10F4

extern void SetupScreenSprts(PSXSCREEN *pScr); // 0x001C132C

extern void DrawScreen(PSXSCREEN *pScr); // 0x001C147C

extern void DisplayOnScreenText(); // 0x001C18E4

extern void SetupExtraPoly(char *fileName, int offset, int offset2); // 0x001C1AD0

extern void ReInitScreens(); // 0x001C1CF4

extern void NewSelection(short dir); // 0x001C1E18

extern int HandleKeyPress(); // 0x001C22A8

extern void PadChecks(); // 0x001C2668

extern void DoFrontEnd(); // 0x001C296C

extern void SetFEDrawMode(); // 0x001C2C2C

extern void EndFrame(); // 0x001C6378

extern void carSelectPlayerText() ; // 0x001C676C

extern int FEPrintString(char *string, int x, int y, int justification, int r, int g, int b); // 0x001C2D90

extern int FEPrintStringSized(char *string, int x, int y, int scale, int transparent, int r, int g, int b); // 0x001C2FD8

extern int CentreScreen(int bSetup); // 0x001C31FC

extern int CarSelectScreen(int bSetup); // 0x001C3430

extern int CopDiffLevelScreen(int bSetup); // 0x001C6404

extern int VibroOnOffScreen(int bSetup); // 0x001C3A60

extern int MissionSelectScreen(int bSetup); // 0x001C3B1C

extern int MissionCityScreen(int bSetup); // 0x001C4338

extern int CutSceneSelectScreen(int bSetup); // 0x001C4600

extern int CutSceneCitySelectScreen(int bSetup); // 0x001C4B30

extern int SetVolumeScreen(int bSetup); // 0x001C50B0

extern void DisplayScoreTable(); // 0x001C55F8

extern int ScoreScreen(int bSetup); // 0x001C59A0

extern int SubtitlesOnOffScreen(int bSetup); // 0x001C64B0

extern int CityCutOffScreen(int bSetup); // 0x001C64FC

extern int ControllerScreen(int bSetup); // 0x001C6548

extern int MainScreen(int bSetup); // 0x001C6614

extern int CheatScreen(int bSetup); // 0x001C5B4C

extern int ImmunityOnOffScreen(int bSetup); // 0x001C6654

extern int InvincibleOnOffScreen(int bSetup); // 0x001C66A0

extern int GamePlayScreen(int bSetup); // 0x001C66EC

extern int GameNameScreen(int bSetup); // 0x001C60A0

extern void FEInitCdIcon(); // 0x001C61AC

extern void FEDrawCDicon(); // 0x001C62F8

extern int CheatNumlayerSelect(int bSetup); // 0x001C6724

extern int BonusGalleryScreen(int bSetup);

#endif
