
/*
 * Offset 0xF65A8
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 49)
 * Stack frame base $sp, length 152
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
struct DISPMAN * /*$ra*/ __7DISPMANPlPPlP3PADP10FILEFORMATib(struct DISPMAN *this /*$s2*/, long *imagePtr /*$a1*/, long **sliceIconPtrs /*stack 8*/, struct PAD *pad /*$a3*/, struct FILEFORMAT *fileFormatPtr /*stack 16*/, int language /*stack 20*/, unsigned int save /*stack 24*/)
{ // line 1, address 0xf65a8
	int n; // $s1
	struct RECT rect; // stack address -112
} // line 340, address 0xf727c
/*
 * Offset 0xF72B8
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 472)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawTitleBar__7DISPMAN(struct DISPMAN *this /*$s3*/)
{ // line 1, address 0xf72b8
	char *titleText; // $s2
	{ // line 1, address 0xf72b8
		{ // line 6, address 0xf72e4
			{ // line 56, address 0xf740c
				{ // line 58, address 0xf742c
					char *titleText2; // $s0
					int i; // $t0
				} // line 72, address 0xf7454
			} // line 76, address 0xf74e8
		} // line 79, address 0xf74ec
	} // line 79, address 0xf74ec
} // line 79, address 0xf74ec
/*
 * Offset 0xF7508
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 555)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ DrawCards__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, address 0xf7508
} // line 35, address 0xf7670
/*
 * Offset 0xF7688
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 602)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawMenu__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, address 0xf7688
} // line 92, address 0xf79ac
/*
 * Offset 0xF79C8
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 701)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawKeyInfo__7DISPMAN(struct DISPMAN *this /*$s3*/)
{ // line 1, address 0xf79c8
} // line 41, address 0xf7c30
/*
 * Offset 0xF7C4C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 747)
 * Stack frame base $sp, length 96
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawBlocks__7DISPMAN(struct DISPMAN *this /*$s1*/)
{ // line 1, address 0xf7c4c
	int x; // $s6
	int y; // $s2
} // line 87, address 0xf816c
/*
 * Offset 0xF819C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 839)
 * Stack frame base $sp, length 144
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawSlices__7DISPMAN(struct DISPMAN *this /*$s2*/)
{ // line 1, address 0xf819c
	int n; // $s3
	char textBuffer[50]; // stack address -104
	int iconRef; // $v1
	int maxIcons; // $s1
	{ // line 29, address 0xf82bc
		{ // line 30, address 0xf82cc
			{ // line 31, address 0xf82cc
				{ // line 35, address 0xf8304
					{ // line 38, address 0xf8304
						{ // line 48, address 0xf83bc
							{ // line 48, address 0xf83bc
								{ // line 57, address 0xf8404
									{ // line 57, address 0xf8404
										{ // line 57, address 0xf841c
											{ // line 59, address 0xf841c
												{ // line 59, address 0xf8460
													{ // line 61, address 0xf8460
														{ // line 63, address 0xf847c
															{ // line 64, address 0xf847c
																{ // line 65, address 0xf8484
																	{ // line 66, address 0xf8484
																		{ // line 67, address 0xf84a8
																		} // line 68, address 0xf84a8
																	} // line 80, address 0xf8574
																} // line 80, address 0xf8574
															} // line 116, address 0xf8770
														} // line 116, address 0xf8770
													} // line 116, address 0xf8770
												} // line 116, address 0xf8770
											} // line 122, address 0xf8784
										} // line 122, address 0xf8784
									} // line 122, address 0xf8784
								} // line 122, address 0xf8784
							} // line 122, address 0xf8784
						} // line 122, address 0xf8784
					} // line 122, address 0xf8784
				} // line 122, address 0xf8784
			} // line 122, address 0xf8784
		} // line 136, address 0xf87d4
	} // line 183, address 0xf8ae8
} // line 189, address 0xf8b28
/*
 * Offset 0xF8B28
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1031)
 * Stack frame base $sp, length 88
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ write_mess_in_box__7DISPMANG4RECTPciiii(struct DISPMAN *this /*$s5*/, struct RECT box /*stack 4*/, char *text /*$fp*/, int font /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, address 0xf8b28
	int n; // $s1
	int textY; // $s2
	int messCount; // $s6
	int lineCount; // $s0
} // line 25, address 0xf8d24
/*
 * Offset 0xF8D24
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1060)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DrawBlockName__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, address 0xf8d24
} // line 40, address 0xf8ed4
/*
 * Offset 0xF8EE4
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1327)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ ActiveAreaLeft__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, address 0xf8ee4
	int start; // $s1
} // line 43, address 0xf9018
/*
 * Offset 0xF902C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1375)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ ActiveAreaRight__7DISPMAN(struct DISPMAN *this /*$s1*/)
{ // line 1, address 0xf902c
	int start; // $s2
} // line 57, address 0xf9258
/*
 * Offset 0xF9270
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1437)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ActiveAreaUp__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, address 0xf9270
} // line 51, address 0xf940c
/*
 * Offset 0xF941C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1493)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ ActiveAreaDown__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, address 0xf941c
	int start; // $s1
} // line 71, address 0xf96dc
/*
 * Offset 0xF96F0
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1568)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ ActiveAreaSelect__7DISPMANii(struct DISPMAN *this /*$s1*/, int x /*$s2*/, int y /*$s0*/)
{ // line 1, address 0xf96f0
	int selected; // $s0
	int newArea; // $a0
} // line 138, address 0xf9bac
/*
 * Offset 0xF9BAC
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1728)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ ActiveAreaConfirm__7DISPMAN(struct DISPMAN *this /*$s1*/)
{ // line 1, address 0xf9bac
} // line 230, address 0xf9fac
/*
 * Offset 0xF9FAC
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2044)
 * Stack frame base $sp, length 40
 */
unsigned int /*$ra*/ intersect__7DISPMANG4RECTT1(struct DISPMAN *this /*$a0*/, struct RECT rect1 /*stack 4*/, struct RECT rect2 /*stack 12*/)
{ // line 1, address 0xf9fac
	int n; // $t0
	struct POINT p[4]; // stack address -40
	char bitPattern[2]; // stack address -8
} // line 34, address 0xfa174
/*
 * Offset 0xFA174
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2139)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
unsigned int /*$ra*/ Update__7DISPMAN(struct DISPMAN *this /*$s1*/)
{ // line 1, address 0xfa174
	int n; // $s0
	struct RECT rect; // stack address -32
	{ // line 28, address 0xfa238
		{ // line 29, address 0xfa260
			{ // line 1, address 0xfa260
				struct DISPMAN *this; // $s1
				{ // line 1, address 0xfa260
					int i; // $a0
				} // line 1, address 0xfa2a4
			} // line 1, address 0xfa2a4
			{ // line 1, address 0xfa2a4
				struct DISPMAN *this; // $s1
				{ // line 1, address 0xfa2a4
					int i; // $a0
				} // line 1, address 0xfa2ec
			} // line 1, address 0xfa2ec
			{ // line 1, address 0xfa2ec
				struct DISPMAN *this; // $s1
				{ // line 1, address 0xfa2ec
					int i; // $a0
				} // line 1, address 0xfa334
			} // line 1, address 0xfa334
			{ // line 1, address 0xfa334
				struct DISPMAN *this; // $s1
				{ // line 1, address 0xfa334
					int i; // $a0
				} // line 1, address 0xfa37c
			} // line 1, address 0xfa37c
			{ // line 1, address 0xfa37c
				struct DISPMAN *this; // $s1
				{ // line 1, address 0xfa37c
				} // line 1, address 0xfa39c
			} // line 1, address 0xfa39c
		} // line 38, address 0xfa39c
	} // line 38, address 0xfa39c
	{ // line 49, address 0xfa3d8
		{ // line 52, address 0xfa3e8
			{ // line 53, address 0xfa3e8
				{ // line 53, address 0xfa3ec
					{ // line 1, address 0xfa3ec
						struct DISPMAN *this; // $s1
						int n; // $s0
						{ // line 1, address 0xfa3ec
						} // line 1, address 0xfa47c
					} // line 1, address 0xfa47c
				} // line 53, address 0xfa47c
			} // line 53, address 0xfa488
		} // line 53, address 0xfa488
	} // line 53, address 0xfa488
} // line 127, address 0xfa684
/*
 * Offset 0xFA684
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2271)
 * Stack frame base $sp, length 352
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ PrintKanji__7DISPMANPsiiiiii(struct DISPMAN *this /*$s1*/, short *string /*$s0*/, int x /*$s4*/, int y /*$fp*/, int maxChars /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, address 0xfa684
	char textBuffer[256]; // stack address -312
	int lookup; // $a1
	int n; // stack address -48
	short *sjisPtr; // $s0
	short sjisCode[3]; // stack address -56
	int chars; // $v1
} // line 79, address 0xfa97c
/*
 * Offset 0xFA97C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2402)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ darken__7DISPMANG4RECT(struct DISPMAN *this /*$s0*/, struct RECT rect /*stack 4*/)
{ // line 1, address 0xfa97c
} // line 31, address 0xfacc4
/*
 * Offset 0xFACD4
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2670)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ DrawSprite__7DISPMANP9TIMSTRUCTiiiiii(struct DISPMAN *this /*$s0*/, struct TIMSTRUCT *tim /*$s1*/, int x /*$s2*/, int y /*$s3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/, int trans /*stack 28*/)
{ // line 1, address 0xfacd4
} // line 25, address 0xfaed0
/*
 * Offset 0xFAED0
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2743)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ AddCircleG16__7DISPMANiiiiiiii(struct DISPMAN *this /*$s0*/, int x /*stack 4*/, int y /*stack 8*/, int diameter /*$a3*/, int complete /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/, int divisor /*stack 32*/)
{ // line 1, address 0xfaed0
	int modX; // $s6
	int modY; // $s5
	{ // line 10, address 0xfaf54
		int n; // $s3
	} // line 31, address 0xfb304
} // line 31, address 0xfb304
/*
 * Offset 0xFB304
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2786)
 * Stack frame base $sp, length 344
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
short /*$ra*/ MessageBox__7DISPMANiPcbT3(struct DISPMAN *this /*$s5*/, int type /*stack 4*/, char *text /*stack 8*/, unsigned int bIgnoreEvents /*stack 12*/, unsigned int bSwapKeys /*stack 16*/)
{ // line 1, address 0xfb304
	int boxHeight; // $s6
	int boxTop; // stack address -72
	int maxTextLen; // stack address -68
	int textLen; // $s0
	int textY; // $s3
	int lineCount; // $s1
	struct RECT darkRect; // stack address -304
	struct RECT rect; // stack address -296
	char textBuffer[128]; // stack address -288
	int sel; // $fp
	unsigned int cardState; // stack address -64
	unsigned int bInBox; // $s4
	int n; // $s2
	int messCount; // $s7
	short padData; // $s4
	{ // line 102, address 0xfb79c
		struct DISPMAN *this; // $s5
		struct RECT rect; // stack address -148
		{ // line 102, address 0xfb79c
			int n; // $s2
		} // line 113, address 0xfb8d0
	} // line 113, address 0xfb8d0
	{ // line 117, address 0xfb8d0
		{ // line 120, address 0xfb8fc
			{ // line 124, address 0xfb954
				{ // line 127, address 0xfb984
					{ // line 129, address 0xfb9a8
						struct DISPMAN *this; // $s5
						int y; // $s3
						{ // line 129, address 0xfb9a8
							struct LINE_F2 strF2; // stack address -88
							struct LINE_F4 strF4; // stack address -120
						} // line 129, address 0xfb9a8
					} // line 129, address 0xfb9a8
					{ // line 130, address 0xfba68
						struct DISPMAN *this; // $s5
						int y; // $s3
						{ // line 130, address 0xfba68
							struct LINE_F2 strF2; // stack address -128
							struct LINE_F4 strF4; // stack address -160
						} // line 130, address 0xfba68
					} // line 130, address 0xfba68
					{ // line 133, address 0xfbb2c
						struct DISPMAN *this; // $s5
						int y; // $s3
						{ // line 133, address 0xfbb2c
							struct LINE_F2 strF2; // stack address -128
							struct LINE_F4 strF4; // stack address -160
						} // line 133, address 0xfbbc8
					} // line 133, address 0xfbbc8
				} // line 136, address 0xfbbc8
			} // line 136, address 0xfbbc8
			{ // line 141, address 0xfbc34
				{ // line 176, address 0xfbd50
					{ // line 179, address 0xfbd80
						{ // line 1, address 0xfbdd4
							struct DISPMAN *this; // $s5
							int y; // $s3
							int r; // $s2
							int g; // $s1
							int b; // $s0
							{ // line 1, address 0xfbdd4
								struct LINE_F2 strF2; // stack address -128
								struct LINE_F4 strF4; // stack address -160
							} // line 1, address 0xfbdd4
						} // line 1, address 0xfbdd4
						{ // line 1, address 0xfbefc
							struct DISPMAN *this; // $s5
							int y; // $s3
							int r; // $s2
							int g; // $s1
							int b; // $s0
							{ // line 1, address 0xfbefc
								struct LINE_F2 strF2; // stack address -128
								struct LINE_F4 strF4; // stack address -160
							} // line 1, address 0xfbefc
						} // line 1, address 0xfbefc
						{ // line 188, address 0xfc01c
							struct DISPMAN *this; // $s5
							int y; // $s3
							int r; // $s1
							{ // line 188, address 0xfc01c
								struct LINE_F2 strF2; // stack address -128
								struct LINE_F4 strF4; // stack address -160
							} // line 188, address 0xfc0cc
						} // line 188, address 0xfc0cc
					} // line 191, address 0xfc0cc
				} // line 191, address 0xfc0cc
			} // line 207, address 0xfc138
		} // line 233, address 0xfc278
		{ // line 236, address 0xfc280
			{ // line 240, address 0xfc2b0
				{ // line 241, address 0xfc2f0
					{ // line 244, address 0xfc2fc
						{ // line 1, address 0xfc390
							struct DISPMAN *this; // $s5
							int y; // $s3
							{ // line 1, address 0xfc390
								struct LINE_F2 strF2; // stack address -128
								struct LINE_F4 strF4; // stack address -160
							} // line 1, address 0xfc390
						} // line 1, address 0xfc390
						{ // line 1, address 0xfc474
							struct DISPMAN *this; // $s5
							int y; // $s3
							{ // line 1, address 0xfc474
								struct LINE_F2 strF2; // stack address -128
								struct LINE_F4 strF4; // stack address -160
							} // line 1, address 0xfc474
						} // line 1, address 0xfc474
					} // line 266, address 0xfc540
					{ // line 283, address 0xfc650
						struct DISPMAN *this; // $s5
						int y; // $s3
						int w; // $v0
						{ // line 283, address 0xfc650
							struct LINE_F2 strF2; // stack address -128
							struct LINE_F4 strF4; // stack address -160
						} // line 283, address 0xfc650
					} // line 283, address 0xfc650
					{ // line 308, address 0xfc848
						struct DISPMAN *this; // $s5
						int y; // $s3
						int w; // $v0
						{ // line 308, address 0xfc848
							struct LINE_F2 strF2; // stack address -128
							struct LINE_F4 strF4; // stack address -160
						} // line 308, address 0xfc8e8
					} // line 308, address 0xfc8e8
				} // line 313, address 0xfc8f0
			} // line 313, address 0xfc8f0
		} // line 313, address 0xfc8f0
	} // line 313, address 0xfc8f0
} // line 321, address 0xfc950
/*
 * Offset 0xFC950
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3112)
 * Stack frame base $sp, length 232
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
struct RECT /*$ra*/ ProgressBox__7DISPMANPci(struct DISPMAN *this /*$s3*/, char *text /*$fp*/, int progress /*stack 12*/)
{ // line 1, address 0xfc950
	int boxHeight; // $s4
	int boxTop; // stack address -48
	int maxTextLen; // $s7
	int textLen; // $v1
	int textY; // $s1
	int lineCount; // $s0
	struct RECT darkRect; // stack address -192
	char textBuffer[128]; // stack address -184
	int n; // $s2
	int messCount; // $s6
} // line 39, address 0xfcb08
/*
 * Offset 0xFCC54
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3182)
 * Stack frame base $sp, length 312
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ message_width__7DISPMANPcii(struct DISPMAN *this /*$s3*/, char *mesPtr /*$s1*/, int font /*$a2*/, int maxChars /*$s6*/)
{ // line 1, address 0xfcc54
	char c; // $a1
	int fRef; // $s0
	int w; // $s2
	int n; // $s5
	{ // line 1, address 0xfcc54
		{ // line 7, address 0xfcc98
			{ // line 1, address 0xfcc98
				short *kanjiStringPtr; // $s1
				int maxChars; // $s6
				{ // line 1, address 0xfcc98
					int totalLen; // $a1
					short textBuffer[128]; // stack address -296
				} // line 1, address 0xfcd04
			} // line 1, address 0xfcd04
		} // line 8, address 0xfcd0c
	} // line 27, address 0xfce00
} // line 27, address 0xfce00
/*
 * Offset 0xFCE00
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3214)
 * Stack frame base $sp, length 184
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ justify_mess__7DISPMANPcii(struct DISPMAN *this /*$fp*/, char *messPtr /*$s3*/, int font /*stack 8*/, int maxLineLength /*$s7*/)
{ // line 1, address 0xfce00
	char c; // $s0
	short kanji; // $s0
	char word[128]; // stack address -168
	int wordCount; // $s1
	int lineLength; // $s6
	int lineCount; // $s4
} // line 117, address 0xfd000
/*
 * Offset 0xFD000
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3337)
 * Stack frame base $sp, length 88
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ write_mess__7DISPMANPciiiiiiii(struct DISPMAN *this /*$s2*/, char *mesPtr /*$s6*/, int x /*$s3*/, int y /*stack 12*/, int font /*stack 16*/, int maxChars /*stack 20*/, int r /*stack 24*/, int g /*stack 28*/, int b /*stack 32*/, int trans /*stack 36*/)
{ // line 1, address 0xfd000
	int fRef; // $s1
	int n; // stack address -56
	char c; // $s0
	{ // line 1, address 0xfd000
		{ // line 9, address 0xfd080
			{ // line 11, address 0xfd0f4
				{ // line 20, address 0xfd124
					{ // line 21, address 0xfd134
						{ // line 22, address 0xfd134
							struct DISPMAN *this; // $s2
							struct TIMSTRUCT *tim; // $a3
							int y; // stack address 12
							int r; // $t1
							int g; // $t0
							int b; // $a3
							int trans; // $v0
							{ // line 22, address 0xfd134
								struct DR_TPAGE *tpagePtr; // $a2
								struct SPRT *spritePtr; // $a1
							} // line 29, address 0xfd27c
						} // line 29, address 0xfd27c
					} // line 29, address 0xfd27c
				} // line 29, address 0xfd27c
				{ // line 39, address 0xfd2a4
					{ // line 40, address 0xfd2b0
						{ // line 1, address 0xfd2b0
							struct DISPMAN *this; // $s2
							struct TIMSTRUCT *tim; // $a3
							int x; // $s3
							int y; // stack address 12
							int r; // $t1
							int g; // $t0
							int b; // $a3
							int trans; // $v0
							{ // line 1, address 0xfd2b0
								struct DR_TPAGE *tpagePtr; // $a2
								struct SPRT *spritePtr; // $a1
							} // line 1, address 0xfd2b0
						} // line 1, address 0xfd2b0
					} // line 44, address 0xfd3a4
				} // line 44, address 0xfd3a4
			} // line 44, address 0xfd3a4
		} // line 49, address 0xfd410
	} // line 49, address 0xfd410
} // line 49, address 0xfd410
/*
 * Offset 0xFD410
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3392)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ font_ref__7DISPMANcb(struct DISPMAN *this /*$a0*/, char c /*$a1*/, unsigned int accent /*$a2*/)
{ // line 1, address 0xfd410
} // line 127, address 0xfd650
/*
 * Offset 0xFD658
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3524)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ Tim2VRAM__7DISPMANPlP9TIMSTRUCTibiiii(struct DISPMAN *this /*$a0*/, long *timDataPtr /*$s0*/, struct TIMSTRUCT *destTimPtr /*$s2*/, int abr /*$s1*/, unsigned int setCoords /*stack 16*/, int clutX /*stack 20*/, int clutY /*stack 24*/, int iconX /*stack 28*/, int iconY /*stack 32*/)
{ // line 1, address 0xfd658
	long flag; // $a0
	struct RECT *timRect; // $a2
	{ // line 19, address 0xfd6a4
		{ // line 25, address 0xfd6b8
			{ // line 34, address 0xfd6d8
				{ // line 39, address 0xfd6f0
					{ // line 40, address 0xfd6f0
						int n; // $a0
					} // line 45, address 0xfd718
				} // line 45, address 0xfd718
			} // line 45, address 0xfd718
		} // line 52, address 0xfd740
	} // line 52, address 0xfd740
} // line 87, address 0xfd86c
/*
 * Offset 0xFD86C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3749)
 * Stack frame base $sp, length 264
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ wipe_screen__7DISPMANii(struct DISPMAN *this /*$s1*/, int wt /*$s3*/, int step /*$s5*/)
{ // line 1, address 0xfd86c
	int i; // $s2
	struct DRAWENV drawenv; // stack address -248
	struct DISPENV de; // stack address -152
	unsigned long fadeOt[3]; // stack address -128
	struct POLY_GT3 FadeSetTp; // stack address -112
	struct POLY_G4 FadePol; // stack address -72
} // line 57, address 0xfdad8
/*
 * Offset 0xFDAD8
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 392)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DISPMAN_ctor(struct DISPMAN *this /*$s2*/, int __in_chrg /*$s3*/)
{ // line 1, address 0xfdad8
	struct RECT rect; // stack address -32
} // line 14, address 0xfdb38
/*
 * Offset 0xFDBEC
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1105)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DrawEnterName__7DISPMANPc(struct DISPMAN *this /*$s0*/, char *ascii /*$a3*/)
{ // line 1, address 0xfdbec
	char message[64]; // stack address -72
} // line 6, address 0xfdc6c
/*
 * Offset 0xFDC6C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1114)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ SetMenuOption__7DISPMANi(struct DISPMAN *this /*$s0*/, int menuOption /*$s1*/)
{ // line 1, address 0xfdc6c
} // line 7, address 0xfdca8
/*
 * Offset 0xFDCBC
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1125)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetActiveFunction__7DISPMANi(struct DISPMAN *this /*$a0*/, int menuOption /*$a1*/)
{ // line 1, address 0xfdcbc
} // line 2, address 0xfdcc4
/*
 * Offset 0xFDCC4
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1131)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ MoveActiveAreaTo__7DISPMANi(struct DISPMAN *this /*$s0*/, int area /*$s1*/)
{ // line 1, address 0xfdcc4
} // line 5, address 0xfdd0c
/*
 * Offset 0xFDD0C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1249)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SelectNewBlock__7DISPMANi(struct DISPMAN *this /*$s0*/, int newBlock /*$a1*/)
{ // line 1, address 0xfdd0c
} // line 16, address 0xfddc0
/*
 * Offset 0xFDDD0
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1710)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetArea__7DISPMANii(struct DISPMAN *this /*$a0*/, int x /*$a1*/, int y /*$a2*/)
{ // line 1, address 0xfddd0
	int n; // $a3
} // line 15, address 0xfde48
/*
 * Offset 0xFDE50
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1962)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ ActiveAreaCancel__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, address 0xfde50
} // line 53, address 0xfdf58
/*
 * Offset 0xFDF58
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2028)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ AddingBlock__7DISPMANi(struct DISPMAN *this /*$a0*/, int n /*$a1*/)
{ // line 1, address 0xfdf58
} // line 1, address 0xfdf60
/*
 * Offset 0xFDF60
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2030)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ DeletingCurrBlock__7DISPMANi(struct DISPMAN *this /*$a0*/, int n /*$a1*/)
{ // line 1, address 0xfdf60
} // line 1, address 0xfdf68
/*
 * Offset 0xFDF68
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2033)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ InvalidateArea__7DISPMANG4RECT(struct DISPMAN *this /*$s3*/, struct RECT rect /*stack 4*/)
{ // line 1, address 0xfdf68
	int n; // $s2
} // line 7, address 0xfe040
/*
 * Offset 0xFE040
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2081)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InvalidateArea__7DISPMANi(struct DISPMAN *this /*$a0*/, int n /*$a1*/)
{ // line 1, address 0xfe040
	int i; // $a2
} // line 14, address 0xfe090
/*
 * Offset 0xFE098
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2100)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DrawArea__7DISPMANi(struct DISPMAN *this /*$a2*/, int n /*$a1*/)
{ // line 1, address 0xfe098
} // line 26, address 0xfe134
/*
 * Offset 0xFE144
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2129)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ FlashOn__7DISPMAN(struct DISPMAN *this /*$a0*/)
{ // line 1, address 0xfe144
} // line 1, address 0xfe150
/*
 * Offset 0xFE150
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2132)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ FlashOff__7DISPMAN(struct DISPMAN *this /*$a0*/)
{ // line 1, address 0xfe150
} // line 3, address 0xfe160
/*
 * Offset 0xFE160
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2355)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ FindKanji__7DISPMANs(struct DISPMAN *this /*$a0*/, short sjisCode /*$a1*/)
{ // line 1, address 0xfe160
	int n; // $v1
} // line 12, address 0xfe1a8
/*
 * Offset 0xFE1B0
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2371)
 * Stack frame base $sp, length 72
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ CentrePrintKanji__7DISPMANPsiiiiii(struct DISPMAN *this /*$s5*/, short *string /*$s3*/, int x /*$s6*/, int y /*$s7*/, int maxChars /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, address 0xfe1b0
} // line 4, address 0xfe258
/*
 * Offset 0xFE258
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2379)
 * Stack frame base $sp, length 288
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ KanjiStrLen__FPsi(short *kanjiStringPtr /*$s1*/, int maxChars /*$s0*/)
{ // line 1, address 0xfe258
	short textBuffer[128]; // stack address -272
	int totalLen; // $a1
} // line 17, address 0xfe2f4
/*
 * Offset 0xFE2F4
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2474)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetCurrBlock__7DISPMAN(struct DISPMAN *this /*$a0*/)
{ // line 1, address 0xfe2f4
} // line 1, address 0xfe300
/*
 * Offset 0xFE300
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2476)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetCurrSlice__7DISPMAN(struct DISPMAN *this /*$a0*/)
{ // line 1, address 0xfe300
} // line 1, address 0xfe30c
/*
 * Offset 0xFE30C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2480)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ draw_card__7DISPMANiiPcb(struct DISPMAN *this /*$s1*/, int x /*$s2*/, int y /*$s3*/, char *text /*$a1*/, unsigned int selected /*stack 16*/)
{ // line 1, address 0xfe30c
} // line 15, address 0xfe418
/*
 * Offset 0xFE434
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2515)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ AddIcon__7DISPMANP9TIMSTRUCTiiiiiib(struct DISPMAN *this /*$a0*/, struct TIMSTRUCT *tim /*$t2*/, int x /*$a2*/, int y /*$a1*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/, int trans /*stack 28*/, unsigned int scale /*stack 32*/)
{ // line 1, address 0xfe434
	int XPlusW; // $t1
	int YPlusH; // $a0
	struct POLY_FT4 *polyFT4Ptr; // $t0
} // line 45, address 0xfe590
/*
 * Offset 0xFE598
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2616)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ AddMoveImage__7DISPMANP4RECTT1(struct DISPMAN *this /*$s0*/, struct RECT *srect /*$a1*/, struct RECT *drect /*$t0*/)
{ // line 1, address 0xfe598
	struct DR_MOVE *movePtr; // $s0
} // line 9, address 0xfe61c
/*
 * Offset 0xFE61C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2630)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ AddSprite__7DISPMANP9TIMSTRUCTiiiiii(struct DISPMAN *this /*$a0*/, struct TIMSTRUCT *tim /*$a1*/, int x /*$a2*/, int y /*$a3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/, int trans /*stack 28*/)
{ // line 1, address 0xfe61c
	struct SPRT *spritePtr; // $t0
	struct DR_TPAGE *tpagePtr; // $a0
} // line 36, address 0xfe72c
/*
 * Offset 0xFE72C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2699)
 * Stack frame base $sp, length 104
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ DrawBox__7DISPMANiiiiiii(struct DISPMAN *this /*$a0*/, int x /*$s2*/, int y /*$s3*/, int w /*$s1*/, int h /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, address 0xfe72c
	struct LINE_F4 strF4; // stack address -88
	struct LINE_F2 strF2; // stack address -56
} // line 32, address 0xfe834
/*
 * Offset 0xFE834
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3172)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ write_mess_c__7DISPMANPciiiiiiii(struct DISPMAN *this /*$s0*/, char *mesPtr /*$s1*/, int x /*stack 8*/, int y /*$s4*/, int font /*stack 16*/, int maxChars /*stack 20*/, int r /*stack 24*/, int g /*stack 28*/, int b /*stack 32*/, int trans /*stack 36*/)
{ // line 1, address 0xfe834
	int w; // $s0
} // line 6, address 0xfe908
/*
 * Offset 0xFE908
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3615)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ download_block_icon__7DISPMANiiii(struct DISPMAN *this /*$s2*/, int iconX /*$s3*/, int iconY /*$s1*/, int clutX /*$a3*/, int clutY /*stack 16*/)
{ // line 1, address 0xfe908
	struct RECT rect; // stack address -32
	struct TIMSTRUCT *timPtr; // $s0
	unsigned short *clutWordPtr; // $v1
	{ // line 1, address 0xfe908
		int n; // $a0
	} // line 22, address 0xfe998
} // line 42, address 0xfea44
/*
 * Offset 0xFEA44
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3809)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ move_screen__7DISPMANiii(struct DISPMAN *this /*$s0*/, int startY /*$a1*/, int finishY /*$s3*/, int steps /*$a3*/)
{ // line 1, address 0xfea44
	int screenY; // $s1
} // line 26, address 0xfeb00
/*
 * Offset 0xFEB24
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3840)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetCyclesPerSecond__7DISPMAN(struct DISPMAN *this /*$a0*/)
{ // line 1, address 0xfeb24
} // line 14, address 0xfeb70