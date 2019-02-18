
// FIXME: XMPlay from PSX sdk or libxmp

/*
 * Offset 0x83218
 * D:\driver2\game\C\XMPLAY.C (line 454)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ InitXMData(unsigned char *mpp /*$s5*/, int XM_ID /*$a1*/, int S3MPan /*$a2*/)
{ // line 1, address 0x83218
	int t; // $s2
	int a; // $s4
	int c; // $s3
	unsigned long b; // $a2
	unsigned short b2; // $v1
} // line 67, address 0x834b4
/*
 * Offset 0x834B4
 * D:\driver2\game\C\XMPLAY.C (line 627)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ XM_Init(int VabID /*$s5*/, int XM_ID /*$s4*/, int SongID /*$s0*/, int FirstCh /*$s2*/, int Loop /*stack 16*/, int PlayMask /*stack 20*/, int PlayType /*stack 24*/, int SFXNum /*stack 28*/)
{ // line 1, address 0x834b4
	int i; // $s1
	int pmsk; // $v1
	int Chn; // $s0
	int t; // $a2
	int SngID; // $s3
	int fr; // $a3
} // line 151, address 0x83994
/*
 * Offset 0x83994
 * D:\driver2\game\C\XMPLAY.C (line 788)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ JPlayNote(unsigned char *j /*$s0*/, int pmsk /*$s3*/)
{ // line 1, address 0x83994
	unsigned char b; // $s1
	int ret; // $s2
	unsigned char note; // $s4
} // line 88, address 0x83bcc
/*
 * Offset 0x83BCC
 * D:\driver2\game\C\XMPLAY.C (line 885)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ JPlayEffects()
{ // line 2, address 0x83bcc
	unsigned char vol; // $a1
	unsigned char eff; // $s1
	unsigned char dat; // $s0
} // line 119, address 0x83e0c
/*
 * Offset 0x83E0C
 * D:\driver2\game\C\XMPLAY.C (line 1012)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SPE(unsigned char eff /*$a0*/, unsigned char dat /*$s0*/)
{ // line 1, address 0x83e0c
	int hi; // $v1
	int lo; // $a0
} // line 162, address 0x84218
/*
 * Offset 0x84218
 * D:\driver2\game\C\XMPLAY.C (line 1182)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ DoEEffects(unsigned char dat /*$a0*/)
{ // line 1, address 0x84218
	unsigned char nib; // $a1
} // line 138, address 0x8458c
/*
 * Offset 0x8458C
 * D:\driver2\game\C\XMPLAY.C (line 1448)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetPer()
{ // line 2, address 0x8458c
	unsigned long *j; // $a1
} // line 61, address 0x84730
/*
 * Offset 0x84740
 * D:\driver2\game\C\XMPLAY.C (line 1596)
 * Stack frame base $sp, length 8
 */
void /*$ra*/ DoS3MRetrig(unsigned char inf /*$a0*/)
{ // line 1, address 0x84740
	unsigned char hi; // $a1
} // line 76, address 0x84958
/*
 * Offset 0x84958
 * D:\driver2\game\C\XMPLAY.C (line 1710)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ DoVibrato()
{ // line 2, address 0x84958
	unsigned char q; // $a1
	unsigned short temp; // $a2
} // line 36, address 0x84a58
/*
 * Offset 0x84A58
 * D:\driver2\game\C\XMPLAY.C (line 1754)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ DoTremolo()
{ // line 2, address 0x84a58
	unsigned char q; // $a2
	unsigned short temp; // $a3
} // line 40, address 0x84ba4
/*
 * Offset 0x84BA4
 * D:\driver2\game\C\XMPLAY.C (line 1921)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ UpdatePatternData(int SC /*$a0*/)
{ // line 1, address 0x84ba4
	int SP; // $s1
	int t; // $s0
	int pmsk; // $a2
	int FindOffset; // $t0
	unsigned char *pataddr; // $a0
	unsigned char patdat; // $a1
} // line 174, address 0x85080
/*
 * Offset 0x8509C
 * D:\driver2\game\C\XMPLAY.C (line 2195)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ ApplyEffs()
{ // line 2, address 0x8509c
	short envpan; // $s2
	short envvol; // $s1
	int t; // $s3
	int pmsk; // $v1
	short vlm; // $s0
	short Pn; // $a1
	unsigned char MaxChans; // $s4
} // line 86, address 0x853b8
/*
 * Offset 0x853DC
 * D:\driver2\game\C\XMPLAY.C (line 2322)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ DoDolbySS()
{
}
/*
 * Offset 0x854B0
 * D:\driver2\game\C\XMPLAY.C (line 2398)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ UpdateHardware()
{ // line 2, address 0x854b0
	int t; // $s2
	int prd; // $s0
	int SPUKeyOn; // $s6
	int pmsk; // $v1
	int Chnl; // $s1
	unsigned char MaxChans; // $s3
	int i; // $v1
} // line 105, address 0x857e4
/*
 * Offset 0x8580C
 * D:\driver2\game\C\XMPLAY.C (line 2564)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
short /*$ra*/ ProcessEnvelope(short v /*$a2*/, unsigned char keyon /*$a1*/, int JSmp /*$a2*/)
{ // line 1, address 0x8580c
	unsigned char a2; // $s2
	unsigned char b; // $s0
	unsigned short p; // $s1
	unsigned long *j; // $s5
	short bpos; // $s3
} // line 63, address 0x859dc
/*
 * Offset 0x859DC
 * D:\driver2\game\C\XMPLAY.C (line 2635)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
short /*$ra*/ ProcessPanEnvelope(short v /*$a2*/, unsigned char keyon /*$a1*/, int JSmp /*$a2*/)
{ // line 1, address 0x859dc
	unsigned char a2; // $s2
	unsigned char b; // $s0
	unsigned short p; // $s1
	unsigned long *j; // $s5
	short bpos; // $s3
} // line 64, address 0x85bac
/*
 * Offset 0x85BAC
 * D:\driver2\game\C\XMPLAY.C (line 3206)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ XM_Restart(int Song_ID /*$a1*/)
{ // line 1, address 0x85bac
	int t; // $s0
} // line 20, address 0x85c8c
/*
 * Offset 0x85CA0
 * D:\driver2\game\C\XMPLAY.C (line 3160)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ XM_Pause(int Song_ID /*$a1*/)
{ // line 1, address 0x85ca0
	int t; // $s0
} // line 19, address 0x85d6c
/*
 * Offset 0x85D80
 * D:\driver2\game\C\XMPLAY.C (line 331)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ XM_Exit()
{ // line 2, address 0x85d80
	int i; // $s0
} // line 11, address 0x85de0
/*
 * Offset 0x85DE0
 * D:\driver2\game\C\XMPLAY.C (line 374)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ XM_Update()
{ // line 2, address 0x85de0
} // line 11, address 0x85e20
/*
 * Offset 0x85E30
 * D:\driver2\game\C\XMPLAY.C (line 429)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ XM_PlayStop(int Song_ID /*$a1*/)
{
}
/*
 * Offset 0x85EA0
 * D:\driver2\game\C\XMPLAY.C (line 409)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ XM_PlayStart(int Song_ID /*$a2*/, int PlayMask /*$a1*/)
{
}
/*
 * Offset 0x85EF4
 * D:\driver2\game\C\XMPLAY.C (line 2707)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ XM_SetSongPos(int Song_ID /*$a2*/, unsigned short pos /*$a1*/)
{ // line 1, address 0x85ef4
	int t; // $a2
} // line 29, address 0x85fdc
/*
 * Offset 0x85FE4
 * D:\driver2\game\C\XMPLAY.C (line 592)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ XM_OnceOffInit(int PAL /*$a0*/)
{
}
/*
 * Offset 0x8601C
 * D:\driver2\game\C\XMPLAY.C (line 345)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ XM_CloseVAB(int VabID /*$a1*/)
{
}
/*
 * Offset 0x86070
 * D:\driver2\game\C\XMPLAY.C (line 3273)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ XM_SetMasterVol(int Song_ID /*$a2*/, unsigned char Vol /*$a1*/)
{
}
/*
 * Offset 0x860C4
 * D:\driver2\game\C\XMPLAY.C (line 3331)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ XM_FreeVAG(int addr /*$a0*/)
{
}
/*
 * Offset 0x860E4
 * D:\driver2\game\C\XMPLAY.C (line 1855)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ UpdateWithTimer(int SC /*$a3*/)
{
}
/*
 * Offset 0x861E0
 * D:\driver2\game\C\XMPLAY.C (line 1887)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ XM_DoFullUpdate(int SC /*$s1*/)
{
}
/*
 * Offset 0x8629C
 * D:\driver2\game\C\XMPLAY.C (line 3351)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ XM_Quit(int SongID /*$s0*/)
{
}
/*
 * Offset 0x862E0
 * D:\driver2\game\C\XMPLAY.C (line 3449)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ XM_GetFreeVAB()
{ // line 2, address 0x862e0
	int i; // $v1
} // line 10, address 0x86318
/*
 * Offset 0x86320
 * D:\driver2\game\C\XMPLAY.C (line 3461)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ XM_SetVAGAddress(int VabID /*$a0*/, int slot /*$a1*/, int addr /*$a2*/)
{
}
/*
 * Offset 0x86358
 * D:\driver2\game\C\XMPLAY.C (line 354)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ XM_CloseVAB2(int VabID /*$a3*/)
{ // line 1, address 0x86358
	int i; // $v0
} // line 13, address 0x863c0
/*
 * Offset 0x863C0
 * D:\driver2\game\C\XMPLAY.C (line 3511)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ XM_SetSongAddress(unsigned char *Address /*$a0*/)
{
}
/*
 * Offset 0x86404
 * D:\driver2\game\C\XMPLAY.C (line 3506)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ XM_GetSongSize()
{
}
/*
 * Offset 0x8640C
 * D:\driver2\game\C\XMPLAY.C (line 3527)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ XM_FreeAllSongIDs()
{
}
/*
 * Offset 0x86418
 * D:\driver2\game\C\XMPLAY.C (line 3537)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ XM_SetFileHeaderAddress(unsigned char *Address /*$a0*/)
{
}
/*
 * Offset 0x8644C
 * D:\driver2\game\C\XMPLAY.C (line 3532)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ XM_GetFileHeaderSize()
{
}
/*
 * Offset 0x86454
 * D:\driver2\game\C\XMPLAY.C (line 256)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
unsigned short /*$ra*/ GetLogPeriod(unsigned char note /*$a0*/, unsigned short fine /*$a1*/)
{ // line 1, address 0x86454
} // line 25, address 0x864ec
/*
 * Offset 0x864EC
 * D:\driver2\game\C\XMPLAY.C (line 1831)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ UpdateXMData()
{ // line 2, address 0x864ec
	int SC; // $s0
} // line 20, address 0x86588
/*
 * Offset 0x865A0
 * D:\driver2\game\C\XMPLAY.C (line 1817)
 * Stack frame base $sp, length 0
 */
short /*$ra*/ DoVol(unsigned long a /*$v0*/, short b /*$a1*/, short c /*$a2*/)
{
}
/*
 * Offset 0x865C8
 * D:\driver2\game\C\XMPLAY.C (line 1802)
 * Stack frame base $sp, length 0
 */
short /*$ra*/ DoPan(short envpan /*$a0*/, short pan /*$a1*/)
{
}
/*
 * Offset 0x8661C
 * D:\driver2\game\C\XMPLAY.C (line 1545)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ DoVolSlide(unsigned char dat /*$a1*/)
{
}
/*
 * Offset 0x866AC
 * D:\driver2\game\C\XMPLAY.C (line 1680)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ DoToneSlide()
{ // line 2, address 0x866ac
	int dist; // $v1
} // line 22, address 0x86714
/*
 * Offset 0x86714
 * D:\driver2\game\C\XMPLAY.C (line 1561)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ DoXMPanSlide(unsigned char inf /*$a0*/)
{ // line 1, address 0x86714
	unsigned char lo; // $v0
	unsigned char hi; // $a0
	short pan; // $v1
} // line 27, address 0x86798
/*
 * Offset 0x867A0
 * D:\driver2\game\C\XMPLAY.C (line 1517)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ Arpeggio(unsigned char dat /*$a1*/)
{ // line 1, address 0x867a0
	unsigned char note; // $a2
} // line 20, address 0x8684c
/*
 * Offset 0x8684C
 * D:\driver2\game\C\XMPLAY.C (line 1372)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetInstr(unsigned char inst /*$a0*/)
{ // line 1, address 0x8684c
	unsigned long *j; // $a2
} // line 61, address 0x86940
/*
 * Offset 0x86948
 * D:\driver2\game\C\XMPLAY.C (line 1328)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetNote(unsigned char note /*$a0*/)
{ // line 1, address 0x86948
	unsigned char *j; // $a0
} // line 35, address 0x86a20
/*
 * Offset 0x86A28
 * D:\driver2\game\C\XMPLAY.C (line 568)
 * Stack frame base $sp, length 0
 */
unsigned long /*$ra*/ GetLong(unsigned char *mpp /*$a0*/)
{ // line 1, address 0x86a28
} // line 16, address 0x86a54
/*
 * Offset 0x86A54
 * D:\driver2\game\C\XMPLAY.C (line 237)
 * Stack frame base $sp, length 0
 */
short /*$ra*/ Interpolate(short p /*$a0*/, short p1 /*$a1*/, short p2 /*$a2*/, short v1 /*$a3*/, int v2 /*stack 16*/)
{ // line 1, address 0x86a54
} // line 11, address 0x86ad4
/*
 * Offset 0x86AD4
 * D:\driver2\game\C\XMPLAY.C (line 288)
 * Stack frame base $sp, length 0
 */
unsigned short /*$ra*/ JPGetPeriod(unsigned char note /*$a0*/, short fine /*$a1*/)
{
}
/*
 * Offset 0x86B08
 * D:\driver2\game\C\XMPLAY.C (line 299)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
unsigned short /*$ra*/ GetPeriod(unsigned char note /*$a2*/, unsigned short c2spd /*$a1*/)
{ // line 1, address 0x86b08
} // line 8, address 0x86b58
/*
 * Offset 0x86B58
 * D:\driver2\game\C\XMPLAY.C (line 2540)
 * Stack frame base $sp, length 0
 */
long /*$ra*/ GetFreq2(long period /*$v1*/)
{ // line 2, address 0x86b58
	int okt; // $a1
	long frequency; // $a0
} // line 16, address 0x86bb0
/*
 * Offset 0x86BB0
 * D:\driver2\game\C\XMPLAY.C (line 3068)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: ra
 */
void /*$ra*/ CurrentKeyStat()
{ // line 2, address 0x86bb0
	int t; // $a1
	char KeyStat[24]; // stack address -32
} // line 15, address 0x86c5c
/*
 * Offset 0x86C5C
 * D:\driver2\game\C\XMPLAY.C (line 3091)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ StpCh(int Channel /*$a0*/)
{
}
/*
 * Offset 0x86C80
 * D:\driver2\game\C\XMPLAY.C (line 3115)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetFrq(int Channel /*$a0*/, int Pitch /*$a1*/)
{
}
/*
 * Offset 0x86CA0
 * D:\driver2\game\C\XMPLAY.C (line 3104)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetVol(int Channel /*$a0*/, int LVol /*$a1*/, int RVol /*$a2*/)
{
}
/*
 * Offset 0x86CCC
 * D:\driver2\game\C\XMPLAY.C (line 3003)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ PlaySFX(int VBID /*$a0*/, int Channel /*$a1*/, int Inst /*$a2*/, int Pitch /*$a3*/, int LV /*stack 16*/, int RV /*stack 20*/)
{ // line 1, address 0x86ccc
} // line 23, address 0x86d60
/*
 * Offset 0x86D60
 * D:\driver2\game\C\XMPLAY.C (line 3308)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ ClearSPU(int VBID /*$a0*/)
{ // line 1, address 0x86d60
	int i; // $s1
	int Amount; // $a1
} // line 15, address 0x86ddc
/*
 * Offset 0x86DDC
 * D:\driver2\game\C\XMPLAY.C (line 3035)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitSPUChannel(int Channel /*$a0*/)
{
}
/*
 * Offset 0x86E44
 * D:\driver2\game\C\XMPLAY.C (line 3126)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SilenceXM(int Song_ID /*$a0*/)
{ // line 2, address 0x86e44
	int t; // $s0
	int i; // $s1
	int c; // $a0
	int pmsk; // $v0
} // line 25, address 0x86f24
/*
 * Offset 0x86F24
 * D:\driver2\game\C\XMPLAY.C (line 2289)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ UpdateEffs()
{ // line 2, address 0x86f24
	int t; // $s0
	int pmsk; // $v1
	unsigned char MaxChans; // $s1
} // line 24, address 0x86fbc
/*
 * Offset 0x86FD8
 * D:\driver2\game\C\XMPLAY.C (line 2516)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ IntVols(int Vol1 /*$a0*/, int Vol2 /*$a1*/)
{ // line 1, address 0x86fd8
	int a; // $v1
} // line 11, address 0x87008
/*
 * Offset 0x87008
 * D:\driver2\game\C\XMPLAY.C (line 3337)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetFreeSongID()
{ // line 2, address 0x87008
	int i; // $v1
} // line 12, address 0x87058
/*
 * Offset 0x87058
 * D:\driver2\game\C\XMPLAY.C (line 3359)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ JPClearSPUFlags(int SongID /*$a0*/)
{ // line 1, address 0x87058
	int i; // $a1
} // line 9, address 0x8708c
/*
 * Offset 0x8708C
 * D:\driver2\game\C\XMPLAY.C (line 2099)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ CalcPlayPos(int StartPos /*$s4*/)
{ // line 1, address 0x8708c
	int SP; // $s1
	int t; // $s0
	int i; // $a1
} // line 15, address 0x87144
/*
 * Offset 0x87144
 * D:\driver2\game\C\XMPLAY.C (line 2143)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ JCalcPat(unsigned char *j /*$a0*/)
{ // line 2, address 0x87144
	unsigned char b; // $v1
	int ret; // $a1
} // line 44, address 0x871b4
/*
 * Offset 0x871B4
 * D:\driver2\game\C\XMPLAY.C (line 2116)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ PACKEDCalcPlayPos(int StartPos /*$s3*/)
{ // line 1, address 0x871b4
	int SP; // $s0
	int i; // $a1
	unsigned char *pataddr; // $a0
	unsigned char patdat; // $v1
} // line 23, address 0x87290
/*
 * Offset 0x87290
 * D:\driver2\game\C\XMPLAY.C (line 2368)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetEmpty(int old /*$t1*/)
{ // line 1, address 0x87290
	int i; // $a3
	struct XMCHANNEL *j; // $a0
} // line 28, address 0x87358