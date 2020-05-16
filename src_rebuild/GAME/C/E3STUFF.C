#include "THISDUST.H"
#include "E3STUFF.H"

#include "PAD.H"
#include "LIBETC.H"
#include "SYSTEM.H"
#include "PRES.H"
#include "PAUSE.H"

#undef v0

POLYCOORD polycoords[6] =
{
  { 0, 0, 640, 0, 256, 256 },
  { 256, 0, 768, 0, 256, 256 },
  { 512, 0, 896, 0, 128, 256 },
  { 0, 256, 640, 256, 256, 256 },
  { 256, 256, 768, 256, 256, 256 },
  { 512, 256, 896, 256, 128, 256 }
};

// decompiled code
// original method signature: 
// void /*$ra*/ ShowHiresScreens(char **names /*$s1*/, int delay /*$s4*/, int wait /*$s3*/)
 // line 139, offset 0x00044ce0
	/* begin block 1 */
		// Start line: 140
		// Start offset: 0x00044CE0
		// Variables:
	// 		char *filename; // $a0
	// 		int timedelay; // $s0
	/* end block 1 */
	// End offset: 0x00044DA0
	// End Line: 164

	/* begin block 2 */
		// Start line: 278
	/* end block 2 */
	// End Line: 279

// [D]
void ShowHiresScreens(char **names, int delay, int wait)
{
	int timedelay;
	char *filename;

	filename = *names;

	do {
		if (!filename) 
			return;

		FadeInHiresScreen(filename);

		timedelay = delay-1;

		do {
			if (timedelay == 0)
				break;

			VSync(0);

			ReadControllers();
			timedelay--;

		} while ((wait != 0) || (Pads[0].dirnew & 0x40) == 0);

		FadeOutHiresScreen();

		filename = *(++names);
	} while (true);
}


// decompiled code
// original method signature: 
// void /*$ra*/ FadeInHiresScreen(char *filename /*stack 0*/)
 // line 171, offset 0x00044244
	/* begin block 1 */
		// Start line: 172
		// Start offset: 0x00044244
		// Variables:
	// 		struct DISPENV disp; // stack offset -488
	// 		struct DRAWENV draw; // stack offset -464
	// 		struct SPRT prims[6]; // stack offset -368
	// 		struct POLY_FT3 nulls[6]; // stack offset -248
	// 		struct RECT rect; // stack offset -56
	// 		unsigned long ot; // stack offset -48
	// 		int i; // $t5
	// 		int col; // $s1
	/* end block 1 */
	// End offset: 0x000445F4
	// End Line: 251

	/* begin block 2 */
		// Start line: 302
	/* end block 2 */
	// End Line: 303

	/* begin block 3 */
		// Start line: 342
	/* end block 3 */
	// End Line: 343

// [D]
void FadeInHiresScreen(char *filename)
{
	UNIMPLEMENTED();
	
	int col;
	
	DISPENV disp;
	DRAWENV draw;
	SPRT prims[6];
	POLY_FT3 nulls[6];
	RECT16 rect;
	OTTYPE ot;

	POLY_FT3 *poly;
	SPRT *prim;
	POLYCOORD *pc;

	DrawSync(0);
	VSync(0);
	SetDispMask(0);
	ResetGraph(3);

	setRECT16(&rect, 0, 0, 512, 512);
	ClearImage2(&rect, 0, 0, 0);
	DrawSync(0);

	setRECT16(&rect, 512, 0, 512, 512);
	ClearImage2(&rect, 0, 0, 0);
	DrawSync(0);

	poly = nulls;
	pc = polycoords;

	prim = prims;

	// prepare polygons
	for(int i = 0; i < 6; i++)
	{
		// set primitive
		setSprt(prim);
		setUV0(prim, 0, 0);

		setClut(prim, 640, 511);

		setXY0(prim, pc->x, pc->y);
		setWH(prim, pc->w, pc->h);

		// set poly
		// FIXME: this is some hacky way to display textured SPRT. OLD SDK?
		setPolyFT3(poly);
		setXY3(poly, -1,-1,-1,-1,-1,-1);

		setTPage(poly, 1, 0, pc->u, pc->v);

		prim++;
		poly++;
		pc++;
	}

	SetupDefDrawEnv(&draw, 0, 0, 640, 512);
	SetupDefDispEnv(&disp, 0, 0, 640, 512);
	VSync(0);
	PutDispEnv(&disp);
	PutDrawEnv(&draw);

	LoadfileSeg(filename, _overlay_buffer, 20, 0x4ff80);
	LoadClut((u_long*)_overlay_buffer, 640, 511);

	DrawSync(0);
	setRECT16(&rect, 640, 0, 320, 511);

	LoadImage(&rect, (u_long*)&_overlay_buffer[512]);

	DrawSync(0);
	SetDispMask(1);

	col = 0;

	do {
		DrawSync(0);
		VSync(0);
		PutDispEnv(&disp);
		PutDrawEnv(&draw);
		ClearOTagR((u_long*)&ot, 1);
		
		poly = nulls;
		prim = prims;

		for (int i = 0; i < 6; i++)
		{
			if (col < 129) 
			{
				setRGB0(prim, col, col, col);
			}
			else 
			{
				setRGB0(prim, 128, 128, 128);
			}

			// UNCERTAIN CODE
			// LEARN TO DECOMPILE MIPS FIRST
			addPrim(&ot, prim);
			addPrim(&ot, poly);
			poly++; prim++;
		}

		DrawOTag((u_long*)&ot);
		col += 4;
	} while (col < 140);

	DrawSync(0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ FadeOutHiresScreen()
 // line 258, offset 0x000445f4
	/* begin block 1 */
		// Start line: 260
		// Start offset: 0x000445F4
		// Variables:
	// 		struct DISPENV disp; // stack offset -496
	// 		struct DRAWENV draw; // stack offset -472
	// 		struct SPRT prims[6]; // stack offset -376
	// 		struct POLY_FT3 nulls[6]; // stack offset -256
	// 		struct RECT rect; // stack offset -64
	// 		unsigned long ot; // stack offset -56
	// 		int i; // $t5
	// 		int col; // $s1
	/* end block 1 */
	// End offset: 0x000448CC
	// End Line: 318

	/* begin block 2 */
		// Start line: 662
	/* end block 2 */
	// End Line: 663

	/* begin block 3 */
		// Start line: 670
	/* end block 3 */
	// End Line: 671

	/* begin block 4 */
		// Start line: 671
	/* end block 4 */
	// End Line: 672

	/* begin block 5 */
		// Start line: 680
	/* end block 5 */
	// End Line: 681

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void FadeOutHiresScreen(void)
{
	UNIMPLEMENTED();

	int col;

	DISPENV disp;
	DRAWENV draw;
	SPRT prims[6];
	POLY_FT3 nulls[6];
	RECT16 rect;
	OTTYPE ot;

	POLY_FT3 *poly;
	SPRT *prim;
	POLYCOORD *pc;

	poly = nulls;
	pc = polycoords;

	prim = prims;

	// prepare polygons
	for (int i = 0; i < 6; i++)
	{
		// set primitive
		setSprt(prim);
		setUV0(prim, 0, 0);

		setClut(prim, 640, 511);

		setXY0(prim, pc->x, pc->y);
		setWH(prim, pc->w, pc->h);

		// set poly
		setPolyFT3(poly);
		setXY3(poly, -1, -1, -1, -1, -1, -1);

		setTPage(poly, 1, 0, pc->u, pc->v);

		prim++;
		poly++;
		pc++;
	}

	SetupDefDrawEnv(&draw, 0, 0, 640, 512);
	SetupDefDispEnv(&disp, 0, 0, 640, 512);
	VSync(0); 
	PutDispEnv(&disp);
	PutDrawEnv(&draw);

	//g_wireframeMode = 1;

	DrawSync(0);
	SetDispMask(1);

	col = 128;
	do {
		DrawSync(0);
		VSync(0);
		PutDispEnv(&disp);
		PutDrawEnv(&draw);
		ClearOTagR((u_long*)&ot, 1);

		poly = nulls;
		prim = prims;

		for (int i = 0; i < 6; i++)
		{
			setRGB0(prim, col, col, col);

			// UNCERTAIN CODE
			// LEARN TO DECOMPILE MIPS FIRST
			addPrim(&ot, prim);
			addPrim(&ot, poly);
			poly++; prim++;
		}

		DrawOTag((u_long*)&ot);
		col -= 4;
	} while (col > -4);


	DrawSync(0);

	setRECT16(&rect, 0, 0, 640, 512);
	ClearImage2(&rect, 0, 0, 0);
	DrawSync(0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDefDrawEnv(struct DRAWENV *env /*$a0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/)
 // line 325, offset 0x00044e40
	/* begin block 1 */
		// Start line: 650
	/* end block 1 */
	// End Line: 651

void SetupDefDrawEnv(DRAWENV *env, int x, int y, int w, int h)
{
	if (h < 257) {
		SetDefDrawEnv(env, x, y, w, 256);
	}
	else {
		SetDefDrawEnv(env, x, y, w, 512);
	}
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDefDispEnv(struct DISPENV *env /*$s0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/)
 // line 350, offset 0x00044da0
	/* begin block 1 */
		// Start line: 1213
	/* end block 1 */
	// End Line: 1214

	/* begin block 2 */
		// Start line: 1400
	/* end block 2 */
	// End Line: 1401


void SetupDefDispEnv(DISPENV *env, int x, int y, int w, int h)
{
	short framey;

	if (h < 0x101) {
		SetDefDispEnv(env, x, y, w, 256);
		env->screen.x = draw_mode.framex;
		framey = draw_mode.framey;
		env->screen.h = 255;
		env->isinter = 0;
	}
	else {
		SetDefDispEnv(env, x, y, w, 512);
		env->screen.x = draw_mode.framex;
		framey = draw_mode.framey;
		env->screen.h = 255;
		env->isinter = 1;
	}
	env->screen.y = framey;
	env->isrgb24 = 0;
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetPleaseWait(char *buffer /*$s2*/)
 // line 391, offset 0x000448cc
	/* begin block 1 */
		// Start line: 392
		// Start offset: 0x000448CC
		// Variables:
	// 		struct DISPENV disp; // stack offset -144
	// 		struct DRAWENV draw; // stack offset -120
	// 		struct RECT rect; // stack offset -24
	// 		char *exe; // $a0
	/* end block 1 */
	// End offset: 0x00044A40
	// End Line: 435

	/* begin block 2 */
		// Start line: 983
	/* end block 2 */
	// End Line: 984

	/* begin block 3 */
		// Start line: 1057
	/* end block 3 */
	// End Line: 1058

int lastrequesteddisc = 0;

// [D]
void SetPleaseWait(char *buffer)
{
	UNIMPLEMENTED();

	CDTYPE CVar1;
	//undefined3 extraout_var;
	char *filename;
	DISPENV disp;
	DRAWENV draw;
	RECT16 rect;

	DrawSync(0);
	VSync(0);
	SetDispMask(0);
	SetupDefDrawEnv(&draw,0,0,320,256);
	SetupDefDispEnv(&disp,0,0, 320, 256);
	draw.dfe = '\x01';
	PutDrawEnv(&draw);
	PutDispEnv(&disp);
	LoadFont(buffer);
	if (buffer == NULL) {
		SetupDrawBuffers();
	}
	else {
		current->primptr = buffer;
	}
	rect.x = 0;
	rect.y = 0;
	rect.w = 320;
	rect.h = 512;
	ClearImage(&rect,0,0,0);
	DrawSync(0);
	gShowMap = 1;
	SetTextColour(128, 128, 128);
	PrintStringCentred("Please wait...",128);
	gShowMap = 0;
	VSync(0);
	SetDispMask(1);
#ifdef PSX
	if (lastrequesteddisc == 0) {
		filename = "\\SLES_029.96;1";
	}
	else {
		filename = "\\SLES_029.96;1";
	}
	CVar1 = DiscSwapped(filename);
	if (CVar1 != 4) {
		ResetCityType();
	}
#else
	ResetCityType();
#endif // PSX
	
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckForCorrectDisc(int disc /*$s0*/)
 // line 443, offset 0x00044a40
	/* begin block 1 */
		// Start line: 444
		// Start offset: 0x00044A40
		// Variables:
	// 		struct DISPENV disp; // stack offset -160
	// 		struct DRAWENV draw; // stack offset -136
	// 		struct RECT rect; // stack offset -40
	// 		char *mess1; // $s6
	// 		char *mess2; // $s3
	// 		char *exe; // $s4
	// 		int ret; // $s0
	// 		int discerror; // $s5

		/* begin block 1.1 */
			// Start line: 492
			// Start offset: 0x00044B70
		/* end block 1.1 */
		// End offset: 0x00044BF4
		// End Line: 522
	/* end block 1 */
	// End offset: 0x00044CB8
	// End Line: 538

	/* begin block 2 */
		// Start line: 1162
	/* end block 2 */
	// End Line: 1163

	/* begin block 3 */
		// Start line: 1171
	/* end block 3 */
	// End Line: 1172

	/* begin block 4 */
		// Start line: 1178
	/* end block 4 */
	// End Line: 1179

void CheckForCorrectDisc(int disc)
{
	UNIMPLEMENTED();

	/*
	CDTYPE CVar1;
	undefined3 extraout_var;
	undefined3 extraout_var_00;
	char *message;
	char *filename;
	int iVar2;
	char *pString;
	DISPENV DStack160;
	DRAWENV DStack136;
	undefined2 ot;
	undefined2 local_26;
	undefined2 local_24;
	undefined2 local_22;

	iVar2 = 0;
	if (lastrequesteddisc != disc) {
		lastrequesteddisc = disc;
		ResetCityType();
	}
	if (disc == 0) {
		pString = s_Inserisci_il_DISCO_1_0001089c;
		filename = s__SLES_029_96_1_0001087c;
	}
	else {
		pString = s_Inserisci_il_DISCO_2_000108b4;
		filename = s__SLES_129_96_1_0001088c;
	}
	CVar1 = DiscSwapped(filename);
	if (CONCAT31(extraout_var, CVar1) != 4) {
		LoadFont((char *)0x0);
		SetupDrawBuffers();
		DrawSync(0);
		VSync(0);
		SetDispMask(0);
		ot = 0;
		local_26 = 0;
		local_24 = 0x140;
		local_22 = 0x200;
		ClearImage(&ot, 0, 0, 0);
		DrawSync(0);
		SetupDefDrawEnv(&DStack136, 0, 0, 0x140, 0x100);
		SetupDefDispEnv(&DStack160, 0, 0, 0x140, 0x100);
		DStack136.dfe = '\x01';
		PutDrawEnv(&DStack136);
		PutDispEnv(&DStack160);
		SetDispMask(1);
		do {
			VSync(10);
			CVar1 = DiscSwapped(filename);
			switch (CONCAT31(extraout_var_00, CVar1)) {
			case 0:
				iVar2 = 0;
			LAB_00044bd4:
				message = s_Nessun_DISCO_inserito_000108cc;
				break;
			case 1:
			case 4:
				iVar2 = 0;
				message = (char *)0xaa46c;
				break;
			case 2:
				iVar2 = iVar2 + 1;
				if (0x1d < iVar2) goto LAB_00044bd4;
				message = s_Verifica_in_corso____000108e4;
				break;
			case 3:
				iVar2 = 0;
				message = s_Hai_inserito_il_DISCO_errato_000108fc;
			}
			VSync(0);
			local_26 = 0x6e;
			ot = 0;
			local_24 = 0x140;
			local_22 = 0x3c;
			ClearImage(&ot, 0, 0, 0);
			DrawSync(0);
			gShowMap = 1;
			SetTextColour(-0x80, -0x80, -0x80);
			PrintStringCentred(pString, 0x6e);
			SetTextColour(-0x80, '\x10', '\x10');
			PrintStringCentred(message, 0x8c);
			gShowMap = 0;
		} while (CONCAT31(extraout_var_00, CVar1) != 4);
		ot = 0;
		local_26 = 0;
		local_24 = 0x140;
		local_22 = 0x200;
		ClearImage(&ot, 0, 0, 0);
		DrawSync(0);
	}
	return;
	*/
}





