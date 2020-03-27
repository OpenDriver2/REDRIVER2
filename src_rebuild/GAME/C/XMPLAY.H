#ifndef XMPLAY_H
#define XMPLAY_H


extern short Interpolate(short p, short p1, short p2, short v1, int v2); // 0x000869EC

extern unsigned short GetLogPeriod(unsigned char note, unsigned short fine); // 0x000863EC

extern unsigned short JPGetPeriod(unsigned char note, short fine); // 0x00086A6C

extern unsigned short GetPeriod(unsigned char note, unsigned short c2spd); // 0x00086AA0

extern void XM_Exit(); // 0x00085D18

extern void XM_CloseVAB(int VabID); // 0x00085FB4

extern void XM_CloseVAB2(int VabID); // 0x000862F0

extern void XM_Update(); // 0x00085D78

extern void XM_PlayStart(int Song_ID, int PlayMask); // 0x00085E38

extern void XM_PlayStop(int Song_ID); // 0x00085DC8

extern int InitXMData(unsigned char *mpp, int XM_ID, int S3MPan); // 0x000831B0

extern unsigned long GetLong(unsigned char *mpp); // 0x000869C0

extern void XM_OnceOffInit(int PAL); // 0x00085F7C

extern int XM_Init(int VabID, int XM_ID, int SongID, int FirstCh, int Loop, int PlayMask, int PlayType, int SFXNum); // 0x0008344C

extern int JPlayNote(unsigned char *j, int pmsk); // 0x0008392C

extern void JPlayEffects(); // 0x00083B64

extern void SPE(unsigned char eff, unsigned char dat); // 0x00083DA4

extern void DoEEffects(unsigned char dat); // 0x000841B0

extern void SetNote(unsigned char note); // 0x000868E0

extern void SetInstr(unsigned char inst); // 0x000867E4

extern void SetPer(); // 0x00084524

extern void Arpeggio(unsigned char dat); // 0x00086738

extern void DoVolSlide(unsigned char dat); // 0x000865B4

extern void DoXMPanSlide(unsigned char inf); // 0x000866AC

extern void DoS3MRetrig(unsigned char inf); // 0x000846D8

extern void DoToneSlide(); // 0x00086644

extern void DoVibrato(); // 0x000848F0

extern void DoTremolo(); // 0x000849F0

extern short DoPan(short envpan, short pan); // 0x00086560

extern short DoVol(unsigned long a, short b, short c); // 0x00086538

extern void UpdateXMData(); // 0x00086484

extern void UpdateWithTimer(int SC); // 0x0008607C

extern void XM_DoFullUpdate(int SC); // 0x00086178

extern void UpdatePatternData(int SC); // 0x00084B3C

extern int CalcPlayPos(int StartPos); // 0x00087024

extern int PACKEDCalcPlayPos(int StartPos); // 0x0008714C

extern int JCalcPat(unsigned char *j); // 0x000870DC

extern void ApplyEffs(); // 0x00085034

extern void UpdateEffs(); // 0x00086EBC

extern void DoDolbySS(); // 0x00085374

extern int GetEmpty(int old); // 0x00087228

extern void UpdateHardware(); // 0x00085448

extern int IntVols(int Vol1, int Vol2); // 0x00086F70

extern long GetFreq2(long period); // 0x00086AF0

extern short ProcessEnvelope(short v, unsigned char keyon, int JSmp); // 0x000857A4

extern short ProcessPanEnvelope(short v, unsigned char keyon, int JSmp); // 0x00085974

extern void XM_SetSongPos(int Song_ID, unsigned short pos); // 0x00085E8C

extern void PlaySFX(int VBID, int Channel, int Inst, int Pitch, int LV, int RV); // 0x00086C64

extern void InitSPUChannel(int Channel); // 0x00086D74

extern void CurrentKeyStat(); // 0x00086B48

extern void StpCh(int Channel); // 0x00086BF4

extern void SetVol(int Channel, int LVol, int RVol); // 0x00086C38

extern void SetFrq(int Channel, int Pitch); // 0x00086C18

extern void SilenceXM(int Song_ID); // 0x00086DDC

extern void XM_Pause(int Song_ID); // 0x00085C38

extern void XM_Restart(int Song_ID); // 0x00085B44

extern void XM_SetMasterVol(int Song_ID, unsigned char Vol); // 0x00086008

extern void ClearSPU(int VBID); // 0x00086CF8

extern void XM_FreeVAG(int addr); // 0x0008605C

extern int GetFreeSongID(); // 0x00086FA0

extern void XM_Quit(int SongID); // 0x00086234

extern void JPClearSPUFlags(int SongID); // 0x00086FF0

extern int XM_GetFreeVAB(); // 0x00086278

extern void XM_SetVAGAddress(int VabID, int slot, int addr); // 0x000862B8

extern int XM_GetSongSize(); // 0x0008639C

extern void XM_SetSongAddress(unsigned char *Address); // 0x00086358

extern void XM_FreeAllSongIDs(); // 0x000863A4

extern int XM_GetFileHeaderSize(); // 0x000863E4

extern void XM_SetFileHeaderAddress(unsigned char *Address); // 0x000863B0


#endif
