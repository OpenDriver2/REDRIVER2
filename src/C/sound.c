
#include "../decomp_defs.h"

long dummylong[3] = { 0, 0, 0 };

/*
 * Offset 0x7914C
 * D:\driver2\game\C\SOUND.C (line 114)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ InitSound()
{ // line 2, address 0x7914c
	int ct; // $s0
} // line 47, address 0x7923c
/*
 * Offset 0x7923C
 * D:\driver2\game\C\SOUND.C (line 163)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ClearChannelFields(int channel /*$a0*/)
{
}
/*
 * Offset 0x792B8
 * D:\driver2\game\C\SOUND.C (line 187)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ ResetSound()
{ // line 2, address 0x792b8
	int ct; // $s0
} // line 35, address 0x79398
/*
 * Offset 0x79398
 * D:\driver2\game\C\SOUND.C (line 399)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ CompleteSoundSetup(int channel /*$s2*/, int bank /*$s0*/, int sample /*$s5*/, int pitch /*$s1*/, int proximity /*stack 16*/)
{ // line 1, address 0x79398
	long bpf; // $a1
	long rate; // $a1
} // line 44, address 0x7956c
/*
 * Offset 0x7956C
 * D:\driver2\game\C\SOUND.C (line 450)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetChannelPitch(int channel /*$a0*/, int pitch /*$a1*/)
{ // line 1, address 0x7956c
	long rate; // $a0
} // line 20, address 0x7961c
/*
 * Offset 0x7962C
 * D:\driver2\game\C\SOUND.C (line 501)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ ComputeDoppler(struct CHANNEL_DATA *ch /*$s1*/)
{ // line 1, address 0x7962c
	int dist; // $s0
	int seperationrate; // $v0
	struct _PLAYER *pl; // $s0
} // line 26, address 0x79788
/*
 * Offset 0x7979C
 * D:\driver2\game\C\SOUND.C (line 635)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ PauseXM()
{ // line 1, address 0x7979c
	int fade; // $v1
} // line 20, address 0x797fc
/*
 * Offset 0x797FC
 * D:\driver2\game\C\SOUND.C (line 657)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ PauseSFX()
{ // line 1, address 0x797fc
	int i; // $s1
	int fade; // $s3
} // line 24, address 0x799c0
/*
 * Offset 0x799C0
 * D:\driver2\game\C\SOUND.C (line 698)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ UnPauseXM()
{ // line 1, address 0x799c0
	int fade; // $a1
} // line 19, address 0x79a18
/*
 * Offset 0x79A18
 * D:\driver2\game\C\SOUND.C (line 720)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ UnPauseSFX()
{ // line 1, address 0x79a18
	int i; // $s1
	int fade; // $s2
} // line 22, address 0x79ba0
/*
 * Offset 0x79BA0
 * D:\driver2\game\C\SOUND.C (line 822)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SoundHandler()
{ // line 2, address 0x79ba0
	int ct; // $a0
	long off; // $a1
} // line 16, address 0x79c24
/*
 * Offset 0x79C34
 * D:\driver2\game\C\SOUND.C (line 904)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ LoadSoundBankDynamic(char *address /*$s2*/, int length /*$s6*/, int dbank /*$a2*/)
{ // line 1, address 0x79c34
	static struct __LSBDinfo tabs; // address 0x0
	int i; // $a3
	int num_samples; // $s1
	int slength; // $s0
} // line 73, address 0x79e6c
/*
 * Offset 0x79E6C
 * D:\driver2\game\C\SOUND.C (line 1124)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ GetFreeChannel()
{ // line 1, address 0x79e6c
	int ct; // $a0
	int least; // $s1
	int il; // $s0
	char status[24]; // stack address -40
} // line 32, address 0x79fa0
/*
 * Offset 0x79FA0
 * D:\driver2\game\C\SOUND.C (line 1163)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ UpdateVolumeAttributesS(int channel /*$s2*/, int proximity /*$s5*/)
{ // line 1, address 0x79fa0
	int volume; // $s1
	int vol; // $a2
	long ang; // $s0
	long dist; // $s6
	int player_id; // $a3
	struct VECTOR *pos; // $s3
	struct VECTOR *cam_pos; // $s4
	int cam_ang; // $fp
	long damp; // $v1
	{ // line 52, address 0x7a21c
	} // line 54, address 0x7a268
} // line 67, address 0x7a398
/*
 * Offset 0x7A3C8
 * D:\driver2\game\C\SOUND.C (line 1257)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ CalculateVolume(int channel /*$a2*/)
{ // line 1, address 0x7a3c8
	int volume; // $s0
	struct VECTOR *pp; // $a3
	{ // line 9, address 0x7a45c
		int distance; // $v1
		{ // line 14, address 0x7a45c
			struct VECTOR ofse; // stack address -24
		} // line 17, address 0x7a45c
		{ // line 29, address 0x7a514
			int fade; // $a0
		} // line 34, address 0x7a56c
	} // line 36, address 0x7a588
} // line 38, address 0x7a59c
/*
 * Offset 0x7A59C
 * D:\driver2\game\C\SOUND.C (line 1326)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ FESound(int sample /*$s0*/)
{ // line 1, address 0x7a59c
	long bpf; // $a1
	long rate; // $a1
	long pitch; // $s5
	int channel; // $s6
} // line 32, address 0x7a728
/*
 * Offset 0x7A728
 * D:\driver2\game\C\SOUND.C (line 233)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetReverbState(int on /*$a0*/)
{
}
/*
 * Offset 0x7A76C
 * D:\driver2\game\C\SOUND.C (line 253)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetReverbInGameState(int on /*$a0*/)
{ // line 1, address 0x7a76c
	long cl; // $a1
} // line 11, address 0x7a7c4
/*
 * Offset 0x7A7C4
 * D:\driver2\game\C\SOUND.C (line 274)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ SetReverbChannelState(int ch /*$a0*/, int on /*$s0*/)
{ // line 1, address 0x7a7c4
	long cl; // $s1
	int prev; // $s2
} // line 7, address 0x7a818
/*
 * Offset 0x7A818
 * D:\driver2\game\C\SOUND.C (line 288)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetMasterVolume(int vol /*$a0*/)
{
}
/*
 * Offset 0x7A860
 * D:\driver2\game\C\SOUND.C (line 323)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ StartSound(int channel /*$a0*/, int bank /*$s1*/, int sample /*$s2*/, int volume /*$s0*/, int pitch /*stack 16*/)
{
}
/*
 * Offset 0x7A8FC
 * D:\driver2\game\C\SOUND.C (line 357)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ Start3DSoundVolPitch(int channel /*$s1*/, int bank /*$s0*/, int sample /*$s4*/, int x /*$s3*/, int y /*stack 16*/, int z /*stack 20*/, int volume /*stack 24*/, int pitch /*stack 28*/)
{
}
/*
 * Offset 0x7A9FC
 * D:\driver2\game\C\SOUND.C (line 342)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ Start3DTrackingSound(int channel /*$s1*/, int bank /*$s0*/, int sample /*$s3*/, struct VECTOR *position /*$s2*/, long *velocity /*stack 16*/)
{
}
/*
 * Offset 0x7AAE0
 * D:\driver2\game\C\SOUND.C (line 477)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ SetChannelVolume(int channel /*$s0*/, int volume /*$t1*/, int proximity /*$a2*/)
{ // line 1, address 0x7aae0
} // line 18, address 0x7ab8c
/*
 * Offset 0x7ABA4
 * D:\driver2\game\C\SOUND.C (line 1303)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ AllocateReverb(long mode /*$s1*/, long depth /*$s0*/)
{ // line 1, address 0x7aba4
	struct SpuReverbAttr r_attr; // stack address -40
} // line 16, address 0x7abfc
/*
 * Offset 0x7AC10
 * D:\driver2\game\C\SOUND.C (line 307)
 * Stack frame base $sp, length 0
 */
char /*$ra*/ SetPlayerOwnsChannel(int chan /*$a0*/, char player /*$a1*/)
{ // line 1, address 0x7ac10
} // line 5, address 0x7ac34
/*
 * Offset 0x7AC34
 * D:\driver2\game\C\SOUND.C (line 588)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ SetChannelPosition3(int channel /*$s1*/, struct VECTOR *position /*$a0*/, long *velocity /*$t0*/, int volume /*$t2*/, int pitch /*stack 16*/, int proximity /*stack 20*/)
{ // line 1, address 0x7ac34
} // line 24, address 0x7ad28
/*
 * Offset 0x7AD40
 * D:\driver2\game\C\SOUND.C (line 683)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ PauseSound()
{
}
/*
 * Offset 0x7AD78
 * D:\driver2\game\C\SOUND.C (line 744)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ UnPauseSound()
{ // line 1, address 0x7ad78
} // line 9, address 0x7ada8
/*
 * Offset 0x7ADA8
 * D:\driver2\game\C\SOUND.C (line 760)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ StopChannel(int channel /*$s2*/)
{ // line 1, address 0x7ada8
	{ // line 3, address 0x7adcc
		unsigned char l; // $s3
		int vsync; // $s0
	} // line 11, address 0x7ae40
} // line 13, address 0x7ae5c
/*
 * Offset 0x7AE5C
 * D:\driver2\game\C\SOUND.C (line 780)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ StopAllChannels()
{ // line 2, address 0x7ae5c
	int ct; // $s0
} // line 10, address 0x7ae9c
/*
 * Offset 0x7AE9C
 * D:\driver2\game\C\SOUND.C (line 797)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ LockChannel(int channel /*$a0*/)
{
}
/*
 * Offset 0x7AECC
 * D:\driver2\game\C\SOUND.C (line 811)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ UnlockChannel(int c /*$a0*/)
{
}
/*
 * Offset 0x7AEF8
 * D:\driver2\game\C\SOUND.C (line 845)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ LoadSoundBank(char *address /*$s3*/, int length /*$s2*/, int bank /*$s1*/)
{ // line 1, address 0x7aef8
	int num_samples; // $s4
	int slength; // $s2
	int spuaddress; // $s1
	int ct; // $v1
} // line 31, address 0x7afec
/*
 * Offset 0x7AFEC
 * D:\driver2\game\C\SOUND.C (line 993)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ FreeXM()
{
}
/*
 * Offset 0x7B038
 * D:\driver2\game\C\SOUND.C (line 1012)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ StartXM(int reverb /*$s2*/)
{ // line 1, address 0x7b038
	int ct; // $s0
} // line 16, address 0x7b0b8
/*
 * Offset 0x7B0B8
 * D:\driver2\game\C\SOUND.C (line 1035)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ StopXM()
{
}
/*
 * Offset 0x7B0DC
 * D:\driver2\game\C\SOUND.C (line 1073)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetXMVolume(int volume /*$a0*/)
{ // line 1, address 0x7b0dc
	int vol; // $a1
} // line 12, address 0x7b12c
/*
 * Offset 0x7B12C
 * D:\driver2\game\C\SOUND.C (line 1232)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ UpdateVolumeAttributesM(int channel /*$s0*/)
{ // line 1, address 0x7b12c
	int volume; // $a1
	int vol; // $a0
} // line 17, address 0x7b1e0
/*
 * Offset 0x7B1E0
 * D:\driver2\game\C\SOUND.C (line 1371)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ VsyncProc()
{
}
/*
 * Offset 0x7B22C
 * D:\driver2\game\C\SOUND.C (line 882)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ UpdateXMSamples(int num_samps /*$s2*/)
{ // line 1, address 0x7b22c
	int i; // $s0
} // line 6, address 0x7b290