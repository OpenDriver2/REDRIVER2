
/*
 * Offset 0xF3644
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 99)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ card_start__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, address 0xf3644
} // line 39, address 0xf3828
/*
 * Offset 0xF3828
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 383)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
unsigned int /*$ra*/ CardRemoved__6MCSLOT(struct MCSLOT *this /*$s6*/)
{ // line 1, address 0xf3828
	int card_status; // $v0
	{ // line 1, address 0xf3828
		struct MCSLOT *this; // $s6
		int timeout; // $s0
		{ // line 1, address 0xf3828
			{ // line 1, address 0xf387c
				{ // line 1, address 0xf387c
				} // line 1, address 0xf3890
				{ // line 1, address 0xf3890
				} // line 1, address 0xf38a4
				{ // line 1, address 0xf38a4
				} // line 1, address 0xf38b8
				{ // line 1, address 0xf38b8
				} // line 1, address 0xf38cc
			} // line 1, address 0xf38cc
		} // line 1, address 0xf38d4
	} // line 1, address 0xf38d4
	{ // line 11, address 0xf38d4
		{ // line 11, address 0xf38e4
			{ // line 11, address 0xf38e4
				struct MCSLOT *this; // $s6
				{ // line 11, address 0xf38e4
				} // line 11, address 0xf38e4
			} // line 11, address 0xf38e4
		} // line 24, address 0xf3924
	} // line 24, address 0xf3924
	{ // line 24, address 0xf3924
		struct MCSLOT *this; // $s6
		{ // line 24, address 0xf3924
		} // line 24, address 0xf3924
	} // line 24, address 0xf3924
} // line 24, address 0xf3994
/*
 * Offset 0xF3994
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 418)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
unsigned int /*$ra*/ CardInserted__6MCSLOT(struct MCSLOT *this /*$s6*/)
{ // line 1, address 0xf3994
	int card_status; // $v1
	{ // line 1, address 0xf3994
		struct MCSLOT *this; // $s6
		int timeout; // $s0
		{ // line 1, address 0xf3994
			{ // line 1, address 0xf39e8
				{ // line 1, address 0xf39e8
				} // line 1, address 0xf39fc
				{ // line 1, address 0xf39fc
				} // line 1, address 0xf3a10
				{ // line 1, address 0xf3a10
				} // line 1, address 0xf3a24
				{ // line 1, address 0xf3a24
				} // line 1, address 0xf3a38
			} // line 1, address 0xf3a38
		} // line 1, address 0xf3a40
	} // line 1, address 0xf3a40
	{ // line 11, address 0xf3a40
		{ // line 12, address 0xf3a54
			{ // line 1, address 0xf3a54
				struct MCSLOT *this; // $s6
				{ // line 1, address 0xf3a54
				} // line 1, address 0xf3a54
			} // line 1, address 0xf3a54
		} // line 19, address 0xf3aa8
	} // line 19, address 0xf3aa8
	{ // line 1, address 0xf3aa8
		struct MCSLOT *this; // $s6
		{ // line 1, address 0xf3aa8
		} // line 1, address 0xf3aa8
	} // line 1, address 0xf3aa8
} // line 24, address 0xf3b04
/*
 * Offset 0xF3B04
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 489)
 * Stack frame base $sp, length 176
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ FormatCard__6MCSLOT(struct MCSLOT *this /*$s2*/)
{ // line 1, address 0xf3b04
	char buffer[128]; // stack address -160
	{ // line 1, address 0xf3b04
		struct MCSLOT *this; // $s2
		{ // line 1, address 0xf3b04
		} // line 1, address 0xf3b04
	} // line 1, address 0xf3b04
	{ // line 1, address 0xf3b04
		{ // line 1, address 0xf3b04
			struct MCSLOT *this; // $s2
			int timeout; // $s3
			{ // line 1, address 0xf3b04
				{ // line 1, address 0xf3bb4
					{ // line 1, address 0xf3bb4
					} // line 1, address 0xf3bc8
					{ // line 1, address 0xf3bc8
					} // line 1, address 0xf3bdc
					{ // line 1, address 0xf3bdc
					} // line 1, address 0xf3bf0
					{ // line 1, address 0xf3bf0
					} // line 1, address 0xf3c04
				} // line 1, address 0xf3c04
			} // line 1, address 0xf3c0c
		} // line 1, address 0xf3c0c
	} // line 15, address 0xf3c28
} // line 20, address 0xf3c74
/*
 * Offset 0xF3C74
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 520)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ ReadCardDir__6MCSLOT(struct MCSLOT *this /*$s3*/)
{ // line 1, address 0xf3c74
	long length; // $a1
	char path[7]; // stack address -48
	struct DIRENTRY *entryPtr; // $s0
	{ // line 17, address 0xf3cf4
	} // line 40, address 0xf3d6c
} // line 49, address 0xf3d8c
/*
 * Offset 0xF3DB8
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 618)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ ReadCardInfo__6MCSLOTPc(struct MCSLOT *this /*$s1*/, char *managerFilename /*$s0*/)
{ // line 1, address 0xf3db8
	int i; // $a2
	int n; // $s0
	char filename[32]; // stack address -64
	int filePtr; // $s2
	{ // line 11, address 0xf3df4
		{ // line 12, address 0xf3e0c
			{ // line 13, address 0xf3e0c
				{ // line 14, address 0xf3e38
					{ // line 16, address 0xf3e38
						{ // line 21, address 0xf3e70
						} // line 24, address 0xf3eb0
					} // line 26, address 0xf3eb0
					{ // line 30, address 0xf3eb0
						{ // line 31, address 0xf3ed4
							{ // line 32, address 0xf3ed4
								{ // line 35, address 0xf3f4c
									{ // line 37, address 0xf3f4c
									} // line 37, address 0xf3f88
								} // line 54, address 0xf4060
							} // line 55, address 0xf4094
						} // line 57, address 0xf4094
					} // line 61, address 0xf40e4
				} // line 68, address 0xf4130
			} // line 68, address 0xf4130
		} // line 73, address 0xf4130
	} // line 79, address 0xf4168
} // line 82, address 0xf41a0
/*
 * Offset 0xF41A0
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 912)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ ReadSlice__6MCSLOTiiP5SLICEP10FILEFORMAT(struct MCSLOT *this /*$t0*/, int block /*$a1*/, int slice /*$a2*/, struct SLICE *slicePtr /*$a3*/, struct FILEFORMAT *fileFormatPtr /*stack 16*/)
{ // line 1, address 0xf41a0
} // line 28, address 0xf43a0
/*
 * Offset 0xF43A0
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 950)
 * Stack frame base $sp, length 216
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ read_block__6MCSLOTiPcR9BLOCKINFO(struct MCSLOT *this /*$s1*/, int block /*$a1*/, char *bufferPtr /*$fp*/, struct BLOCKINFO *blockInfo /*$s7*/)
{ // line 1, address 0xf43a0
	int n; // $s5
	char verifyBuffer[128]; // stack address -200
	char filename[32]; // stack address -72
	long bytesRead; // $v0
	unsigned int verifyFailed; // $v0
	int retry; // $s0
	{ // line 1, address 0xf43a0
		{ // line 12, address 0xf43e4
		} // line 39, address 0xf44a0
	} // line 39, address 0xf44a0
	{ // line 44, address 0xf44a0
		{ // line 45, address 0xf44b8
			{ // line 48, address 0xf44b8
				{ // line 48, address 0xf44c0
					{ // line 50, address 0xf44c0
						{ // line 55, address 0xf44ec
							{ // line 58, address 0xf44f4
								{ // line 61, address 0xf44f4
									{ // line 62, address 0xf44f4
										{ // line 67, address 0xf4524
										} // line 67, address 0xf4524
									} // line 67, address 0xf4524
								} // line 67, address 0xf4524
								{ // line 85, address 0xf4530
									{ // line 86, address 0xf4530
										{ // line 91, address 0xf455c
										} // line 91, address 0xf455c
									} // line 91, address 0xf455c
								} // line 91, address 0xf455c
								{ // line 106, address 0xf4564
									{ // line 109, address 0xf4584
									} // line 109, address 0xf4584
								} // line 109, address 0xf4584
							} // line 109, address 0xf4584
						} // line 121, address 0xf458c
					} // line 121, address 0xf458c
				} // line 126, address 0xf458c
			} // line 127, address 0xf45b4
		} // line 130, address 0xf45dc
		{ // line 132, address 0xf45dc
			{ // line 134, address 0xf45dc
				{ // line 142, address 0xf4608
					{ // line 143, address 0xf4608
						int check; // $a1
					} // line 146, address 0xf4640
				} // line 158, address 0xf4678
			} // line 158, address 0xf4678
		} // line 167, address 0xf46b4
	} // line 167, address 0xf46b4
} // line 167, address 0xf46b4
/*
 * Offset 0xF46B4
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1261)
 * Stack frame base $sp, length 216
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ write_block__6MCSLOTR9BLOCKINFOPc(struct MCSLOT *this /*$s1*/, struct BLOCKINFO *blockInfo /*$s7*/, char *bufferPtr /*$fp*/)
{ // line 1, address 0xf46b4
	int n; // $s5
	char verifyBuffer[128]; // stack address -200
	char filename[32]; // stack address -72
	int filePtr; // $v0
	long bytes; // $v0
	unsigned int verifyFailed; // $v0
	int retry; // $s0
	{ // line 1, address 0xf46b4
		{ // line 12, address 0xf46f8
		} // line 47, address 0xf478c
	} // line 47, address 0xf478c
	{ // line 51, address 0xf478c
		{ // line 54, address 0xf47c0
			{ // line 56, address 0xf47c0
				{ // line 56, address 0xf47cc
					{ // line 58, address 0xf47cc
						{ // line 64, address 0xf4814
							{ // line 66, address 0xf481c
								{ // line 69, address 0xf481c
									{ // line 71, address 0xf481c
										{ // line 76, address 0xf484c
										} // line 76, address 0xf484c
									} // line 76, address 0xf484c
								} // line 76, address 0xf484c
								{ // line 94, address 0xf4858
									{ // line 95, address 0xf4858
										{ // line 100, address 0xf4884
										} // line 100, address 0xf4884
									} // line 100, address 0xf4884
								} // line 100, address 0xf4884
								{ // line 117, address 0xf488c
									{ // line 120, address 0xf48ac
									} // line 120, address 0xf48ac
								} // line 120, address 0xf48ac
							} // line 120, address 0xf48ac
						} // line 134, address 0xf48b4
					} // line 134, address 0xf48b4
				} // line 139, address 0xf48b4
			} // line 140, address 0xf48dc
		} // line 143, address 0xf4924
		{ // line 145, address 0xf4924
			{ // line 148, address 0xf4924
				struct MCSLOT *this; // $s1
				{ // line 148, address 0xf4924
					{ // line 148, address 0xf4924
						int n; // $a1
					} // line 150, address 0xf496c
					{ // line 1, address 0xf496c
						{ // line 1, address 0xf497c
						} // line 1, address 0xf498c
					} // line 1, address 0xf498c
					{ // line 1, address 0xf498c
						{ // line 1, address 0xf499c
						} // line 1, address 0xf49ac
					} // line 1, address 0xf49ac
				} // line 1, address 0xf49ac
			} // line 1, address 0xf49ac
		} // line 204, address 0xf49e8
	} // line 204, address 0xf49e8
} // line 204, address 0xf49e8
/*
 * Offset 0xF49E8
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1473)
 * Stack frame base $sp, length 704
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CreateBlock__6MCSLOTP10FILEFORMATP5SLICE(struct MCSLOT *this /*$s5*/, struct FILEFORMAT *fileFormatPtr /*$s4*/, struct SLICE *slicePtr /*stack 8*/)
{ // line 1, address 0xf49e8
	int i; // $a1
	int n; // $s0
	struct _CARD header; // stack address -680
	char filename[32]; // stack address -168
	int filePtr; // $s1
	int bytes; // $s3
	int blockNum; // $fp
	char charBuffer[64]; // stack address -136
	struct SLICEHEADER emptySlice; // stack address -72
	char *charPtr; // $a2
	{ // line 94, address 0xf4d98
		{ // line 97, address 0xf4db0
		} // line 104, address 0xf4ddc
	} // line 107, address 0xf4ddc
	{ // line 111, address 0xf4ddc
		{ // line 112, address 0xf4df0
			{ // line 113, address 0xf4df0
				{ // line 121, address 0xf4e28
				} // line 141, address 0xf4f28
			} // line 142, address 0xf4f4c
		} // line 147, address 0xf4f74
	} // line 147, address 0xf4f74
	{ // line 152, address 0xf4f74
		struct MCSLOT *this; // $s5
		{ // line 152, address 0xf4f74
			{ // line 152, address 0xf4f74
				int n; // $a1
			} // line 152, address 0xf4fb8
			{ // line 1, address 0xf4fb8
				{ // line 1, address 0xf4fc8
				} // line 1, address 0xf4fd8
			} // line 1, address 0xf4fd8
			{ // line 1, address 0xf4fd8
				{ // line 1, address 0xf4fe8
				} // line 1, address 0xf4ff8
			} // line 1, address 0xf4ff8
		} // line 1, address 0xf4ff8
	} // line 1, address 0xf4ff8
} // line 157, address 0xf502c
/*
 * Offset 0xF502C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1640)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ DeleteBlock__6MCSLOTi(struct MCSLOT *this /*$s1*/, int block /*$a1*/)
{ // line 1, address 0xf502c
	char filename[32]; // stack address -48
	{ // line 1, address 0xf502c
		{ // line 7, address 0xf506c
			{ // line 9, address 0xf506c
				struct MCSLOT *this; // $s1
				{ // line 9, address 0xf506c
					{ // line 9, address 0xf506c
						int n; // $a1
					} // line 11, address 0xf50cc
					{ // line 1, address 0xf50cc
						{ // line 1, address 0xf50dc
						} // line 1, address 0xf50ec
					} // line 1, address 0xf50ec
					{ // line 1, address 0xf50ec
						{ // line 1, address 0xf50fc
						} // line 1, address 0xf510c
					} // line 1, address 0xf510c
				} // line 1, address 0xf510c
			} // line 1, address 0xf510c
		} // line 26, address 0xf5114
	} // line 28, address 0xf512c
} // line 28, address 0xf512c
/*
 * Offset 0xF512C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2067)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ Ascii2ShiftJis__FPsPc(short *dest /*$a0*/, char *source /*$a1*/)
{ // line 1, address 0xf512c
	char a; // $a2
	short scode; // $v1
} // line 49, address 0xf523c
/*
 * Offset 0xF523C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 58)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
struct MCSLOT * /*$ra*/ __6MCSLOTiiiiiiPc(struct MCSLOT *this /*$s0*/, int port /*$a1*/, int card /*$a2*/, int iconX /*$a3*/, int iconY /*stack 16*/, int clutX /*stack 20*/, int clutY /*stack 24*/, char *bufferPtr /*stack 28*/)
{ // line 1, address 0xf523c
} // line 29, address 0xf52d8
/*
 * Offset 0xF52F0
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 159)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ MCSLOT_ctor(struct MCSLOT *this /*$s0*/, int __in_chrg /*$s1*/)
{ // line 1, address 0xf52f0
} // line 11, address 0xf5324
/*
 * Offset 0xF534C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 193)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ card_stop__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, address 0xf534c
} // line 25, address 0xf5474
/*
 * Offset 0xF5474
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 235)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ CheckCard__6MCSLOT(struct MCSLOT *this /*$s0*/)
{ // line 1, address 0xf5474
	int card_status; // $v1
	{ // line 1, address 0xf5474
		{ // line 13, address 0xf54c0
		} // line 64, address 0xf555c
	} // line 64, address 0xf555c
} // line 64, address 0xf555c
/*
 * Offset 0xF555C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 311)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ card_event__6MCSLOTi(struct MCSLOT *this /*$a0*/, int timeout /*$s0*/)
{ // line 1, address 0xf555c
	{ // line 5, address 0xf5584
		{ // line 7, address 0xf5584
		} // line 7, address 0xf55a4
		{ // line 9, address 0xf55a4
		} // line 9, address 0xf55c0
		{ // line 11, address 0xf55c0
		} // line 11, address 0xf55d4
		{ // line 13, address 0xf55d4
		} // line 13, address 0xf55f0
	} // line 13, address 0xf55f0
} // line 16, address 0xf5610
/*
 * Offset 0xF5610
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 332)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ clear_event__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, address 0xf5610
} // line 5, address 0xf5668
/*
 * Offset 0xF5668
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 579)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ invalidate_info__6MCSLOT(struct MCSLOT *this /*$s0*/)
{ // line 1, address 0xf5668
	{ // line 1, address 0xf5668
		int n; // $v1
	} // line 11, address 0xf56a8
	{ // line 14, address 0xf56a8
		{ // line 15, address 0xf56b8
		} // line 17, address 0xf56c8
	} // line 17, address 0xf56c8
	{ // line 20, address 0xf56c8
		{ // line 21, address 0xf56d8
		} // line 23, address 0xf56e8
	} // line 23, address 0xf56e8
} // line 23, address 0xf56e8
/*
 * Offset 0xF56FC
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 712)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ download_icon__6MCSLOTR9BLOCKINFOiiiii(struct MCSLOT *this /*$a0*/, struct BLOCKINFO *blockInfo /*$s2*/, int iconX /*$s3*/, int iconY /*$s4*/, int clutX /*stack 16*/, int clutY /*stack 20*/, int icon /*stack 24*/)
{ // line 1, address 0xf56fc
	struct RECT rect; // stack address -32
	struct TIMSTRUCT *timPtr; // $s0
	{ // line 1, address 0xf56fc
		int n; // $a0
	} // line 22, address 0xf5790
} // line 42, address 0xf5860
/*
 * Offset 0xF5860
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 764)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ CopyBlock__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
{ // line 1, address 0xf5860
} // line 15, address 0xf5918
/*
 * Offset 0xF5918
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1130)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ PasteBlock__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, address 0xf5918
} // line 7, address 0xf5968
/*
 * Offset 0xF5968
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1146)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ ReadHeader__6MCSLOTii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/)
{ // line 1, address 0xf5968
} // line 18, address 0xf5a60
/*
 * Offset 0xF5A60
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1173)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ RenameCopyBlock__6MCSLOTP10FILEFORMAT(struct MCSLOT *this /*$a0*/, struct FILEFORMAT *fileFormatPtr /*$s1*/)
{ // line 1, address 0xf5a60
	struct _CARD *headerptr; // $s0
} // line 6, address 0xf5b24
/*
 * Offset 0xF5B38
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1187)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ WriteSlice__6MCSLOTiiP5SLICEP10FILEFORMATPc(struct MCSLOT *this /*$s0*/, int block /*$s4*/, int slice /*$s1*/, struct SLICE *slicePtr /*$a2*/, struct FILEFORMAT *fileFormatPtr /*stack 16*/, char *bufferPtr /*stack 20*/)
{ // line 1, address 0xf5b38
} // line 62, address 0xf5c70
/*
 * Offset 0xF5C70
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1675)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ SetPort__6MCSLOTii(struct MCSLOT *this /*$s0*/, int port /*$a1*/, int card /*$a2*/)
{ // line 1, address 0xf5c70
	{ // line 1, address 0xf5c70
		struct MCSLOT *this; // $s0
		{ // line 1, address 0xf5c70
			{ // line 1, address 0xf5c70
				int n; // $v1
			} // line 7, address 0xf5cdc
			{ // line 1, address 0xf5cdc
				{ // line 1, address 0xf5cec
				} // line 1, address 0xf5cfc
			} // line 1, address 0xf5cfc
			{ // line 1, address 0xf5cfc
				{ // line 1, address 0xf5d0c
				} // line 1, address 0xf5d1c
			} // line 1, address 0xf5d1c
		} // line 1, address 0xf5d1c
	} // line 1, address 0xf5d30
} // line 9, address 0xf5d30
/*
 * Offset 0xF5D30
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1710)
 * Stack frame base $sp, length 0
 */
unsigned int /*$ra*/ BlocksShared__6MCSLOTii(struct MCSLOT *this /*$t0*/, int block1 /*$a1*/, int block2 /*$a2*/)
{ // line 1, address 0xf5d30
} // line 9, address 0xf5dc0
/*
 * Offset 0xF5DC8
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1723)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetBlockSize__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
{ // line 1, address 0xf5dc8
} // line 4, address 0xf5dfc
/*
 * Offset 0xF5DFC
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1731)
 * Stack frame base $sp, length 0
 */
unsigned int /*$ra*/ CardInfoRead__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, address 0xf5dfc
} // line 2, address 0xf5e08
/*
 * Offset 0xF5E08
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1755)
 * Stack frame base $sp, length 0
 */
struct TIMSTRUCT * /*$ra*/ GetBlockIconPtr__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
{ // line 1, address 0xf5e08
} // line 8, address 0xf5e84
/*
 * Offset 0xF5E84
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1788)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetNoUsedBlocks__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, address 0xf5e84
} // line 6, address 0xf5ea0
/*
 * Offset 0xF5EA0
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1806)
 * Stack frame base $sp, length 0
 */
short * /*$ra*/ GetBlockTitlePtr__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
{ // line 1, address 0xf5ea0
} // line 7, address 0xf5ee4
/*
 * Offset 0xF5EE4
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1822)
 * Stack frame base $sp, length 0
 */
char * /*$ra*/ GetBlockFilenamePtr__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
{ // line 1, address 0xf5ee4
} // line 8, address 0xf5f1c
/*
 * Offset 0xF5F1C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1836)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ FilenameUsed__6MCSLOTPc(struct MCSLOT *this /*$s3*/, char *filename /*$s4*/)
{ // line 1, address 0xf5f1c
	int n; // $s0
} // line 15, address 0xf5fbc
/*
 * Offset 0xF5FBC
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1872)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ GetNumGremBlocks__6MCSLOTPc(struct MCSLOT *this /*$s3*/, char *filename /*$s5*/)
{ // line 1, address 0xf5fbc
	int n; // $s2
	int files; // $s4
	{ // line 7, address 0xf5ffc
		{ // line 7, address 0xf6014
			{ // line 9, address 0xf6014
			} // line 12, address 0xf6048
		} // line 12, address 0xf6048
	} // line 14, address 0xf6060
} // line 16, address 0xf6088
/*
 * Offset 0xF6088
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1896)
 * Stack frame base $sp, length 88
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ InsertSliceIntoCopyBuffer__6MCSLOTiPccccT2(struct MCSLOT *this /*$a0*/, int slice /*$s4*/, char *sliceName /*$a2*/, char icon0 /*$s7*/, int icon1 /*stack 16*/, int icon2 /*stack 20*/, char *dataPtr /*stack 24*/)
{ // line 1, address 0xf6088
	struct SLICEHEADER *sliceHeaderPtr; // $s1
	char *sliceDataPtr; // $a3
	int sliceSize; // $a2
	struct SLICEHEADER dummySlice; // stack address -72
	int check; // $a1
} // line 55, address 0xf61f0
/*
 * Offset 0xF61F0
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1955)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ ExtractSliceFromCopyBuffer__6MCSLOTiPc(struct MCSLOT *this /*$a0*/, int slice /*$a1*/, char *bufferPtr /*$a0*/)
{ // line 1, address 0xf61f0
	struct SLICEHEADER *sliceHeaderPtr; // $a2
	char *sliceDataPtr; // $a1
} // line 23, address 0xf628c
/*
 * Offset 0xF628C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1982)
 * Stack frame base $sp, length 0
 */
char * /*$ra*/ GetSliceFilenamePtr__6MCSLOTii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/)
{ // line 1, address 0xf628c
} // line 15, address 0xf633c
/*
 * Offset 0xF633C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2001)
 * Stack frame base $sp, length 0
 */
unsigned int /*$ra*/ SliceUsed__6MCSLOTii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/)
{ // line 1, address 0xf633c
} // line 15, address 0xf63e4
/*
 * Offset 0xF63EC
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2019)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetNoUsedSlices__6MCSLOTi(struct MCSLOT *this /*$a2*/, int block /*$a1*/)
{ // line 1, address 0xf63ec
} // line 8, address 0xf6448
/*
 * Offset 0xF6448
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2030)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetSliceIconRef__6MCSLOTiii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/, int ref /*$a3*/)
{ // line 1, address 0xf6448
} // line 11, address 0xf64f4
/*
 * Offset 0xF64F4
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2044)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetNoSlices__6MCSLOTi(struct MCSLOT *this /*$a2*/, int block /*$a1*/)
{ // line 1, address 0xf64f4
} // line 8, address 0xf6550
/*
 * Offset 0xF6550
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2055)
 * Stack frame base $sp, length 0
 */
unsigned int /*$ra*/ GremlinBlock__6MCSLOTi(struct MCSLOT *this /*$a2*/, int block /*$a1*/)
{ // line 1, address 0xf6550
} // line 4, address 0xf6588