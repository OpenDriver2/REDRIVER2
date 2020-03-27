#include "THISDUST.H"
#include "CMAN.H"


// decompiled code
// original method signature: 
// int /*$ra*/ card_manager(int operation /*$a0*/, int options /*$a1*/, char *textBuffer /*$a2*/, struct FILEFORMAT *fileFormatPtr /*$a3*/, struct SLICE *slicePtr /*stack 16*/, char *backImageName /*stack 20*/, char *bufferPtr96K /*stack 24*/)
 // line 24, offset 0x00102710
	/* begin block 1 */
		// Start line: 25
		// Start offset: 0x00102710
	/* end block 1 */
	// End offset: 0x00102744
	// End Line: 30

	/* begin block 2 */
		// Start line: 48
	/* end block 2 */
	// End Line: 49

void FUN_MCARD__00102710(void)

{
  FUN_MCARD__001005e0();
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ cardman__FiiPcP10FILEFORMATP5SLICET2T2(int operation /*stack 0*/, int options /*$a1*/, char *textBuffer /*$s4*/, struct FILEFORMAT *fileFormatPtr /*stack 12*/, struct SLICE *slicePtr /*stack 16*/, char *backImageName /*stack 20*/, char *bufferPtr96K /*stack 24*/)
 // line 33, offset 0x001005e0
	/* begin block 1 */
		// Start line: 34
		// Start offset: 0x001005E0
		// Variables:
	// 		struct TIMSTRUCT tempTimStruct; // stack offset -51840
	// 		struct RECT rect; // stack offset -51824
	// 		int n; // $s0
	// 		char charBuffer[250]; // stack offset -51816
	// 		char kanjiFree[6]; // stack offset -51560
	// 		char kanjiSize[6]; // stack offset -51552
	// 		char kanjiDel[6]; // stack offset -51544
	// 		int card_process; // $s3
	// 		int padWait; // stack offset -56
	// 		int dirCount; // $s0
	// 		int delCount; // stack offset -52
	// 		int copyStatus; // $s0
	// 		int pasteStatus; // $a3
	// 		int destFree; // $s6
	// 		int sourceSize; // $s5
	// 		int newBlock; // $s2
	// 		int nMessage; // $s2
	// 		int language; // stack offset -48
	// 		short padData; // $s1
	// 		struct PAD pad; // stack offset -51536
	// 		struct DISPMAN dispMan; // stack offset -18128

		/* begin block 1.1 */
			// Start line: 69
			// Start offset: 0x0010067C

			/* begin block 1.1.1 */
				// Start line: 77
				// Start offset: 0x001006C4
			/* end block 1.1.1 */
			// End offset: 0x00100708
			// End Line: 80
		/* end block 1.1 */
		// End offset: 0x00100708
		// End Line: 80

		/* begin block 1.2 */
			// Start line: 84
			// Start offset: 0x00100708

			/* begin block 1.2.1 */
				// Start line: 85
				// Start offset: 0x00100720
				// Variables:
			// 		struct _CARD *header; // $a1
			/* end block 1.2.1 */
			// End offset: 0x00100970
			// End Line: 107
		/* end block 1.2 */
		// End offset: 0x00100970
		// End Line: 107

		/* begin block 1.3 */
			// Start line: 157
			// Start offset: 0x00100A14

			/* begin block 1.3.1 */
				// Start line: 175
				// Start offset: 0x00100A14

				/* begin block 1.3.1.1 */
					// Start line: 181
					// Start offset: 0x00100A58

					/* begin block 1.3.1.1.1 */
						// Start line: 182
						// Start offset: 0x00100A58

						/* begin block 1.3.1.1.1.1 */
							// Start line: 183
							// Start offset: 0x00100A68
						/* end block 1.3.1.1.1.1 */
						// End offset: 0x00100B40
						// End Line: 200
					/* end block 1.3.1.1.1 */
					// End offset: 0x00100B40
					// End Line: 200
				/* end block 1.3.1.1 */
				// End offset: 0x00100B48
				// End Line: 203
			/* end block 1.3.1 */
			// End offset: 0x00100B48
			// End Line: 203

			/* begin block 1.3.2 */
				// Start line: 207
				// Start offset: 0x00100B48

				/* begin block 1.3.2.1 */
					// Start line: 216
					// Start offset: 0x00100B64

					/* begin block 1.3.2.1.1 */
						// Start line: 217
						// Start offset: 0x00100B64

						/* begin block 1.3.2.1.1.1 */
							// Start line: 218
							// Start offset: 0x00100B74

							/* begin block 1.3.2.1.1.1.1 */
								// Start line: 219
								// Start offset: 0x00100B74

								/* begin block 1.3.2.1.1.1.1.1 */
									// Start line: 223
									// Start offset: 0x00100B94
								/* end block 1.3.2.1.1.1.1.1 */
								// End offset: 0x00100D8C
								// End Line: 306

								/* begin block 1.3.2.1.1.1.1.2 */
									// Start line: 311
									// Start offset: 0x00100D9C
								/* end block 1.3.2.1.1.1.1.2 */
								// End offset: 0x00100E08
								// End Line: 326
							/* end block 1.3.2.1.1.1.1 */
							// End offset: 0x00100E08
							// End Line: 326
						/* end block 1.3.2.1.1.1 */
						// End offset: 0x00100E08
						// End Line: 326
					/* end block 1.3.2.1.1 */
					// End offset: 0x00100E08
					// End Line: 326
				/* end block 1.3.2.1 */
				// End offset: 0x00100E08
				// End Line: 326
			/* end block 1.3.2 */
			// End offset: 0x00100E08
			// End Line: 326

			/* begin block 1.3.3 */
				// Start line: 334
				// Start offset: 0x00100E08

				/* begin block 1.3.3.1 */
					// Start line: 335
					// Start offset: 0x00100E30
				/* end block 1.3.3.1 */
				// End offset: 0x00100E94
				// End Line: 350
			/* end block 1.3.3 */
			// End offset: 0x00100E94
			// End Line: 350

			/* begin block 1.3.4 */
				// Start line: 354
				// Start offset: 0x00100E94

				/* begin block 1.3.4.1 */
					// Start line: 355
					// Start offset: 0x00100EBC

					/* begin block 1.3.4.1.1 */
						// Start line: 358
						// Start offset: 0x00100EBC

						/* begin block 1.3.4.1.1.1 */
							// Start line: 359
							// Start offset: 0x00100ECC

							/* begin block 1.3.4.1.1.1.1 */
								// Start line: 360
								// Start offset: 0x00100ECC
							/* end block 1.3.4.1.1.1.1 */
							// End offset: 0x00100ECC
							// End Line: 360
						/* end block 1.3.4.1.1.1 */
						// End offset: 0x00100EF4
						// End Line: 366
					/* end block 1.3.4.1.1 */
					// End offset: 0x00100EF4
					// End Line: 366

					/* begin block 1.3.4.1.2 */
						// Start line: 424
						// Start offset: 0x0010108C
					/* end block 1.3.4.1.2 */
					// End offset: 0x0010108C
					// End Line: 424

					/* begin block 1.3.4.1.3 */
						// Start line: 470
						// Start offset: 0x001011A8
					/* end block 1.3.4.1.3 */
					// End offset: 0x001011A8
					// End Line: 470

					/* begin block 1.3.4.1.4 */
						// Start line: 478
						// Start offset: 0x001011B0

						/* begin block 1.3.4.1.4.1 */
							// Start line: 479
							// Start offset: 0x001011D8

							/* begin block 1.3.4.1.4.1.1 */
								// Start line: 499
								// Start offset: 0x0010126C
							/* end block 1.3.4.1.4.1.1 */
							// End offset: 0x0010126C
							// End Line: 499

							/* begin block 1.3.4.1.4.1.2 */
								// Start line: 522
								// Start offset: 0x00101354
							/* end block 1.3.4.1.4.1.2 */
							// End offset: 0x00101354
							// End Line: 522

							/* begin block 1.3.4.1.4.1.3 */
								// Start line: 532
								// Start offset: 0x00101364
							/* end block 1.3.4.1.4.1.3 */
							// End offset: 0x00101364
							// End Line: 532
						/* end block 1.3.4.1.4.1 */
						// End offset: 0x00101364
						// End Line: 532
					/* end block 1.3.4.1.4 */
					// End offset: 0x00101364
					// End Line: 532

					/* begin block 1.3.4.1.5 */
						// Start line: 532
						// Start offset: 0x00101364
					/* end block 1.3.4.1.5 */
					// End offset: 0x00101364
					// End Line: 532

					/* begin block 1.3.4.1.6 */
						// Start line: 565
						// Start offset: 0x00101448
					/* end block 1.3.4.1.6 */
					// End offset: 0x00101448
					// End Line: 565

					/* begin block 1.3.4.1.7 */
						// Start line: 573
						// Start offset: 0x00101460

						/* begin block 1.3.4.1.7.1 */
							// Start line: 574
							// Start offset: 0x001014A4

							/* begin block 1.3.4.1.7.1.1 */
								// Start line: 575
								// Start offset: 0x001014A4
							/* end block 1.3.4.1.7.1.1 */
							// End offset: 0x001014A4
							// End Line: 575
						/* end block 1.3.4.1.7.1 */
						// End offset: 0x001014B8
						// End Line: 577
					/* end block 1.3.4.1.7 */
					// End offset: 0x001014B8
					// End Line: 577

					/* begin block 1.3.4.1.8 */
						// Start line: 580
						// Start offset: 0x001014B8

						/* begin block 1.3.4.1.8.1 */
							// Start line: 584
							// Start offset: 0x00101500

							/* begin block 1.3.4.1.8.1.1 */
								// Start line: 585
								// Start offset: 0x00101500
							/* end block 1.3.4.1.8.1.1 */
							// End offset: 0x00101500
							// End Line: 585
						/* end block 1.3.4.1.8.1 */
						// End offset: 0x00101548
						// End Line: 589
					/* end block 1.3.4.1.8 */
					// End offset: 0x00101548
					// End Line: 589

					/* begin block 1.3.4.1.9 */
						// Start line: 593
						// Start offset: 0x00101548

						/* begin block 1.3.4.1.9.1 */
							// Start line: 596
							// Start offset: 0x00101580

							/* begin block 1.3.4.1.9.1.1 */
								// Start line: 597
								// Start offset: 0x00101580
							/* end block 1.3.4.1.9.1.1 */
							// End offset: 0x00101580
							// End Line: 597
						/* end block 1.3.4.1.9.1 */
						// End offset: 0x00101590
						// End Line: 599
					/* end block 1.3.4.1.9 */
					// End offset: 0x00101590
					// End Line: 599

					/* begin block 1.3.4.1.10 */
						// Start line: 612
						// Start offset: 0x00101650

						/* begin block 1.3.4.1.10.1 */
							// Start line: 613
							// Start offset: 0x00101658

							/* begin block 1.3.4.1.10.1.1 */
								// Start line: 614
								// Start offset: 0x00101658
							/* end block 1.3.4.1.10.1.1 */
							// End offset: 0x00101658
							// End Line: 614
						/* end block 1.3.4.1.10.1 */
						// End offset: 0x00101670
						// End Line: 616
					/* end block 1.3.4.1.10 */
					// End offset: 0x00101670
					// End Line: 616

					/* begin block 1.3.4.1.11 */
						// Start line: 627
						// Start offset: 0x00101714

						/* begin block 1.3.4.1.11.1 */
							// Start line: 628
							// Start offset: 0x0010171C

							/* begin block 1.3.4.1.11.1.1 */
								// Start line: 629
								// Start offset: 0x0010171C
							/* end block 1.3.4.1.11.1.1 */
							// End offset: 0x0010171C
							// End Line: 629
						/* end block 1.3.4.1.11.1 */
						// End offset: 0x00101734
						// End Line: 631
					/* end block 1.3.4.1.11 */
					// End offset: 0x00101734
					// End Line: 631

					/* begin block 1.3.4.1.12 */
						// Start line: 634
						// Start offset: 0x00101734
					/* end block 1.3.4.1.12 */
					// End offset: 0x00101734
					// End Line: 634

					/* begin block 1.3.4.1.13 */
						// Start line: 644
						// Start offset: 0x0010177C

						/* begin block 1.3.4.1.13.1 */
							// Start line: 648
							// Start offset: 0x001017B0

							/* begin block 1.3.4.1.13.1.1 */
								// Start line: 708
								// Start offset: 0x001019C8
							/* end block 1.3.4.1.13.1.1 */
							// End offset: 0x001019C8
							// End Line: 708
						/* end block 1.3.4.1.13.1 */
						// End offset: 0x001019F4
						// End Line: 711
					/* end block 1.3.4.1.13 */
					// End offset: 0x001019F4
					// End Line: 711

					/* begin block 1.3.4.1.14 */
						// Start line: 714
						// Start offset: 0x001019F4

						/* begin block 1.3.4.1.14.1 */
							// Start line: 715
							// Start offset: 0x00101A14

							/* begin block 1.3.4.1.14.1.1 */
								// Start line: 740
								// Start offset: 0x00101AFC

								/* begin block 1.3.4.1.14.1.1.1 */
									// Start line: 744
									// Start offset: 0x00101B1C

									/* begin block 1.3.4.1.14.1.1.1.1 */
										// Start line: 745
										// Start offset: 0x00101B1C
									/* end block 1.3.4.1.14.1.1.1.1 */
									// End offset: 0x00101B1C
									// End Line: 745
								/* end block 1.3.4.1.14.1.1.1 */
								// End offset: 0x00101B30
								// End Line: 747
							/* end block 1.3.4.1.14.1.1 */
							// End offset: 0x00101B30
							// End Line: 747
						/* end block 1.3.4.1.14.1 */
						// End offset: 0x00101B30
						// End Line: 750
					/* end block 1.3.4.1.14 */
					// End offset: 0x00101B4C
					// End Line: 765

					/* begin block 1.3.4.1.15 */
						// Start line: 765
						// Start offset: 0x00101B4C
					/* end block 1.3.4.1.15 */
					// End offset: 0x00101B4C
					// End Line: 765

					/* begin block 1.3.4.1.16 */
						// Start line: 771
						// Start offset: 0x00101B4C

						/* begin block 1.3.4.1.16.1 */
							// Start line: 775
							// Start offset: 0x00101B8C

							/* begin block 1.3.4.1.16.1.1 */
								// Start line: 776
								// Start offset: 0x00101B8C

								/* begin block 1.3.4.1.16.1.1.1 */
									// Start line: 782
									// Start offset: 0x00101BC0

									/* begin block 1.3.4.1.16.1.1.1.1 */
										// Start line: 786
										// Start offset: 0x00101C04
									/* end block 1.3.4.1.16.1.1.1.1 */
									// End offset: 0x00101C04
									// End Line: 786
								/* end block 1.3.4.1.16.1.1.1 */
								// End offset: 0x00101C0C
								// End Line: 787

								/* begin block 1.3.4.1.16.1.1.2 */
									// Start line: 791
									// Start offset: 0x00101C0C

									/* begin block 1.3.4.1.16.1.1.2.1 */
										// Start line: 797
										// Start offset: 0x00101C50

										/* begin block 1.3.4.1.16.1.1.2.1.1 */
											// Start line: 801
											// Start offset: 0x00101CB4

											/* begin block 1.3.4.1.16.1.1.2.1.1.1 */
												// Start line: 803
												// Start offset: 0x00101CEC
											/* end block 1.3.4.1.16.1.1.2.1.1.1 */
											// End offset: 0x00101CEC
											// End Line: 803
										/* end block 1.3.4.1.16.1.1.2.1.1 */
										// End offset: 0x00101CF4
										// End Line: 804
									/* end block 1.3.4.1.16.1.1.2.1 */
									// End offset: 0x00101CF4
									// End Line: 804
								/* end block 1.3.4.1.16.1.1.2 */
								// End offset: 0x00101CF4
								// End Line: 804
							/* end block 1.3.4.1.16.1.1 */
							// End offset: 0x00101CF4
							// End Line: 804
						/* end block 1.3.4.1.16.1 */
						// End offset: 0x00101CF4
						// End Line: 804
					/* end block 1.3.4.1.16 */
					// End offset: 0x00101CF4
					// End Line: 804

					/* begin block 1.3.4.1.17 */
						// Start line: 837
						// Start offset: 0x00101D38

						/* begin block 1.3.4.1.17.1 */
							// Start line: 838
							// Start offset: 0x00101D40

							/* begin block 1.3.4.1.17.1.1 */
								// Start line: 841
								// Start offset: 0x00101D40
							/* end block 1.3.4.1.17.1.1 */
							// End offset: 0x00101D40
							// End Line: 841
						/* end block 1.3.4.1.17.1 */
						// End offset: 0x00101D58
						// End Line: 843
					/* end block 1.3.4.1.17 */
					// End offset: 0x00101D58
					// End Line: 843

					/* begin block 1.3.4.1.18 */
						// Start line: 872
						// Start offset: 0x00101E94

						/* begin block 1.3.4.1.18.1 */
							// Start line: 873
							// Start offset: 0x00101E9C

							/* begin block 1.3.4.1.18.1.1 */
								// Start line: 874
								// Start offset: 0x00101E9C
							/* end block 1.3.4.1.18.1.1 */
							// End offset: 0x00101E9C
							// End Line: 874
						/* end block 1.3.4.1.18.1 */
						// End offset: 0x00101EB4
						// End Line: 876
					/* end block 1.3.4.1.18 */
					// End offset: 0x00101EB4
					// End Line: 876

					/* begin block 1.3.4.1.19 */
						// Start line: 900
						// Start offset: 0x00101F98
					/* end block 1.3.4.1.19 */
					// End offset: 0x00101F98
					// End Line: 900

					/* begin block 1.3.4.1.20 */
						// Start line: 907
						// Start offset: 0x00101FB0
					/* end block 1.3.4.1.20 */
					// End offset: 0x00101FB0
					// End Line: 907

					/* begin block 1.3.4.1.21 */
						// Start line: 931
						// Start offset: 0x00102104

						/* begin block 1.3.4.1.21.1 */
							// Start line: 932
							// Start offset: 0x0010210C

							/* begin block 1.3.4.1.21.1.1 */
								// Start line: 937
								// Start offset: 0x0010210C
							/* end block 1.3.4.1.21.1.1 */
							// End offset: 0x0010210C
							// End Line: 937
						/* end block 1.3.4.1.21.1 */
						// End offset: 0x00102124
						// End Line: 940

						/* begin block 1.3.4.1.21.2 */
							// Start line: 943
							// Start offset: 0x00102124

							/* begin block 1.3.4.1.21.2.1 */
								// Start line: 943
								// Start offset: 0x00102124

								/* begin block 1.3.4.1.21.2.1.1 */
									// Start line: 944
									// Start offset: 0x0010212C

									/* begin block 1.3.4.1.21.2.1.1.1 */
										// Start line: 946
										// Start offset: 0x0010212C
									/* end block 1.3.4.1.21.2.1.1.1 */
									// End offset: 0x0010212C
									// End Line: 946
								/* end block 1.3.4.1.21.2.1.1 */
								// End offset: 0x00102150
								// End Line: 949
							/* end block 1.3.4.1.21.2.1 */
							// End offset: 0x00102150
							// End Line: 955
						/* end block 1.3.4.1.21.2 */
						// End offset: 0x00102150
						// End Line: 955
					/* end block 1.3.4.1.21 */
					// End offset: 0x00102150
					// End Line: 955

					/* begin block 1.3.4.1.22 */
						// Start line: 955
						// Start offset: 0x00102150
					/* end block 1.3.4.1.22 */
					// End offset: 0x00102150
					// End Line: 955

					/* begin block 1.3.4.1.23 */
						// Start line: 970
						// Start offset: 0x001021B0

						/* begin block 1.3.4.1.23.1 */
							// Start line: 971
							// Start offset: 0x001021B0

							/* begin block 1.3.4.1.23.1.1 */
								// Start line: 973
								// Start offset: 0x001021B0

								/* begin block 1.3.4.1.23.1.1.1 */
									// Start line: 974
									// Start offset: 0x001021D8

									/* begin block 1.3.4.1.23.1.1.1.1 */
										// Start line: 976
										// Start offset: 0x001021D8
									/* end block 1.3.4.1.23.1.1.1.1 */
									// End offset: 0x001021D8
									// End Line: 976

									/* begin block 1.3.4.1.23.1.1.1.2 */
										// Start line: 981
										// Start offset: 0x0010220C
									/* end block 1.3.4.1.23.1.1.1.2 */
									// End offset: 0x0010220C
									// End Line: 981
								/* end block 1.3.4.1.23.1.1.1 */
								// End offset: 0x0010220C
								// End Line: 981
							/* end block 1.3.4.1.23.1.1 */
							// End offset: 0x0010220C
							// End Line: 981
						/* end block 1.3.4.1.23.1 */
						// End offset: 0x001022A8
						// End Line: 997
					/* end block 1.3.4.1.23 */
					// End offset: 0x001022A8
					// End Line: 997

					/* begin block 1.3.4.1.24 */
						// Start line: 1000
						// Start offset: 0x001022A8
					/* end block 1.3.4.1.24 */
					// End offset: 0x001022A8
					// End Line: 1000
				/* end block 1.3.4.1 */
				// End offset: 0x001022A8
				// End Line: 1000
			/* end block 1.3.4 */
			// End offset: 0x001022A8
			// End Line: 1000
		/* end block 1.3 */
		// End offset: 0x001022EC
		// End Line: 1013

		/* begin block 1.4 */
			// Start line: 1030
			// Start offset: 0x00102304
		/* end block 1.4 */
		// End offset: 0x00102304
		// End Line: 1030
	/* end block 1 */
	// End offset: 0x00102364
	// End Line: 1030

	/* begin block 2 */
		// Start line: 66
	/* end block 2 */
	// End Line: 67

uint FUN_MCARD__001005e0(uint param_1,uint param_2,undefined4 param_3,byte *param_4,int param_5,
                        undefined4 param_6,undefined4 param_7)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined2 local_ca70;
  undefined2 local_ca6e;
  undefined2 local_ca6c;
  undefined2 local_ca6a;
  char acStack51816 [280];
  undefined auStack51536 [33408];
  undefined auStack18128 [18064];
  undefined4 uStack64;
  undefined4 uStack60;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  uVar11 = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  if ((param_2 & 8) != 0) {
    local_30 = 9;
  }
  DAT_MCARD__0010ee08 = param_2;
  FUN_MCARD__00102744(param_6,param_7);
  param_4[0x6e] = 0;
  *(undefined *)(param_5 + 0x13) = 0;
  if (*(short *)(param_4 + 0x22) == 0) {
    sprintf(acStack51816,(char *)&PTR_DAT_MCARD__000f3600,param_4 + 1);
    memset(param_4 + 0x22,0,0x40);
    FUN_MCARD__000f512c(param_4 + 0x22,acStack51816);
  }
  if ((DAT_MCARD__0010ee08 & 0x1000) != 0) {
    if (param_1 == 0) {
      return 0;
    }
    DAT_MCARD__0010ee08 = DAT_MCARD__0010ee08 & 0xffffffbf | 0x200;
    iVar8 = *(int *)(param_5 + 0x18);
    puVar7 = (undefined4 *)(param_4 + 0x90);
    puVar5 = (undefined4 *)(iVar8 + 0x80);
    bVar1 = *(byte *)(iVar8 + 3);
    param_4[0x6f] = 0x50;
    param_4[0x68] = 0x50;
    *param_4 = bVar1;
    uVar6 = *(undefined4 *)(iVar8 + 100);
    uVar9 = *(undefined4 *)(iVar8 + 0x68);
    uVar10 = *(undefined4 *)(iVar8 + 0x6c);
    *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(iVar8 + 0x60);
    *(undefined4 *)(param_4 + 0x74) = uVar6;
    *(undefined4 *)(param_4 + 0x78) = uVar9;
    *(undefined4 *)(param_4 + 0x7c) = uVar10;
    uVar6 = *(undefined4 *)(iVar8 + 0x74);
    uVar9 = *(undefined4 *)(iVar8 + 0x78);
    uVar10 = *(undefined4 *)(iVar8 + 0x7c);
    *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(iVar8 + 0x70);
    *(undefined4 *)(param_4 + 0x84) = uVar6;
    *(undefined4 *)(param_4 + 0x88) = uVar9;
    *(undefined4 *)(param_4 + 0x8c) = uVar10;
    if ((((uint)puVar5 | (uint)puVar7) & 3) == 0) {
      do {
        uVar6 = puVar5[1];
        uVar9 = puVar5[2];
        uVar10 = puVar5[3];
        *puVar7 = *puVar5;
        puVar7[1] = uVar6;
        puVar7[2] = uVar9;
        puVar7[3] = uVar10;
        puVar5 = puVar5 + 4;
        puVar7 = puVar7 + 4;
      } while (puVar5 != (undefined4 *)(iVar8 + 0x100U));
    }
    else {
      do {
        uVar6 = puVar5[1];
        uVar9 = puVar5[2];
        uVar10 = puVar5[3];
        *puVar7 = *puVar5;
        puVar7[1] = uVar6;
        puVar7[2] = uVar9;
        puVar7[3] = uVar10;
        puVar5 = puVar5 + 4;
        puVar7 = puVar7 + 4;
      } while (puVar5 != (undefined4 *)(iVar8 + 0x100U));
    }
    puVar5 = (undefined4 *)(iVar8 + 4);
    puVar7 = (undefined4 *)(param_4 + 0x22);
    if ((((uint)puVar5 | (uint)puVar7) & 3) == 0) {
      do {
        uVar9 = puVar5[1];
        uVar10 = puVar5[2];
        uVar6 = puVar5[3];
        *puVar7 = *puVar5;
        puVar7[1] = uVar9;
        puVar7[2] = uVar10;
        puVar7[3] = uVar6;
        puVar5 = puVar5 + 4;
        puVar7 = puVar7 + 4;
      } while (puVar5 != (undefined4 *)(iVar8 + 0x44));
    }
    else {
      do {
        uVar6 = puVar5[1];
        uVar9 = puVar5[2];
        uVar10 = puVar5[3];
        *puVar7 = *puVar5;
        puVar7[1] = uVar6;
        puVar7[2] = uVar9;
        puVar7[3] = uVar10;
        puVar5 = puVar5 + 4;
        puVar7 = puVar7 + 4;
      } while (puVar5 != (undefined4 *)(iVar8 + 0x44));
    }
    *(uint *)(param_4 + 0x110) = (uint)*param_4 * 0x2000 + -0x200;
  }
  FUN_MCARD__000feb70(auStack51536,param_7);
  FUN_MCARD__001004c8(param_3,local_30);
  FUN_MCARD__000f65a8(auStack18128,0,param_4 + 0x114,auStack51536,param_4,local_30,
                      (uint)(param_1 == 1));
  do {
    FUN_MCARD__000fecc0(auStack51536,0);
    if (1 < param_1) {
      FUN_MCARD__000fdad8(auStack18128,2);
      FUN_MCARD__000ffe44(auStack51536,2);
      return param_1;
    }
    local_ca70 = FUN_MCARD__00100158(auStack51536);
    local_ca6e = FUN_MCARD__0010016c(auStack51536);
    local_ca6c = 0x10;
    local_ca6a = 0x10;
    iVar8 = FUN_MCARD__000fff48(auStack51536);
    if ((iVar8 != 0) || (iVar8 = FUN_MCARD__000fff10(auStack51536), iVar8 == 0)) {
      iVar8 = FUN_MCARD__000fff10(auStack51536);
      if (iVar8 == 0) {
        memset(acStack51816,0,0xfa);
        iVar8 = FUN_MCARD__001000d0(auStack51536);
        if (iVar8 == 0) {
          uVar6 = FUN_MCARD__00100214(auStack51536);
          sprintf(acStack51816,DAT_MCARD__0010ed7c,uVar6);
        }
        else {
          uVar6 = FUN_MCARD__00100214(auStack51536);
          sprintf(acStack51816,DAT_MCARD__0010edd8,uVar6);
        }
        do {
          FUN_MCARD__000fecc0(auStack51536,0);
          iVar8 = FUN_MCARD__000fff10(auStack51536);
        } while (iVar8 == 0);
        memcpy(&uStack64,&local_ca70,8);
        FUN_MCARD__000fdf68(auStack18128,uStack64,uStack60);
        FUN_MCARD__000fe040(auStack18128,3);
        FUN_MCARD__000ffea0(auStack51536);
        FUN_MCARD__000ffea0(auStack51536);
      }
      FUN_MCARD__000fff5c(auStack51536);
    }
    FUN_MCARD__000ffea0(auStack51536);
    iVar8 = FUN_MCARD__001003b0(auStack51536,0);
    if ((iVar8 != 0) && (iVar8 = FUN_MCARD__0010042c(auStack51536,0), iVar8 == 0)) {
      FUN_MCARD__000fa174(auStack18128);
      if (param_1 == 1) {
        memset(acStack51816,0,0xfa);
        sprintf(acStack51816,DAT_MCARD__0010ed34);
        uVar3 = FUN_MCARD__000fb304(auStack18128,3,acStack51816,0,0);
        if ((uVar3 & DAT_MCARD__0010ec8a) == 0) {
          iVar8 = FUN_MCARD__001003b0(auStack51536,0);
          if (iVar8 != 0) {
            memset(acStack51816,0,0xfa);
            sprintf(acStack51816,DAT_MCARD__0010ed3c);
            FUN_MCARD__000fb304(auStack18128,7,acStack51816,0,0);
            FUN_MCARD__000fe040(auStack18128,6);
            VSync(0);
            DrawSync(0);
            iVar8 = FUN_MCARD__000ff3c0(auStack51536,0);
            if (iVar8 == 0) {
              do {
                iVar8 = FUN_MCARD__000fa174(auStack18128);
              } while (iVar8 == 0);
LAB_MCARD__00100d84:
              uVar11 = 0xb;
              libcman_CancelSound();
            }
LAB_MCARD__00100d8c:
            FUN_MCARD__000fa174(auStack18128);
          }
        }
        else {
          FUN_MCARD__000fdcbc(auStack18128,5);
          FUN_MCARD__000fe040(auStack18128,0);
          libcman_ConfirmSound();
          FUN_MCARD__000ffea0(auStack51536);
          iVar8 = FUN_MCARD__0010042c(auStack51536,0);
          if (iVar8 == 0) {
            iVar8 = FUN_MCARD__00100460(auStack51536,0);
            if (iVar8 != 0x14) {
              FUN_MCARD__000fb304(auStack18128,4,DAT_MCARD__0010ede0,0,0);
              memset(acStack51816,0,0xfa);
              sprintf(acStack51816,DAT_MCARD__0010ed3c);
              FUN_MCARD__000fb304(auStack18128,7,acStack51816,0,0);
              iVar8 = FUN_MCARD__000ff3c0(auStack51536,0);
              if (iVar8 == 0) {
                do {
                  iVar8 = FUN_MCARD__000fa174(auStack18128);
                } while (iVar8 == 0);
                goto LAB_MCARD__00100d84;
              }
              goto LAB_MCARD__00100d8c;
            }
            iVar8 = 0;
            FUN_MCARD__000fb304(auStack18128,6,DAT_MCARD__0010ed40,0,0);
            while( true ) {
              iVar4 = FUN_MCARD__000feb24(auStack18128);
              uVar11 = 5;
              if (iVar4 * 5 <= iVar8) break;
              VSync(0);
              DrawSync(0);
              iVar8 = iVar8 + 1;
            }
          }
        }
      }
      else {
        memset(acStack51816,0,0xfa);
        sprintf(acStack51816,DAT_MCARD__0010ed3c);
        FUN_MCARD__000fb304(auStack18128,7,acStack51816,0,0);
        iVar8 = FUN_MCARD__000ff3c0(auStack51536,0);
        if (iVar8 == 0) {
          do {
            iVar8 = FUN_MCARD__000fa174(auStack18128);
          } while (iVar8 == 0);
          uVar11 = 0xb;
          libcman_CancelSound();
        }
        FUN_MCARD__000fa174(auStack18128);
      }
    }
    iVar8 = FUN_MCARD__001003b0(auStack51536,0);
    bVar2 = uVar11 < 0xd;
    if (iVar8 == 0) {
      iVar8 = FUN_MCARD__001003b0(auStack51536,1);
      bVar2 = uVar11 < 0xd;
      if (iVar8 == 0) {
        memset(acStack51816,0,0xfa);
        sprintf(acStack51816,DAT_MCARD__0010ed98);
        FUN_MCARD__000fb304(auStack18128,7,acStack51816,0,0);
        iVar8 = FUN_MCARD__000ff6e4(auStack51536);
        bVar2 = uVar11 < 0xd;
        if (iVar8 == 0) {
          do {
            iVar8 = FUN_MCARD__000fa174(auStack18128);
          } while (iVar8 == 0);
          uVar11 = 0xb;
          libcman_CancelSound();
          bVar2 = true;
        }
      }
    }
    if (bVar2) {
                    /* WARNING: Could not recover jumptable at 0x00100eb4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar6 = (**(code **)(uVar11 * 4 + 0xf3610))();
      return uVar6;
    }
    if ((DAT_MCARD__0010ee08 & 0x400) != 0) {
      FUN_MCARD__00100180(auStack51536);
    }
    do {
      iVar8 = FUN_MCARD__000fa174(auStack18128);
    } while (iVar8 == 0);
  } while( true );
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadBackground__FPcT0(char *filename /*$s5*/, char *buffer /*$s2*/)
 // line 1034, offset 0x00102744
	/* begin block 1 */
		// Start line: 1035
		// Start offset: 0x00102744
		// Variables:
	// 		struct RECT rect; // stack offset -40
	// 		int i; // $s0

		/* begin block 1.1 */
			// Start line: 1035
			// Start offset: 0x00102744

			/* begin block 1.1.1 */
				// Start line: 1039
				// Start offset: 0x0010277C
			/* end block 1.1.1 */
			// End offset: 0x0010277C
			// End Line: 1042
		/* end block 1.1 */
		// End offset: 0x001027E8
		// End Line: 1046
	/* end block 1 */
	// End offset: 0x001027E8
	// End Line: 1046

	/* begin block 2 */
		// Start line: 3667
	/* end block 2 */
	// End Line: 3668

void FUN_MCARD__00102744(char *param_1,char *param_2)

{
  int iVar1;
  short sVar2;
  undefined2 local_28;
  short local_26;
  undefined2 local_24;
  undefined2 local_22;
  
  iVar1 = 0;
  sVar2 = 0x100;
  do {
    local_28 = 0;
    local_24 = 0x200;
    local_22 = 0x20;
    local_26 = sVar2;
    LoadfileSeg(param_1,param_2,iVar1 << 0xf,0x8000);
    LoadImage(&local_28,param_2);
    DrawSync(0);
    iVar1 = iVar1 + 1;
    sVar2 = sVar2 + 0x20;
  } while (iVar1 < 8);
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ EnterName__FP3PADP7DISPMANPc(struct PAD *pad /*$fp*/, struct DISPMAN *disp /*stack 4*/, char *username /*stack 8*/)
 // line 1065, offset 0x00102364
	/* begin block 1 */
		// Start line: 1066
		// Start offset: 0x00102364
		// Variables:
	// 		char asciiname[20]; // stack offset -72
	// 		int ret; // stack offset -48
	// 		short padData; // $s5
	// 		short prevData; // $s7
	// 		int so; // $s2
	// 		int co; // $s6
	// 		int delay; // $s3
	// 		char c; // $s1
	// 		char toggle; // stack offset -44
	/* end block 1 */
	// End offset: 0x00102710
	// End Line: 1222

	/* begin block 2 */
		// Start line: 2353
	/* end block 2 */
	// End Line: 2354

	/* begin block 3 */
		// Start line: 2355
	/* end block 3 */
	// End Line: 2356

int FUN_MCARD__00102364(undefined4 param_1,undefined4 param_2,char *param_3)

{
  bool bVar1;
  char cVar2;
  ushort uVar3;
  short sVar4;
  int iVar5;
  size_t sVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  char *pcVar10;
  ushort uVar11;
  uint uVar12;
  char acStack72 [24];
  int local_30;
  uint local_2c;
  
  iVar9 = 0;
  local_30 = 0;
  local_2c = 0;
  FUN_MCARD__000fe150(param_2);
  while( true ) {
    iVar5 = FUN_MCARD__000fecc0(param_1,0);
    if (iVar5 == 0) break;
    VSync(0);
  }
  memset(acStack72,0,0x14);
  strcpy(acStack72,param_3);
  sVar6 = strlen(acStack72);
  uVar12 = 0x26;
  pcVar10 = acStack72 + sVar6;
  uVar11 = 0;
  while (iVar5 = FUN_MCARD__001003b0(param_1,0), iVar5 != 0) {
    FUN_MCARD__000ffea0(param_1);
    uVar3 = FUN_MCARD__000fecc0(param_1,0);
    if ((uVar3 & DAT_MCARD__0010ec8c) != 0) {
      local_30 = 0;
      break;
    }
    if ((uVar3 & (ushort)PTR_LAB_MCARD__00102000_MCARD__0010ec8e) == 0) {
      if ((uVar3 & DAT_MCARD__0010ec94) == 0) {
        if ((uVar3 & DAT_MCARD__0010ec96) == 0) {
          iVar9 = 0;
        }
        else {
          bVar1 = iVar9 == 0;
          iVar9 = iVar9 + -1;
          if (bVar1) {
            iVar9 = 0x14;
            local_2c = 0;
            uVar12 = uVar12 + 1;
            libcman_SelectSound();
            bVar1 = uVar12 < 0x27;
          }
          else {
            bVar1 = uVar12 < 0x27;
            if (iVar9 < 1) {
              iVar9 = 4;
              local_2c = 0;
              uVar12 = uVar12 + 1;
              libcman_SelectSound();
              bVar1 = uVar12 < 0x27;
            }
          }
          if (!bVar1) {
            uVar12 = 0;
          }
        }
      }
      else {
        bVar1 = iVar9 == 0;
        iVar9 = iVar9 + -1;
        if (bVar1) {
          iVar9 = 0x14;
          local_2c = 0;
          uVar12 = uVar12 - 1;
          libcman_SelectSound();
        }
        else {
          if (iVar9 < 1) {
            iVar9 = 4;
            local_2c = 0;
            uVar12 = uVar12 - 1;
            libcman_SelectSound();
          }
        }
        if ((int)uVar12 < 0) {
          uVar12 = 0x26;
        }
      }
    }
    else {
      if (iVar9 == 0) {
        iVar9 = 0x14;
        local_2c = 0;
        uVar12 = 0x26;
        libcman_SelectSound();
      }
    }
    uVar7 = local_2c + 1;
    local_2c = uVar7 & 0xff;
    cVar2 = (&DAT_MCARD__0010ee0c)[uVar12];
    if ((uVar7 & 8) == 0) {
      if (cVar2 == ' ') {
        *pcVar10 = '.';
      }
      else {
        *pcVar10 = cVar2;
      }
    }
    else {
      *pcVar10 = '\0';
    }
    if ((uVar3 & ~uVar11 & DAT_MCARD__0010ec8a) != 0) {
      if (cVar2 == -2) {
        acStack72[sVar6] = '\0';
        local_30 = 1;
        break;
      }
      libcman_SelectSound();
      if (cVar2 == -1) {
        if (0 < (int)sVar6) {
          pcVar10 = pcVar10 + -1;
          sVar6 = sVar6 - 1;
        }
        acStack72[sVar6] = '\0';
        acStack72[sVar6 + 1] = '\0';
      }
      else {
        pcVar8 = acStack72 + sVar6;
        if ((int)sVar6 < 9) {
          pcVar10 = pcVar10 + 1;
          sVar6 = sVar6 + 1;
          *pcVar8 = cVar2;
          acStack72[sVar6] = '\0';
        }
      }
    }
    FUN_MCARD__000fdbec(param_2,acStack72);
    FUN_MCARD__000fa174(param_2);
    uVar11 = uVar3;
  }
  do {
    sVar4 = FUN_MCARD__000fecc0(param_1,0);
    if ((int)sVar4 == 0) break;
    VSync(0);
  } while (((int)sVar4 & (uint)(DAT_MCARD__0010ec8a | DAT_MCARD__0010ec8c)) != 0);
  if (local_30 == 0) {
    libcman_CancelSound();
  }
  else {
    strcpy(param_3,acStack72);
    libcman_ConfirmSound();
  }
  FUN_MCARD__000fe144(param_2);
  FUN_MCARD__000fe040(param_2,6);
  FUN_MCARD__000fa174(param_2);
  return local_30;
}





