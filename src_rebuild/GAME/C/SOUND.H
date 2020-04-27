#ifndef SOUND_H
#define SOUND_H

extern int gMasterVolume;
extern int gMusicVolume;
extern CHANNEL_DATA channels[16];

extern void InitSound(); // 0x000790E4

extern void ClearChannelFields(int channel); // 0x000791D4

extern void ResetSound(); // 0x00079250

extern void SetReverbState(int on); // 0x0007A6C0

extern void SetReverbInGameState(int on); // 0x0007A704

extern int SetReverbChannelState(int ch, int on); // 0x0007A75C

extern void SetMasterVolume(int vol); // 0x0007A7B0

extern char SetPlayerOwnsChannel(int chan, char player); // 0x0007ABA8

extern int StartSound(int channel, int bank, int sample, int volume, int pitch); // 0x0007A7F8

extern int Start3DTrackingSound(int channel, int bank, int sample, VECTOR *position, long *velocity); // 0x0007A994

extern int Start3DSoundVolPitch(int channel, int bank, int sample, int x, int y, int z, int volume, int pitch); // 0x0007A894

extern int CompleteSoundSetup(int channel, int bank, int sample, int pitch, int proximity); // 0x00079330

extern void SetChannelPitch(int channel, int pitch); // 0x00079504

extern void SetChannelVolume(int channel, int volume, int proximity); // 0x0007AA78

extern void ComputeDoppler(struct CHANNEL_DATA *ch); // 0x000795C4

extern void SetChannelPosition3(int channel, VECTOR *position, long *velocity, int volume, int pitch, int proximity); // 0x0007ABCC

extern void PauseXM(); // 0x00079734

extern void PauseSFX(); // 0x00079794

extern void PauseSound(); // 0x0007ACD8

extern void UnPauseXM(); // 0x00079958

extern void UnPauseSFX(); // 0x000799B0

extern void UnPauseSound(); // 0x0007AD10

extern void StopChannel(int channel); // 0x0007AD40

extern void StopAllChannels(); // 0x0007ADF4

extern void LockChannel(int channel); // 0x0007AE34

extern void UnlockChannel(int c); // 0x0007AE64

extern void SoundHandler(); // 0x00079B38

extern int LoadSoundBank(char *address, int length, int bank); // 0x0007AE90

extern void UpdateXMSamples(int num_samps); // 0x0007B1C4

extern int LoadSoundBankDynamic(char *address, int length, int dbank); // 0x00079BCC

extern void FreeXM(); // 0x0007AF84

extern void StartXM(int reverb); // 0x0007AFD0

extern void StopXM(); // 0x0007B050

extern void SetXMVolume(int volume); // 0x0007B074

extern int GetFreeChannel(); // 0x00079E04

extern void UpdateVolumeAttributesS(int channel, int proximity); // 0x00079F38

extern void UpdateVolumeAttributesM(int channel); // 0x0007B0C4

extern int CalculateVolume(int channel); // 0x0007A360

extern void AllocateReverb(long mode, long depth); // 0x0007AB3C

extern int FESound(int sample); // 0x0007A534

extern void VsyncProc(); // 0x0007B178


#endif
