#include "THISDUST.H"
#include "SLOT.H"


// decompiled code
// original method signature: 
// struct MCSLOT * /*$ra*/ __6MCSLOTiiiiiiPc(struct MCSLOT *this /*$s0*/, int port /*$a1*/, int card /*$a2*/, int iconX /*$a3*/, int iconY /*stack 16*/, int clutX /*stack 20*/, int clutY /*stack 24*/, char *bufferPtr /*stack 28*/)
 // line 58, offset 0x000f523c
	/* begin block 1 */
		// Start line: 59
		// Start offset: 0x000F523C
	/* end block 1 */
	// End offset: 0x000F52D8
	// End Line: 87

	/* begin block 2 */
		// Start line: 116
	/* end block 2 */
	// End Line: 117

int FUN_MCARD__000f523c(int param_1,uint param_2,uint param_3,undefined4 param_4,undefined4 param_5,
                       undefined4 param_6,undefined4 param_7,int param_8)

{
  param_2 = param_2 & 1;
  param_3 = param_3 & 3;
  *(uint *)(&DAT_000040bc + param_1) = param_2;
  *(uint *)(&DAT_000040c0 + param_1) = param_3;
  *(undefined4 *)(&DAT_000040f4 + param_1) = param_4;
  *(uint *)(&DAT_000040c4 + param_1) = param_2 * 0x10 + param_3;
  *(undefined4 *)(&DAT_000040f8 + param_1) = param_5;
  *(undefined4 *)(&DAT_000040fc + param_1) = param_6;
  *(undefined4 *)(&DAT_00004100 + param_1) = param_7;
  sprintf((char *)(param_1 + 0x40c8),s_bu_d_d__MCARD__000f3000,param_2,param_3);
  if (param_8 != 0) {
    DAT_MCARD__0010eb6c = param_8;
  }
  FUN_MCARD__000f5668(param_1);
  DAT_MCARD__0010eb40 = DAT_MCARD__0010eb40 + 1;
  if (DAT_MCARD__0010eb40 == 1) {
    FUN_MCARD__000f3644(param_1);
  }
  return param_1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ card_start__6MCSLOT(struct MCSLOT *this /*$a0*/)
 // line 99, offset 0x000f3644
	/* begin block 1 */
		// Start line: 100
		// Start offset: 0x000F3644
	/* end block 1 */
	// End offset: 0x000F3828
	// End Line: 138

	/* begin block 2 */
		// Start line: 198
	/* end block 2 */
	// End Line: 199

	/* begin block 3 */
		// Start line: 200
	/* end block 3 */
	// End Line: 201

void FUN_MCARD__000f3644(void)

{
  EnterCriticalSection();
  DAT_MCARD__0010eb44 = OpenEvent(0xf4000001,4,0x2000,0);
  DAT_MCARD__0010eb48 = OpenEvent(0xf4000001,0x8000,0x2000,0);
  DAT_MCARD__0010eb4c = OpenEvent(0xf4000001,0x100,0x2000,0);
  DAT_MCARD__0010eb50 = OpenEvent(0xf4000001,0x2000,0x2000,0);
  DAT_MCARD__0010eb54 = OpenEvent(0xf0000011,4,0x2000,0);
  DAT_MCARD__0010eb58 = OpenEvent(0xf0000011,0x8000,0x2000,0);
  DAT_MCARD__0010eb5c = OpenEvent(0xf0000011,0x100,0x2000,0);
  DAT_MCARD__0010eb60 = OpenEvent(0xf0000011,0x2000,0x2000,0);
  ExitCriticalSection();
  EnableEvent(DAT_MCARD__0010eb44);
  EnableEvent(DAT_MCARD__0010eb48);
  EnableEvent(DAT_MCARD__0010eb4c);
  EnableEvent(DAT_MCARD__0010eb50);
  EnableEvent(DAT_MCARD__0010eb54);
  EnableEvent(DAT_MCARD__0010eb58);
  EnableEvent(DAT_MCARD__0010eb5c);
  EnableEvent(DAT_MCARD__0010eb60);
  StopCARD();
  InitCARD(0);
  StartCARD();
  _bu_init();
  VSync(0);
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ _._6MCSLOT(struct MCSLOT *this /*$s0*/, int __in_chrg /*$s1*/)
 // line 159, offset 0x000f52f0
	/* begin block 1 */
		// Start line: 160
		// Start offset: 0x000F52F0
	/* end block 1 */
	// End offset: 0x000F5324
	// End Line: 170

	/* begin block 2 */
		// Start line: 2770
	/* end block 2 */
	// End Line: 2771

	/* begin block 3 */
		// Start line: 2775
	/* end block 3 */
	// End Line: 2776

void FUN_MCARD__000f52f0(undefined4 param_1,uint param_2)

{
  DAT_MCARD__0010eb40 = DAT_MCARD__0010eb40 + -1;
  if (DAT_MCARD__0010eb40 == 0) {
    FUN_MCARD__000f534c();
  }
  if ((param_2 & 1) != 0) {
    __builtin_delete(param_1);
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ card_stop__6MCSLOT(struct MCSLOT *this /*$a0*/)
 // line 193, offset 0x000f534c
	/* begin block 1 */
		// Start line: 194
		// Start offset: 0x000F534C
	/* end block 1 */
	// End offset: 0x000F5474
	// End Line: 218

	/* begin block 2 */
		// Start line: 2848
	/* end block 2 */
	// End Line: 2849

	/* begin block 3 */
		// Start line: 2850
	/* end block 3 */
	// End Line: 2851

void FUN_MCARD__000f534c(void)

{
  DisableEvent(DAT_MCARD__0010eb44);
  DisableEvent(DAT_MCARD__0010eb48);
  DisableEvent(DAT_MCARD__0010eb4c);
  DisableEvent(DAT_MCARD__0010eb50);
  DisableEvent(DAT_MCARD__0010eb54);
  DisableEvent(DAT_MCARD__0010eb58);
  DisableEvent(DAT_MCARD__0010eb5c);
  DisableEvent(DAT_MCARD__0010eb60);
  EnterCriticalSection();
  CloseEvent(DAT_MCARD__0010eb44);
  CloseEvent(DAT_MCARD__0010eb48);
  CloseEvent(DAT_MCARD__0010eb4c);
  CloseEvent(DAT_MCARD__0010eb50);
  CloseEvent(DAT_MCARD__0010eb54);
  CloseEvent(DAT_MCARD__0010eb58);
  CloseEvent(DAT_MCARD__0010eb5c);
  CloseEvent(DAT_MCARD__0010eb60);
  ExitCriticalSection();
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckCard__6MCSLOT(struct MCSLOT *this /*$s0*/)
 // line 235, offset 0x000f5474
	/* begin block 1 */
		// Start line: 236
		// Start offset: 0x000F5474
		// Variables:
	// 		int card_status; // $v1

		/* begin block 1.1 */
			// Start line: 236
			// Start offset: 0x000F5474

			/* begin block 1.1.1 */
				// Start line: 248
				// Start offset: 0x000F54C0
			/* end block 1.1.1 */
			// End offset: 0x000F555C
			// End Line: 299
		/* end block 1.1 */
		// End offset: 0x000F555C
		// End Line: 299
	/* end block 1 */
	// End offset: 0x000F555C
	// End Line: 299

	/* begin block 2 */
		// Start line: 2932
	/* end block 2 */
	// End Line: 2933

undefined4 FUN_MCARD__000f5474(int param_1)

{
  int iVar1;
  
  _card_wait(*(undefined4 *)(&DAT_000040bc + param_1));
  func_0x000991d0(*(undefined4 *)(&DAT_000040c4 + param_1));
  iVar1 = FUN_MCARD__000f555c(param_1,0x50000);
  if (iVar1 != 0x14) {
    if (iVar1 != 0x17) goto LAB_MCARD__000f5534;
    FUN_MCARD__000f5610(param_1);
    _card_clear(*(undefined4 *)(&DAT_000040c4 + param_1));
    _card_wait(*(undefined4 *)(&DAT_000040bc + param_1));
    FUN_MCARD__000f5668(param_1);
  }
  FUN_MCARD__000f5610(param_1);
  func_0x000991e0(*(undefined4 *)(&DAT_000040c4 + param_1));
  iVar1 = FUN_MCARD__000f555c(param_1,0x50000);
  if (iVar1 == 0x14) {
    return 0x14;
  }
  if (iVar1 == 0x17) {
    FUN_MCARD__000f5668(param_1);
    return 0x18;
  }
LAB_MCARD__000f5534:
  FUN_MCARD__000f5668(param_1);
  FUN_MCARD__000f5610(param_1);
  return 0x19;
}



// decompiled code
// original method signature: 
// int /*$ra*/ card_event__6MCSLOTi(struct MCSLOT *this /*$a0*/, int timeout /*$s0*/)
 // line 311, offset 0x000f555c
	/* begin block 1 */
		// Start line: 312
		// Start offset: 0x000F555C

		/* begin block 1.1 */
			// Start line: 316
			// Start offset: 0x000F5584

			/* begin block 1.1.1 */
				// Start line: 318
				// Start offset: 0x000F5584
			/* end block 1.1.1 */
			// End offset: 0x000F55A4
			// End Line: 318

			/* begin block 1.1.2 */
				// Start line: 320
				// Start offset: 0x000F55A4
			/* end block 1.1.2 */
			// End offset: 0x000F55C0
			// End Line: 320

			/* begin block 1.1.3 */
				// Start line: 322
				// Start offset: 0x000F55C0
			/* end block 1.1.3 */
			// End offset: 0x000F55D4
			// End Line: 322

			/* begin block 1.1.4 */
				// Start line: 324
				// Start offset: 0x000F55D4
			/* end block 1.1.4 */
			// End offset: 0x000F55F0
			// End Line: 324
		/* end block 1.1 */
		// End offset: 0x000F55F0
		// End Line: 324
	/* end block 1 */
	// End offset: 0x000F5610
	// End Line: 327

	/* begin block 2 */
		// Start line: 3084
	/* end block 2 */
	// End Line: 3085

undefined4 FUN_MCARD__000f555c(undefined4 param_1,int param_2)

{
  int iVar1;
  
  VSync(0);
  param_2 = param_2 + -1;
  while( true ) {
    if (param_2 < 1) {
      return 0x16;
    }
    iVar1 = TestEvent(DAT_MCARD__0010eb44);
    if (iVar1 == 1) {
      return 0x14;
    }
    iVar1 = TestEvent(DAT_MCARD__0010eb48);
    if (iVar1 == 1) {
      return 0xffffffff;
    }
    iVar1 = TestEvent(DAT_MCARD__0010eb4c);
    if (iVar1 == 1) break;
    iVar1 = TestEvent(DAT_MCARD__0010eb50);
    param_2 = param_2 + -1;
    if (iVar1 == 1) {
      return 0x17;
    }
  }
  return 0x16;
}



// decompiled code
// original method signature: 
// void /*$ra*/ clear_event__6MCSLOT(struct MCSLOT *this /*$a0*/)
 // line 332, offset 0x000f5610
	/* begin block 1 */
		// Start line: 333
		// Start offset: 0x000F5610
	/* end block 1 */
	// End offset: 0x000F5668
	// End Line: 337

	/* begin block 2 */
		// Start line: 3127
	/* end block 2 */
	// End Line: 3128

	/* begin block 3 */
		// Start line: 3128
	/* end block 3 */
	// End Line: 3129

void FUN_MCARD__000f5610(void)

{
  TestEvent(DAT_MCARD__0010eb44);
  TestEvent(DAT_MCARD__0010eb48);
  TestEvent(DAT_MCARD__0010eb4c);
  TestEvent(DAT_MCARD__0010eb50);
  return;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ CardRemoved__6MCSLOT(struct MCSLOT *this /*$s6*/)
 // line 383, offset 0x000f3828
	/* begin block 1 */
		// Start line: 384
		// Start offset: 0x000F3828
		// Variables:
	// 		int card_status; // $v0

		/* begin block 1.1 */
			// Start line: 384
			// Start offset: 0x000F3828
			// Variables:
		// 		struct MCSLOT *this; // $s6
		// 		int timeout; // $s0

			/* begin block 1.1.1 */
				// Start line: 384
				// Start offset: 0x000F3828

				/* begin block 1.1.1.1 */
					// Start line: 384
					// Start offset: 0x000F387C

					/* begin block 1.1.1.1.1 */
						// Start line: 384
						// Start offset: 0x000F387C
					/* end block 1.1.1.1.1 */
					// End offset: 0x000F3890
					// End Line: 384

					/* begin block 1.1.1.1.2 */
						// Start line: 384
						// Start offset: 0x000F3890
					/* end block 1.1.1.1.2 */
					// End offset: 0x000F38A4
					// End Line: 384

					/* begin block 1.1.1.1.3 */
						// Start line: 384
						// Start offset: 0x000F38A4
					/* end block 1.1.1.1.3 */
					// End offset: 0x000F38B8
					// End Line: 384

					/* begin block 1.1.1.1.4 */
						// Start line: 384
						// Start offset: 0x000F38B8
					/* end block 1.1.1.1.4 */
					// End offset: 0x000F38CC
					// End Line: 384
				/* end block 1.1.1.1 */
				// End offset: 0x000F38CC
				// End Line: 384
			/* end block 1.1.1 */
			// End offset: 0x000F38D4
			// End Line: 384
		/* end block 1.1 */
		// End offset: 0x000F38D4
		// End Line: 384

		/* begin block 1.2 */
			// Start line: 394
			// Start offset: 0x000F38D4

			/* begin block 1.2.1 */
				// Start line: 394
				// Start offset: 0x000F38E4

				/* begin block 1.2.1.1 */
					// Start line: 394
					// Start offset: 0x000F38E4
					// Variables:
				// 		struct MCSLOT *this; // $s6

					/* begin block 1.2.1.1.1 */
						// Start line: 394
						// Start offset: 0x000F38E4
					/* end block 1.2.1.1.1 */
					// End offset: 0x000F38E4
					// End Line: 394
				/* end block 1.2.1.1 */
				// End offset: 0x000F38E4
				// End Line: 394
			/* end block 1.2.1 */
			// End offset: 0x000F3924
			// End Line: 407
		/* end block 1.2 */
		// End offset: 0x000F3924
		// End Line: 407

		/* begin block 1.3 */
			// Start line: 407
			// Start offset: 0x000F3924
			// Variables:
		// 		struct MCSLOT *this; // $s6

			/* begin block 1.3.1 */
				// Start line: 407
				// Start offset: 0x000F3924
			/* end block 1.3.1 */
			// End offset: 0x000F3924
			// End Line: 407
		/* end block 1.3 */
		// End offset: 0x000F3924
		// End Line: 407
	/* end block 1 */
	// End offset: 0x000F3994
	// End Line: 407

	/* begin block 2 */
		// Start line: 775
	/* end block 2 */
	// End Line: 776

uint FUN_MCARD__000f3828(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0x4ffff;
  func_0x000991d0(*(undefined4 *)(&DAT_000040c4 + param_1));
  VSync(0);
  do {
    iVar2 = TestEvent(DAT_MCARD__0010eb44);
    iVar3 = 0x14;
    if (iVar2 == 1) break;
    iVar2 = TestEvent(DAT_MCARD__0010eb48);
    iVar3 = -1;
    if (iVar2 == 1) break;
    iVar2 = TestEvent(DAT_MCARD__0010eb4c);
    iVar3 = 0x16;
    if (iVar2 == 1) break;
    iVar2 = TestEvent(DAT_MCARD__0010eb50);
    iVar4 = iVar4 + -1;
    if (iVar2 == 1) {
      iVar3 = 0x17;
      break;
    }
    iVar3 = 0x16;
  } while (0 < iVar4);
  bVar1 = 1 < iVar3 - 0x14U;
  if (bVar1) {
    TestEvent(DAT_MCARD__0010eb44);
    TestEvent(DAT_MCARD__0010eb48);
    TestEvent(DAT_MCARD__0010eb4c);
    TestEvent(DAT_MCARD__0010eb50);
    _card_clear(*(undefined4 *)(&DAT_000040c4 + param_1));
    FUN_MCARD__000f5668(param_1);
  }
  else {
    TestEvent(DAT_MCARD__0010eb44);
    TestEvent(DAT_MCARD__0010eb48);
    TestEvent(DAT_MCARD__0010eb4c);
    TestEvent(DAT_MCARD__0010eb50);
  }
  return (uint)bVar1;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ CardInserted__6MCSLOT(struct MCSLOT *this /*$s6*/)
 // line 418, offset 0x000f3994
	/* begin block 1 */
		// Start line: 419
		// Start offset: 0x000F3994
		// Variables:
	// 		int card_status; // $v1

		/* begin block 1.1 */
			// Start line: 419
			// Start offset: 0x000F3994
			// Variables:
		// 		struct MCSLOT *this; // $s6
		// 		int timeout; // $s0

			/* begin block 1.1.1 */
				// Start line: 419
				// Start offset: 0x000F3994

				/* begin block 1.1.1.1 */
					// Start line: 419
					// Start offset: 0x000F39E8

					/* begin block 1.1.1.1.1 */
						// Start line: 419
						// Start offset: 0x000F39E8
					/* end block 1.1.1.1.1 */
					// End offset: 0x000F39FC
					// End Line: 419

					/* begin block 1.1.1.1.2 */
						// Start line: 419
						// Start offset: 0x000F39FC
					/* end block 1.1.1.1.2 */
					// End offset: 0x000F3A10
					// End Line: 419

					/* begin block 1.1.1.1.3 */
						// Start line: 419
						// Start offset: 0x000F3A10
					/* end block 1.1.1.1.3 */
					// End offset: 0x000F3A24
					// End Line: 419

					/* begin block 1.1.1.1.4 */
						// Start line: 419
						// Start offset: 0x000F3A24
					/* end block 1.1.1.1.4 */
					// End offset: 0x000F3A38
					// End Line: 419
				/* end block 1.1.1.1 */
				// End offset: 0x000F3A38
				// End Line: 419
			/* end block 1.1.1 */
			// End offset: 0x000F3A40
			// End Line: 419
		/* end block 1.1 */
		// End offset: 0x000F3A40
		// End Line: 419

		/* begin block 1.2 */
			// Start line: 429
			// Start offset: 0x000F3A40

			/* begin block 1.2.1 */
				// Start line: 430
				// Start offset: 0x000F3A54

				/* begin block 1.2.1.1 */
					// Start line: 419
					// Start offset: 0x000F3A54
					// Variables:
				// 		struct MCSLOT *this; // $s6

					/* begin block 1.2.1.1.1 */
						// Start line: 419
						// Start offset: 0x000F3A54
					/* end block 1.2.1.1.1 */
					// End offset: 0x000F3A54
					// End Line: 419
				/* end block 1.2.1.1 */
				// End offset: 0x000F3A54
				// End Line: 419
			/* end block 1.2.1 */
			// End offset: 0x000F3AA8
			// End Line: 437
		/* end block 1.2 */
		// End offset: 0x000F3AA8
		// End Line: 437

		/* begin block 1.3 */
			// Start line: 419
			// Start offset: 0x000F3AA8
			// Variables:
		// 		struct MCSLOT *this; // $s6

			/* begin block 1.3.1 */
				// Start line: 419
				// Start offset: 0x000F3AA8
			/* end block 1.3.1 */
			// End offset: 0x000F3AA8
			// End Line: 419
		/* end block 1.3 */
		// End offset: 0x000F3AA8
		// End Line: 419
	/* end block 1 */
	// End offset: 0x000F3B04
	// End Line: 442

	/* begin block 2 */
		// Start line: 843
	/* end block 2 */
	// End Line: 844

	/* begin block 3 */
		// Start line: 855
	/* end block 3 */
	// End Line: 856

undefined4 FUN_MCARD__000f3994(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0x4ffff;
  func_0x000991d0(*(undefined4 *)(&DAT_000040c4 + param_1));
  VSync(0);
  do {
    iVar1 = TestEvent(DAT_MCARD__0010eb44);
    iVar3 = 0x14;
    if (iVar1 == 1) break;
    iVar1 = TestEvent(DAT_MCARD__0010eb48);
    iVar3 = -1;
    if (iVar1 == 1) break;
    iVar1 = TestEvent(DAT_MCARD__0010eb4c);
    iVar3 = 0x16;
    if (iVar1 == 1) break;
    iVar1 = TestEvent(DAT_MCARD__0010eb50);
    iVar4 = iVar4 + -1;
    if (iVar1 == 1) {
      iVar3 = 0x17;
      break;
    }
    iVar3 = 0x16;
  } while (0 < iVar4);
  if ((iVar3 == 0x17) || (iVar3 == 0x14)) {
    TestEvent(DAT_MCARD__0010eb44);
    TestEvent(DAT_MCARD__0010eb48);
    TestEvent(DAT_MCARD__0010eb4c);
    TestEvent(DAT_MCARD__0010eb50);
    _card_clear(*(undefined4 *)(&DAT_000040c4 + param_1));
    FUN_MCARD__000f5668(param_1);
    uVar2 = 1;
  }
  else {
    TestEvent(DAT_MCARD__0010eb44);
    TestEvent(DAT_MCARD__0010eb48);
    TestEvent(DAT_MCARD__0010eb4c);
    TestEvent(DAT_MCARD__0010eb50);
    uVar2 = 0;
  }
  return uVar2;
}



// decompiled code
// original method signature: 
// int /*$ra*/ FormatCard__6MCSLOT(struct MCSLOT *this /*$s2*/)
 // line 489, offset 0x000f3b04
	/* begin block 1 */
		// Start line: 490
		// Start offset: 0x000F3B04
		// Variables:
	// 		char buffer[128]; // stack offset -160

		/* begin block 1.1 */
			// Start line: 490
			// Start offset: 0x000F3B04
			// Variables:
		// 		struct MCSLOT *this; // $s2

			/* begin block 1.1.1 */
				// Start line: 490
				// Start offset: 0x000F3B04
			/* end block 1.1.1 */
			// End offset: 0x000F3B04
			// End Line: 490
		/* end block 1.1 */
		// End offset: 0x000F3B04
		// End Line: 490

		/* begin block 1.2 */
			// Start line: 490
			// Start offset: 0x000F3B04

			/* begin block 1.2.1 */
				// Start line: 490
				// Start offset: 0x000F3B04
				// Variables:
			// 		struct MCSLOT *this; // $s2
			// 		int timeout; // $s3

				/* begin block 1.2.1.1 */
					// Start line: 490
					// Start offset: 0x000F3B04

					/* begin block 1.2.1.1.1 */
						// Start line: 490
						// Start offset: 0x000F3BB4

						/* begin block 1.2.1.1.1.1 */
							// Start line: 490
							// Start offset: 0x000F3BB4
						/* end block 1.2.1.1.1.1 */
						// End offset: 0x000F3BC8
						// End Line: 490

						/* begin block 1.2.1.1.1.2 */
							// Start line: 490
							// Start offset: 0x000F3BC8
						/* end block 1.2.1.1.1.2 */
						// End offset: 0x000F3BDC
						// End Line: 490

						/* begin block 1.2.1.1.1.3 */
							// Start line: 490
							// Start offset: 0x000F3BDC
						/* end block 1.2.1.1.1.3 */
						// End offset: 0x000F3BF0
						// End Line: 490

						/* begin block 1.2.1.1.1.4 */
							// Start line: 490
							// Start offset: 0x000F3BF0
						/* end block 1.2.1.1.1.4 */
						// End offset: 0x000F3C04
						// End Line: 490
					/* end block 1.2.1.1.1 */
					// End offset: 0x000F3C04
					// End Line: 490
				/* end block 1.2.1.1 */
				// End offset: 0x000F3C0C
				// End Line: 490
			/* end block 1.2.1 */
			// End offset: 0x000F3C0C
			// End Line: 490
		/* end block 1.2 */
		// End offset: 0x000F3C28
		// End Line: 504
	/* end block 1 */
	// End offset: 0x000F3C74
	// End Line: 509

	/* begin block 2 */
		// Start line: 997
	/* end block 2 */
	// End Line: 998

undefined4 FUN_MCARD__000f3b04(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  char local_a0;
  char local_9f;
  
  format(param_1 + 0x40c8);
  FUN_MCARD__000f5668(param_1);
  bzero(&local_a0,0x80);
  iVar4 = 0x4ffff;
  TestEvent(DAT_MCARD__0010eb54);
  TestEvent(DAT_MCARD__0010eb58);
  TestEvent(DAT_MCARD__0010eb5c);
  TestEvent(DAT_MCARD__0010eb60);
  _new_card();
  _card_read(*(undefined4 *)(&DAT_000040c4 + param_1),0,&local_a0);
  VSync(0);
  do {
    iVar1 = TestEvent(DAT_MCARD__0010eb54);
    iVar3 = 0x14;
    if (iVar1 == 1) break;
    iVar1 = TestEvent(DAT_MCARD__0010eb58);
    iVar3 = -1;
    if (iVar1 == 1) break;
    iVar1 = TestEvent(DAT_MCARD__0010eb5c);
    iVar3 = 0x16;
    if (iVar1 == 1) break;
    iVar1 = TestEvent(DAT_MCARD__0010eb60);
    iVar4 = iVar4 + -1;
    if (iVar1 == 1) {
      iVar3 = 0x17;
      break;
    }
    iVar3 = 0x16;
  } while (0 < iVar4);
  uVar2 = 0xffffffff;
  if (((iVar3 == 0x14) && (uVar2 = 0xffffffff, local_a0 == 'M')) && (uVar2 = 0x14, local_9f != 'C'))
  {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReadCardDir__6MCSLOT(struct MCSLOT *this /*$s3*/)
 // line 520, offset 0x000f3c74
	/* begin block 1 */
		// Start line: 521
		// Start offset: 0x000F3C74
		// Variables:
	// 		long size; // $a1
	// 		char path[7]; // stack offset -48
	// 		struct DIRENTRY *entryPtr; // $s0

		/* begin block 1.1 */
			// Start line: 537
			// Start offset: 0x000F3CF4
		/* end block 1.1 */
		// End offset: 0x000F3D6C
		// End Line: 560
	/* end block 1 */
	// End offset: 0x000F3D8C
	// End Line: 569

	/* begin block 2 */
		// Start line: 1062
	/* end block 2 */
	// End Line: 1063

void FUN_MCARD__000f3c74(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  char acStack48 [8];
  
  if (param_1[0x102d] == 0) {
    *param_1 = 0;
    sprintf(acStack48,(char *)&PTR_DAT_MCARD__000f3008,param_1 + 0x1032);
    iVar1 = firstfile(acStack48,param_1 + 5);
    if (iVar1 != 0) {
      iVar7 = 0;
      piVar6 = param_1 + 0x119;
      piVar5 = param_1 + 3;
      iVar8 = 0;
      do {
        iVar8 = iVar8 + 0x450;
        iVar7 = iVar7 + 0x450;
        iVar2 = *param_1;
        iVar1 = *(int *)(iVar1 + 0x18) >> 0xd;
        *param_1 = iVar2 + iVar1;
        piVar5[-1] = iVar2 + iVar1;
        *piVar5 = iVar1;
        piVar5 = piVar5 + 0x114;
        if (1 < iVar1) {
          puVar4 = (undefined4 *)(iVar7 + (int)(param_1 + 3));
          piVar3 = (int *)((int)param_1 + iVar8 + 0x458);
          do {
            iVar1 = iVar1 + -1;
            piVar6 = piVar6 + 0x114;
            piVar5 = piVar5 + 0x114;
            iVar8 = iVar8 + 0x450;
            iVar7 = iVar7 + 0x450;
            *piVar3 = *param_1;
            *puVar4 = 0;
            puVar4 = puVar4 + 0x114;
            piVar3 = piVar3 + 0x114;
          } while (1 < iVar1);
        }
        iVar1 = nextfile(piVar6);
        piVar6 = piVar6 + 0x114;
        iVar8 = iVar8;
      } while (iVar1 != 0);
    }
    param_1[0x102d] = 1;
    param_1[0x1034] = 0;
  }
  return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ invalidate_info__6MCSLOT(struct MCSLOT *this /*$s0*/)
 // line 579, offset 0x000f5668
	/* begin block 1 */
		// Start line: 580
		// Start offset: 0x000F5668

		/* begin block 1.1 */
			// Start line: 580
			// Start offset: 0x000F5668
			// Variables:
		// 		int n; // $v1
		/* end block 1.1 */
		// End offset: 0x000F56A8
		// End Line: 590

		/* begin block 1.2 */
			// Start line: 593
			// Start offset: 0x000F56A8

			/* begin block 1.2.1 */
				// Start line: 594
				// Start offset: 0x000F56B8
			/* end block 1.2.1 */
			// End offset: 0x000F56C8
			// End Line: 596
		/* end block 1.2 */
		// End offset: 0x000F56C8
		// End Line: 596

		/* begin block 1.3 */
			// Start line: 599
			// Start offset: 0x000F56C8

			/* begin block 1.3.1 */
				// Start line: 600
				// Start offset: 0x000F56D8
			/* end block 1.3.1 */
			// End offset: 0x000F56E8
			// End Line: 602
		/* end block 1.3 */
		// End offset: 0x000F56E8
		// End Line: 602
	/* end block 1 */
	// End offset: 0x000F56E8
	// End Line: 602

	/* begin block 2 */
		// Start line: 3621
	/* end block 2 */
	// End Line: 3622

	/* begin block 3 */
		// Start line: 3626
	/* end block 3 */
	// End Line: 3627

void FUN_MCARD__000f5668(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(param_1 + 0x248);
  iVar2 = 0xe;
  *(undefined4 *)(&DAT_000040b4 + param_1) = 0;
  *(undefined4 *)(&DAT_000040b8 + param_1) = 0;
  do {
    puVar1[-0x91] = 0;
    puVar1[-0x8f] = 0xffffffff;
    *puVar1 = 0;
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + 0x114;
  } while (-1 < iVar2);
  if (*(int *)(&DAT_000040d8 + param_1) != -2) {
    close(*(int *)(&DAT_000040d4 + param_1));
    *(undefined4 *)(&DAT_000040d8 + param_1) = 0xfffffffe;
  }
  if (*(int *)(&DAT_000040e8 + param_1) != -2) {
    close(*(int *)(&DAT_000040e4 + param_1));
    *(undefined4 *)(&DAT_000040e8 + param_1) = 0xfffffffe;
  }
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ ReadCardInfo__6MCSLOTPc(struct MCSLOT *this /*$s1*/, char *managerFilename /*$s0*/)
 // line 618, offset 0x000f3db8
	/* begin block 1 */
		// Start line: 619
		// Start offset: 0x000F3DB8
		// Variables:
	// 		int i; // $a2
	// 		int n; // $s0
	// 		char filename[32]; // stack offset -64
	// 		int filePtr; // $s2

		/* begin block 1.1 */
			// Start line: 629
			// Start offset: 0x000F3DF4

			/* begin block 1.1.1 */
				// Start line: 630
				// Start offset: 0x000F3E0C

				/* begin block 1.1.1.1 */
					// Start line: 631
					// Start offset: 0x000F3E0C

					/* begin block 1.1.1.1.1 */
						// Start line: 632
						// Start offset: 0x000F3E38

						/* begin block 1.1.1.1.1.1 */
							// Start line: 634
							// Start offset: 0x000F3E38

							/* begin block 1.1.1.1.1.1.1 */
								// Start line: 639
								// Start offset: 0x000F3E70
							/* end block 1.1.1.1.1.1.1 */
							// End offset: 0x000F3EB0
							// End Line: 642
						/* end block 1.1.1.1.1.1 */
						// End offset: 0x000F3EB0
						// End Line: 644

						/* begin block 1.1.1.1.1.2 */
							// Start line: 648
							// Start offset: 0x000F3EB0

							/* begin block 1.1.1.1.1.2.1 */
								// Start line: 649
								// Start offset: 0x000F3ED4

								/* begin block 1.1.1.1.1.2.1.1 */
									// Start line: 650
									// Start offset: 0x000F3ED4

									/* begin block 1.1.1.1.1.2.1.1.1 */
										// Start line: 653
										// Start offset: 0x000F3F4C

										/* begin block 1.1.1.1.1.2.1.1.1.1 */
											// Start line: 655
											// Start offset: 0x000F3F4C
										/* end block 1.1.1.1.1.2.1.1.1.1 */
										// End offset: 0x000F3F88
										// End Line: 655
									/* end block 1.1.1.1.1.2.1.1.1 */
									// End offset: 0x000F4060
									// End Line: 672
								/* end block 1.1.1.1.1.2.1.1 */
								// End offset: 0x000F4094
								// End Line: 673
							/* end block 1.1.1.1.1.2.1 */
							// End offset: 0x000F4094
							// End Line: 675
						/* end block 1.1.1.1.1.2 */
						// End offset: 0x000F40E4
						// End Line: 679
					/* end block 1.1.1.1.1 */
					// End offset: 0x000F4130
					// End Line: 686
				/* end block 1.1.1.1 */
				// End offset: 0x000F4130
				// End Line: 686
			/* end block 1.1.1 */
			// End offset: 0x000F4130
			// End Line: 691
		/* end block 1.1 */
		// End offset: 0x000F4168
		// End Line: 697
	/* end block 1 */
	// End offset: 0x000F41A0
	// End Line: 700

	/* begin block 2 */
		// Start line: 1275
	/* end block 2 */
	// End Line: 1276

int FUN_MCARD__000f3db8(int *param_1,char *param_2)

{
  ssize_t sVar1;
  int iVar2;
  int __fd;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  char acStack64 [5];
  char acStack59 [16];
  char local_2b;
  
  if (param_1[0x102d] == 0) {
    FUN_MCARD__000f3c74();
  }
  __fd = param_1[0x1034];
  if (*param_1 <= __fd) {
    param_1[0x102e] = 1;
    return 0x14;
  }
  piVar3 = param_1 + 3;
  if (piVar3[__fd * 0x114] < 1) {
LAB_MCARD__000f4130:
    param_1[param_1[0x1034] * 0x114 + 1] = 1;
    __fd = param_1[0x1034];
    param_1[0x1034] = __fd + 1;
  }
  else {
    sprintf(acStack64,&DAT_MCARD__000f300c,param_1 + 0x1032,param_1 + __fd * 0x114 + 5);
    __fd = open(acStack64,1);
    if (-1 < __fd) {
      sVar1 = read(__fd,param_1 + param_1[0x1034] * 0x114 + 0xf,0x200);
      if (sVar1 == 0x200) {
        iVar2 = strncmp(acStack59,param_2,0x11);
        if ((iVar2 == 0) && (piVar5 = param_1 + 0x93, local_2b != 'P')) {
          piVar4 = param_1 + 0x94;
          piVar5[param_1[0x1034] * 0x114] = 0;
          iVar2 = 0;
          piVar4[param_1[0x1034] * 0x114] = 0;
          iVar6 = param_1[0x1034];
          if (0 < piVar3[iVar6 * 0x114]) {
            do {
              sVar1 = read(__fd,param_1 + (iVar6 + iVar2) * 0x114 + 0x95,0x200);
              iVar6 = 0;
              if (sVar1 != 0x200) goto LAB_MCARD__000f3ea8;
              iVar7 = iVar2 + 1;
              do {
                if (0 < param_1[(param_1[0x1034] + iVar2) * 0x114 + iVar6 * 8 + 0x95]) {
                  piVar5[param_1[0x1034] * 0x114] = piVar5[param_1[0x1034] * 0x114] + 1;
                  if (*(char *)((int)param_1 +
                               iVar6 * 0x20 + (param_1[0x1034] + iVar2) * 0x450 + 0x26f) != '\0') {
                    piVar4[param_1[0x1034] * 0x114] = piVar4[param_1[0x1034] * 0x114] + 1;
                  }
                }
                iVar6 = iVar6 + 1;
              } while (iVar6 < 0x10);
              iVar6 = param_1[0x1034];
              iVar2 = iVar7;
            } while (iVar7 < piVar3[iVar6 * 0x114]);
          }
          param_1[param_1[0x1034] * 0x114 + 0x92] = 1;
        }
        else {
          param_1[param_1[0x1034] * 0x114 + 0x92] = 0;
        }
        close(__fd);
        FUN_MCARD__000f56fc(param_1,param_1 + param_1[0x1034] * 0x114 + 1,param_1[0x103d],
                            param_1[0x103e],param_1[0x103f],param_1[0x1040],param_1[0x1034]);
        goto LAB_MCARD__000f4130;
      }
    }
LAB_MCARD__000f3ea8:
    __fd = -1;
  }
  return __fd;
}



// decompiled code
// original method signature: 
// void /*$ra*/ download_icon__6MCSLOTR9BLOCKINFOiiiii(struct MCSLOT *this /*$a0*/, struct BLOCKINFO *blockInfo /*$s2*/, int iconX /*$s3*/, int iconY /*$s4*/, int clutX /*stack 16*/, int clutY /*stack 20*/, int icon /*stack 24*/)
 // line 712, offset 0x000f56fc
	/* begin block 1 */
		// Start line: 713
		// Start offset: 0x000F56FC
		// Variables:
	// 		struct RECT rect; // stack offset -32
	// 		struct TIMSTRUCT *timPtr; // $s0

		/* begin block 1.1 */
			// Start line: 713
			// Start offset: 0x000F56FC
			// Variables:
		// 		int n; // $a0
		/* end block 1.1 */
		// End offset: 0x000F5790
		// End Line: 734
	/* end block 1 */
	// End offset: 0x000F5860
	// End Line: 754

	/* begin block 2 */
		// Start line: 3895
	/* end block 2 */
	// End Line: 3896

	/* begin block 3 */
		// Start line: 3904
	/* end block 3 */
	// End Line: 3905

void FUN_MCARD__000f56fc(undefined4 param_1,int param_2,int param_3,int param_4,short param_5,
                        int param_6,int param_7)

{
  u_short uVar1;
  ushort *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  short local_20;
  ushort local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  
  local_1c = 0x10;
  local_1a = 1;
  local_20 = param_5;
  local_1e = (ushort)(param_6 + param_7);
  uVar1 = GetClut((int)param_5,(param_6 + param_7) * 0x10000 >> 0x10);
  puVar2 = (ushort *)(param_2 + 0x98);
  iVar3 = 0xf;
  *(u_short *)(param_2 + 0x238) = uVar1;
  do {
    if (*puVar2 != 0) {
      *puVar2 = *puVar2 | 0x8000;
    }
    iVar3 = iVar3 + -1;
    puVar2 = puVar2 + 1;
  } while (-1 < iVar3);
  LoadImage(&local_20,param_2 + 0x98);
  DrawSync(0);
  iVar3 = param_7;
  if (param_7 < 0) {
    iVar3 = param_7 + 7;
  }
  uVar5 = param_3 + (param_7 + (iVar3 >> 3) * -8) * 4;
  local_20 = (short)uVar5;
  uVar4 = param_4 + (iVar3 >> 3) * 0x10;
  local_1e = (ushort)uVar4;
  local_1c = 4;
  local_1a = 0x10;
  *(ushort *)(param_2 + 0x23a) =
       (short)(local_1e & 0x100) >> 4 | (ushort)((uVar5 & 0x3ff) >> 6) | 0x20 |
       (ushort)((uVar4 & 0x200) << 2);
  *(ushort *)(param_2 + 0x23e) = local_1e & 0xff;
  *(undefined2 *)(param_2 + 0x23c) = (short)((uVar5 & 0x3f) << 2);
  *(undefined2 *)(param_2 + 0x240) = 0x10;
  *(undefined2 *)(param_2 + 0x242) = 0x10;
  LoadImage(&local_20,param_2 + 0xb8);
  DrawSync(0);
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CopyBlock__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
 // line 764, offset 0x000f5860
	/* begin block 1 */
		// Start line: 765
		// Start offset: 0x000F5860
	/* end block 1 */
	// End offset: 0x000F5918
	// End Line: 779

	/* begin block 2 */
		// Start line: 4096
	/* end block 2 */
	// End Line: 4097

	/* begin block 3 */
		// Start line: 4097
	/* end block 3 */
	// End Line: 4098

undefined4 FUN_MCARD__000f5860(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if (*(int *)(&DAT_000040d8 + param_1) == -2) {
    if (DAT_MCARD__0010eb6c == 0) {
      return 0x1a;
    }
    puVar2 = &DAT_MCARD__0010ee38;
    iVar1 = param_2 * 0x450 + param_1;
    puVar3 = (undefined4 *)(iVar1 + 4);
    do {
      uVar4 = puVar3[1];
      uVar5 = puVar3[2];
      uVar6 = puVar3[3];
      *puVar2 = *puVar3;
      puVar2[1] = uVar4;
      puVar2[2] = uVar5;
      puVar2[3] = uVar6;
      puVar3 = puVar3 + 4;
      puVar2 = puVar2 + 4;
    } while (puVar3 != (undefined4 *)(iVar1 + 0x454));
    *(undefined4 *)(&DAT_000040dc + param_1) = 0;
    iVar1 = DAT_MCARD__0010ee40;
    *(undefined4 *)(&DAT_00004104 + param_1) = 0;
    *(int *)(&DAT_000040e0 + param_1) = iVar1 << 0xd;
  }
  uVar4 = FUN_MCARD__000f43a0(param_1,param_2,DAT_MCARD__0010eb6c,&DAT_MCARD__0010ee38);
  return uVar4;
}



// decompiled code
// original method signature: 
// int /*$ra*/ ReadSlice__6MCSLOTiiP5SLICEP10FILEFORMAT(struct MCSLOT *this /*$t0*/, int block /*$a1*/, int slice /*$a2*/, struct SLICE *slicePtr /*$a3*/, struct FILEFORMAT *fileFormatPtr /*stack 16*/)
 // line 912, offset 0x000f41a0
	/* begin block 1 */
		// Start line: 913
		// Start offset: 0x000F41A0
	/* end block 1 */
	// End offset: 0x000F43A0
	// End Line: 940

	/* begin block 2 */
		// Start line: 1906
	/* end block 2 */
	// End Line: 1907

	/* begin block 3 */
		// Start line: 1907
	/* end block 3 */
	// End Line: 1908

undefined4 FUN_MCARD__000f41a0(int param_1,int param_2,int param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  
  if (*(int *)(&DAT_000040d8 + param_1) == -2) {
    if (DAT_MCARD__0010eb6c == 0) {
      return 0x1a;
    }
    puVar3 = &DAT_MCARD__0010ee38;
    iVar1 = param_2 * 0x450 + param_1;
    puVar2 = (undefined4 *)(iVar1 + 4);
    do {
      uVar6 = puVar2[1];
      uVar7 = puVar2[2];
      uVar9 = puVar2[3];
      *puVar3 = *puVar2;
      puVar3[1] = uVar6;
      puVar3[2] = uVar7;
      puVar3[3] = uVar9;
      puVar2 = puVar2 + 4;
      puVar3 = puVar3 + 4;
    } while (puVar2 != (undefined4 *)(iVar1 + 0x454));
    if (DAT_MCARD__0010ee38 != 0) {
      if (DAT_MCARD__0010f07c == 0) {
        return 0xffffffff;
      }
      if (param_3 <= DAT_MCARD__0010f080) {
        iVar8 = param_3 * 0x20 + DAT_MCARD__0010eb6c;
        iVar1 = param_3;
        if (param_3 < 0) {
          iVar1 = param_3 + 0xf;
        }
        iVar5 = (param_2 + (iVar1 >> 4)) * 0x450;
        iVar4 = (param_3 + (iVar1 >> 4) * -0x10) * 0x20;
        iVar1 = iVar5 + param_1 + iVar4;
        uVar6 = *(undefined4 *)(iVar1 + 600);
        uVar7 = *(undefined4 *)(iVar1 + 0x25c);
        uVar9 = *(undefined4 *)(iVar1 + 0x260);
        *(undefined4 *)(iVar8 + 0x200) = *(undefined4 *)(iVar1 + 0x254);
        *(undefined4 *)(iVar8 + 0x204) = uVar6;
        *(undefined4 *)(iVar8 + 0x208) = uVar7;
        *(undefined4 *)(iVar8 + 0x20c) = uVar9;
        uVar6 = *(undefined4 *)(iVar1 + 0x268);
        uVar7 = *(undefined4 *)(iVar1 + 0x26c);
        uVar9 = *(undefined4 *)(iVar1 + 0x270);
        *(undefined4 *)(iVar8 + 0x210) = *(undefined4 *)(iVar1 + 0x264);
        *(undefined4 *)(iVar8 + 0x214) = uVar6;
        *(undefined4 *)(iVar8 + 0x218) = uVar7;
        *(undefined4 *)(iVar8 + 0x21c) = uVar9;
        iVar1 = DAT_MCARD__0010ee40 * 0x200 + *(int *)(param_5 + 0x110) * param_3 + 0x200;
        *(int *)(&DAT_000040dc + param_1) = iVar1;
        iVar8 = *(int *)(param_5 + 0x110);
        *(undefined4 *)(&DAT_00004104 + param_1) = 1;
        *(undefined2 *)(&DAT_00004108 + param_1) = 0;
        *(int *)(&DAT_000040e0 + param_1) = iVar1 + iVar8;
        *(undefined2 *)(&DAT_0000410a + param_1) = *(undefined2 *)(param_1 + iVar4 + iVar5 + 0x270);
        goto LAB_MCARD__000f437c;
      }
    }
    uVar6 = 0xffffffff;
  }
  else {
LAB_MCARD__000f437c:
    uVar6 = FUN_MCARD__000f43a0(param_1,param_2,DAT_MCARD__0010eb6c,&DAT_MCARD__0010ee38);
  }
  return uVar6;
}



// decompiled code
// original method signature: 
// int /*$ra*/ read_block__6MCSLOTiPcR9BLOCKINFO(struct MCSLOT *this /*$s1*/, int block /*$a1*/, char *bufferPtr /*$fp*/, struct BLOCKINFO *blockInfo /*$s7*/)
 // line 950, offset 0x000f43a0
	/* begin block 1 */
		// Start line: 951
		// Start offset: 0x000F43A0
		// Variables:
	// 		int n; // $s5
	// 		char verifyBuffer[128]; // stack offset -200
	// 		char filename[32]; // stack offset -72
	// 		long bytesRead; // $v0
	// 		unsigned int verifyFailed; // $v0
	// 		int retry; // $s0

		/* begin block 1.1 */
			// Start line: 951
			// Start offset: 0x000F43A0

			/* begin block 1.1.1 */
				// Start line: 962
				// Start offset: 0x000F43E4
			/* end block 1.1.1 */
			// End offset: 0x000F44A0
			// End Line: 989
		/* end block 1.1 */
		// End offset: 0x000F44A0
		// End Line: 989

		/* begin block 1.2 */
			// Start line: 994
			// Start offset: 0x000F44A0

			/* begin block 1.2.1 */
				// Start line: 995
				// Start offset: 0x000F44B8

				/* begin block 1.2.1.1 */
					// Start line: 998
					// Start offset: 0x000F44B8

					/* begin block 1.2.1.1.1 */
						// Start line: 998
						// Start offset: 0x000F44C0

						/* begin block 1.2.1.1.1.1 */
							// Start line: 1000
							// Start offset: 0x000F44C0

							/* begin block 1.2.1.1.1.1.1 */
								// Start line: 1005
								// Start offset: 0x000F44EC

								/* begin block 1.2.1.1.1.1.1.1 */
									// Start line: 1008
									// Start offset: 0x000F44F4

									/* begin block 1.2.1.1.1.1.1.1.1 */
										// Start line: 1011
										// Start offset: 0x000F44F4

										/* begin block 1.2.1.1.1.1.1.1.1.1 */
											// Start line: 1012
											// Start offset: 0x000F44F4

											/* begin block 1.2.1.1.1.1.1.1.1.1.1 */
												// Start line: 1017
												// Start offset: 0x000F4524
											/* end block 1.2.1.1.1.1.1.1.1.1.1 */
											// End offset: 0x000F4524
											// End Line: 1017
										/* end block 1.2.1.1.1.1.1.1.1.1 */
										// End offset: 0x000F4524
										// End Line: 1017
									/* end block 1.2.1.1.1.1.1.1.1 */
									// End offset: 0x000F4524
									// End Line: 1017

									/* begin block 1.2.1.1.1.1.1.1.2 */
										// Start line: 1035
										// Start offset: 0x000F4530

										/* begin block 1.2.1.1.1.1.1.1.2.1 */
											// Start line: 1036
											// Start offset: 0x000F4530

											/* begin block 1.2.1.1.1.1.1.1.2.1.1 */
												// Start line: 1041
												// Start offset: 0x000F455C
											/* end block 1.2.1.1.1.1.1.1.2.1.1 */
											// End offset: 0x000F455C
											// End Line: 1041
										/* end block 1.2.1.1.1.1.1.1.2.1 */
										// End offset: 0x000F455C
										// End Line: 1041
									/* end block 1.2.1.1.1.1.1.1.2 */
									// End offset: 0x000F455C
									// End Line: 1041

									/* begin block 1.2.1.1.1.1.1.1.3 */
										// Start line: 1056
										// Start offset: 0x000F4564

										/* begin block 1.2.1.1.1.1.1.1.3.1 */
											// Start line: 1059
											// Start offset: 0x000F4584
										/* end block 1.2.1.1.1.1.1.1.3.1 */
										// End offset: 0x000F4584
										// End Line: 1059
									/* end block 1.2.1.1.1.1.1.1.3 */
									// End offset: 0x000F4584
									// End Line: 1059
								/* end block 1.2.1.1.1.1.1.1 */
								// End offset: 0x000F4584
								// End Line: 1059
							/* end block 1.2.1.1.1.1.1 */
							// End offset: 0x000F458C
							// End Line: 1071
						/* end block 1.2.1.1.1.1 */
						// End offset: 0x000F458C
						// End Line: 1071
					/* end block 1.2.1.1.1 */
					// End offset: 0x000F458C
					// End Line: 1076
				/* end block 1.2.1.1 */
				// End offset: 0x000F45B4
				// End Line: 1077
			/* end block 1.2.1 */
			// End offset: 0x000F45DC
			// End Line: 1080

			/* begin block 1.2.2 */
				// Start line: 1082
				// Start offset: 0x000F45DC

				/* begin block 1.2.2.1 */
					// Start line: 1084
					// Start offset: 0x000F45DC

					/* begin block 1.2.2.1.1 */
						// Start line: 1092
						// Start offset: 0x000F4608

						/* begin block 1.2.2.1.1.1 */
							// Start line: 1093
							// Start offset: 0x000F4608
							// Variables:
						// 		int check; // $a1
						/* end block 1.2.2.1.1.1 */
						// End offset: 0x000F4640
						// End Line: 1096
					/* end block 1.2.2.1.1 */
					// End offset: 0x000F4678
					// End Line: 1108
				/* end block 1.2.2.1 */
				// End offset: 0x000F4678
				// End Line: 1108
			/* end block 1.2.2 */
			// End offset: 0x000F46B4
			// End Line: 1117
		/* end block 1.2 */
		// End offset: 0x000F46B4
		// End Line: 1117
	/* end block 1 */
	// End offset: 0x000F46B4
	// End Line: 1117

	/* begin block 2 */
		// Start line: 1988
	/* end block 2 */
	// End Line: 1989

int FUN_MCARD__000f43a0(int param_1,int param_2,int param_3,undefined4 *param_4)

{
  int iVar1;
  ssize_t sVar2;
  int iVar3;
  ushort *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  undefined auStack200 [128];
  char acStack72 [32];
  
  if (*(int *)(&DAT_000040d8 + param_1) == -2) {
    if (*(int *)(param_1 + param_2 * 0x450 + 4) == 0) {
      *(undefined4 *)(&DAT_000040d8 + param_1) = 0;
      iVar1 = param_2 * 0x450 + param_1;
      puVar5 = (undefined4 *)(iVar1 + 4);
      puVar6 = param_4;
      do {
        uVar7 = puVar5[1];
        uVar8 = puVar5[2];
        uVar9 = puVar5[3];
        *puVar6 = *puVar5;
        puVar6[1] = uVar7;
        puVar6[2] = uVar8;
        puVar6[3] = uVar9;
        puVar5 = puVar5 + 4;
        puVar6 = puVar6 + 4;
      } while (puVar5 != (undefined4 *)(iVar1 + 0x454));
      *param_4 = 0;
    }
    else {
      *(undefined4 *)(&DAT_000040d8 + param_1) = 0;
      *param_4 = 0;
    }
    sprintf(acStack72,&DAT_MCARD__000f300c,param_1 + 0x40c8,param_4 + 4);
    iVar1 = open(acStack72,1);
    *(int *)(&DAT_000040d4 + param_1) = iVar1;
    if (iVar1 == -1) {
      return 0xffffffff;
    }
  }
  if (*(int *)(&DAT_000040d8 + param_1) < (int)(param_4[2] << 0xd)) {
    iVar1 = 0;
    if (0 < (int)(param_4[2] << 2)) {
      do {
        iVar10 = 6;
        if ((*(int *)(&DAT_000040dc + param_1) <= *(int *)(&DAT_000040d8 + param_1)) &&
           (*(int *)(&DAT_000040d8 + param_1) <= *(int *)(&DAT_000040e0 + param_1))) {
          do {
            do {
              iVar10 = iVar10 + -1;
              lseek(*(int *)(&DAT_000040d4 + param_1),*(__off_t *)(&DAT_000040d8 + param_1),0);
              sVar2 = read(*(int *)(&DAT_000040d4 + param_1),
                           (void *)(param_3 + *(int *)(&DAT_000040d8 + param_1)),0x80);
              if (iVar10 == -1) {
LAB_MCARD__000f4660:
                *(undefined4 *)(&DAT_000040d8 + param_1) = 0xfffffffe;
                close(*(int *)(&DAT_000040d4 + param_1));
                return 0xffffffff;
              }
            } while (sVar2 != 0x80);
            do {
              iVar3 = iVar10;
              iVar10 = iVar3 + -1;
              lseek(*(int *)(&DAT_000040d4 + param_1),*(__off_t *)(&DAT_000040d8 + param_1),0);
              sVar2 = read(*(int *)(&DAT_000040d4 + param_1),auStack200,0x80);
              if (iVar10 == -1) goto LAB_MCARD__000f4660;
            } while (sVar2 != 0x80);
            iVar10 = iVar3 + -2;
            iVar3 = memcmp((void *)(param_3 + *(int *)(&DAT_000040d8 + param_1)),auStack200,0x80);
            if (iVar10 == -1) goto LAB_MCARD__000f4660;
          } while (iVar3 != 0);
        }
        *(int *)(&DAT_000040d8 + param_1) = *(int *)(&DAT_000040d8 + param_1) + 0x80;
        iVar1 = iVar1 + 1;
      } while (iVar1 < (int)(param_4[2] << 2));
    }
    iVar1 = *(int *)(&DAT_000040d8 + param_1) / (int)(param_4[2] << 9);
    if (param_4[2] << 9 == 0) {
      trap(7);
    }
  }
  else {
    close(*(int *)(&DAT_000040d4 + param_1));
    *(undefined4 *)(&DAT_000040d8 + param_1) = 0xfffffffe;
    *param_4 = 1;
    if (*(int *)(&DAT_00004104 + param_1) != 0) {
      iVar1 = *(int *)(&DAT_000040dc + param_1);
      while (iVar1 < *(int *)(&DAT_000040e0 + param_1)) {
        puVar4 = (ushort *)(param_3 + iVar1);
        iVar1 = iVar1 + 2;
        *(ushort *)(&DAT_00004108 + param_1) = *(ushort *)(&DAT_00004108 + param_1) ^ *puVar4;
      }
      *(undefined4 *)(&DAT_000040ec + param_1) = 0;
      *(undefined4 *)(&DAT_000040f0 + param_1) = 0;
      if (*(short *)(&DAT_0000410a + param_1) != *(short *)(&DAT_00004108 + param_1)) {
        *param_4 = 0;
        return 0x1f;
      }
    }
    iVar1 = -2;
    *(undefined4 *)(&DAT_000040ec + param_1) = 0;
    *(undefined4 *)(&DAT_000040f0 + param_1) = 0;
  }
  return iVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ PasteBlock__6MCSLOT(struct MCSLOT *this /*$a0*/)
 // line 1130, offset 0x000f5918
	/* begin block 1 */
		// Start line: 1131
		// Start offset: 0x000F5918
	/* end block 1 */
	// End offset: 0x000F5968
	// End Line: 1137

	/* begin block 2 */
		// Start line: 4831
	/* end block 2 */
	// End Line: 4832

	/* begin block 3 */
		// Start line: 4832
	/* end block 3 */
	// End Line: 4833

undefined4 FUN_MCARD__000f5918(int param_1)

{
  undefined4 uVar1;
  
  if (DAT_MCARD__0010ee38 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    *(undefined4 *)(&DAT_000040ec + param_1) = 0;
    uVar1 = DAT_MCARD__0010eb6c;
    *(int *)(&DAT_000040f0 + param_1) = DAT_MCARD__0010ee40 << 0xd;
    uVar1 = FUN_MCARD__000f46b4(param_1,&DAT_MCARD__0010ee38,uVar1);
  }
  return uVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ ReadHeader__6MCSLOTii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/)
 // line 1146, offset 0x000f5968
	/* begin block 1 */
		// Start line: 1147
		// Start offset: 0x000F5968
	/* end block 1 */
	// End offset: 0x000F5A60
	// End Line: 1164

	/* begin block 2 */
		// Start line: 4868
	/* end block 2 */
	// End Line: 4869

	/* begin block 3 */
		// Start line: 4869
	/* end block 3 */
	// End Line: 4870

undefined4 FUN_MCARD__000f5968(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if (*(int *)(&DAT_000040d8 + param_1) == -2) {
    puVar3 = &DAT_MCARD__0010ee38;
    iVar1 = param_2 * 0x450 + param_1;
    puVar2 = (undefined4 *)(iVar1 + 4);
    do {
      uVar4 = puVar2[1];
      uVar5 = puVar2[2];
      uVar6 = puVar2[3];
      *puVar3 = *puVar2;
      puVar3[1] = uVar4;
      puVar3[2] = uVar5;
      puVar3[3] = uVar6;
      puVar2 = puVar2 + 4;
      puVar3 = puVar3 + 4;
    } while (puVar2 != (undefined4 *)(iVar1 + 0x454));
    if ((DAT_MCARD__0010ee08 & 0x1000) == 0) {
      if (DAT_MCARD__0010ee38 == 0) {
        return 0xffffffff;
      }
      if (DAT_MCARD__0010f07c == 0) {
        return 0xffffffff;
      }
      if (DAT_MCARD__0010f080 < param_3) {
        return 0xffffffff;
      }
    }
    *(undefined4 *)(&DAT_00004104 + param_1) = 0;
    *(undefined4 *)(&DAT_000040dc + param_1) = 0;
    *(int *)(&DAT_000040e0 + param_1) = DAT_MCARD__0010ee40 * 0x200 + 0x200;
  }
  uVar4 = FUN_MCARD__000f43a0(param_1,param_2,DAT_MCARD__0010eb6c,&DAT_MCARD__0010ee38);
  return uVar4;
}



// decompiled code
// original method signature: 
// int /*$ra*/ RenameCopyBlock__6MCSLOTP10FILEFORMAT(struct MCSLOT *this /*$a0*/, struct FILEFORMAT *fileFormatPtr /*$s1*/)
 // line 1173, offset 0x000f5a60
	/* begin block 1 */
		// Start line: 1174
		// Start offset: 0x000F5A60
		// Variables:
	// 		struct _CARD *headerptr; // $s0
	/* end block 1 */
	// End offset: 0x000F5B24
	// End Line: 1179

	/* begin block 2 */
		// Start line: 4922
	/* end block 2 */
	// End Line: 4923

	/* begin block 3 */
		// Start line: 4923
	/* end block 3 */
	// End Line: 4924

void FUN_MCARD__000f5a60(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *__s;
  
  __s = (undefined4 *)(DAT_MCARD__0010eb6c + 4);
  memset(__s,0,0x40);
  puVar1 = (undefined4 *)(param_2 + 0x22);
  if ((((uint)puVar1 | (uint)__s) & 3) == 0) {
    do {
      uVar2 = puVar1[1];
      uVar3 = puVar1[2];
      uVar4 = puVar1[3];
      *__s = *puVar1;
      __s[1] = uVar2;
      __s[2] = uVar3;
      __s[3] = uVar4;
      puVar1 = puVar1 + 4;
      __s = __s + 4;
    } while (puVar1 != (undefined4 *)(param_2 + 0x62));
  }
  else {
    do {
      uVar2 = puVar1[1];
      uVar3 = puVar1[2];
      uVar4 = puVar1[3];
      *__s = *puVar1;
      __s[1] = uVar2;
      __s[2] = uVar3;
      __s[3] = uVar4;
      puVar1 = puVar1 + 4;
      __s = __s + 4;
    } while (puVar1 != (undefined4 *)(param_2 + 0x62));
  }
  return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ WriteSlice__6MCSLOTiiP5SLICEP10FILEFORMATPc(struct MCSLOT *this /*$s0*/, int block /*$s4*/, int slice /*$s1*/, struct SLICE *slicePtr /*$a2*/, struct FILEFORMAT *fileFormatPtr /*stack 16*/, char *bufferPtr /*stack 20*/)
 // line 1187, offset 0x000f5b38
	/* begin block 1 */
		// Start line: 1188
		// Start offset: 0x000F5B38
	/* end block 1 */
	// End offset: 0x000F5C70
	// End Line: 1249

	/* begin block 2 */
		// Start line: 4955
	/* end block 2 */
	// End Line: 4956

	/* begin block 3 */
		// Start line: 4957
	/* end block 3 */
	// End Line: 4958

undefined4 FUN_MCARD__000f5b38(int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(&DAT_000040e8 + param_1) == -2) {
    if ((DAT_MCARD__0010ee08 & 0x1000) == 0) {
      if (DAT_MCARD__0010ee38 == 0) {
        return 0xffffffff;
      }
      if (DAT_MCARD__0010f07c == 0) {
        return 0xffffffff;
      }
      if (DAT_MCARD__0010f080 < param_3) {
        return 0xffffffff;
      }
    }
    FUN_MCARD__000f6088(param_1,param_3,param_4,(uint)*(byte *)(param_4 + 0x14),
                        (uint)*(byte *)(param_4 + 0x15),(uint)*(byte *)(param_4 + 0x16),
                        *(undefined4 *)(param_4 + 0x18));
    FUN_MCARD__000f502c(param_1,param_2);
    iVar1 = DAT_MCARD__0010ee40 * 0x200 + *(int *)(param_5 + 0x110) * param_3 + 0x200;
    *(int *)(&DAT_000040ec + param_1) = iVar1;
    *(int *)(&DAT_000040f0 + param_1) = iVar1 + *(int *)(param_5 + 0x110);
  }
  uVar2 = FUN_MCARD__000f46b4(param_1,&DAT_MCARD__0010ee38,DAT_MCARD__0010eb6c);
  return uVar2;
}



// decompiled code
// original method signature: 
// int /*$ra*/ write_block__6MCSLOTR9BLOCKINFOPc(struct MCSLOT *this /*$s1*/, struct BLOCKINFO *blockInfo /*$s7*/, char *bufferPtr /*$fp*/)
 // line 1261, offset 0x000f46b4
	/* begin block 1 */
		// Start line: 1262
		// Start offset: 0x000F46B4
		// Variables:
	// 		int n; // $s5
	// 		char verifyBuffer[128]; // stack offset -200
	// 		char filename[32]; // stack offset -72
	// 		int filePtr; // $v0
	// 		long bytes; // $v0
	// 		unsigned int verifyFailed; // $v0
	// 		int retry; // $s0

		/* begin block 1.1 */
			// Start line: 1262
			// Start offset: 0x000F46B4

			/* begin block 1.1.1 */
				// Start line: 1273
				// Start offset: 0x000F46F8
			/* end block 1.1.1 */
			// End offset: 0x000F478C
			// End Line: 1308
		/* end block 1.1 */
		// End offset: 0x000F478C
		// End Line: 1308

		/* begin block 1.2 */
			// Start line: 1312
			// Start offset: 0x000F478C

			/* begin block 1.2.1 */
				// Start line: 1315
				// Start offset: 0x000F47C0

				/* begin block 1.2.1.1 */
					// Start line: 1317
					// Start offset: 0x000F47C0

					/* begin block 1.2.1.1.1 */
						// Start line: 1317
						// Start offset: 0x000F47CC

						/* begin block 1.2.1.1.1.1 */
							// Start line: 1319
							// Start offset: 0x000F47CC

							/* begin block 1.2.1.1.1.1.1 */
								// Start line: 1325
								// Start offset: 0x000F4814

								/* begin block 1.2.1.1.1.1.1.1 */
									// Start line: 1327
									// Start offset: 0x000F481C

									/* begin block 1.2.1.1.1.1.1.1.1 */
										// Start line: 1330
										// Start offset: 0x000F481C

										/* begin block 1.2.1.1.1.1.1.1.1.1 */
											// Start line: 1332
											// Start offset: 0x000F481C

											/* begin block 1.2.1.1.1.1.1.1.1.1.1 */
												// Start line: 1337
												// Start offset: 0x000F484C
											/* end block 1.2.1.1.1.1.1.1.1.1.1 */
											// End offset: 0x000F484C
											// End Line: 1337
										/* end block 1.2.1.1.1.1.1.1.1.1 */
										// End offset: 0x000F484C
										// End Line: 1337
									/* end block 1.2.1.1.1.1.1.1.1 */
									// End offset: 0x000F484C
									// End Line: 1337

									/* begin block 1.2.1.1.1.1.1.1.2 */
										// Start line: 1355
										// Start offset: 0x000F4858

										/* begin block 1.2.1.1.1.1.1.1.2.1 */
											// Start line: 1356
											// Start offset: 0x000F4858

											/* begin block 1.2.1.1.1.1.1.1.2.1.1 */
												// Start line: 1361
												// Start offset: 0x000F4884
											/* end block 1.2.1.1.1.1.1.1.2.1.1 */
											// End offset: 0x000F4884
											// End Line: 1361
										/* end block 1.2.1.1.1.1.1.1.2.1 */
										// End offset: 0x000F4884
										// End Line: 1361
									/* end block 1.2.1.1.1.1.1.1.2 */
									// End offset: 0x000F4884
									// End Line: 1361

									/* begin block 1.2.1.1.1.1.1.1.3 */
										// Start line: 1378
										// Start offset: 0x000F488C

										/* begin block 1.2.1.1.1.1.1.1.3.1 */
											// Start line: 1381
											// Start offset: 0x000F48AC
										/* end block 1.2.1.1.1.1.1.1.3.1 */
										// End offset: 0x000F48AC
										// End Line: 1381
									/* end block 1.2.1.1.1.1.1.1.3 */
									// End offset: 0x000F48AC
									// End Line: 1381
								/* end block 1.2.1.1.1.1.1.1 */
								// End offset: 0x000F48AC
								// End Line: 1381
							/* end block 1.2.1.1.1.1.1 */
							// End offset: 0x000F48B4
							// End Line: 1395
						/* end block 1.2.1.1.1.1 */
						// End offset: 0x000F48B4
						// End Line: 1395
					/* end block 1.2.1.1.1 */
					// End offset: 0x000F48B4
					// End Line: 1400
				/* end block 1.2.1.1 */
				// End offset: 0x000F48DC
				// End Line: 1401
			/* end block 1.2.1 */
			// End offset: 0x000F4924
			// End Line: 1404

			/* begin block 1.2.2 */
				// Start line: 1406
				// Start offset: 0x000F4924

				/* begin block 1.2.2.1 */
					// Start line: 1409
					// Start offset: 0x000F4924
					// Variables:
				// 		struct MCSLOT *this; // $s1

					/* begin block 1.2.2.1.1 */
						// Start line: 1409
						// Start offset: 0x000F4924

						/* begin block 1.2.2.1.1.1 */
							// Start line: 1409
							// Start offset: 0x000F4924
							// Variables:
						// 		int n; // $a1
						/* end block 1.2.2.1.1.1 */
						// End offset: 0x000F496C
						// End Line: 1411

						/* begin block 1.2.2.1.1.2 */
							// Start line: 1262
							// Start offset: 0x000F496C

							/* begin block 1.2.2.1.1.2.1 */
								// Start line: 1262
								// Start offset: 0x000F497C
							/* end block 1.2.2.1.1.2.1 */
							// End offset: 0x000F498C
							// End Line: 1262
						/* end block 1.2.2.1.1.2 */
						// End offset: 0x000F498C
						// End Line: 1262

						/* begin block 1.2.2.1.1.3 */
							// Start line: 1262
							// Start offset: 0x000F498C

							/* begin block 1.2.2.1.1.3.1 */
								// Start line: 1262
								// Start offset: 0x000F499C
							/* end block 1.2.2.1.1.3.1 */
							// End offset: 0x000F49AC
							// End Line: 1262
						/* end block 1.2.2.1.1.3 */
						// End offset: 0x000F49AC
						// End Line: 1262
					/* end block 1.2.2.1.1 */
					// End offset: 0x000F49AC
					// End Line: 1262
				/* end block 1.2.2.1 */
				// End offset: 0x000F49AC
				// End Line: 1262
			/* end block 1.2.2 */
			// End offset: 0x000F49E8
			// End Line: 1465
		/* end block 1.2 */
		// End offset: 0x000F49E8
		// End Line: 1465
	/* end block 1 */
	// End offset: 0x000F49E8
	// End Line: 1465

	/* begin block 2 */
		// Start line: 2708
	/* end block 2 */
	// End Line: 2709

int FUN_MCARD__000f46b4(int *param_1,int param_2,int param_3)

{
  int __fd;
  ssize_t sVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  undefined auStack200 [128];
  char acStack72 [32];
  
  if (param_1[0x103a] == -2) {
    if (param_1[0x102d] == 0) {
      FUN_MCARD__000f3c74();
    }
    if (param_3 == 0) {
      return 0xffffffff;
    }
    if (0xf - *param_1 < *(int *)(param_2 + 8)) {
      return 0x1b;
    }
    sprintf(acStack72,&DAT_MCARD__000f300c,param_1 + 0x1032,param_2 + 0x10);
    __fd = open(acStack72,*(int *)(param_2 + 8) << 0x10 | 0x200);
    if (__fd != -1) {
      param_1[0x103a] = 0;
      close(__fd);
      __fd = open(acStack72,3);
      param_1[0x1039] = __fd;
      if (__fd != -1) goto LAB_MCARD__000f478c;
    }
LAB_MCARD__000f491c:
    __fd = -1;
  }
  else {
LAB_MCARD__000f478c:
    sprintf(acStack72,&DAT_MCARD__000f300c,param_1 + 0x1032,param_2 + 0x10);
    if (param_1[0x103a] < *(int *)(param_2 + 8) << 0xd) {
      __fd = 0;
      if (0 < *(int *)(param_2 + 8) << 2) {
        do {
          iVar3 = param_1[0x103a];
          iVar6 = 6;
          if (((param_1[0x103b] <= iVar3) && (iVar3 <= param_1[0x103c])) ||
             (iVar3 < *(int *)(param_2 + 8) * 0x200 + 0x200)) {
            do {
              do {
                iVar6 = iVar6 + -1;
                lseek(param_1[0x1039],param_1[0x103a],0);
                sVar1 = write(param_1[0x1039],(void *)(param_3 + param_1[0x103a]),0x80);
                if (iVar6 == -1) {
LAB_MCARD__000f4904:
                  param_1[0x103a] = -2;
                  close(param_1[0x1039]);
                  FUN_MCARD__000f6588(acStack72);
                  goto LAB_MCARD__000f491c;
                }
              } while (sVar1 != 0x80);
              do {
                iVar3 = iVar6;
                iVar6 = iVar3 + -1;
                lseek(param_1[0x1039],param_1[0x103a],0);
                sVar1 = read(param_1[0x1039],auStack200,0x80);
                if (iVar6 == -1) goto LAB_MCARD__000f4904;
              } while (sVar1 != 0x80);
              iVar6 = iVar3 + -2;
              iVar3 = memcmp((void *)(param_3 + param_1[0x103a]),auStack200,0x80);
              if (iVar6 == -1) goto LAB_MCARD__000f4904;
            } while (iVar3 != 0);
          }
          param_1[0x103a] = param_1[0x103a] + 0x80;
          __fd = __fd + 1;
        } while (__fd < *(int *)(param_2 + 8) << 2);
      }
      iVar6 = *(int *)(param_2 + 8) << 9;
      __fd = param_1[0x103a] / iVar6;
      if (iVar6 == 0) {
        trap(7);
      }
    }
    else {
      param_1[0x103a] = -2;
      close(param_1[0x1039]);
      piVar5 = param_1 + 0x92;
      piVar4 = param_1 + 3;
      piVar2 = param_1 + 1;
      __fd = 0xe;
      param_1[0x102d] = 0;
      param_1[0x102e] = 0;
      do {
        *piVar2 = 0;
        *piVar4 = -1;
        *piVar5 = 0;
        piVar5 = piVar5 + 0x114;
        piVar4 = piVar4 + 0x114;
        __fd = __fd + -1;
        piVar2 = piVar2 + 0x114;
      } while (-1 < __fd);
      if (param_1[0x1036] != -2) {
        close(param_1[0x1035]);
        param_1[0x1036] = -2;
      }
      if (param_1[0x103a] != -2) {
        close(param_1[0x1039]);
        param_1[0x103a] = -2;
      }
      __fd = -2;
      param_1[0x103b] = 0;
      param_1[0x103c] = 0;
    }
  }
  return __fd;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CreateBlock__6MCSLOTP10FILEFORMATP5SLICE(struct MCSLOT *this /*$s5*/, struct FILEFORMAT *fileFormatPtr /*$s4*/, struct SLICE *slicePtr /*stack 8*/)
 // line 1473, offset 0x000f49e8
	/* begin block 1 */
		// Start line: 1474
		// Start offset: 0x000F49E8
		// Variables:
	// 		int i; // $a1
	// 		int n; // $s0
	// 		struct _CARD header; // stack offset -680
	// 		char filename[32]; // stack offset -168
	// 		int filePtr; // $s1
	// 		int bytes; // $s3
	// 		int blockNum; // $fp
	// 		char charBuffer[64]; // stack offset -136
	// 		struct SLICEHEADER emptySlice; // stack offset -72
	// 		char *charPtr; // $a2

		/* begin block 1.1 */
			// Start line: 1567
			// Start offset: 0x000F4D98

			/* begin block 1.1.1 */
				// Start line: 1570
				// Start offset: 0x000F4DB0
			/* end block 1.1.1 */
			// End offset: 0x000F4DDC
			// End Line: 1577
		/* end block 1.1 */
		// End offset: 0x000F4DDC
		// End Line: 1580

		/* begin block 1.2 */
			// Start line: 1584
			// Start offset: 0x000F4DDC

			/* begin block 1.2.1 */
				// Start line: 1585
				// Start offset: 0x000F4DF0

				/* begin block 1.2.1.1 */
					// Start line: 1586
					// Start offset: 0x000F4DF0

					/* begin block 1.2.1.1.1 */
						// Start line: 1594
						// Start offset: 0x000F4E28
					/* end block 1.2.1.1.1 */
					// End offset: 0x000F4F28
					// End Line: 1614
				/* end block 1.2.1.1 */
				// End offset: 0x000F4F4C
				// End Line: 1615
			/* end block 1.2.1 */
			// End offset: 0x000F4F74
			// End Line: 1620
		/* end block 1.2 */
		// End offset: 0x000F4F74
		// End Line: 1620

		/* begin block 1.3 */
			// Start line: 1625
			// Start offset: 0x000F4F74
			// Variables:
		// 		struct MCSLOT *this; // $s5

			/* begin block 1.3.1 */
				// Start line: 1625
				// Start offset: 0x000F4F74

				/* begin block 1.3.1.1 */
					// Start line: 1625
					// Start offset: 0x000F4F74
					// Variables:
				// 		int n; // $a1
				/* end block 1.3.1.1 */
				// End offset: 0x000F4FB8
				// End Line: 1625

				/* begin block 1.3.1.2 */
					// Start line: 1474
					// Start offset: 0x000F4FB8

					/* begin block 1.3.1.2.1 */
						// Start line: 1474
						// Start offset: 0x000F4FC8
					/* end block 1.3.1.2.1 */
					// End offset: 0x000F4FD8
					// End Line: 1474
				/* end block 1.3.1.2 */
				// End offset: 0x000F4FD8
				// End Line: 1474

				/* begin block 1.3.1.3 */
					// Start line: 1474
					// Start offset: 0x000F4FD8

					/* begin block 1.3.1.3.1 */
						// Start line: 1474
						// Start offset: 0x000F4FE8
					/* end block 1.3.1.3.1 */
					// End offset: 0x000F4FF8
					// End Line: 1474
				/* end block 1.3.1.3 */
				// End offset: 0x000F4FF8
				// End Line: 1474
			/* end block 1.3.1 */
			// End offset: 0x000F4FF8
			// End Line: 1474
		/* end block 1.3 */
		// End offset: 0x000F4FF8
		// End Line: 1474
	/* end block 1 */
	// End offset: 0x000F502C
	// End Line: 1630

	/* begin block 2 */
		// Start line: 3243
	/* end block 2 */
	// End Line: 3244

	/* begin block 3 */
		// Start line: 3249
	/* end block 3 */
	// End Line: 3250

int FUN_MCARD__000f49e8(int *param_1,byte *param_2,int param_3)

{
  uint uVar1;
  size_t __n;
  int __fd;
  undefined4 *puVar2;
  ssize_t sVar3;
  ssize_t sVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int *piVar10;
  undefined4 uVar11;
  int *piVar12;
  undefined4 uVar13;
  int iVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  byte *__src;
  int iVar18;
  int iVar19;
  int iVar20;
  undefined local_2a8;
  undefined uStack679;
  undefined uStack678;
  byte bStack677;
  uint local_2a4 [16];
  undefined auStack612 [28];
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228 [32];
  undefined4 local_1a8 [32];
  undefined4 local_128 [32];
  char acStack168 [5];
  undefined auStack163 [17];
  char local_92;
  byte local_91;
  char acStack136 [64];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  
  iVar20 = 0;
  if (param_1[0x102d] == 0) {
    FUN_MCARD__000f3c74();
  }
  if (param_2 == (byte *)0x0) {
    return 0xffffffff;
  }
  if (0xf - *param_1 < (int)(uint)*param_2) {
    return 0x1b;
  }
  sprintf(acStack168,s__s_sGREM_c00_MCARD__000f3020,param_1 + 0x1032,param_2 + 0x62,
          (uint)param_2[0x6f]);
  memset(local_2a4,0,0x40);
  memset(auStack612,0,0x1c);
  __src = param_2 + 0x22;
  __n = FUN_MCARD__000fe258(__src,1000);
  memcpy(local_2a4,__src,__n);
  if ((DAT_MCARD__0010ee08 & 0x40) == 0) {
    __fd = FUN_MCARD__000f5f1c(param_1,auStack163);
    if (__fd != -1) {
      return 0x1e;
    }
  }
  else {
    while (__fd = FUN_MCARD__000f5f1c(param_1,auStack163), __fd != -1) {
      local_91 = local_91 + 1;
      if (0x39 < local_91) {
        local_91 = 0x30;
        local_92 = local_92 + '\x01';
      }
      iVar20 = iVar20 + 1;
    }
    memset(acStack136,0,0x40);
    sprintf(acStack136,s___s_d_MCARD__000f3030,DAT_MCARD__0010ecf0,iVar20 + 1);
    __fd = FUN_MCARD__000fe258(__src,1000);
    FUN_MCARD__000f512c((int)local_2a4 + __fd,acStack136);
  }
  __fd = open(acStack168,(uint)*param_2 << 0x10 | 0x200);
  if (__fd == -1) {
    return 0xffffffff;
  }
  close(__fd);
  puVar16 = local_228;
  puVar15 = (undefined4 *)(param_2 + 0x90);
  puVar17 = (undefined4 *)(param_2 + 0x110);
  puVar7 = local_1a8;
  puVar8 = local_128;
  local_2a8 = 0x53;
  uStack679 = 0x43;
  bStack677 = *param_2;
  local_248 = *(undefined4 *)(param_2 + 0x70);
  local_244 = *(undefined4 *)(param_2 + 0x74);
  local_240 = *(undefined4 *)(param_2 + 0x78);
  local_23c = *(undefined4 *)(param_2 + 0x7c);
  local_238 = *(undefined4 *)(param_2 + 0x80);
  local_234 = *(undefined4 *)(param_2 + 0x84);
  local_230 = *(undefined4 *)(param_2 + 0x88);
  local_22c = *(undefined4 *)(param_2 + 0x8c);
  uStack678 = 0x11;
  puVar9 = puVar15;
  do {
    uVar6 = puVar9[1];
    uVar11 = puVar9[2];
    uVar13 = puVar9[3];
    *puVar16 = *puVar9;
    puVar16[1] = uVar6;
    puVar16[2] = uVar11;
    puVar16[3] = uVar13;
    puVar9 = puVar9 + 4;
    puVar16 = puVar16 + 4;
    puVar2 = puVar15;
  } while (puVar9 != puVar17);
  do {
    uVar11 = puVar2[1];
    uVar13 = puVar2[2];
    uVar6 = puVar2[3];
    *puVar7 = *puVar2;
    puVar7[1] = uVar11;
    puVar7[2] = uVar13;
    puVar7[3] = uVar6;
    puVar2 = puVar2 + 4;
    puVar7 = puVar7 + 4;
  } while (puVar2 != puVar17);
  do {
    uVar6 = puVar15[1];
    uVar11 = puVar15[2];
    uVar13 = puVar15[3];
    *puVar8 = *puVar15;
    puVar8[1] = uVar6;
    puVar8[2] = uVar11;
    puVar8[3] = uVar13;
    puVar15 = puVar15 + 4;
    puVar8 = puVar8 + 4;
  } while (puVar15 != puVar17);
  memset(auStack612,0,0x1c);
  if (param_3 != 0) {
    puVar15 = *(undefined4 **)(param_3 + 0x18);
    puVar9 = &local_2a8;
    if (((uint)puVar15 & 3) == 0) {
      puVar7 = puVar15 + 0x80;
      do {
        uVar6 = puVar15[1];
        uVar11 = puVar15[2];
        uVar13 = puVar15[3];
        *puVar9 = *puVar15;
        puVar9[1] = uVar6;
        puVar9[2] = uVar11;
        puVar9[3] = uVar13;
        puVar15 = puVar15 + 4;
        puVar9 = puVar9 + 4;
      } while (puVar15 != puVar7);
    }
    else {
      puVar7 = puVar15 + 0x80;
      do {
        uVar6 = puVar15[1];
        uVar11 = puVar15[2];
        uVar13 = puVar15[3];
        *puVar9 = *puVar15;
        puVar9[1] = uVar6;
        puVar9[2] = uVar11;
        puVar9[3] = uVar13;
        puVar15 = puVar15 + 4;
        puVar9 = puVar9 + 4;
      } while (puVar15 != puVar7);
    }
  }
  __fd = open(acStack168,3);
  if (-1 < __fd) {
    sVar3 = write(__fd,&local_2a8,0x200);
    if (sVar3 == 0x200) {
      if ((DAT_MCARD__0010ee08 & 0x1000) != 0) {
LAB_MCARD__000f4f74:
        close(__fd);
        piVar12 = param_1 + 0x92;
        piVar10 = param_1 + 3;
        piVar5 = param_1 + 1;
        __fd = 0xe;
        param_1[0x102d] = 0;
        param_1[0x102e] = 0;
        do {
          *piVar5 = 0;
          *piVar10 = -1;
          *piVar12 = 0;
          piVar12 = piVar12 + 0x114;
          piVar10 = piVar10 + 0x114;
          __fd = __fd + -1;
          piVar5 = piVar5 + 0x114;
        } while (-1 < __fd);
        if (param_1[0x1036] != -2) {
          close(param_1[0x1035]);
          param_1[0x1036] = -2;
        }
        if (param_1[0x103a] == -2) {
          return iVar20;
        }
        close(param_1[0x1039]);
        param_1[0x103a] = -2;
        return iVar20;
      }
      local_48 = *(undefined4 *)(param_2 + 0x110);
      iVar18 = 0;
      local_30 = local_30 & 0xffffff;
      sprintf((char *)&local_44,DAT_MCARD__0010ed18);
      local_30 = local_30 & 0xff000000 | 0xffffff;
      if (*param_2 != 0) {
        do {
          memset(&local_2a8,0,0x200);
          puVar9 = &local_2a8;
          iVar14 = 0;
          iVar19 = iVar18 + 1;
          do {
            uVar13 = local_3c;
            uVar11 = local_40;
            uVar6 = local_44;
            if (*(int *)(param_2 + 0x110) == 0) {
              trap(7);
            }
            if (iVar18 * 0x10 + iVar14 < (int)((uint)*param_2 * 0x1c00) / *(int *)(param_2 + 0x110))
            {
              *puVar9 = local_48;
              puVar9[1] = uVar6;
              puVar9[2] = uVar11;
              puVar9[3] = uVar13;
              uVar11 = local_2c;
              uVar1 = local_30;
              uVar6 = local_34;
              puVar9[4] = local_38;
              puVar9[5] = uVar6;
              puVar9[6] = uVar1;
              puVar9[7] = uVar11;
            }
            puVar9 = puVar9 + 8;
            if ((DAT_MCARD__0010ee08 & 0x1200) != 0) {
              iVar14 = 0x10;
            }
            iVar14 = iVar14 + 1;
          } while (iVar14 < 0x10);
          sVar4 = write(__fd,&local_2a8,0x200);
          sVar3 = sVar3 + sVar4;
          iVar18 = iVar19;
        } while (iVar19 < (int)(uint)*param_2);
      }
      if (sVar3 == (uint)*param_2 * 0x200 + 0x200) goto LAB_MCARD__000f4f74;
    }
    else {
      close(__fd);
    }
    FUN_MCARD__000f6588(acStack168);
  }
  return 0xffffffff;
}



// decompiled code
// original method signature: 
// int /*$ra*/ DeleteBlock__6MCSLOTi(struct MCSLOT *this /*$s1*/, int block /*$a1*/)
 // line 1640, offset 0x000f502c
	/* begin block 1 */
		// Start line: 1641
		// Start offset: 0x000F502C
		// Variables:
	// 		char filename[32]; // stack offset -48

		/* begin block 1.1 */
			// Start line: 1641
			// Start offset: 0x000F502C

			/* begin block 1.1.1 */
				// Start line: 1647
				// Start offset: 0x000F506C

				/* begin block 1.1.1.1 */
					// Start line: 1649
					// Start offset: 0x000F506C
					// Variables:
				// 		struct MCSLOT *this; // $s1

					/* begin block 1.1.1.1.1 */
						// Start line: 1649
						// Start offset: 0x000F506C

						/* begin block 1.1.1.1.1.1 */
							// Start line: 1649
							// Start offset: 0x000F506C
							// Variables:
						// 		int n; // $a1
						/* end block 1.1.1.1.1.1 */
						// End offset: 0x000F50CC
						// End Line: 1651

						/* begin block 1.1.1.1.1.2 */
							// Start line: 1641
							// Start offset: 0x000F50CC

							/* begin block 1.1.1.1.1.2.1 */
								// Start line: 1641
								// Start offset: 0x000F50DC
							/* end block 1.1.1.1.1.2.1 */
							// End offset: 0x000F50EC
							// End Line: 1641
						/* end block 1.1.1.1.1.2 */
						// End offset: 0x000F50EC
						// End Line: 1641

						/* begin block 1.1.1.1.1.3 */
							// Start line: 1641
							// Start offset: 0x000F50EC

							/* begin block 1.1.1.1.1.3.1 */
								// Start line: 1641
								// Start offset: 0x000F50FC
							/* end block 1.1.1.1.1.3.1 */
							// End offset: 0x000F510C
							// End Line: 1641
						/* end block 1.1.1.1.1.3 */
						// End offset: 0x000F510C
						// End Line: 1641
					/* end block 1.1.1.1.1 */
					// End offset: 0x000F510C
					// End Line: 1641
				/* end block 1.1.1.1 */
				// End offset: 0x000F510C
				// End Line: 1641
			/* end block 1.1.1 */
			// End offset: 0x000F5114
			// End Line: 1666
		/* end block 1.1 */
		// End offset: 0x000F512C
		// End Line: 1668
	/* end block 1 */
	// End offset: 0x000F512C
	// End Line: 1668

	/* begin block 2 */
		// Start line: 3624
	/* end block 2 */
	// End Line: 3625

undefined4 FUN_MCARD__000f502c(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  char acStack48 [32];
  
  puVar1 = (undefined4 *)(param_1 + 4);
  if (puVar1[param_2 * 0x114] == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    sprintf(acStack48,&DAT_MCARD__000f300c,param_1 + 0x40c8,param_1 + param_2 * 0x450 + 0x14);
    FUN_MCARD__000f6588(acStack48);
    puVar4 = (undefined4 *)(param_1 + 0x248);
    puVar3 = (undefined4 *)(param_1 + 0xc);
    iVar5 = 0xe;
    *(undefined4 *)(&DAT_000040b4 + param_1) = 0;
    *(undefined4 *)(&DAT_000040b8 + param_1) = 0;
    do {
      *puVar1 = 0;
      *puVar3 = 0xffffffff;
      *puVar4 = 0;
      puVar4 = puVar4 + 0x114;
      puVar3 = puVar3 + 0x114;
      iVar5 = iVar5 + -1;
      puVar1 = puVar1 + 0x114;
    } while (-1 < iVar5);
    if (*(int *)(&DAT_000040d8 + param_1) != -2) {
      close(*(int *)(&DAT_000040d4 + param_1));
      *(undefined4 *)(&DAT_000040d8 + param_1) = 0xfffffffe;
    }
    uVar2 = 0x14;
    if (*(int *)(&DAT_000040e8 + param_1) != -2) {
      close(*(int *)(&DAT_000040e4 + param_1));
      *(undefined4 *)(&DAT_000040e8 + param_1) = 0xfffffffe;
      uVar2 = 0x14;
    }
  }
  return uVar2;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetPort__6MCSLOTii(struct MCSLOT *this /*$s0*/, int port /*$a1*/, int card /*$a2*/)
 // line 1675, offset 0x000f5c70
	/* begin block 1 */
		// Start line: 1676
		// Start offset: 0x000F5C70

		/* begin block 1.1 */
			// Start line: 1676
			// Start offset: 0x000F5C70
			// Variables:
		// 		struct MCSLOT *this; // $s0

			/* begin block 1.1.1 */
				// Start line: 1676
				// Start offset: 0x000F5C70

				/* begin block 1.1.1.1 */
					// Start line: 1676
					// Start offset: 0x000F5C70
					// Variables:
				// 		int n; // $v1
				/* end block 1.1.1.1 */
				// End offset: 0x000F5CDC
				// End Line: 1682

				/* begin block 1.1.1.2 */
					// Start line: 1676
					// Start offset: 0x000F5CDC

					/* begin block 1.1.1.2.1 */
						// Start line: 1676
						// Start offset: 0x000F5CEC
					/* end block 1.1.1.2.1 */
					// End offset: 0x000F5CFC
					// End Line: 1676
				/* end block 1.1.1.2 */
				// End offset: 0x000F5CFC
				// End Line: 1676

				/* begin block 1.1.1.3 */
					// Start line: 1676
					// Start offset: 0x000F5CFC

					/* begin block 1.1.1.3.1 */
						// Start line: 1676
						// Start offset: 0x000F5D0C
					/* end block 1.1.1.3.1 */
					// End offset: 0x000F5D1C
					// End Line: 1676
				/* end block 1.1.1.3 */
				// End offset: 0x000F5D1C
				// End Line: 1676
			/* end block 1.1.1 */
			// End offset: 0x000F5D1C
			// End Line: 1676
		/* end block 1.1 */
		// End offset: 0x000F5D30
		// End Line: 1676
	/* end block 1 */
	// End offset: 0x000F5D30
	// End Line: 1684

	/* begin block 2 */
		// Start line: 5939
	/* end block 2 */
	// End Line: 5940

void FUN_MCARD__000f5c70(int param_1,uint param_2,uint param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  *(uint *)(&DAT_000040c0 + param_1) = param_3 & 3;
  *(uint *)(&DAT_000040bc + param_1) = param_2 & 1;
  *(uint *)(&DAT_000040c4 + param_1) = (param_2 & 1) * 0x10 + (param_3 & 3);
  sprintf((char *)(param_1 + 0x40c8),s_bu_d_d__MCARD__000f3000);
  puVar1 = (undefined4 *)(param_1 + 0x248);
  iVar2 = 0xe;
  *(undefined4 *)(&DAT_000040b4 + param_1) = 0;
  *(undefined4 *)(&DAT_000040b8 + param_1) = 0;
  do {
    puVar1[-0x91] = 0;
    puVar1[-0x8f] = 0xffffffff;
    *puVar1 = 0;
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + 0x114;
  } while (-1 < iVar2);
  if (*(int *)(&DAT_000040d8 + param_1) != -2) {
    close(*(int *)(&DAT_000040d4 + param_1));
    *(undefined4 *)(&DAT_000040d8 + param_1) = 0xfffffffe;
  }
  if (*(int *)(&DAT_000040e8 + param_1) != -2) {
    close(*(int *)(&DAT_000040e4 + param_1));
    *(undefined4 *)(&DAT_000040e8 + param_1) = 0xfffffffe;
  }
  return;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ BlocksShared__6MCSLOTii(struct MCSLOT *this /*$t0*/, int block1 /*$a1*/, int block2 /*$a2*/)
 // line 1710, offset 0x000f5d30
	/* begin block 1 */
		// Start line: 1711
		// Start offset: 0x000F5D30
	/* end block 1 */
	// End offset: 0x000F5DC0
	// End Line: 1719

	/* begin block 2 */
		// Start line: 6020
	/* end block 2 */
	// End Line: 6021

	/* begin block 3 */
		// Start line: 6021
	/* end block 3 */
	// End Line: 6022

int * FUN_MCARD__000f5d30(int param_1,uint param_2,int param_3)

{
  int *piVar1;
  
  if (((param_2 < 0x10) && (-1 < param_3)) && (param_3 < 0x10)) {
    piVar1 = (int *)(param_1 + 4 + param_2 * 0x450);
    if (*piVar1 != 0) {
      piVar1 = *(int **)(param_1 + 4 + param_3 * 0x450);
      if (piVar1 != (int *)0x0) {
        piVar1 = (int *)(uint)(*(int *)(param_1 + 8 + param_2 * 0x450) ==
                              *(int *)(param_1 + 8 + param_3 * 0x450));
      }
    }
    return piVar1;
  }
  return (int *)0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetBlockSize__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
 // line 1723, offset 0x000f5dc8
	/* begin block 1 */
		// Start line: 1724
		// Start offset: 0x000F5DC8
	/* end block 1 */
	// End offset: 0x000F5DFC
	// End Line: 1727

	/* begin block 2 */
		// Start line: 6046
	/* end block 2 */
	// End Line: 6047

	/* begin block 3 */
		// Start line: 6047
	/* end block 3 */
	// End Line: 6048

undefined4 FUN_MCARD__000f5dc8(int param_1,uint param_2)

{
  if (param_2 < 0x10) {
    return *(undefined4 *)(param_1 + param_2 * 0x450 + 0xc);
  }
  return 0;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ CardInfoRead__6MCSLOT(struct MCSLOT *this /*$a0*/)
 // line 1731, offset 0x000f5dfc
	/* begin block 1 */
		// Start line: 1732
		// Start offset: 0x000F5DFC
	/* end block 1 */
	// End offset: 0x000F5E08
	// End Line: 1733

	/* begin block 2 */
		// Start line: 6062
	/* end block 2 */
	// End Line: 6063

	/* begin block 3 */
		// Start line: 6063
	/* end block 3 */
	// End Line: 6064

undefined4 FUN_MCARD__000f5dfc(int param_1)

{
  return *(undefined4 *)(&DAT_000040b8 + param_1);
}



// decompiled code
// original method signature: 
// struct TIMSTRUCT * /*$ra*/ GetBlockIconPtr__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
 // line 1755, offset 0x000f5e08
	/* begin block 1 */
		// Start line: 1756
		// Start offset: 0x000F5E08
	/* end block 1 */
	// End offset: 0x000F5E84
	// End Line: 1763

	/* begin block 2 */
		// Start line: 6110
	/* end block 2 */
	// End Line: 6111

	/* begin block 3 */
		// Start line: 6111
	/* end block 3 */
	// End Line: 6112

int FUN_MCARD__000f5e08(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  if (*(int *)(param_1 + param_2 * 0x450 + 4) == 0) {
    return 0;
  }
  piVar2 = (int *)(param_1 + 0xc + param_2 * 0x450);
  iVar1 = *piVar2;
  while (iVar1 == 0) {
    piVar2 = piVar2 + -0x114;
    iVar1 = *piVar2;
    param_2 = param_2 + -1;
  }
  return param_1 + param_2 * 0x450 + 0x23c;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetNoUsedBlocks__6MCSLOT(struct MCSLOT *this /*$a0*/)
 // line 1788, offset 0x000f5e84
	/* begin block 1 */
		// Start line: 1789
		// Start offset: 0x000F5E84
	/* end block 1 */
	// End offset: 0x000F5EA0
	// End Line: 1794

	/* begin block 2 */
		// Start line: 6165
	/* end block 2 */
	// End Line: 6166

	/* begin block 3 */
		// Start line: 6176
	/* end block 3 */
	// End Line: 6177

	/* begin block 4 */
		// Start line: 6179
	/* end block 4 */
	// End Line: 6180

undefined4 FUN_MCARD__000f5e84(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0xffffffff;
  if (param_1[0x102d] != 0) {
    uVar1 = *param_1;
  }
  return uVar1;
}



// decompiled code
// original method signature: 
// short * /*$ra*/ GetBlockTitlePtr__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
 // line 1806, offset 0x000f5ea0
	/* begin block 1 */
		// Start line: 1807
		// Start offset: 0x000F5EA0
	/* end block 1 */
	// End offset: 0x000F5EE4
	// End Line: 1813

	/* begin block 2 */
		// Start line: 6212
	/* end block 2 */
	// End Line: 6213

	/* begin block 3 */
		// Start line: 6213
	/* end block 3 */
	// End Line: 6214

undefined * FUN_MCARD__000f5ea0(int param_1,int param_2)

{
  if (*(int *)(param_1 + param_2 * 0x450 + 4) == 0) {
    return &DAT_MCARD__0010eb64;
  }
  return (undefined *)(param_1 + param_2 * 0x450 + 0x40);
}



// decompiled code
// original method signature: 
// char * /*$ra*/ GetBlockFilenamePtr__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
 // line 1822, offset 0x000f5ee4
	/* begin block 1 */
		// Start line: 1823
		// Start offset: 0x000F5EE4
	/* end block 1 */
	// End offset: 0x000F5F1C
	// End Line: 1830

	/* begin block 2 */
		// Start line: 6237
	/* end block 2 */
	// End Line: 6238

	/* begin block 3 */
		// Start line: 6247
	/* end block 3 */
	// End Line: 6248

	/* begin block 4 */
		// Start line: 6250
	/* end block 4 */
	// End Line: 6251

/* WARNING: Control flow encountered bad instruction data */

char * GetBlockFilenamePtr__6MCSLOTi(MCSLOT *this,int block)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// decompiled code
// original method signature: 
// int /*$ra*/ FilenameUsed__6MCSLOTPc(struct MCSLOT *this /*$s3*/, char *filename /*$s4*/)
 // line 1836, offset 0x000f5f1c
	/* begin block 1 */
		// Start line: 1837
		// Start offset: 0x000F5F1C
		// Variables:
	// 		int n; // $s0
	/* end block 1 */
	// End offset: 0x000F5FBC
	// End Line: 1851

	/* begin block 2 */
		// Start line: 6270
	/* end block 2 */
	// End Line: 6271

	/* begin block 3 */
		// Start line: 6277
	/* end block 3 */
	// End Line: 6278

	/* begin block 4 */
		// Start line: 6282
	/* end block 4 */
	// End Line: 6283

int FUN_MCARD__000f5f1c(int *param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *__s1;
  
  iVar2 = 0;
  if (0 < *param_1) {
    __s1 = param_1 + 5;
    piVar3 = param_1 + 3;
    do {
      if ((0 < *piVar3) && (iVar1 = strcmp((char *)__s1,param_2), iVar1 == 0)) {
        return iVar2;
      }
      __s1 = __s1 + 0x114;
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 0x114;
    } while (iVar2 < *param_1);
  }
  return 0xffffffff;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetNumGremBlocks__6MCSLOTPc(struct MCSLOT *this /*$s3*/, char *filename /*$s5*/)
 // line 1872, offset 0x000f5fbc
	/* begin block 1 */
		// Start line: 1873
		// Start offset: 0x000F5FBC
		// Variables:
	// 		int n; // $s2
	// 		int files; // $s4

		/* begin block 1.1 */
			// Start line: 1879
			// Start offset: 0x000F5FFC

			/* begin block 1.1.1 */
				// Start line: 1879
				// Start offset: 0x000F6014

				/* begin block 1.1.1.1 */
					// Start line: 1881
					// Start offset: 0x000F6014
				/* end block 1.1.1.1 */
				// End offset: 0x000F6048
				// End Line: 1884
			/* end block 1.1.1 */
			// End offset: 0x000F6048
			// End Line: 1884
		/* end block 1.1 */
		// End offset: 0x000F6060
		// End Line: 1886
	/* end block 1 */
	// End offset: 0x000F6088
	// End Line: 1888

	/* begin block 2 */
		// Start line: 6354
	/* end block 2 */
	// End Line: 6355

	/* begin block 3 */
		// Start line: 6356
	/* end block 3 */
	// End Line: 6357

int FUN_MCARD__000f5fbc(int *param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  int *piVar3;
  int *__s1;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  if (param_1[0x102d] == 0) {
    iVar5 = 0;
  }
  else {
    iVar4 = 0;
    if (0 < *param_1) {
      __s1 = param_1 + 5;
      piVar3 = param_1 + 3;
      do {
        if (0 < *piVar3) {
          sVar1 = strlen(param_2);
          iVar2 = strncmp((char *)__s1,param_2,sVar1 - 2);
          if (iVar2 == 0) {
            iVar5 = iVar5 + 1;
          }
        }
        __s1 = __s1 + 0x114;
        iVar4 = iVar4 + 1;
        piVar3 = piVar3 + 0x114;
      } while (iVar4 < *param_1);
    }
  }
  return iVar5;
}



// decompiled code
// original method signature: 
// int /*$ra*/ InsertSliceIntoCopyBuffer__6MCSLOTiPccccT2(struct MCSLOT *this /*$a0*/, int slice /*$s4*/, char *sliceName /*$a2*/, char icon0 /*$s7*/, int icon1 /*stack 16*/, int icon2 /*stack 20*/, char *dataPtr /*stack 24*/)
 // line 1896, offset 0x000f6088
	/* begin block 1 */
		// Start line: 1897
		// Start offset: 0x000F6088
		// Variables:
	// 		struct SLICEHEADER *sliceHeaderPtr; // $s1
	// 		char *sliceDataPtr; // $a3
	// 		int sliceSize; // $a2
	// 		struct SLICEHEADER dummySlice; // stack offset -72
	// 		int check; // $a1
	/* end block 1 */
	// End offset: 0x000F61F0
	// End Line: 1951

	/* begin block 2 */
		// Start line: 6408
	/* end block 2 */
	// End Line: 6409

undefined4
FUN_MCARD__000f6088(undefined4 param_1,int param_2,undefined4 param_3,undefined param_4,
                   undefined param_5,undefined param_6,void *param_7)

{
  byte *pbVar1;
  int iVar2;
  ushort *puVar3;
  size_t __n;
  int iVar4;
  void *__dest;
  size_t *psVar5;
  size_t asStack72 [8];
  
  if ((DAT_MCARD__0010ee08 & 0x1000) == 0) {
    if (DAT_MCARD__0010f07c == 0) {
      return 0xffffffff;
    }
    if (DAT_MCARD__0010f080 < param_2) {
      return 0xffffffff;
    }
    psVar5 = (size_t *)(DAT_MCARD__0010eb6c + param_2 * 0x20 + 0x200);
    *(undefined *)((int)psVar5 + 0x1b) = 0xff;
    sprintf((char *)(psVar5 + 1),(char *)&PTR_DAT_MCARD__000f3038);
    __n = *psVar5;
    *(undefined *)(psVar5 + 6) = param_4;
    *(undefined *)((int)psVar5 + 0x19) = param_5;
    *(undefined *)((int)psVar5 + 0x1a) = param_6;
    iVar2 = DAT_MCARD__0010ee40;
    iVar4 = DAT_MCARD__0010eb6c;
    *(undefined2 *)(psVar5 + 7) = 0;
    __dest = (void *)(iVar4 + iVar2 * 0x200 + 0x200 + param_2 * __n);
  }
  else {
    psVar5 = asStack72;
    pbVar1 = (byte *)((int)param_7 + 3);
    param_7 = (void *)((int)param_7 + 0x200);
    __dest = (void *)(DAT_MCARD__0010eb6c + 0x200);
    __n = (uint)*pbVar1 * 0x2000 - 0x200;
  }
  iVar4 = 0;
  if (0 < (int)__n) {
    do {
      puVar3 = (ushort *)((int)param_7 + iVar4);
      iVar4 = iVar4 + 2;
      *(ushort *)(psVar5 + 7) = *(ushort *)(psVar5 + 7) ^ *puVar3;
    } while (iVar4 < (int)__n);
  }
  memcpy(__dest,param_7,__n);
  return 0x14;
}



// decompiled code
// original method signature: 
// int /*$ra*/ ExtractSliceFromCopyBuffer__6MCSLOTiPc(struct MCSLOT *this /*$a0*/, int slice /*$a1*/, char *bufferPtr /*$a0*/)
 // line 1955, offset 0x000f61f0
	/* begin block 1 */
		// Start line: 1956
		// Start offset: 0x000F61F0
		// Variables:
	// 		struct SLICEHEADER *sliceHeaderPtr; // $a2
	// 		char *sliceDataPtr; // $a1
	/* end block 1 */
	// End offset: 0x000F628C
	// End Line: 1978

	/* begin block 2 */
		// Start line: 6564
	/* end block 2 */
	// End Line: 6565

	/* begin block 3 */
		// Start line: 6568
	/* end block 3 */
	// End Line: 6569

undefined4 FUN_MCARD__000f61f0(undefined4 param_1,int param_2,void *param_3)

{
  size_t *psVar1;
  size_t __n;
  
  if (DAT_MCARD__0010f07c != 0) {
    if (DAT_MCARD__0010f080 < param_2) {
      return 0xffffffff;
    }
    psVar1 = (size_t *)(DAT_MCARD__0010eb6c + param_2 * 0x20 + 0x200);
    if (*(char *)((int)psVar1 + 0x1b) != '\0') {
      __n = *psVar1;
      memcpy(param_3,(void *)(DAT_MCARD__0010eb6c + DAT_MCARD__0010ee40 * 0x200 + 0x200 +
                             param_2 * __n),__n);
      return 0x14;
    }
  }
  return 0xffffffff;
}



// decompiled code
// original method signature: 
// char * /*$ra*/ GetSliceFilenamePtr__6MCSLOTii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/)
 // line 1982, offset 0x000f628c
	/* begin block 1 */
		// Start line: 1983
		// Start offset: 0x000F628C
	/* end block 1 */
	// End offset: 0x000F633C
	// End Line: 1997

	/* begin block 2 */
		// Start line: 6623
	/* end block 2 */
	// End Line: 6624

	/* begin block 3 */
		// Start line: 6626
	/* end block 3 */
	// End Line: 6627

int FUN_MCARD__000f628c(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (((*(int *)(&DAT_000040b8 + param_1) != 0) &&
      (iVar1 = param_1 + param_2 * 0x450, *(int *)(iVar1 + 4) != 0)) &&
     (*(int *)(iVar1 + 0x248) != 0)) {
    if (*(int *)(iVar1 + 0x24c) < param_3) {
      return 0;
    }
    iVar1 = param_3;
    if (param_3 < 0) {
      iVar1 = param_3 + 0xf;
    }
    return param_3 * 0x20 + (iVar1 >> 4) * 0x250 + param_1 + param_2 * 0x450 + 600;
  }
  return 0;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ SliceUsed__6MCSLOTii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/)
 // line 2001, offset 0x000f633c
	/* begin block 1 */
		// Start line: 2002
		// Start offset: 0x000F633C
	/* end block 1 */
	// End offset: 0x000F63E4
	// End Line: 2016

	/* begin block 2 */
		// Start line: 6661
	/* end block 2 */
	// End Line: 6662

	/* begin block 3 */
		// Start line: 6664
	/* end block 3 */
	// End Line: 6665

uint FUN_MCARD__000f633c(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (((*(int *)(&DAT_000040b8 + param_1) != 0) &&
      (iVar1 = param_1 + param_2 * 0x450, *(int *)(iVar1 + 4) != 0)) &&
     (*(int *)(iVar1 + 0x248) != 0)) {
    if (param_3 <= *(int *)(iVar1 + 0x24c)) {
      iVar1 = param_3;
      if (param_3 < 0) {
        iVar1 = param_3 + 0xf;
      }
      return (uint)(*(char *)(param_1 + param_3 * 0x20 + (iVar1 >> 4) * 0x250 + param_2 * 0x450 +
                             0x26f) != '\0');
    }
    return 0;
  }
  return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetNoUsedSlices__6MCSLOTi(struct MCSLOT *this /*$a2*/, int block /*$a1*/)
 // line 2019, offset 0x000f63ec
	/* begin block 1 */
		// Start line: 2020
		// Start offset: 0x000F63EC
	/* end block 1 */
	// End offset: 0x000F6448
	// End Line: 2027

	/* begin block 2 */
		// Start line: 6697
	/* end block 2 */
	// End Line: 6698

undefined4 FUN_MCARD__000f63ec(int param_1,int param_2)

{
  if (((*(int *)(&DAT_000040b8 + param_1) != 0) &&
      (param_1 = param_1 + param_2 * 0x450, *(int *)(param_1 + 4) != 0)) &&
     (*(int *)(param_1 + 0x248) != 0)) {
    return *(undefined4 *)(param_1 + 0x250);
  }
  return 0xffffffff;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetSliceIconRef__6MCSLOTiii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/, int ref /*$a3*/)
 // line 2030, offset 0x000f6448
	/* begin block 1 */
		// Start line: 2031
		// Start offset: 0x000F6448
	/* end block 1 */
	// End offset: 0x000F64F4
	// End Line: 2041

	/* begin block 2 */
		// Start line: 6719
	/* end block 2 */
	// End Line: 6720

	/* begin block 3 */
		// Start line: 6723
	/* end block 3 */
	// End Line: 6724

uint FUN_MCARD__000f6448(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if ((((*(int *)(&DAT_000040b8 + param_1) != 0) &&
       (iVar1 = param_1 + param_2 * 0x450, *(int *)(iVar1 + 4) != 0)) &&
      (*(int *)(iVar1 + 0x248) != 0)) && (param_3 < *(int *)(iVar1 + 0x24c))) {
    iVar1 = param_3;
    if (param_3 < 0) {
      iVar1 = param_3 + 0xf;
    }
    return (uint)*(byte *)(param_1 + param_4 + param_3 * 0x20 + (iVar1 >> 4) * 0x250 +
                                     param_2 * 0x450 + 0x26c);
  }
  return 0xffffffff;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetNoSlices__6MCSLOTi(struct MCSLOT *this /*$a2*/, int block /*$a1*/)
 // line 2044, offset 0x000f64f4
	/* begin block 1 */
		// Start line: 2045
		// Start offset: 0x000F64F4
	/* end block 1 */
	// End offset: 0x000F6550
	// End Line: 2052

	/* begin block 2 */
		// Start line: 6747
	/* end block 2 */
	// End Line: 6748

undefined4 FUN_MCARD__000f64f4(int param_1,int param_2)

{
  if (((*(int *)(&DAT_000040b8 + param_1) != 0) &&
      (param_1 = param_1 + param_2 * 0x450, *(int *)(param_1 + 4) != 0)) &&
     (*(int *)(param_1 + 0x248) != 0)) {
    return *(undefined4 *)(param_1 + 0x24c);
  }
  return 0xffffffff;
}



// decompiled code
// original method signature: 
// unsigned int /*$ra*/ GremlinBlock__6MCSLOTi(struct MCSLOT *this /*$a2*/, int block /*$a1*/)
 // line 2055, offset 0x000f6550
	/* begin block 1 */
		// Start line: 2056
		// Start offset: 0x000F6550
	/* end block 1 */
	// End offset: 0x000F6588
	// End Line: 2059

	/* begin block 2 */
		// Start line: 6769
	/* end block 2 */
	// End Line: 6770

undefined4 FUN_MCARD__000f6550(int param_1,int param_2)

{
  undefined4 uVar1;
  
  param_1 = param_1 + param_2 * 0x450;
  uVar1 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    uVar1 = *(undefined4 *)(param_1 + 0x248);
  }
  return uVar1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ Ascii2ShiftJis__FPsPc(short *dest /*$a0*/, char *source /*$a1*/)
 // line 2067, offset 0x000f512c
	/* begin block 1 */
		// Start line: 2068
		// Start offset: 0x000F512C
		// Variables:
	// 		char a; // $a2
	// 		short scode; // $v1
	/* end block 1 */
	// End offset: 0x000F523C
	// End Line: 2116

	/* begin block 2 */
		// Start line: 4488
	/* end block 2 */
	// End Line: 4489

	/* begin block 3 */
		// Start line: 4494
	/* end block 3 */
	// End Line: 4495

void FUN_MCARD__000f512c(ushort *param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  
  bVar1 = *param_2;
  while (bVar1 != 0) {
    uVar3 = (uint)*param_2;
    pbVar2 = param_2 + 1;
    if (((uVar3 + 0x7f & 0xff) < 0x18) || ((*param_2 == 0x20 && ((uint)*pbVar2 == uVar3)))) {
      bVar1 = *pbVar2;
      uVar4 = (uint)bVar1;
      pbVar2 = param_2 + 2;
      if ((uVar4 - 0x40 < 0x3f) || (((uVar4 + 0x80 & 0xff) < 0x7d || (bVar1 == 0x20)))) {
        uVar4 = (int)(uVar3 << 0x18) >> 0x10 | uVar4;
      }
      else {
        uVar4 = 0xffff8140;
      }
    }
    else {
      uVar4 = 0xffff8140;
      if (uVar3 - 0x41 < 0x1a) {
        uVar4 = (int)((uVar3 + 0x821f) * 0x10000) >> 0x10;
      }
      if (uVar3 - 0x61 < 0x1a) {
        uVar4 = (int)((uVar3 + 0x8220) * 0x10000) >> 0x10;
      }
      if (uVar3 - 0x30 < 10) {
        uVar4 = (int)((uVar3 + 0x821f) * 0x10000) >> 0x10;
      }
    }
    *param_1 = (ushort)((uVar4 & 0xff) << 8) | (ushort)(uVar4 >> 8) & 0xff;
    bVar1 = *pbVar2;
    param_1 = param_1 + 1;
    param_2 = pbVar2;
  }
  return;
}





