/*****************************************************************************
XMPLAY.C
	XM (Extended MOD) Player code.

	Backported version from PS2 and Driver 2 disassembly
	Written by Jason Page
	(c)1999 SCEE

****************************************************************************/

#include "TYPES.H"
#include "STRINGS.H"

#include "XMPLAY.H"
#include "XMCALLS.H"

#include "LIBETC.H"
#include "LIBSPU.H"
#include "LIBMATH.H"



/**** PSX SPECIFIC ****/

SpuVoiceAttr xm_g_s_attr; 		/* Structure for individual voice attributes*/
SpuVoiceAttr uxm_g_s_attr; 		/* Structure for individual voice attributes*/
SpuReverbAttr xm_r_attr;		/* Structure for reverb */
unsigned long xm_l_vag_spu_addr[8][128];  /* Address in memory for first sound file */


/**** XM SPECIFIC ****/

int JP_Do_Nothing;

#define NTSCBPMLIMIT 150	//150 //750/5	//750/5
int BPMLimit;
int PALType;

int XM_SCAN = 0;
int JPError = 0;

char MonoMode = XM_STEREO;

XMCHANNEL *XMCU;
XMCHANNEL *XMC;
//XMHEADER	XM_Header[8];		/* MAX 8 XM's files in memory at once */
XMHEADER *mh;					/* Pointer used by internal routines */
XMHEADER *mhu;					/* Pointer used by User routines */
//XMSONG	XM_Song[24];		/* MAX 24 XM's playing at once */
XMSONG	*ms;					/* Pointer used by internal routines */
XMSONG	*mu;					/* Pointer used by User routines */


int		XM_NSA = 0;			// NEXT SONG ADDRESS
int		XM_HA = 0;				// NEXT HEADER Address;
u_char	*XM_SngAddress[32];
u_char	*XM_HeaderAddress[8];
//XMSONG	*XM_SngAddress[24];

//#define getSWord(mpp)	((short)((u_char)(*(mpp))+(u_char)((*((mpp)+1))<<8)))
//#define getWord(mpp)		((u_short)((u_char)(*(mpp))+(u_char)((*((mpp)+1))<<8)))

#define getWord(mpp) ((u_short)((*(u_char *)(mpp)) + ((*((u_char *)(mpp) + 1)) << 8)))
#define getSWord(mpp) ((short)((*(u_char *)(mpp)) + ((*((u_char *)(mpp) + 1)) << 8)))

int CurrentCh;


short iVABID[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };
short XMSongIDs[24] =
{ -1,-1,-1,-1,-1,-1,-1,-1,
 -1,-1,-1,-1,-1,-1,-1,-1,
 -1,-1,-1,-1,-1,-1,-1,-1};

short XMSPU_SFX[24] =
{ -1,-1,-1,-1,-1,-1,-1,-1,
 -1,-1,-1,-1,-1,-1,-1,-1,
 -1,-1,-1,-1,-1,-1,-1,-1};

/*****************************************************************************
LINEAR FREQUENCY TABLE used to calculate final SPU pitch
*****************************************************************************/

u_short lintab[768] = {
16726,16741,16756,16771,16786,16801,16816,16832,16847,16862,16877,16892,16908,16923,16938
,16953,
16969,16984,16999,17015,17030,17046,17061,17076,17092,17107,17123,17138,17154,17169,17185
,17200,
17216,17231,17247,17262,17278,17293,17309,17325,17340,17356,17372,17387,17403,17419,17435
,17450,
17466,17482,17498,17513,17529,17545,17561,17577,17593,17608,17624,17640,17656,17672,17688
,17704,
17720,17736,17752,17768,17784,17800,17816,17832,17848,17865,17881,17897,17913,17929,17945
,17962,
17978,17994,18010,18027,18043,18059,18075,18092,18108,18124,18141,18157,18174,18190,18206
,18223,
18239,18256,18272,18289,18305,18322,18338,18355,18372,18388,18405,18421,18438,18455,18471
,18488,
18505,18521,18538,18555,18572,18588,18605,18622,18639,18656,18672,18689,18706,18723,18740
,18757,

18774,18791,18808,18825,18842,18859,18876,18893,18910,18927,18944,18961,18978,18995,19013
,19030,
19047,19064,19081,19099,19116,19133,19150,19168,19185,19202,19220,19237,19254,19272,19289
,19306,
19324,19341,19359,19376,19394,19411,19429,19446,19464,19482,19499,19517,19534,19552,19570
,19587,
19605,19623,19640,19658,19676,19694,19711,19729,19747,19765,19783,19801,19819,19836,19854
,19872,
19890,19908,19926,19944,19962,19980,19998,20016,20034,20052,20071,20089,20107,20125,20143
,20161,
20179,20198,20216,20234,20252,20271,20289,20307,20326,20344,20362,20381,20399,20418,20436
,20455,
20473,20492,20510,20529,20547,20566,20584,20603,20621,20640,20659,20677,20696,20715,20733
,20752,
20771,20790,20808,20827,20846,20865,20884,20902,20921,20940,20959,20978,20997,21016,21035
,21054,
21073,21092,21111,21130,21149,21168,21187,21206,21226,21245,21264,21283,21302,21322,21341
,21360,
21379,21399,21418,21437,21457,21476,21496,21515,21534,21554,21573,21593,21612,21632,21651
,21671,
21690,21710,21730,21749,21769,21789,21808,21828,21848,21867,21887,21907,21927,21946,21966
,21986,
22006,22026,22046,22066,22086,22105,22125,22145,22165,22185,22205,22226,22246,22266,22286
,22306,
22326,22346,22366,22387,22407,22427,22447,22468,22488,22508,22528,22549,22569,22590,22610
,22630,
22651,22671,22692,22712,22733,22753,22774,22794,22815,22836,22856,22877,22897,22918,22939
,22960,
22980,23001,23022,23043,23063,23084,23105,23126,23147,23168,23189,23210,23230,23251,23272
,23293,
23315,23336,23357,23378,23399,23420,23441,23462,23483,23505,23526,23547,23568,23590,23611
,23632,
23654,23675,23696,23718,23739,23761,23782,23804,23825,23847,23868,23890,23911,23933,23954
,23976,
23998,24019,24041,24063,24084,24106,24128,24150,24172,24193,24215,24237,24259,24281,24303
,24325,
24347,24369,24391,24413,24435,24457,24479,24501,24523,24545,24567,24590,24612,24634,24656
,24679,
24701,24723,24746,24768,24790,24813,24835,24857,24880,24902,24925,24947,24970,24992,25015
,25038,
25060,25083,25105,25128,25151,25174,25196,25219,25242,25265,25287,25310,25333,25356,25379
,25402,
25425,25448,25471,25494,25517,25540,25563,25586,25609,25632,25655,25678,25702,25725,25748
,25771,
25795,25818,25841,25864,25888,25911,25935,25958,25981,26005,26028,26052,26075,26099,26123
,26146,
26170,26193,26217,26241,26264,26288,26312,26336,26359,26383,26407,26431,26455,26479,26502
,26526,
26550,26574,26598,26622,26646,26670,26695,26719,26743,26767,26791,26815,26839,26864,26888
,26912,
26937,26961,26985,27010,27034,27058,27083,27107,27132,27156,27181,27205,27230,27254,27279
,27304,
27328,27353,27378,27402,27427,27452,27477,27502,27526,27551,27576,27601,27626,27651,27676
,27701,
27726,27751,27776,27801,27826,27851,27876,27902,27927,27952,27977,28003,28028,28053,28078
,28104,
28129,28155,28180,28205,28231,28256,28282,28307,28333,28359,28384,28410,28435,28461,28487
,28513,
28538,28564,28590,28616,28642,28667,28693,28719,28745,28771,28797,28823,28849,28875,28901
,28927,
28953,28980,29006,29032,29058,29084,29111,29137,29163,29190,29216,29242,29269,29295,29322
,29348,
29375,29401,29428,29454,29481,29507,29534,29561,29587,29614,29641,29668,29694,29721,29748
,29775,
29802,29829,29856,29883,29910,29937,29964,29991,30018,30045,30072,30099,30126,30154,30181
,30208,
30235,30263,30290,30317,30345,30372,30400,30427,30454,30482,30509,30537,30565,30592,30620
,30647,
30675,30703,30731,30758,30786,30814,30842,30870,30897,30925,30953,30981,31009,31037,31065
,31093,
31121,31149,31178,31206,31234,31262,31290,31319,31347,31375,31403,31432,31460,31489,31517
,31546,
31574,31602,31631,31660,31688,31717,31745,31774,31803,31832,31860,31889,31918,31947,31975
,32004,
32033,32062,32091,32120,32149,32178,32207,32236,32265,32295,32324,32353,32382,32411,32441
,32470,
32499,32529,32558,32587,32617,32646,32676,32705,32735,32764,32794,32823,32853,32883,32912
,32942,
32972,33002,33031,33061,33091,33121,33151,33181,33211,33241,33271,33301,33331,33361,33391
,33421
};


/*****************************************************************************
AMIGA FREQUENCY TABLE
*****************************************************************************/

#define LOGFAC 2*16

u_short logtab[] = {
	LOGFAC * 907,LOGFAC * 900,LOGFAC * 894,LOGFAC * 887,LOGFAC * 881,LOGFAC * 875,LOGFAC * 868,LOGFAC * 862,
	LOGFAC * 856,LOGFAC * 850,LOGFAC * 844,LOGFAC * 838,LOGFAC * 832,LOGFAC * 826,LOGFAC * 820,LOGFAC * 814,
	LOGFAC * 808,LOGFAC * 802,LOGFAC * 796,LOGFAC * 791,LOGFAC * 785,LOGFAC * 779,LOGFAC * 774,LOGFAC * 768,
	LOGFAC * 762,LOGFAC * 757,LOGFAC * 752,LOGFAC * 746,LOGFAC * 741,LOGFAC * 736,LOGFAC * 730,LOGFAC * 725,
	LOGFAC * 720,LOGFAC * 715,LOGFAC * 709,LOGFAC * 704,LOGFAC * 699,LOGFAC * 694,LOGFAC * 689,LOGFAC * 684,
	LOGFAC * 678,LOGFAC * 675,LOGFAC * 670,LOGFAC * 665,LOGFAC * 660,LOGFAC * 655,LOGFAC * 651,LOGFAC * 646,
	LOGFAC * 640,LOGFAC * 636,LOGFAC * 632,LOGFAC * 628,LOGFAC * 623,LOGFAC * 619,LOGFAC * 614,LOGFAC * 610,
	LOGFAC * 604,LOGFAC * 601,LOGFAC * 597,LOGFAC * 592,LOGFAC * 588,LOGFAC * 584,LOGFAC * 580,LOGFAC * 575,
	LOGFAC * 570,LOGFAC * 567,LOGFAC * 563,LOGFAC * 559,LOGFAC * 555,LOGFAC * 551,LOGFAC * 547,LOGFAC * 543,
	LOGFAC * 538,LOGFAC * 535,LOGFAC * 532,LOGFAC * 528,LOGFAC * 524,LOGFAC * 520,LOGFAC * 516,LOGFAC * 513,
	LOGFAC * 508,LOGFAC * 505,LOGFAC * 502,LOGFAC * 498,LOGFAC * 494,LOGFAC * 491,LOGFAC * 487,LOGFAC * 484,
	LOGFAC * 480,LOGFAC * 477,LOGFAC * 474,LOGFAC * 470,LOGFAC * 467,LOGFAC * 463,LOGFAC * 460,LOGFAC * 457,
	LOGFAC * 453,LOGFAC * 450,LOGFAC * 447,LOGFAC * 443,LOGFAC * 440,LOGFAC * 437,LOGFAC * 434,LOGFAC * 431
};


/*****************************************************************************
VIBRATO SINE TABLE
*****************************************************************************/

static u_char VibratoTable[32] = {
	0,24,49,74,97,120,141,161,
	180,197,212,224,235,244,250,253,
	255,253,250,244,235,224,212,197,
	180,161,141,120,97,74,49,24
};


/*****************************************************************************
Interpolate
	Requires:
				p	CurrentPos
				p1	Start Pos
				p2 End Pos
				v1 Original Value
				v2 Destination value
*****************************************************************************/

short Interpolate(short p, short p1, short p2, short v1, short v2)
{
	short dp, dv, di;

	if (p1 == p2) return v1;

	dv = v2 - v1;
	dp = p2 - p1;
	di = p - p1;

	return v1 + ((long)(di*dv) / dp);
}



/*****************************************************************************
GetLogPeriod
	Returns AMIGA period, calculated from note and fine.
*****************************************************************************/

u_short GetLogPeriod(u_char note, u_short fine)
{
	u_char n, o;
	u_short p1, p2, i;
	short j;
	int f;

	n = note % 12;
	o = (note / 12);

	i = fine >> 4;
	i += (n << 3);                     /* n*8 + fine/16 */

	p1 = logtab[i];
	p2 = logtab[i + 1];

	j = (Interpolate(fine / 16, 0, 15, p1, p2) >> o);

	if (j == 0)
	{
		f = 1;
	}

	return(j);

}


/*****************************************************************************
JPGetPeriod
	Returns linear period calculated from note and fine.
*****************************************************************************/
u_short JPGetPeriod(u_char note, short fine)
{
	return((10L * 12 * 16 * 4) - ((u_short)note * 16 * 4) - (fine / 2) + 64);
}



/*****************************************************************************
GetPeriod
	Returns period using either linear or Amiga(log) frequency
*****************************************************************************/

u_short GetPeriod(u_char note, u_short c2spd)
{
	int a;
	a = mh->flags;
	if (ms->NotAmiga == 1)
		return (JPGetPeriod(note, c2spd));		// Linear Freq table
	else
		return (GetLogPeriod(note, c2spd));		// Amiga Freq table
}



/*****************************************************************************
XM_Exit
	Stop all tunes.
	Clear SPU of all samples used.
*****************************************************************************/

void XM_Exit(void)
{
	int i;
	for (i = 0; i < XM_NSA; i++)
	{
		XM_Quit(i);
	}
	for (i = 0; i < 8; i++)
	{
		XM_CloseVAB(i);
	}
}



void XM_CloseVAB(int VabID)
{
	if (iVABID[VabID] != -1)
	{
		ClearSPU(VabID);
		iVABID[VabID] = -1;
	}
}



void XM_CloseVAB2(int VabID)
{
	int Amount, i;

	if (iVABID[VabID] != -1)
	{
		Amount = iVABID[VabID];
		for (i = 0; i < (Amount); i++)
		{
			xm_l_vag_spu_addr[VabID][i] = 0;
		}
		iVABID[VabID] = -1;
	}
}



/*****************************************************************************
XM_Update
	Updates all songs and SFX.
*****************************************************************************/

void XM_Update(void)
{
	//XM_SCAN=VSync(1);

	if (JP_Do_Nothing)			/* Failsafe switch - if called on interrupt */
		return;

	UpdateXMData();

	//XM_SCAN=VSync(1)-XM_SCAN;

}


/*****************************************************************************
XM_PlayStart
	Starts or continues a song.

	Requires:			Song_ID
*****************************************************************************/

void XM_PlayStart(int Song_ID, int PlayMask)
{
	if (XMSongIDs[Song_ID] == -1)
		return;
	if (PlayMask != 0)
	{
		mu = (XMSONG*)(XM_SngAddress[Song_ID]);
		//		mu=&XM_Song[Song_ID]; 
		mu->PlayMask = PlayMask;
		mu->XMPlay = XM_PLAYING;
	}
}



/*****************************************************************************
XM_PlayStop
	Stops a currently playing song.
	Silences SPU.
*****************************************************************************/

void XM_PlayStop(int Song_ID)
{
	if (XMSongIDs[Song_ID] == -1)
		return;

	mu = (XMSONG*)(XM_SngAddress[Song_ID]);
	//	mu=&XM_Song[Song_ID];
	if (!mu->XMPlay)
		return;
	mu->XMPlay = XM_STOPPED;
	SilenceXM(Song_ID);
}


/*****************************************************************************
InitXMData
	Initialise an XM file.
	Requires:
				Address of XM File
				XM ID (up to user 0-23)
				S3MPan switch (XM_UseS3MPanning or XM_UseXMPanning)
*****************************************************************************/

int InitXMData(u_char *mpp, int XM_ID, int S3MPan)
{
	int t;
	int a;
	int c;

	u_long b;
	u_short b2;


	//	mhu=&XM_Header[XM_ID];
	mhu = (XMHEADER*)(XM_HeaderAddress[XM_ID]);

	mhu->S3MPanning = S3MPan;

	mhu->version = getWord(mpp + MD_version);

	mhu->songlength = getWord(mpp + MD_snglen);
	mhu->restart = getWord(mpp + MD_restart);
	mhu->XMChannels = getWord(mpp + MD_numchan);
	mhu->numpat = getWord(mpp + MD_numpat);
	mhu->numins = getWord(mpp + MD_numins);
	mhu->flags = getWord(mpp + MD_flags);
	mhu->tempo = getWord(mpp + MD_tempo);
	mhu->bpm = getWord(mpp + MD_bpm);
	mhu->XMPSXChannels = mhu->XMChannels;
	if (mhu->XMPSXChannels > 24)
		mhu->XMPSXChannels = 24;

	for (t = 0; t < mhu->songlength; t++)
	{
		mhu->jorders[t] = ((u_char)*(mpp + MD_orders + t));
	}

	a = MD_patstrt;
	c = mhu->numpat;

	for (t = 0; t < c; t++)
	{
		mhu->JAP_PAT_ADDR[t] = (u_long*)(mpp + a);				/* Store Pattern Addr's */
		b = GetLong(mpp + a);
		mhu->JAP_PAT_ADDR2[t] = (u_long*)(mpp + a + b);			/* Store Pattern Addr's */
		b2 = getWord(mpp + a + 7);
		b += b2;
		a += b;
	}

	c = mhu->numins;
	for (t = 0; t < c; t++)
	{
		b = GetLong(mpp + a);
		b2 = getWord(mpp + a + 27);
		if (b2 != 0)
		{
			mhu->JAP_SampAddr[t] = (u_long*)(mpp + 29 + a);
			mhu->JAP_SampHdrAddr[t] = (u_long*)(mpp + b + a);
			b += (40 * b2);
		}
		else
		{
			mhu->JAP_SampAddr[t] = (u_long*)0xcdcdcdcd;	//(u_long*)(mpp+29+a);
			mhu->JAP_SampHdrAddr[t] = (u_long*)0x01234567;	//(u_long*)(mpp+b+a);
		}
		mhu->JAP_InstrumentOffset[t] = (u_long*)(mpp + a);		/* Store Instrument Addr's*/
		a += b;
	}
	return(mhu->XMPSXChannels);
}


/*****************************************************************************
GetLong
	Returns a long from given address
*****************************************************************************/

u_long GetLong(u_char *mpp)
{
	u_char a;
	u_char b;
	u_char c;
	u_char d;
	u_long e;

	a = *(mpp);
	b = *(mpp + 1);
	c = *(mpp + 2);
	d = *(mpp + 3);

	e = a + (b << 8) + (c << 16) + (d << 24);

	return(e);
}



/*****************************************************************************
XM_OnceOffInit
	Initialises system. Sets up for 50 or 60 fps playback
*****************************************************************************/

void XM_OnceOffInit(int PAL)
{
	XM_NSA = 0;
	JP_Do_Nothing = 0;				/* Allow XM_Update to process */
//	for (i=0;i<24;i++)
//	{
//		mu=&XM_Song[i];
//		mu->Status=0;				/* Turn off every song */
//	}
	BPMLimit = NTSCBPMLIMIT;		/* Set Max limit for BPM */
	if (PAL == XM_NTSC)
		PALType = 0;
	else if (PAL == XM_PAL)
	{
		PALType = 1;					/* Set if PAL or NTSC */
//		PALType=0;					/* Set if PAL or NTSC */
//		BPMLimit=125;
	}
}



/*****************************************************************************
XM_Init
	Initialise a song or SFX.
	Requires:
			VAB_ID (0-7)		ID of VAB data (returned from PSX_Init)
			XM_ID (0-23)		Value corresponding to InitXMData call.
			FirstCh				First SPU Channel to play back on.
			Loop					XM_Loop or XM_NoLoop
			PlayMask				Bitpattern for which channels to process
			PlayType				XM_Music or XM_SFX (|0x80 will not start sound)
			SFXNum				Pattern number to play, if XM_SFX
*****************************************************************************/

int  XM_Init(int VabID,int XM_ID,int SongID, int FirstCh,
				 int Loop,int PlayMask,int PlayType,int SFXNum)
{
	int i;
	int pmsk;
	int Chn;
	int t;
	int SngID;
	int fr;

	if (SongID==-1)
	{
		SngID=GetFreeSongID();
		if (SngID==-1)
			return(-1);
	}
	else
	{
		if (SongID>=XM_NSA)
			return(-1);				// Not enough malloc'd song structures..
		XM_Quit(SongID);
		XMSongIDs[SongID]=0;
		SngID=SongID;
	}

	JP_Do_Nothing=1;
	mu=(XMSONG*)(XM_SngAddress[SngID]);

//	mhu=&XM_Header[XM_ID];
	mhu=(XMHEADER*)(XM_HeaderAddress[XM_ID]);

//	mu=&XM_Song[SngID];
	mu->XMPlay=XM_STOPPED;

	mu->JUp=0;

	mu->VabID=VabID;
	mu->SongLoop=Loop;
	mu->PlayMask=PlayMask;
	mu->SFXNum=SFXNum;

	mu->Status=PlayType&0x7f;
	mu->HeaderNum=XM_ID;
	mu->JBPM=0;
	mu->PCounter=3;
	mu->reppos=mhu->restart;
	mu->repcnt=0;
	mu->CurPos=0;
	mu->SongPos=0;
	if ((PlayType&0x7f)==XM_Music)
	{
		mu->SongPos=SFXNum;
		mu->CurrentStart=SFXNum;
	}
	mu->SongSpeed=mhu->tempo;
	mu->vbtick=mu->SongSpeed;
	mu->SongBPM=mhu->bpm;

	mu->NotAmiga=mhu->flags;
	mu->patdly=0;
	mu->patdly2=0;
	mu->SongVolume=128;
	mu->MasterVolume=128;
	mu->FirstCh=FirstCh;
	mu->PatternPos=0;
	mu->posjmp=1;			/* <- make sure the player fetches the first note */
	mu->patbrk=0;
	mu->PlayNext=-1;
	mu->BPlayNext=-1;
	mu->BPlayFlag=0;
	mu->UserPan=0;		/* Default Middle */
	mu->MaxChans=0;
	if (FirstCh!=-1)
	{
		Chn=FirstCh;
		for(i=0;i<mhu->XMPSXChannels;i++)
		{
			pmsk=mu->PlayMask;
			pmsk&=(1<<i);
			if (pmsk!=0)
			{
				XMCU=&mu->XM_Chnl[i];		/* Build list of SPU Channels to use */
				XMCU->SPUChannel=Chn;		/* Depending on bitmask */
				mu->MaxChans++;
				if (Chn<24)
					InitSPUChannel(Chn);
				Chn++;
			}
		}
	}
	else
	{
		for(i=0;i<mhu->XMPSXChannels;i++)
		{
			pmsk=mu->PlayMask;
			pmsk&=(1<<i);
			if (pmsk!=0)
			{
				XMCU=&mu->XM_Chnl[i];		/* Build list of SPU Channels to use */
				fr=0;
				for (t=0;t<24;t++)
				{
					if (XMSPU_SFX[t]==0)
					{
						XMSPU_SFX[t]=SngID+1;
						XMCU->SPUChannel=t;		/* Depending on bitmask */
						mu->MaxChans++;
						InitSPUChannel(t);
						fr=1;
						break;
					}
				}
				if (fr==0)
				{
					JPClearSPUFlags(SngID+1);
					XMSongIDs[SngID]=-1;
					JP_Do_Nothing=0;
					return (-2);			/* NOT ENOUGH FREE CHANNELS */
				}
			}
		}
	}

	for(i=0;i<mhu->XMChannels;i++)
	{
		mu->XM_Chnl[i].UserVol=0;
		mu->XM_Chnl[i].kick=0;
		mu->XM_Chnl[i].tmpvolume=0+64;
		mu->XM_Chnl[i].retrig=0;
		mu->XM_Chnl[i].wavecontrol=0;
		mu->XM_Chnl[i].glissando=0;
		mu->XM_Chnl[i].panning=128;
		mu->XM_Chnl[i].note=0;
		mu->XM_Chnl[i].vol=0;
		mu->XM_Chnl[i].eff=0;
		mu->XM_Chnl[i].dat=0;
		mu->XM_Chnl[i].ins=0;
		mu->XM_Chnl[i].ChDead=1;
		mu->XM_Chnl[i].nothing=1;
		mu->XM_Chnl[i].OldLVol=-1;
		mu->XM_Chnl[i].OldRVol=-1;
		mu->XM_Chnl[i].OldPeriod=0;
		mu->XM_Chnl[i].sample=254;
		mu->XM_Chnl[i].OldSample=-1;
		mu->XM_Chnl[i].Dolby=XM_DOLBY_OFF;
	}
	if (PlayType<0x80)
		mu->XMPlay=XM_PLAYING;

	JP_Do_Nothing=0;

	return(SngID);
}



/*****************************************************************************
JPlayNote
	Decode Pattern data.
	Setup note/instrument/volume/effect
	Return amount of bytes read.
*****************************************************************************/

int JPlayNote(u_char *j, int pmsk)
{
	u_char b;
	int ret = 1;
	u_char note = 0;

	b = *j;

	XMC->eff = 0;
	XMC->vol = 0;
	XMC->dat = 0;

	if (b == 0x80)
	{
		XMC->nothing = 1;
		return(ret);
	}

	j++;

	if ((b & 0x80) != 0)
	{
		if ((b & 1) != 0)
		{
			if (pmsk != 0)
			{
				XMC->nothing = 0;
				note = *(j);
				SetNote(note - 1);
			}
			j++;
			ret++;
		}

		if ((b & 2) != 0)
		{
			if (pmsk != 0)
			{
				XMC->ins = *(j);
				SetInstr(XMC->ins - 1);
			}
			j++;
			ret++;
		}
		if (((b & 3) != 0) && (note != 97) && (pmsk != 0))
			SetPer();			/* Set Pitch if new instrument/note */

		if ((b & 4) != 0)
		{
			XMC->nothing = 0;
			XMC->vol = *(j);
			j++;
			ret++;
		}

		if ((b & 8) != 0)
		{
			XMC->nothing = 0;
			XMC->eff = *(j);
			j++;
			ret++;
		}
		if ((b & 16) != 0)
		{
			XMC->dat = *(j);
			ret++;
		}

	}
	else
	{
		XMC->nothing = 0;
		note = b;

		if (pmsk != 0)
		{
			SetNote(note - 1);
			XMC->ins = *(j);
			SetInstr(XMC->ins - 1);
			if (note != 97)
				SetPer();
			XMC->vol = *(j + 1);
			XMC->eff = *(j + 2);
			XMC->dat = *(j + 3);
		}
		ret = 5;
	}
	return(ret);
}



/*****************************************************************************
JPlayEffects
	Checks if any effects to be played.
	Calls relevent routines if thay are.
*****************************************************************************/

void JPlayEffects(void)
{
u_char note=0;
u_char ins=0;
u_char vol=0;
u_char eff=0;
u_char dat=0;

	note=XMC->note;
	vol=XMC->vol;
	eff=XMC->eff;
	dat=XMC->dat;
	ins=XMC->ins;

	XMC->ownper=0;
	XMC->ownvol=0;

	switch(vol>>4)
	{
		case 0x6:
			if(vol&0xf)
				SPE(0xa,vol&0xf);				/* Volume slide down */
			break;
	
		case 0x7:
			if(vol&0xf)
				SPE(0xa,vol<<4);				/* Volume slide up */
			break;
	
		case 0x8:
			SPE (0xe,0xb0 | (vol&0xf));	/* Fine volume slide down */
			break;

		case 0x9:                     
			SPE (0xe,0xa0 | (vol&0xf));	/* Fine volume slide up */
			break;

		case 0xa:
			SPE (0x4,vol<<4);					/* Set Vibrato speed */
			break;

		case 0xb:
			SPE (0x4,vol&0xf);				/* Vibrato */
			break;

		case 0xc:
			XMC->panning=(vol&0xf)<<4;		/* Set Panning */
			break;

		case 0xd:
			if(vol&0xf)
				DoXMPanSlide(vol&0xf);		/* Pan slide left */
			break;

		case 0xe:
			if(vol&0xf)
				DoXMPanSlide(vol<<4);		/* Pan slide right */
			break;

		case 0xf:
			SPE (0x3,vol<<4);					/* Portamento */
			break;

		default:
			if(vol>=0x10 && vol<=0x50)
			{
				SPE (0xc,vol-0x10);			/* Set volume */
			}
	}
//	if (eff!=0)
//	{
		switch(eff)
			{
			case 'G'-55:                    /* G - set global volume */
				ms->SongVolume=dat*2;
				break;

			case 'H'-55:                    /* H - global volume slide */
				break;

			case 'K'-55:                    /* K - keyoff */
					SetNote(96);
				break;

			case 'L'-55:                    /* L - set envelope position */
				break;

			case 'P'-55:                    /* P - panning slide */
				XMC->panning=dat;
//				DoXMPanSlide(dat);
				break;

			case 'R'-55:                    /* R - multi retrig note */
				DoS3MRetrig(dat);
				break;

			case 'T'-55:
				SPE (0x6,dat);
				break;

			case 'X'-55:
				break;

			default:
				if(eff<=0xf)
					SPE (eff,dat);				/* Do most of the effects */
				break;
		}
//	}

	if(!XMC->ownper)
	{
		XMC->period=XMC->tmpperiod;
	}

	if(!XMC->ownvol)
	{
		XMC->volume=XMC->tmpvolume;
	}
}



/*****************************************************************************
SPE
	This is the bit that does most of the updating of effects
*****************************************************************************/

void SPE (u_char eff,u_char dat)
{
int hi;
int lo;

	switch(eff)
	{
		case XMEF_APPREGIO:		/* 0 */
			Arpeggio(dat);
			break;

		case XMEF_PORTUP:			/* 1 */
			if(dat!=0)
				XMC->slidespeed=((u_short)(dat))<<2;
			if(ms->vbtick)
			{
				XMC->tmpperiod-=XMC->slidespeed;
			}
			break;

		case XMEF_PORTDOWN:		/* 2 */
			if(dat!=0)
				XMC->slidespeed=(u_short)(dat)<<2;
			if(ms->vbtick)
			{
				XMC->tmpperiod+=XMC->slidespeed;
			}
			break;

		case XMEF_TONEPORT:		/* 3 */
			XMC->kick=0;
			if(dat!=0)
			{
				XMC->portspeed=dat;
				XMC->portspeed<<=2;
			}
			DoToneSlide();
			XMC->ownper=1;
			break;

		case XMEF_VIBRATO:		/* 4 */
			if(dat&0x0f) XMC->vibdepth=dat&0x0f;
			if(dat&0xf0) XMC->vibspd=(dat&0xf0)>>2;
			DoVibrato();
			XMC->ownper=1;
			break;

		case XMEF_PORT_VOLSLD:	/* 5 */
			XMC->kick=0;
			DoToneSlide();
			if (dat==0)
				dat=XMC->oldvslide;
			XMC->oldvslide=dat;
			DoVolSlide(dat);
			XMC->ownper=1;
			break;

		case XMEF_VIB_VOLSLD:	/* 6 */
			DoVibrato();
			if (dat==0)
				dat=XMC->oldvslide;
			XMC->oldvslide=dat;
			DoVolSlide(dat);
			XMC->ownper=1;
			break;

		case XMEF_TREMELO:		/* 7 */
			if(dat&0x0f) XMC->trmdepth=dat&0xf;
			if(dat&0xf0) XMC->trmspd=(dat&0xf0)>>2;
			DoTremolo();
			XMC->ownvol=1;
			break;

		case XMEF_PANPOS:			/* 8 */
			XMC->panning=dat;
			break;

		case XMEF_SAMPOFFSET:	/* 9 */
			if(ms->vbtick)
				break;
			if(dat==0)
				break;

			XMC->SOffset=dat;
			XMC->SOffset*=256;
			XMC->SOffset*=2;
			XMC->SOffset/=7;
			XMC->SOffset*=2;
			XMC->SOffset&=(~31);
			break;

		case XMEF_VOLSLD:			/* A */
			if (dat==0)
				dat=XMC->oldvslide;
			XMC->oldvslide=dat;
			DoVolSlide(dat);
			break;

		case XMEF_POSJMP:			/* B */
			if(ms->patdly2)
				break;
			ms->patbrk=0;
			ms->SongPos=dat-1;
			ms->posjmp=2;
			break;

		case XMEF_VOLUME:			/* C */
			if(ms->vbtick)
				break;
			if (dat==0xff)				// 0xff = set user jump flag
				ms->BPlayFlag=1;	
			else if (dat==0xfe)		// 0xfe = clear user jump flag
				ms->BPlayFlag=0;
			else if (dat==0xfd)		// 0xfd = force tune to end.
				ms->BPlayFlag=2;
			else if (dat==0xfc)
				XMC->Dolby=XM_DOLBY_OFF;
			else if (dat==0xfb)
				XMC->Dolby=XM_DOLBY_LEFT;
			else if (dat==0xfa)
				XMC->Dolby=XM_DOLBY_RIGHT;
			else
			{
				if(dat>64) dat=64;
				XMC->tmpvolume=dat+64;
			}
			break;

		case XMEF_PATBREAK:		/* D */
			if(ms->patdly2)
				break;
			hi=(dat&0xf0)>>4;
			lo=(dat&0xf);
			ms->patbrk=((hi*10)+lo)+1;

			if(ms->patbrk>(ms->numrow+1))
				ms->patbrk=ms->numrow+1;
			ms->posjmp=2;
			break;

		case XMEF_E:				/* E */
			DoEEffects(dat);
			break;

		case XMEF_SETSPEED:		/* F */
			if(ms->vbtick || ms->patdly2)
				break;
			if(dat<0x20)
			{
				ms->SongSpeed=dat;	// Speed
				ms->vbtick=0;
			}
			else
			{
				ms->SongBPM=dat;		// BPM
				ms->vbtick=0;
			}
			break;

		default:
			break;
	}
}



/*****************************************************************************
DoEEffects
	Process effects if 0xe command used.
*****************************************************************************/

void DoEEffects(u_char dat)
{
	u_char nib;

	nib = dat & 0xf;

	switch (dat >> 4)
	{
	case 0x0:							/* 0 filter toggle */
		break;

	case XMEF_E_FINESLD_UP:			/* 1 Fineslide up */
		if (!ms->vbtick)
		{
			if (nib == 0)
				nib = XMC->oldfslide;
			XMC->oldfslide = nib;
			XMC->tmpperiod += (nib << 2);
		}
		break;

	case XMEF_E_FINESLD_DOWN:		/* 2 Fineslide down */
		if (!ms->vbtick)
		{
			if (nib == 0)
				nib = XMC->oldfslide;
			XMC->oldfslide = nib;
			XMC->tmpperiod -= (nib << 2);
		}

		break;

	case XMEF_E_GLISSANDO:			/* 3 Glissando ctrl */
		XMC->glissando = nib;
		break;

	case XMEF_E_VIB_WAVE:			/* 4 Set vibrato waveform */
		XMC->wavecontrol &= 0xf0;
		XMC->wavecontrol |= nib;
		break;

	case XMEF_E_FINETUNE:			/* 5 Set finetune */
		break;

	case XMEF_E_PATLOOP:				/* 6 Set patternloop */

		if (ms->vbtick)
			break;
		if (nib)
		{
			if (ms->repcnt > 0)
				ms->repcnt--;		/* already looping, decrease counter */
			else
				ms->repcnt = nib;    /* not yet looping, so set repcnt */

			if (ms->repcnt)        /* jump to reppos if repcnt>0 */
				ms->PatternPos = ms->reppos;
		}
		else
		{
			ms->reppos = ms->PatternPos - 1;	/* set reppos */
		}
		break;

	case XMEF_E_TREM_WAVE:			/* 7 Set tremolo waveform */
		XMC->wavecontrol &= 0x0f;
		XMC->wavecontrol |= nib << 4;
		break;

	case XMEF_E_NOTUSED:				/* 8 Not used */
		XMC->panning = nib << 4;
		break;

	case XMEF_E_RETRIG:				/* 9 Retrig note */

			/* only retrigger if
			   data nibble > 0 */

		if (nib > 0)
		{
			if (XMC->retrig == 0)
			{
				XMC->kick = 1;
				XMC->retrig = nib;
			}
			XMC->retrig--; /* countdown */
		}
		break;

	case XMEF_E_FINEVOL_UP:			/* A - Fine volume slide up */
		if (ms->vbtick)
			break;

		if (nib == 0)
			nib = XMC->oldfvslide;
		XMC->oldfvslide = nib;
		XMC->tmpvolume += nib;
		if (XMC->tmpvolume > 128) XMC->tmpvolume = 128;
		break;

	case XMEF_E_FINEVOL_DOWN:		/* B - Fine volume slide down */
		if (ms->vbtick)
			break;

		if (nib == 0)
			nib = XMC->oldfvslide;
		XMC->oldfvslide = nib;
		XMC->tmpvolume -= nib;
		if (XMC->tmpvolume < 64) XMC->tmpvolume = 64;
		break;

	case XMEF_E_CUTNOTE:				/* C - Cut note */

		if (ms->vbtick >= nib)
		{
			XMC->tmpvolume = 64;
		}
		break;

	case XMEF_E_NOTEDELAY:			/* D - Note delay */

		if (ms->vbtick == nib)
		{
			XMC->kick = 1;
		}
		else XMC->kick = 0;
		break;

	case XMEF_E_PATDELAY:			/* E - Pattern delay */
		if (ms->vbtick)
			break;
		if (!ms->patdly2)
			ms->patdly = nib + 1;		/* only once (when vbtick=0) */
		break;

	case 0xf:       /* invert loop, not supported */
		break;
	}
}



/*****************************************************************************
SetNote
	Set note if a new note is to processed
*****************************************************************************/

void SetNote(u_char note)
{
	u_char* j;
	u_char vf;

	if (CurrentCh > 23)
		return;

	if (note == 96)
	{
		XMC->keyon = 0;
		if (XMC->sample == 254)
		{
			XMC->tmpvolume = 64;			/* Force 0 vol if no envelope used */
		}
		else
		{
			j = (u_char*)mh->JAP_InstrumentOffset[XMC->sample];
			vf = *((u_char*)j + 233);
			if (!(vf & EF_ON))
			{
				XMC->tmpvolume = 64;			/* Force 0 vol if no envelope used */
			}
		}
	}
	else
	{
		XMC->note = note;
		XMC->kick = 1;

		if (!(XMC->wavecontrol & 0x80))	/* retrig tremolo and vibrato waves ? */
			XMC->trmpos = 0;
		if (!(XMC->wavecontrol & 0x08))
			XMC->vibpos = 0;
	}
}



/*****************************************************************************
SetInstr
	Set instrument if new one to be processed
	Copy values from XM data (transpose, fine,volume...)
*****************************************************************************/

void SetInstr(u_char inst)
{
	u_long *j;
	u_char j2;
	short ddd;

	//	if (ms->SongPos==4)
	//	{
	//		inst+=0;
	//	}

	if (CurrentCh > 23)
		return;

	if (!XMC->kick)
		return;							// Instrument but no note...

	if (inst == 255)
	{
		inst = XMC->sample;				// If instrument=0, use last instrument.
	}

	if (inst >= mh->numins) return;             // No Instrument available

	XMC->sample = inst;

	/*
		j=mh->JAP_InstrumentOffset[inst];
		j2=*((u_char*)j+(XMC->note+33));
		j3=*((u_char*)j);

		if (j2!=0)
		{
			ddd=243*j2;			// Not using instrument 0
		}
	//	if (j2>=j3)
	//		return;
	*/

	j = mh->JAP_SampHdrAddr[inst];
	if (j == (u_long*)0x01234567)
		return;

	j2 = *((u_char*)j + 12);
	XMC->tmpvolume = j2 + 64;
	XMC->volume = j2 + 64;
	XMC->vol = j2 + 0x10;
	XMC->retrig = 0;

	if (mh->S3MPanning == XM_UseXMPanning)
		XMC->panning = *((u_char*)j + 15);

	XMC->transpose = *((u_char*)j + 16);
	ddd = (*((u_char*)j + 13));
	ddd += 128;
	XMC->c2spd = ddd;
	XMC->c2spd &= 255;

}


/*****************************************************************************
SetPer
	Init insturment envelopes, period...
	Called if either SetInst or SetNote are called
*****************************************************************************/

void SetPer(void)
{
	u_long *j;
	u_short period;
	u_char a;
	if (CurrentCh > 23)
		return;

	a = XMC->note;
	a += XMC->transpose;


	//	a+=jtt;

	period = GetPeriod(a, XMC->c2spd);
	//if (XMC->sample==5)
	//FntPrint("%d,%d,%d=%d\n",XMC->note,XMC->transpose,a,period);

	XMC->wantedperiod = period;
	XMC->tmpperiod = period;
	XMC->OldPeriod = 0;
	XMC->SOffset = 0;
	//	XMC->OldLVol=-1;
	//	XMC->OldRVol=-1;

	if (XMC->OldSample != XMC->sample)
	{
		XMC->OldSample = XMC->sample;
		j = mh->JAP_InstrumentOffset[XMC->sample];

		XMC->keyoffspd = *((u_char*)j + 239);
		XMC->keyoffspd;	//*=1;	//4;
		XMC->envflg = *((u_char*)j + 233);
		if (XMC->envflg & EF_ON)
		{
			XMC->envpts = *((u_char*)j + 225);
			XMC->envsus = *((u_char*)j + 227);
			XMC->envbeg = *((u_char*)j + 228);
			XMC->envend = *((u_char*)j + 229);
		}
		XMC->panenvflg = *((u_char*)j + 234);
		if (XMC->panenvflg & EF_ON)
		{
			XMC->panenvpts = *((u_char*)j + 226);
			XMC->panenvsus = *((u_char*)j + 230);
			XMC->panenvbeg = *((u_char*)j + 231);
			XMC->panenvend = *((u_char*)j + 232);
		}
	}
	if (XMC->panenvflg & EF_ON)
	{
		XMC->panenvp = 0;
		XMC->panenva = 0;
		XMC->panenvb = 1;
	}
	if (XMC->envflg & EF_ON)
	{
		XMC->envp = 0;
		XMC->enva = 0;
		XMC->envb = 1;
	}
}



/*****************************************************************************
Arpeggio
	EFFECT - Modify pitch
*****************************************************************************/

void Arpeggio(u_char dat)
{
	u_char note;

	note = XMC->note;

	if (dat != 0)
	{
		switch (ms->vbtick % 3)
		{
		case 1:
			note += (dat >> 4);
			break;
		case 2:
			note += (dat & 0xf);
			break;
		}
		XMC->period = GetPeriod(note + XMC->transpose, XMC->c2spd);
		XMC->ownper = 1;
	}
}



/*****************************************************************************
DoVolSlide
	EFFECT - Either +/- 0-0xf to volume
*****************************************************************************/

void DoVolSlide(u_char dat)
{
	if (!ms->vbtick) return;				 /* do not update when vbtick==0 */

	XMC->tmpvolume += dat >> 4;           /* volume slide */
	if (XMC->tmpvolume > 128) XMC->tmpvolume = 128;
	XMC->tmpvolume -= dat & 0xf;
	if (XMC->tmpvolume < 64) XMC->tmpvolume = 64;
}



/*****************************************************************************
DoXMPanSlide
	EFFECT - Pan slide
*****************************************************************************/

void DoXMPanSlide(u_char inf)
{
	u_char lo, hi;
	short pan;

	if (inf != 0) XMC->pansspd = inf;
	else inf = XMC->pansspd;

	if (!ms->vbtick) return;

	lo = inf & 0xf;
	hi = inf >> 4;

	/* slide right has absolute priority: */

	if (hi)
		lo = 0;

	pan = XMC->panning;

	pan -= lo;
	pan += hi;

	if (pan < 0) pan = 0;
	if (pan > 255) pan = 255;

	XMC->panning = pan;
}



/*****************************************************************************
DoS3MRetrig
	EFFECT - Pan slide
*****************************************************************************/

void DoS3MRetrig(u_char inf)
{
	u_char hi,lo;

	hi=inf>>4;
	lo=inf&0xf;

	if(lo)
	{
		XMC->s3mrtgslide=hi;
		XMC->s3mrtgspeed=lo;
	}

	if(hi)
	{
		XMC->s3mrtgslide=hi;
	}

	/* only retrigger if lo nibble > 0 */

	if(XMC->s3mrtgspeed>0)
	{
		if(XMC->retrig==0)
		{

			/* when retrig counter reaches 0,
			   reset counter and restart the sample */

			XMC->kick=1;
			XMC->retrig=XMC->s3mrtgspeed;

			if(ms->vbtick)
			{                     /* don't slide on first retrig */
				switch(XMC->s3mrtgslide)
				{

					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
						XMC->tmpvolume-=(1<<(XMC->s3mrtgslide-1));
						break;

					case 6:
						XMC->tmpvolume=(2*XMC->tmpvolume)/3;
						break;

					case 7:
						XMC->tmpvolume=XMC->tmpvolume>>1;
						if (XMC->tmpvolume<64)
							XMC->tmpvolume=64;
						break;

					case 9:
					case 0xa:
					case 0xb:
					case 0xc:
					case 0xd:
						XMC->tmpvolume+=(1<<(XMC->s3mrtgslide-9));
						break;

					case 0xe:
						XMC->tmpvolume=(3*XMC->tmpvolume)/2;
						break;

					case 0xf:
						XMC->tmpvolume=XMC->tmpvolume<<1;
						break;
				}
				if(XMC->tmpvolume<64) XMC->tmpvolume=64;
				if(XMC->tmpvolume>128) XMC->tmpvolume=128;
			}
		}
		XMC->retrig--; /* countdown */
	}
}



/*****************************************************************************
DoToneSlide
	EFFECT
*****************************************************************************/

void DoToneSlide(void)
{
int dist;

	/* We have to slide XMC->period towards XMC->wantedperiod, so
	   compute the difference between those two values */

	dist=XMC->period-XMC->wantedperiod;

	if(dist==0 || XMC->portspeed>abs(dist))/* if they are equal */
	{											      /* or if portamentospeed is too big */

		XMC->period=XMC->wantedperiod;      /* make tmpperiod equal tperiod */
	}
	else if(dist>0)
	{		                                 /* dist>0 ? */
		XMC->period-=XMC->portspeed;        /* then slide up */
	}
	else
		XMC->period+=XMC->portspeed;        /* dist<0 -> slide down */

	XMC->tmpperiod=XMC->period;				/* Store new period */
}



/*****************************************************************************
DoVibrato
	EFFECT
*****************************************************************************/

void DoVibrato(void)
{
u_char q;
u_short temp=0;

	q=(XMC->vibpos>>2)&0x1f;

	switch(XMC->wavecontrol&3)
	{

		case 0: /* sine */
			temp=VibratoTable[q];
			break;

		case 1: /* ramp down */
			q<<=3;
			if(XMC->vibpos>127)
				q=255-q;
			temp=q;
			break;

		case 2: /* square wave */
			temp=255;
			break;
	}

	temp*=XMC->vibdepth;
	temp>>=7;
	temp<<=2;

	if(XMC->vibpos<128)
		XMC->period=XMC->tmpperiod+temp;
	else
		XMC->period=XMC->tmpperiod-temp;

	if(ms->vbtick) XMC->vibpos+=XMC->vibspd;        /* do not update when vbtick==0 */
}



/*****************************************************************************
DoTremelo
	EFFECT
*****************************************************************************/

void DoTremolo(void)
{
	u_char q;
	u_short temp = 0;

	q = (XMC->trmpos >> 2) & 0x1f;

	switch ((XMC->wavecontrol >> 4) & 3)
	{

	case 0: /* sine */
		temp = VibratoTable[q];
		break;

	case 1: /* ramp down */
		q <<= 3;
		if (XMC->trmpos > 127) q = 255 - q;
		temp = q;
		break;

	case 2: /* square wave */
		temp = 255;
		break;
	}

	temp *= XMC->trmdepth;
	temp >>= 6;

	if (XMC->trmpos < 128)
	{
		XMC->volume = XMC->tmpvolume + temp;
		if (XMC->volume > 128) XMC->volume = 128;
	}
	else
	{
		XMC->volume = XMC->tmpvolume - temp;
		if (XMC->volume < 64) XMC->volume = 64;
	}

	if (ms->vbtick) XMC->trmpos += XMC->trmspd;        /* do not update when vbtick==0 */
}



/*****************************************************************************
DoPan
	Calculate panning using current envelope panning and instrument pan
*****************************************************************************/

short DoPan(short envpan,short pan)
{
	return(pan + (((envpan-128)*(128-abs(pan-128)))/128));
}



/*****************************************************************************
DoVol
	Calculate volume using

	a Fade volume
	b Envelope volume
	c Instrument volume
*****************************************************************************/

short DoVol(u_long a,short b,short c)
{
	a*=b;
	a*=c;
	a>>=23;
	return(a);
}



/*****************************************************************************
UpdateXMData
	This does everything
*****************************************************************************/

void UpdateXMData(void)
{
	int SC;

	if(JP_Do_Nothing)			/* Failsafe switch - if called on interrupt */
		return;

	for (SC=0;SC<XM_NSA;SC++)
	{
		ms=(XMSONG*)(XM_SngAddress[SC]);
//		ms=&XM_Song[SC];
		UpdateWithTimer(SC);
		if (ms->PCounter==5)
		{
			UpdateWithTimer(SC);
			ms->PCounter=0;
		}
	}
}



int tt=0;
int aa=0;
void UpdateWithTimer(int SC)
{
	aa++;

	ms=(XMSONG*)(XM_SngAddress[SC]);
	if (ms->XMPlay!=XM_PLAYING)
		return;

 	if (PALType==1)
 		ms->PCounter++;		/* PAL Mode stuff...bodge timer */

	mh=(XMHEADER*)(XM_HeaderAddress[ms->HeaderNum]);

	ms->JBPM+=ms->SongBPM;


	if (ms->JBPM<BPMLimit)	/* Time to process data ? */
	{
		if ((ms->JUp==0)&&(PALType!=0))
		{
			ms->JUp=1;
			UpdateEffs();		/* If nothing else to do for a frame */
			ApplyEffs();		/* (spread out processing time */
			UpdateHardware();			/* Update SPU */
		}
		return;
	}
	ms->JBPM-=BPMLimit;		/* YES! Update song/hardware */
	XM_DoFullUpdate(SC);
}



void XM_DoFullUpdate(int SC)
{
	ms = (XMSONG*)(XM_SngAddress[SC]);
	//	ms=&XM_Song[SC];
	if (ms->XMPlay == XM_PLAYING)
	{
		//		mh=&XM_Header[ms->HeaderNum];
		mh = (XMHEADER*)(XM_HeaderAddress[ms->HeaderNum]);

		if (ms->JUp == 0)
		{
			//		UpdatePatternData(SC);
			UpdateEffs();			/* Do this if not done before in spare frame*/
			ApplyEffs();
		}
		ms->JUp = 0;					/* Clear update flag */

		UpdateHardware();			/* Update SPU */
		if (ms->vbtick == 1)		/* Check for zero volume,keyed off channels*/
			CurrentKeyStat();		/* BUT not on first tick - wait for keyons */

/****
	Update song at the end - so it doesn't have to process so much in
	a frame. This does mean that what you are hearing the notes processed
	a frame ago. But saves on processing time due to not keying on/initialising
	channels AND processing song data AND processing effects at once.
****/

		UpdatePatternData(SC);
	}
	//		UpdateHardware();			/* Update SPU */
}



void UpdatePatternData(int SC)
{
	int SP, t, pmsk;
	int FindOffset;
	u_char *pataddr;
	u_char patdat;

	if (++ms->vbtick >= ms->SongSpeed)
	{
		ms->PatternPos++;		/* Time to read more pattern data */
		ms->vbtick = 0;

		if (ms->patdly)
		{
			ms->patdly2 = ms->patdly;
			ms->patdly = 0;
		}

		if (ms->patdly2)
		{
			/* patterndelay active */
			if (--ms->patdly2)
			{
				ms->PatternPos--;    /* so turn back PatternPos by 1 */
			}
		}

		/*
		Do we have to get a new patternpointer ?
		(when PatternPos reaches, say 64 or when a patternbreak is active)
		*/

		FindOffset = 0;

		if (ms->PatternPos == ms->numrow)
			ms->posjmp = 2;


		if (ms->BPlayFlag == 2)
		{
			XM_Quit(SC);
			return;
		}

		if (ms->posjmp)
		{
			if ((ms->posjmp == 2) && (ms->Status == XM_SFX))	/* SFX ? */
			{

				//	t=ms->posjmp;
				//	t=ms->patbrk;
				//				ms->posjmp--;
				if (ms->patbrk == 0)
				{
					XM_Quit(SC);
					return;
				}
			}

			if (ms->patbrk != 0)
				ms->PatternPos = ms->patbrk - 1;
			else
				ms->PatternPos = 0;

			ms->CurPos = ms->PatternPos;
			if (ms->CurPos != 0)
				FindOffset = 1;

			//			if (ms->BPlayFlag==2)
			//			{
			//				XM_Quit(SC);
			//				return;
			//			}

			if ((ms->BPlayNext != -1) && (ms->BPlayFlag != 0))
			{
				ms->BPlayFlag = 0;
				ms->SongPos = ms->BPlayNext;
				ms->CurrentStart = ms->SongPos;
				ms->BPlayNext = -1;
			}

			else if (ms->PlayNext != -1)
			{
				ms->SongPos = ms->PlayNext;
				ms->CurrentStart = ms->SongPos;
				ms->PlayNext = -1;
			}
			else			// if (ms->Status==XM_Music)
			{
				ms->SongPos += (ms->posjmp - 1);
				t = ms->SongPos;
			}

			ms->patbrk = ms->posjmp = 0;
			if (ms->SongPos >= mh->songlength)		/* End of song data ? */
			{
				if (!ms->SongLoop)
				{
					ms->XMPlay = XM_STOPPED;			/* Once off tune */
					return;
				}
				ms->SongPos = ms->reppos;				/* Loop to loop point */
			}
			if (ms->SongPos < 0)
				ms->SongPos = mh->songlength - 1;
			if (ms->Status == XM_Music)
				SP = mh->jorders[ms->SongPos];		/* Pattern from song data*/
			else
				SP = ms->SFXNum;							/* Pattern from user SFX */

//		SP+=0;
			ms->CurrentPattern = SP;
			ms->PatAdr = mh->JAP_PAT_ADDR[SP];		/* Addr of pat header */
			ms->PatAdr2 = mh->JAP_PAT_ADDR2[SP];	/* Addr of pat data */
			ms->numrow = getWord((u_char*)ms->PatAdr + 5);	/* Number of rows */
			ms->PatSize = getWord((u_char*)ms->PatAdr + 7);	/* pattern size */
		}
		if (!ms->patdly2)
		{
			if (ms->PatSize > 0)
			{
				if (mh->version == 0xddba)				/*** SUPER COMPRESSED ***/
				{
					if (FindOffset != 0)
						ms->CurPos = PACKEDCalcPlayPos(ms->CurPos);
					SP = ms->CurPos;
					for (t = 0; t < mh->XMPSXChannels; t++)
					{
						XMC = &ms->XM_Chnl[t];		/* Decode pattern data */
						XMC->eff = 0;
						XMC->vol = 0;
						XMC->dat = 0;
						//						XMC->nothing=1;
					}

					while (1)
					{

						pataddr = ((u_char*)ms->PatAdr2 + SP);
						patdat = *pataddr++;				/* Channel or 0xff for end */
						SP++;
						if (patdat == 0xff)
							break;

						CurrentCh = patdat;
						XMC = &ms->XM_Chnl[patdat];		/* Decode pattern data */
						pmsk = ms->PlayMask;
						pmsk &= (1 << patdat);
						SP += JPlayNote((u_char*)ms->PatAdr2 + SP, pmsk);
					}
					ms->CurPos = SP;

				}
				else
				{


					if (FindOffset != 0)					/**** ORIGNAL XM FILE ****/
						ms->CurPos = CalcPlayPos(ms->CurPos);
					SP = ms->CurPos;
					for (t = 0; t < mh->XMChannels; t++)
					{
						CurrentCh = t;
						XMC = &ms->XM_Chnl[t];				/* Decode pattern data */
						pmsk = ms->PlayMask;
						pmsk &= (1 << t);
						SP += JPlayNote((u_char*)ms->PatAdr2 + SP, pmsk);
					}
					ms->CurPos = SP;
				}
			}
		}
	}
}



int CalcPlayPos(int StartPos)
{
	int SP = 0;
	int t, i;

	for (i = 0; i < StartPos; i++)
	{
		for (t = 0; t < mh->XMChannels; t++)
		{
			CurrentCh = t;
			XMC = &ms->XM_Chnl[t];				/* Decode pattern data */
			SP += JCalcPat((u_char*)ms->PatAdr2 + SP);
		}
	}
	return(SP);
}



int PACKEDCalcPlayPos(int StartPos)
{
	int SP = 0;
	int i;
	u_char *pataddr;
	u_char patdat;

	for (i = 0; i < StartPos; i++)
	{
		while (1)
		{
			pataddr = ((u_char*)ms->PatAdr2 + SP);
			patdat = *pataddr++;				/* Channel or 0xff for end */
			SP++;
			if (patdat == 0xff)
				break;

			CurrentCh = patdat;
			XMC = &ms->XM_Chnl[patdat];		/* Decode pattern data */
			SP += JCalcPat((u_char*)ms->PatAdr2 + SP);
		}
	}
	return(SP);
}



int JCalcPat(u_char *j)
{
	u_char b;
	int ret = 1;

	b = *j;

	if (b == 0x80)
		return(ret);
	j++;

	if ((b & 0x80) != 0)
	{
		if ((b & 1) != 0)
		{
			j++;
			ret++;
		}

		if ((b & 2) != 0)
		{
			j++;
			ret++;
		}

		if ((b & 4) != 0)
		{
			j++;
			ret++;
		}

		if ((b & 8) != 0)
		{
			j++;
			ret++;
		}
		if ((b & 16) != 0)
		{
			ret++;
		}
	}
	else
		ret = 5;
	return(ret);
}



/*****************************************************************************
ApplyEffs
	Process envelope/panning.
	Kill silent, keyed off channels.
*****************************************************************************/

void ApplyEffs(void)
{
	short envpan,envvol;
	int t;
	int pmsk;
	short vlm;
	short Pn;
	u_char MaxChans;

 	ms->XMActiveVoices=0;
	MaxChans=ms->MaxChans;
 	for(t=0;t<mh->XMPSXChannels;t++)
 	{
		if (MaxChans==0)
			return;

 		pmsk=ms->PlayMask;
 		pmsk&=(1<<t);
 		if (pmsk!=0)
 		{
			MaxChans--;
 			XMC=&ms->XM_Chnl[t];

 			if(XMC->kick)							/* New note keyed on ? */
 			{
 				XMC->keyon=1;
 				XMC->fadevol=32767;
 				XMC->ChDead=0;
 			}
 			if (!XMC->ChDead)						/* Update envelope/pitch/vol */
 			{											/* If channel not dead */
 				ms->XMActiveVoices++;

				if(XMC->period<1)					/* Cap period */
					XMC->period=1;
				else if(XMC->period>32768)
					XMC->period=32768;

				if(XMC->envflg & EF_ON)
					envvol=ProcessEnvelope(256,XMC->keyon,XMC->sample);
				else
					envvol=256;
				if(XMC->panenvflg & EF_ON)
					envpan=ProcessPanEnvelope(128,XMC->keyon,XMC->sample);
				else
					envpan=128;

//				vlm=XMC->volume-XMC->UserVol;
				vlm=((XMC->volume-64)*(64-XMC->UserVol))/64;
				vlm+=64;
				if (vlm<=64)
				{
					XMC->LVol=XMC->RVol=0;
				}
				else
				{
					vlm=((DoVol(XMC->fadevol,envvol,vlm-64)*ms->SongVolume)/128);
					vlm*=ms->MasterVolume;
					vlm/=128;

					Pn=XMC->panning;
					Pn+=ms->UserPan;
					if (Pn<0)
						Pn=0;
					else if (Pn>255)
						Pn=255;
					Pn=DoPan(envpan,Pn);

					XMC->LVol=(vlm*(255-Pn));	// /128;
					XMC->RVol=(vlm*Pn);			// /128;
				}

				if ((!XMC->LVol)&&(!XMC->RVol)&&(!XMC->keyon))
				{ 
					StpCh(XMC->SPUChannel);
					XMC->ChDead=1;			/* Released & 0vol - so kill channel */
				} 
				else if(!XMC->keyon)		/* Key off? - do release on envelope */
				{
					XMC->fadevol-=XMC->keyoffspd;
					if(XMC->fadevol<0)
						 XMC->fadevol=0;
				}
			}
		}
	}
}



/*****************************************************************************
UpdateEffs
		Play any effects if required
*****************************************************************************/

void UpdateEffs(void)
{
	int t;
	int pmsk;
	u_char MaxChans;

	MaxChans = ms->MaxChans;
	for (t = 0; t < mh->XMPSXChannels; t++)
	{
		if (MaxChans == 0)
			return;

		XMC = &ms->XM_Chnl[t];
		pmsk = ms->PlayMask;
		pmsk &= (1 << t);
		if (pmsk != 0)
		{
			MaxChans--;
			if (!XMC->nothing)			/* Any note/vol/eff's to process? */
			{
				JPlayEffects();
			}
		}
	}
}



#define JPPIT 2682522


int DVL;
int DVR;

void DoDolbySS(void)
{
	if (MonoMode==XM_MONO)
	{
		DVL=(XMC->OldLVol+XMC->OldRVol)/2;
		DVR=DVL;
		return;
	}

	if (XMC->Dolby==XM_DOLBY_LEFT)
	{
		DVL=XMC->OldLVol;
		if (XMC->OldRVol>XMC->OldLVol)
		{
			DVR=-XMC->OldRVol;
			DVL=XMC->OldRVol;
		}
		else
			DVR=-XMC->OldRVol;
	}
	else if (XMC->Dolby==XM_DOLBY_RIGHT)
	{
		DVR=XMC->OldLVol;
		if (XMC->OldRVol>XMC->OldLVol)
		{
			DVL=-XMC->OldRVol;
			DVR=XMC->OldRVol;
		}
		else
			DVL=-XMC->OldRVol;
	}
	else
	{
		DVL=XMC->OldLVol;
		DVR=XMC->OldRVol;
	}

}

int dd = 0;
int de = 0;

// [D]
int GetEmpty(int old)
{
	unsigned char bVar1;
	XMCHANNEL *j;
	int iVar3;
	int i;

	de++;

	if (mh->XMPSXChannels <= de) 
		de = 0;

	dd = de;

	for (i = 0; i < mh->XMPSXChannels; i++)
	{
		j = ms->XM_Chnl + dd;
		dd++;

		if (mh->XMPSXChannels <= dd)
			dd = 0;

		if (j->kick == 0 && j->ChDead == 1)
		{
			bVar1 = j->SPUChannel;
			j->SPUChannel = old;
			return bVar1;
		}
	}
	return -1;
}

/*****************************************************************************
UpdateHardware
		Update SPU if needed
*****************************************************************************/

// [D] [A] Half-source, half-decomp
void UpdateHardware(void) 
{
	int t;
	int prd;
	int SPUKeyOn = 0;
	int pmsk;
	int Chnl; 
	int Ch2;
	u_char MaxChans;

	MaxChans=ms->MaxChans;
	for(t=0;t<mh->XMPSXChannels;t++)
	{
		if (MaxChans==0)
			break;

		pmsk=ms->PlayMask;
		pmsk&=(1<<t);
		if (pmsk!=0)
		{
			MaxChans--;
			XMC=&ms->XM_Chnl[t];
			if(XMC->kick)
			{
				Chnl = XMC->SPUChannel;

				SpuSetKey(0, 1 << XMC->SPUChannel);

				Ch2 = GetEmpty(XMC->SPUChannel);

				if (Ch2 != -1)
					Chnl = Ch2;
					
				XMC->SPUChannel = Chnl;

				prd=XMC->period; 
				if (ms->NotAmiga==0)
					prd=((JPPIT<<2)/prd)>>3;		/* Using AMIGA freq table */
				else
					prd=GetFreq2(prd);				/* Using LINEAR freq table */

				XMC->OldLVol=XMC->LVol; 
				XMC->OldRVol=XMC->RVol; 
				DoDolbySS(); 
				SPUKeyOn|=(1<< Chnl);
				XMC->SPUPitch=prd; 
				XMC->OldPeriod=XMC->period; 

				PlaySFX(ms->VabID,Chnl,XMC->sample,prd,DVL,DVR);
			} 
		} 
	} 
	if (SPUKeyOn!=0) 
	{
		//XMTime1 = 1;
		SpuSetKey(1, SPUKeyOn);
		SpuFlush(SPU_EVENT_ALL);
		aa = 0;
	} 

	MaxChans=ms->MaxChans;
	for(t=0;t<mh->XMPSXChannels;t++)
	{
		if (MaxChans==0)
			return;
		pmsk=ms->PlayMask;
		pmsk&=(1<<t);
		if (pmsk!=0)
		{
			MaxChans--;
			XMC=&ms->XM_Chnl[t];
			if (!XMC->ChDead) 
			{ 
				Ch2=XMC->SPUChannel;

				if (XMC->kick==0)
				{
					if ((XMC->LVol!=XMC->OldLVol)||(XMC->RVol!=XMC->OldRVol))
					{
						if (XMC->OldLVol!=XMC->LVol)
								XMC->OldLVol=IntVols(XMC->LVol,XMC->OldLVol);

//						if (XMC->LVol==XMC->RVol)
//							XMC->OldRVol=XMC->OldLVol;	/* Mono sound */
//						else
//						{
							if (XMC->OldRVol!=XMC->RVol)
								XMC->OldRVol=IntVols(XMC->RVol,XMC->OldRVol);
//						}
						DoDolbySS();

//						SetVol(Ch2,XMC->OldLVol,XMC->OldRVol);	/* Update volumes */
						SetVol(Ch2,DVL,DVR);		/* Update volumes */
					}
					if (XMC->period!=XMC->OldPeriod) 
					{ 
						XMC->OldPeriod=XMC->period;
						prd=XMC->period; 
						if(ms->NotAmiga==0)
							prd=((JPPIT<<2)/prd)>>3;	/* Using AMIGA freq table */
						else 
							prd=GetFreq2(prd); 
						XMC->SPUPitch=prd; 
						SetFrq(Ch2,prd);							/* Update periods */
					} 
				}
				else
					XMC->kick=0;
			}
		}
	}
}



/*****************************************************************************
IntVols
	Calculates point between Current volume and Required volume.
	Requires:
				Vol1		LVol
				Vol2		OldLVol
	Returns:
				value half way between two points.
*****************************************************************************/

int IntVols(int Vol1, int Vol2)
{
	int a;
	a = abs(Vol2 - Vol1);
	a >>= 2;
	a += 1;

	if (Vol1 < Vol2)
		return(Vol1 + a);
	else
		return(Vol2 + a);
}



/*****************************************************************************
GetFreq2
	Returns SPU pitch.
	Calculated from linear value
*****************************************************************************/

#define joc 8
//int JPPer = 6578;	//6578  D1 has this value and game were shipped with broken soundtrack

int JPPer = 7350;	//6578

long GetFreq2(long period)
{
	int okt;
	long frequency;

	//FntPrint("period %d\n",period);
	period = JPPer - period;
	okt = period / 768;
	//FntPrint("octave %d\n",okt);
	frequency = lintab[period % 768];
	//FntPrint("freq %d\n",frequency);

	//if (XMC->sample==5)
	//printf("aa %d aa\n",frequency>>(joc-okt));

	return(frequency >> (joc - okt));		/* Final SPU pitch */
}



/*****************************************************************************
ProcessEnvelope
	Updates amplitude envelope
*****************************************************************************/

short ProcessEnvelope(short v,u_char keyon,int JSmp)
{

u_char a2,b;
u_short p;

u_long* j;
short apos;
short aval;
short bpos;
short bval;

	a2=XMC->enva;
	b=XMC->envb;
	p=XMC->envp;

	/* compute the envelope value between points a and b */

	j=mh->JAP_InstrumentOffset[JSmp];
	aval=(getSWord((u_char*)j+129+2+(a2*4)))<<2;
	bval=(getSWord((u_char*)j+129+2+(b*4)))<<2;
	apos=getSWord((u_char*)j+129+(a2*4));
	bpos=getSWord((u_char*)j+129+(b*4));

	v=Interpolate(p,apos,bpos,aval,bval);

		/* Should we sustain? (sustain flag on, key-on, point a is the sustain
		   point, and the pointer is exactly on point a) */

	if((XMC->envflg & EF_SUSTAIN) && keyon && a2==XMC->envsus && p==apos)
	{
		/* do nothing */
	}
	else
	{
		p++;							/* don't sustain, so increase pointer. */
		if(p >= bpos)				/* pointer reached point b? */
		{
			a2=b; b++;				/* shift points a and b */
			if(XMC->envflg & EF_LOOP)
			{
				if(b > XMC->envend)
				{
					a2=XMC->envbeg;
					b=a2+1;
					p=getSWord((u_char*)j+129+(a2*4));
				}
			}
			else
			{
				if(b >= XMC->envpts)
				{
					b--;
					p--;
				}
			}
		}
	}
	XMC->enva=a2;
	XMC->envb=b;
	XMC->envp=p;

	return v;
}



/*****************************************************************************
ProcessPanEnvelope
	Updates panning envelope
*****************************************************************************/

short ProcessPanEnvelope(short v, u_char keyon, int JSmp)
{

	u_char a2, b;
	u_short p;

	u_long* j;
	short apos;
	short aval;
	short bpos;
	short bval;


	a2 = XMC->panenva;
	b = XMC->panenvb;
	p = XMC->panenvp;

	/* compute the panenvelope value between points a and b */

	j = mh->JAP_InstrumentOffset[JSmp];
	aval = (getSWord((u_char*)j + 177 + 2 + (a2 * 4))) << 2;
	bval = (getSWord((u_char*)j + 177 + 2 + (b * 4))) << 2;
	apos = getSWord((u_char*)j + 177 + (a2 * 4));
	bpos = getSWord((u_char*)j + 177 + (b * 4));

	v = Interpolate(p, apos, bpos, aval, bval);

	/* Should we sustain? (sustain flag on, key-on, point a is the sustain
	   point, and the pointer is exactly on point a) */

	if ((XMC->panenvflg & EF_SUSTAIN) && keyon && a2 == XMC->panenvsus && p == apos)
	{
		/* do nothing */
	}
	else
	{
		p++;							/* don't sustain, so increase pointer. */

		if (p >= bpos)				/* pointer reached point b? */
		{
			a2 = b; b++;				/* shift points a and b */
			if (XMC->panenvflg & EF_LOOP)
			{
				if (b > XMC->panenvend)
				{
					a2 = XMC->panenvbeg;
					b = a2 + 1;
					p = getSWord((u_char*)j + 177 + (a2 * 4));
				}
			}
			else
			{
				if (b >= XMC->panenvpts)
				{
					b--;
					p--;
				}
			}
		}
	}
	XMC->panenva = a2;
	XMC->panenvb = b;
	XMC->panenvp = p;
	return v;
}



/*****************************************************************************
XM_SetSongPos
	User Call. Set song position to requested value.
*****************************************************************************/

void XM_SetSongPos(int Song_ID,u_short pos)
{
int t;
	if (XMSongIDs[Song_ID]==-1)
		return;

	mu=(XMSONG*)(XM_SngAddress[Song_ID]);
//	mu=&XM_Song[Song_ID];
//	mhu=&XM_Header[mu->HeaderNum];
	mhu=(XMHEADER*)(XM_HeaderAddress[mu->HeaderNum]);

	if (pos>=mhu->songlength)
		return;

	JP_Do_Nothing=1;	/* Incase user using interrupt to call player */

	for(t=0;t<mhu->XMChannels;t++)
	{
		XMCU=&mu->XM_Chnl[t];
		XMCU->keyon=0;
		XMCU->tmpvolume=64;
		XMCU->kick=1;			// [A] temporary fix
	}

	mu->posjmp=1;
	mu->patbrk=0;
	mu->SongPos=pos;
	mu->vbtick=mu->SongSpeed;
//	mu->JBPM=0;
	JP_Do_Nothing=0;
}


/*****************************************************************************
PlaySFX
	Requires:
				Channel 0-23	Channel to play SFX on
				Voice 0-?		SFX number to play
				Note	0-127		Note number
				Fine  0-127		Fine tune number
				VolL	0-127		Left vol
				VolR	0-127		Right vol

(To be added)
				Reverb 0-1		1=Use reverb
****************************************************************************/
void PlaySFX(int VBID,int Channel,int Inst,int Pitch,int LV,int RV)
{
	int a;

	/* Mask which specific voice attributes are to be set */
	xm_g_s_attr.mask = (SPU_VOICE_VOLL |
						SPU_VOICE_VOLR | 
						SPU_VOICE_PITCH |
						SPU_VOICE_WDSA |
						SPU_VOICE_LSAX);

	xm_g_s_attr.voice = SPU_VOICECH(Channel);	//(1<<Channel);
	xm_g_s_attr.volume.left  = LV; 
	xm_g_s_attr.volume.right = RV; 
	xm_g_s_attr.pitch        = Pitch; 
	a=xm_l_vag_spu_addr[VBID][Inst]; 
	a=xm_l_vag_spu_addr[VBID][Inst]+XMC->SOffset; 

	xm_g_s_attr.addr         = xm_l_vag_spu_addr[VBID][Inst]+XMC->SOffset; 
	xm_g_s_attr.loop_addr    = xm_l_vag_spu_addr[VBID][Inst]+XMC->SOffset; 
	SpuSetVoiceAttr(&xm_g_s_attr); 
}



/*****************************************************************************
InitSPUChannel
	Sets up ADSR for selected channel
	Called only when Init_XM
*****************************************************************************/

void InitSPUChannel(int Channel)
{ 
	xm_g_s_attr.mask =
			(SPU_VOICE_WDSA |
			SPU_VOICE_ADSR_AMODE |
			SPU_VOICE_ADSR_SMODE |
			SPU_VOICE_ADSR_RMODE |
			SPU_VOICE_ADSR_AR |
			SPU_VOICE_ADSR_DR |
			SPU_VOICE_ADSR_SR |
			SPU_VOICE_ADSR_RR |
			SPU_VOICE_ADSR_SL
			);

	xm_g_s_attr.voice = SPU_VOICECH(Channel);	//(1<<Channel);
	xm_g_s_attr.a_mode       = SPU_VOICE_LINEARIncN;
	xm_g_s_attr.s_mode       = SPU_VOICE_LINEARIncN;
	xm_g_s_attr.r_mode       = SPU_VOICE_LINEARDecN;
	xm_g_s_attr.ar           = 0x4;
	xm_g_s_attr.dr           = 0x0;
	xm_g_s_attr.sr           = 0x0;
	xm_g_s_attr.rr           = 0x1;
	xm_g_s_attr.sl           = 0xf;	//0xf;
	SpuSetVoiceAttr(&xm_g_s_attr);
}


/*****************************************************************************
CurrentKeyStat
	Stops processing of any dead channels
*****************************************************************************/

// [D]
void CurrentKeyStat(void)
{
	int t;
	char KeyStat[24];

	SpuGetAllKeysStatus(KeyStat);

	for (t = 0; t < mh->XMPSXChannels; t++)
	{
		XMC = &ms->XM_Chnl[t];

		if (KeyStat[XMC->SPUChannel] != 1 && XMC->ChDead == 0)
		{
			XMC->ChDead = 1;
			XMC->nothing = 1;
		}
	}
}



/*****************************************************************************
StpCh
	Turns off channel
*****************************************************************************/

void StpCh(int Channel)
{
	SpuSetVoiceVolume(Channel, 0, 0);
}

/*****************************************************************************
SetVol
	Sets volume for channel
*****************************************************************************/

void SetVol(int Channel, int LVol, int RVol)
{
	SpuSetVoiceVolume(Channel, LVol, RVol);
}

/*****************************************************************************
SetFrq
	Sets frequency for channel
*****************************************************************************/

void SetFrq(int Channel, int Pitch)
{
	SpuSetVoicePitch(Channel, Pitch);
}



/*****************************************************************************
SilenceXM
	Silence any channel used for Song_ID
*****************************************************************************/

void SilenceXM(int Song_ID)
{
	int t, i, c;

	int pmsk;


	mu = (XMSONG*)(XM_SngAddress[Song_ID]);
	//	mu=&XM_Song[Song_ID]; 
	//	mhu=&XM_Header[mu->HeaderNum]; 
	mhu = (XMHEADER*)(XM_HeaderAddress[mu->HeaderNum]);
	i = 0;
	for (t = 0; t < mhu->XMPSXChannels; t++)
	{
		pmsk = mu->PlayMask;
		pmsk &= (1 << t);
		if (pmsk != 0)
		{
			XMC = &mu->XM_Chnl[t];
			c = XMC->SPUChannel;

			i |= (1 << c);
			SetVol(c, 0, 0);
		}
	}

	SpuSetKey(0, i);
}


/*****************************************************************************
XM_Pause
	User Call. Pauses Song_ID
	(by setting pitch to 0 - not by keying off..)
*****************************************************************************/

void XM_Pause(int Song_ID)
{
	int t;
	if (XMSongIDs[Song_ID] == -1)
		return;

	mu = (XMSONG*)(XM_SngAddress[Song_ID]);
	//	mu=&XM_Song[Song_ID]; 
	//	mhu=&XM_Header[mu->HeaderNum]; 
	mhu = (XMHEADER*)(XM_HeaderAddress[mu->HeaderNum]);
	if (mu->XMPlay == XM_PLAYING)
	{
		mu->XMPlay = XM_PAUSED;
		for (t = 0; t < mhu->XMPSXChannels; t++)
		{
			XMCU = &mu->XM_Chnl[t];
			SetFrq(XMCU->SPUChannel, 0);
		}
	}
}




/*****************************************************************************
XM_Restart
	User Call. Restarts Song_ID
	(returns the channels pitch to the original value)
*****************************************************************************/

void XM_Restart(int Song_ID)
{
	int t;

	if (XMSongIDs[Song_ID] == -1)
		return;

	mu = (XMSONG*)(XM_SngAddress[Song_ID]);
	//	mu=&XM_Song[Song_ID];
	//	mhu=&XM_Header[mu->HeaderNum];
	mhu = (XMHEADER*)(XM_HeaderAddress[mu->HeaderNum]);
	if (mu->XMPlay == XM_PAUSED)
	{
		mu->XMPlay = XM_PLAYING;
		for (t = 0; t < mhu->XMPSXChannels; t++)
		{
			XMCU = &mu->XM_Chnl[t];
			if (!XMCU->ChDead)
			{
				SetFrq(XMCU->SPUChannel, XMCU->SPUPitch);
			}
		}
	}
}


/*****************************************************************************
XM_SetMasterVol
	User Call. Set Master Volume from 0-128;

	Requires:
				Song ID
				Volume;
*****************************************************************************/
void XM_SetMasterVol(int Song_ID, u_char Vol)
{
	if (XMSongIDs[Song_ID] == -1)
		return;
	if (Vol <= 128)
	{
		mu = (XMSONG*)(XM_SngAddress[Song_ID]);
		//		mu=&XM_Song[Song_ID];
		//		mu->SongVolume=Vol;
		mu->MasterVolume = Vol;
	}
}


/*****************************************************************************
ClearSPU
	Free up malloc'ed blocks. Call between exiting game/loading menus fx etc.
	(same sort of thing as closevab).
****************************************************************************/
void ClearSPU(int VBID)
{
int i;
int Amount;

	Amount=iVABID[VBID];

	for (i=0;i<(Amount);i++)
	{
		if(xm_l_vag_spu_addr[VBID][i]!=0)
		{
			XM_FreeVAG(xm_l_vag_spu_addr[VBID][i]);
			xm_l_vag_spu_addr[VBID][i]=0;
		}
	}
}


/*****************************************************************************
XM_FreeVAG
	UserCall. Free up SPU RAM (deallocate VAG).
	Use if the XM_SendVAGToSRAM has been used.
****************************************************************************/

void XM_FreeVAG(int addr)
{
	SpuFree(addr);
}


int GetFreeSongID(void)
{
	int i;
	for (i = 0; i < XM_NSA; i++)
	{
		if (XMSongIDs[i] == -1)
		{
			XMSongIDs[i] = 0;
			return i;
		}
	}
	return(-1);
}



void XM_Quit(int SongID)
{
	XM_PlayStop(SongID);
	XMSongIDs[SongID]=-1;
	JPClearSPUFlags(SongID+1);
}



void JPClearSPUFlags(int SongID)
{
	int i;

	for (i = 0; i < 24; i++)
	{
		if (XMSPU_SFX[i] == SongID)
			XMSPU_SFX[i] = 0;
	}
}



int XM_GetFreeVAB(void)
{
int i;

	for (i=0;i<8;i++)
	{
		if (iVABID[i]==-1)
			return(i);			/* Free VAB slot */
	}
	return(-1);					/* No Free VAB slots */
}



void XM_SetVAGAddress(int VabID, int slot, int addr)
{
	xm_l_vag_spu_addr[VabID][slot] = addr;
	iVABID[VabID] = slot + 1;
}



int XM_GetSongSize(void)
{
	return(sizeof(XMSONG));
}


void XM_SetSongAddress(u_char *Address)
{
	XM_SngAddress[XM_NSA] = Address;
	mu = ((XMSONG*)(Address));
	mu->Status = 0;				/* Turn off song */
	mu->XMPlay = XM_STOPPED;
	XM_NSA++;
}

void XM_FreeAllSongIDs(void)
{
	XM_NSA = 0;
}



int XM_GetFileHeaderSize(void)
{
	return(sizeof(XMHEADER));
}



void XM_SetFileHeaderAddress(u_char *Address)
{
	if (XM_HA<8)
	{
	 	XM_HeaderAddress[XM_HA]=Address;
		XM_HA++;
	}
}





