
/*
 * Offset 0x1005E0
 * D:\driver2\game\MEMCARD\CMAN.CPP (line 33)
 * Stack frame base $sp, length 51872
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ cardman__FiiPcP10FILEFORMATP5SLICET2T2(int operation /*stack 0*/, int options /*$a1*/, char *textBuffer /*$s4*/, struct FILEFORMAT *fileFormatPtr /*stack 12*/, struct SLICE *slicePtr /*stack 16*/, char *backImageName /*stack 20*/, char *bufferPtr96K /*stack 24*/)
{ // line 1, address 0x1005e0
	struct TIMSTRUCT tempTimStruct; // stack address -51840
	struct RECT rect; // stack address -51824
	int n; // $s0
	char charBuffer[250]; // stack address -51816
	char kanjiFree[6]; // stack address -51560
	char kanjiSize[6]; // stack address -51552
	char kanjiDel[6]; // stack address -51544
	int card_process; // $s3
	int padWait; // stack address -56
	int dirCount; // $s0
	int delCount; // stack address -52
	int copyStatus; // $s0
	int pasteStatus; // $a3
	int destFree; // $s6
	int sourceSize; // $s5
	int newBlock; // $s2
	int nMessage; // $s2
	int language; // stack address -48
	short padData; // $s1
	struct PAD pad; // stack address -51536
	struct DISPMAN dispMan; // stack address -18128
	{ // line 36, address 0x10067c
		{ // line 44, address 0x1006c4
		} // line 47, address 0x100708
	} // line 47, address 0x100708
	{ // line 51, address 0x100708
		{ // line 52, address 0x100720
			struct _CARD *header; // $a1
		} // line 74, address 0x100970
	} // line 74, address 0x100970
	{ // line 124, address 0x100a14
		{ // line 142, address 0x100a14
			{ // line 148, address 0x100a58
				{ // line 149, address 0x100a58
					{ // line 150, address 0x100a68
					} // line 167, address 0x100b40
				} // line 167, address 0x100b40
			} // line 170, address 0x100b48
		} // line 170, address 0x100b48
		{ // line 174, address 0x100b48
			{ // line 183, address 0x100b64
				{ // line 184, address 0x100b64
					{ // line 185, address 0x100b74
						{ // line 186, address 0x100b74
							{ // line 190, address 0x100b94
							} // line 273, address 0x100d8c
							{ // line 278, address 0x100d9c
							} // line 293, address 0x100e08
						} // line 293, address 0x100e08
					} // line 293, address 0x100e08
				} // line 293, address 0x100e08
			} // line 293, address 0x100e08
		} // line 293, address 0x100e08
		{ // line 301, address 0x100e08
			{ // line 302, address 0x100e30
			} // line 317, address 0x100e94
		} // line 317, address 0x100e94
		{ // line 321, address 0x100e94
			{ // line 322, address 0x100ebc
				{ // line 325, address 0x100ebc
					{ // line 326, address 0x100ecc
						{ // line 327, address 0x100ecc
						} // line 327, address 0x100ecc
					} // line 333, address 0x100ef4
				} // line 333, address 0x100ef4
				{ // line 391, address 0x10108c
				} // line 391, address 0x10108c
				{ // line 437, address 0x1011a8
				} // line 437, address 0x1011a8
				{ // line 445, address 0x1011b0
					{ // line 446, address 0x1011d8
						{ // line 466, address 0x10126c
						} // line 466, address 0x10126c
						{ // line 489, address 0x101354
						} // line 489, address 0x101354
						{ // line 499, address 0x101364
						} // line 499, address 0x101364
					} // line 499, address 0x101364
				} // line 499, address 0x101364
				{ // line 499, address 0x101364
				} // line 499, address 0x101364
				{ // line 532, address 0x101448
				} // line 532, address 0x101448
				{ // line 540, address 0x101460
					{ // line 541, address 0x1014a4
						{ // line 542, address 0x1014a4
						} // line 542, address 0x1014a4
					} // line 544, address 0x1014b8
				} // line 544, address 0x1014b8
				{ // line 547, address 0x1014b8
					{ // line 551, address 0x101500
						{ // line 552, address 0x101500
						} // line 552, address 0x101500
					} // line 556, address 0x101548
				} // line 556, address 0x101548
				{ // line 560, address 0x101548
					{ // line 563, address 0x101580
						{ // line 564, address 0x101580
						} // line 564, address 0x101580
					} // line 566, address 0x101590
				} // line 566, address 0x101590
				{ // line 579, address 0x101650
					{ // line 580, address 0x101658
						{ // line 581, address 0x101658
						} // line 581, address 0x101658
					} // line 583, address 0x101670
				} // line 583, address 0x101670
				{ // line 594, address 0x101714
					{ // line 595, address 0x10171c
						{ // line 596, address 0x10171c
						} // line 596, address 0x10171c
					} // line 598, address 0x101734
				} // line 598, address 0x101734
				{ // line 601, address 0x101734
				} // line 601, address 0x101734
				{ // line 611, address 0x10177c
					{ // line 615, address 0x1017b0
						{ // line 675, address 0x1019c8
						} // line 675, address 0x1019c8
					} // line 678, address 0x1019f4
				} // line 678, address 0x1019f4
				{ // line 681, address 0x1019f4
					{ // line 682, address 0x101a14
						{ // line 707, address 0x101afc
							{ // line 711, address 0x101b1c
								{ // line 712, address 0x101b1c
								} // line 712, address 0x101b1c
							} // line 714, address 0x101b30
						} // line 714, address 0x101b30
					} // line 717, address 0x101b30
				} // line 732, address 0x101b4c
				{ // line 732, address 0x101b4c
				} // line 732, address 0x101b4c
				{ // line 738, address 0x101b4c
					{ // line 742, address 0x101b8c
						{ // line 743, address 0x101b8c
							{ // line 749, address 0x101bc0
								{ // line 753, address 0x101c04
								} // line 753, address 0x101c04
							} // line 754, address 0x101c0c
							{ // line 758, address 0x101c0c
								{ // line 764, address 0x101c50
									{ // line 768, address 0x101cb4
										{ // line 770, address 0x101cec
										} // line 770, address 0x101cec
									} // line 771, address 0x101cf4
								} // line 771, address 0x101cf4
							} // line 771, address 0x101cf4
						} // line 771, address 0x101cf4
					} // line 771, address 0x101cf4
				} // line 771, address 0x101cf4
				{ // line 804, address 0x101d38
					{ // line 805, address 0x101d40
						{ // line 808, address 0x101d40
						} // line 808, address 0x101d40
					} // line 810, address 0x101d58
				} // line 810, address 0x101d58
				{ // line 839, address 0x101e94
					{ // line 840, address 0x101e9c
						{ // line 841, address 0x101e9c
						} // line 841, address 0x101e9c
					} // line 843, address 0x101eb4
				} // line 843, address 0x101eb4
				{ // line 867, address 0x101f98
				} // line 867, address 0x101f98
				{ // line 874, address 0x101fb0
				} // line 874, address 0x101fb0
				{ // line 898, address 0x102104
					{ // line 899, address 0x10210c
						{ // line 904, address 0x10210c
						} // line 904, address 0x10210c
					} // line 907, address 0x102124
					{ // line 910, address 0x102124
						{ // line 910, address 0x102124
							{ // line 911, address 0x10212c
								{ // line 913, address 0x10212c
								} // line 913, address 0x10212c
							} // line 916, address 0x102150
						} // line 922, address 0x102150
					} // line 922, address 0x102150
				} // line 922, address 0x102150
				{ // line 922, address 0x102150
				} // line 922, address 0x102150
				{ // line 937, address 0x1021b0
					{ // line 938, address 0x1021b0
						{ // line 940, address 0x1021b0
							{ // line 941, address 0x1021d8
								{ // line 943, address 0x1021d8
								} // line 943, address 0x1021d8
								{ // line 948, address 0x10220c
								} // line 948, address 0x10220c
							} // line 948, address 0x10220c
						} // line 948, address 0x10220c
					} // line 964, address 0x1022a8
				} // line 964, address 0x1022a8
				{ // line 967, address 0x1022a8
				} // line 967, address 0x1022a8
			} // line 967, address 0x1022a8
		} // line 967, address 0x1022a8
	} // line 980, address 0x1022ec
	{ // line 997, address 0x102304
	} // line 997, address 0x102304
} // line 997, address 0x102364
/*
 * Offset 0x102364
 * D:\driver2\game\MEMCARD\CMAN.CPP (line 1065)
 * Stack frame base $sp, length 88
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ EnterName__FP3PADP7DISPMANPc(struct PAD *pad /*$fp*/, struct DISPMAN *disp /*stack 4*/, char *username /*stack 8*/)
{ // line 1, address 0x102364
	char asciiname[20]; // stack address -72
	int ret; // stack address -48
	short padData; // $s5
	short prevData; // $s7
	int so; // $s2
	int co; // $s6
	int delay; // $s3
	char c; // $s1
	char toggle; // stack address -44
} // line 157, address 0x102710
/*
 * Offset 0x102710
 * D:\driver2\game\MEMCARD\CMAN.CPP (line 24)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: ra
 */
int /*$ra*/ card_manager(int operation /*$a0*/, int options /*$a1*/, char *textBuffer /*$a2*/, struct FILEFORMAT *fileFormatPtr /*$a3*/, struct SLICE *slicePtr /*stack 16*/, char *backImageName /*stack 20*/, char *bufferPtr96K /*stack 24*/)
{ // line 1, address 0x102710
} // line 6, address 0x102744
/*
 * Offset 0x102744
 * D:\driver2\game\MEMCARD\CMAN.CPP (line 1034)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ LoadBackground__FPcT0(char *filename /*$s5*/, char *buffer /*$s2*/)
{ // line 1, address 0x102744
	struct RECT rect; // stack address -40
	int i; // $s0
	{ // line 1, address 0x102744
		{ // line 5, address 0x10277c
		} // line 8, address 0x10277c
	} // line 12, address 0x1027e8
} // line 12, address 0x1027e8