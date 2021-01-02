#ifndef XMCALLS
#define XMCALLS

#define XM_UseXMPanning 0	/* S3M Panning switches */
#define XM_UseS3MPanning 1
#define XM_Loop 1				/* Looping song */
#define XM_NoLoop 0			/* Once off song */
#define XM_STOPPED 0			/* Song/SFX Status */
#define XM_PLAYING 1
#define XM_PAUSED  2
#define XM_NO_SONG_ALLOCATED 3
#define XM_NOT_INIT 4

// IOP COMMANDS (for talking between EE<>IOP via SIFDMA)

#define XMI_GetVABID 0
#define XMI_SetTransAddress 1
#define XMI_CreateTransBuff 2
#define XMI_SetSampleOffsets 3
#define XMI_AllocXMBuffer 4
#define XMI_AllocXMSong 5
#define XMI_FreeXMPatternRAM 6
#define XMI_INIT_SPU 7
#define XMI_AllocXMPatternRAM 8
#define XMI_InitXMData 9
#define XMI_PlayXM 10
#define XMI_XMInit 11
#define XMI_TransferSample 12
#define XMI_FreeTransBuff 13
#define XMI_Pause 14
#define XMI_PauseAll 15
#define XMI_Resume 16
#define XMI_ResumeAll 17
#define XMI_FreeXMBuffer 18
#define XMI_XMExit 19
#define XMI_XMQuit 20
#define XMI_CloseSampleBank 21
#define XMI_SetSongPos 22
#define XMI_SetChannelVolume 23
#define XMI_FreeXMSong 24
#define XMI_SetMasterVolume 25
#define XMI_SetMasterPan 26
#define XMI_GetSongFeedback 27
#define XMI_SetBPM 28
#define XMI_SetStereo 29
#define XMI_SetSpeed 30
#define XMI_SetMono 31
#define XMI_PlaySample 32
#define XMI_StopSample 33

#endif