#ifndef XMPLAY_H
#define XMPLAY_H

#define XM_NTSC 0				/* Machine type */
#define XM_PAL 1

#define XM_MONO 0
#define XM_STEREO 1

#define XM_DOLBY_OFF 0
#define XM_DOLBY_LEFT 1
#define XM_DOLBY_RIGHT 2

#define XM_Loop 1				/* Looping song */
#define XM_NoLoop 0			/* Once off song */

#define XM_Music 0			/* Playback as music */
#define XM_SFX 1				/* Playback as SFX */

#define MD_id 0
#define MD_sngname  17
#define MD_trkname  21+17
#define MD_version  20+21+17
#define MD_hdsize   20+21+17+2
#define MD_snglen   20+21+17+2+4
#define MD_restart  20+21+17+2+4+2
#define MD_numchan  20+21+17+2+4+2+2
#define MD_numpat   20+21+17+2+4+2+2+2
#define MD_numins   20+21+17+2+4+2+2+2+2
#define MD_flags    20+21+17+2+4+2+2+2+2+2
#define MD_tempo    20+21+17+2+4+2+2+2+2+2+2
#define MD_bpm      20+21+17+2+4+2+2+2+2+2+2+2
#define MD_orders   20+21+17+2+4+2+2+2+2+2+2+2+2
#define MD_patstrt 20+21+17+2+4+2+2+2+2+2+2+2+2+256

typedef struct _XMHEADER {
	u_short version;
	u_short songlength;               /* (word) Song length (in patten order table) */
	u_short restart;                  /* (word) Restart position */
	u_short numchn;                   /* (word) Number of channels (2,4,6,8,10,...,32) */
	u_short numpat;                   /* (word) Number of patterns (max 256) */
	u_short numins;                   /* (word) Number of instruments (max 128) */
	u_short flags;                    /* (word) Flags: bit 0: 0 = Amiga freq */
	u_short tempo;                    /* (word) Default tempo */
	u_short bpm;
	u_short XMChannels;
	u_short XMPSXChannels;
	u_long *JAP_PAT_ADDR[256];     /* Pattern Start Addresses (maxpatt*chnls)*/
	u_long *JAP_PAT_ADDR2[256];     /* Pattern Start Addresses (maxpatt*chnls)*/
	u_long *JAP_InstrumentOffset[128];
	u_long *JAP_SampAddr[128];
	u_long *JAP_SampHdrAddr[128];
	u_char jorders[256];		/* list of patterns */
	int	  S3MPanning;
} XMHEADER;


typedef struct _XMCHANNEL {
	u_short Octave;
	short LVol;
	short RVol;
	short OldLVol;
	short OldRVol;
	u_short OldPeriod;
	u_char OldSample;
	u_long OldSOff;
	u_long SOffset;
	u_char nothing;
	u_char ChDead;
	u_char panenvflg;		/* envelope flag */
	u_char panenvpts;		/* number of envelope points */
	u_char panenvsus;		/* envelope sustain index */
	u_char panenvbeg;		/* envelope loop begin */
	u_char panenvend;		/* envelope loop end */
	short panenvp;			/* current envelope counter */
	u_short panenva;		/* envelope index a */
	u_short panenvb;		/* envelope index b */
	u_short keyoffspd;
	u_char envflg;       /* envelope flag */
	u_char envpts;			/* number of envelope points */
	u_char envsus;			/* envelope sustain index */
	u_char envbeg;			/* envelope loop begin */
	u_char envend;			/* envelope loop end */
	short envp;				/* current envelope counter */
	u_short enva;			/* envelope index a */
	u_short envb;			/* envelope index b */

	u_char ins;
	u_char vol;
	u_char dat;
	u_char datold;
	u_char eff;
	u_char not;
	u_char oldvslide;
	u_char oldfvslide;
	u_char oldfslide;
	short fadevol;		/* fading volume */
	u_char keyon;		/* if 1=key is pressed. */
	u_char kick;	   	/* if 1=sample has to be restarted */
	u_char kick2;	   	/* if 1=sample has to be restarted */
	u_char sample;		/* which sample number (0-31) */
	short handle;		/* which sample-handle */
	u_long start;		/* The start byte index in the sample */
	u_char panning;		/* panning position */
	u_char pansspd;		/* panslide speed */
	u_char volume;		/* volume (0 - 64) to play the sample at */
	u_short period;		/* period to play the sample at */
	u_short SPUPitch;		/* period to play the sample at */
	char transpose;
	u_char note;
	short ownper;
	short ownvol;
	short UserVol;
	char retrig;		/* retrig value (0 means don't retrig) */
	u_short c2spd;		/* what finetune to use */
	u_char tmpvolume;	/* tmp volume  JAP */
	u_short tmpperiod;	/* tmp period */
	u_short wantedperiod;	/* period to slide to (with effect 3 or 5) */
	u_short slidespeed;	/* */
	u_short portspeed;	/* noteslide speed (toneportamento) */
	u_char s3mtremor;	/* s3m tremor (effect I) counter */
	u_char s3mvolslide;	/* last used volslide */
	u_char s3mrtgspeed;	/* last used retrig speed */
	u_char s3mrtgslide;	/* last used retrig slide */
	u_char glissando;	/* glissando (0 means off) */
	u_char wavecontrol;	/* */
	u_char vibpos;		/* current vibrato position */
	u_char vibspd;		/* "" speed */
	u_char vibdepth;		/* "" depth */
	u_char trmpos;		/* current tremolo position */
	u_char trmspd;		/* "" speed */
	u_char trmdepth;		/* "" depth */
	u_char SPUChannel;	/* SPU Channel to play sound on */
	u_char Dolby;
//108
} XMCHANNEL;


typedef struct _XMSONG {
	u_char Status;
	int	  HeaderNum;
	int	  CurPos;			  /* Index into pattern data */
	u_short reppos;			  /* patternloop position */
	u_short repcnt;           /* times to loop */
	u_short vbtick;           /* tick counter */
	u_short patbrk;           /* position where to start a new pattern */
	u_char  patdly;           /* patterndelay counter */
	u_char  patdly2;          /* patterndelay counter */
	u_short numrow;           /* number of rows on current pattern */
	short   posjmp;           /* flag to indicate a position jump is needed*/
	u_short PatternPos;       /* current row number (0-255) */
	short   SongPos;          /* current song position */
	u_short CurrentPattern;
	u_short SongSpeed;        /* current songspeed */
	u_short SongBPM;
	int	  SongLoop;         /* loop module ? */
	u_char  SongVolume;	     /* song volume (0-128) */
	u_char  MasterVolume;	     /* song volume (0-128) */
	int	  XMActiveVoices;	  /* number of voices currently playing */
	int	  NotAmiga;
	u_char  XMPlay;
	int	  FirstCh;			  /* First SPU channel to playback on */
	int	  JBPM;
	int	  PCounter;
	u_short PatSize;
	u_long *PatAdr;
	u_long *PatAdr2;
	int	  PlayMask;
	int	  SFXNum;
	XMCHANNEL XM_Chnl[24];	  /* max 32 channels per song*/
	int JUp;
	short	  PlayNext;
	short BPlayNext;
	short BPlayFlag;
	int  CurrentStart;
	u_char  VabID;
	short	  UserPan;
	u_char  MaxChans;
	//2689
}XMSONG;


#define	XMEF_APPREGIO 0		/* Effects */
#define	XMEF_PORTUP 1
#define	XMEF_PORTDOWN 2
#define	XMEF_TONEPORT 3
#define	XMEF_VIBRATO 4
#define	XMEF_PORT_VOLSLD 5
#define	XMEF_VIB_VOLSLD 6
#define	XMEF_TREMELO 7
#define	XMEF_PANPOS 8
#define	XMEF_SAMPOFFSET 9
#define	XMEF_VOLSLD 10
#define	XMEF_POSJMP 11
#define	XMEF_VOLUME 12
#define	XMEF_PATBREAK 13
#define	XMEF_E 14
#define	XMEF_SETSPEED 15
#define	XMEF_GLOBALVOL 16
#define	XMEF_GLOBALVOLSLD 17
#define	XMEF_XM_VOLSLD 23
#define	XMEF_XM_PANSLD 24

#define	XMEF_E_FINESLD_UP 1	/* Effects from above E command */
#define	XMEF_E_FINESLD_DOWN 2
#define	XMEF_E_GLISSANDO 3
#define	XMEF_E_VIB_WAVE 4
#define	XMEF_E_FINETUNE 5
#define	XMEF_E_PATLOOP 6
#define	XMEF_E_TREM_WAVE 7
#define	XMEF_E_NOTUSED 8
#define	XMEF_E_RETRIG 9
#define	XMEF_E_FINEVOL_UP 10
#define	XMEF_E_FINEVOL_DOWN 11
#define	XMEF_E_CUTNOTE 12
#define	XMEF_E_NOTEDELAY 13
#define	XMEF_E_PATDELAY 14

/*Envelope flags*/

#define EF_ON           1
#define EF_SUSTAIN      2
#define EF_LOOP         4

typedef struct _XM_HeaderInfo
{
	u_short	BPM;
	u_short	Speed;
} XM_HeaderInfo;

typedef struct _XM_VABInfo
{
	u_char*		Address;
	u_long		Size;
} XM_VABInfo;

typedef struct _XM_Feedback
{
	u_char	Volume;
	short		Panning;
	int		CurrentStart;
	short		PlayNext;
	u_short	SongLength;
	u_char	Status;
	u_short	PatternPos;
	short		SongPos;
	u_short	CurrentPattern;
	u_short	SongSpeed;
	u_short	SongBPM;
	int		SongLoop;
	int		ActiveVoices;
} XM_Feedback;

short Interpolate(short p, short p1, short p2, short v1, short v2); // 0x000869EC

u_short GetLogPeriod(u_char note, u_short fine); // 0x000863EC

u_short JPGetPeriod(u_char note, short fine); // 0x00086A6C

u_short GetPeriod(u_char note, u_short c2spd); // 0x00086AA0

void XM_Exit(); // 0x00085D18

void XM_CloseVAB(int VabID); // 0x00085FB4

void XM_CloseVAB2(int VabID); // 0x000862F0

void XM_Update(); // 0x00085D78

void XM_PlayStart(int Song_ID, int PlayMask); // 0x00085E38

void XM_PlayStop(int Song_ID); // 0x00085DC8

int InitXMData(u_char *mpp, int XM_ID, int S3MPan); // 0x000831B0

unsigned long GetLong(u_char *mpp); // 0x000869C0

void XM_OnceOffInit(int PAL); // 0x00085F7C

int XM_Init(int VabID, int XM_ID, int SongID, int FirstCh, int Loop, int PlayMask, int PlayType, int SFXNum); // 0x0008344C

int JPlayNote(u_char *j, int pmsk); // 0x0008392C

void JPlayEffects(); // 0x00083B64

void SPE(u_char eff, u_char dat); // 0x00083DA4

void DoEEffects(u_char dat); // 0x000841B0

void SetNote(u_char note); // 0x000868E0

void SetInstr(u_char inst); // 0x000867E4

void SetPer(); // 0x00084524

void Arpeggio(u_char dat); // 0x00086738

void DoVolSlide(u_char dat); // 0x000865B4

void DoXMPanSlide(u_char inf); // 0x000866AC

void DoS3MRetrig(u_char inf); // 0x000846D8

void DoToneSlide(); // 0x00086644

void DoVibrato(); // 0x000848F0

void DoTremolo(); // 0x000849F0

short DoPan(short envpan, short pan); // 0x00086560

short DoVol(unsigned long a, short b, short c); // 0x00086538

void UpdateXMData(); // 0x00086484

void UpdateWithTimer(int SC); // 0x0008607C

void XM_DoFullUpdate(int SC); // 0x00086178

void UpdatePatternData(int SC); // 0x00084B3C

int CalcPlayPos(int StartPos); // 0x00087024

int PACKEDCalcPlayPos(int StartPos); // 0x0008714C

int JCalcPat(u_char *j); // 0x000870DC

void ApplyEffs(); // 0x00085034

void UpdateEffs(); // 0x00086EBC

void DoDolbySS(); // 0x00085374

int GetEmpty(int old); // 0x00087228

void UpdateHardware(); // 0x00085448

int IntVols(int Vol1, int Vol2); // 0x00086F70

long GetFreq2(long period); // 0x00086AF0

short ProcessEnvelope(short v, u_char keyon, int JSmp); // 0x000857A4

short ProcessPanEnvelope(short v, u_char keyon, int JSmp); // 0x00085974

void XM_SetSongPos(int Song_ID, u_short pos); // 0x00085E8C

void PlaySFX(int VBID, int Channel, int Inst, int Pitch, int LV, int RV); // 0x00086C64

void InitSPUChannel(int Channel); // 0x00086D74

void CurrentKeyStat(); // 0x00086B48

void StpCh(int Channel); // 0x00086BF4

void SetVol(int Channel, int LVol, int RVol); // 0x00086C38

void SetFrq(int Channel, int Pitch); // 0x00086C18

void SilenceXM(int Song_ID); // 0x00086DDC

void XM_Pause(int Song_ID); // 0x00085C38

void XM_Restart(int Song_ID); // 0x00085B44

void XM_SetMasterVol(int Song_ID, u_char Vol); // 0x00086008

void ClearSPU(int VBID); // 0x00086CF8

void XM_FreeVAG(int addr); // 0x0008605C

int GetFreeSongID(); // 0x00086FA0

void XM_Quit(int SongID); // 0x00086234

void JPClearSPUFlags(int SongID); // 0x00086FF0

int XM_GetFreeVAB(); // 0x00086278

void XM_SetVAGAddress(int VabID, int slot, int addr); // 0x000862B8

int XM_GetSongSize(); // 0x0008639C

void XM_SetSongAddress(u_char *Address); // 0x00086358

void XM_FreeAllSongIDs(); // 0x000863A4

int XM_GetFileHeaderSize(); // 0x000863E4

void XM_SetFileHeaderAddress(u_char *Address); // 0x000863B0


#endif
