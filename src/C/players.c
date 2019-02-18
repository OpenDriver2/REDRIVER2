
/*
 * Offset 0x7339C
 * D:\driver2\game\C\PLAYERS.C (line 130)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ ChangeCarPlayerToPed(int playerID /*$s0*/)
{ // line 1, address 0x7339c
	struct _CAR_DATA *lcp; // $s2
} // line 51, address 0x73574
/*
 * Offset 0x73574
 * D:\driver2\game\C\PLAYERS.C (line 184)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ ChangePedPlayerToCar(int playerID /*$s4*/, struct _CAR_DATA *newCar /*$s2*/)
{ // line 1, address 0x73574
	struct _PLAYER *lPlayer; // $s1
	int siren; // $s5
	long *pos; // $s3
	int carParked; // $s6
} // line 60, address 0x73900
/*
 * Offset 0x73900
 * D:\driver2\game\C\PLAYERS.C (line 247)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ UpdatePlayers()
{ // line 2, address 0x73900
	struct _PLAYER *locPlayer; // $t0
	struct _CAR_DATA *cp; // $v1
} // line 39, address 0x73a40
/*
 * Offset 0x73A40
 * D:\driver2\game\C\PLAYERS.C (line 75)
 * Stack frame base $sp, length 72
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ InitPlayer(struct _PLAYER *locPlayer /*$s1*/, struct _CAR_DATA *cp /*$s2*/, char carCtrlType /*$s3*/, int direction /*$s6*/, long *startPos[4] /*stack 16*/, int externModel /*stack 20*/, int palette /*stack 24*/, char *padid /*stack 28*/)
{ // line 1, address 0x73a40
} // line 52, address 0x73c74
/*
 * Offset 0x73C74
 * D:\driver2\game\C\PLAYERS.C (line 298)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ RequestSlightPauseBeforeCarSoundStarts(char player_id /*$a0*/)
{
}
/*
 * Offset 0x73CBC
 * D:\driver2\game\C\PLAYERS.C (line 305)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ HaveCarSoundStraightAway(char player_id /*$a0*/)
{
}
/*
 * Offset 0x73CF4
 * D:\driver2\game\C\PLAYERS.C (line 310)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ MakeTheCarShutUp(char player_id /*$a0*/)
{
}