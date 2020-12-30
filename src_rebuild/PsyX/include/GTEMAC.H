#ifndef GTEMAC_H
#define GTEMAC_H

/*
 * GTE inline functions(Simple)
 */

#define gte_RotTransPers(r1,r2,r3,r4,r5)   			\
				{	gte_ldv0(r1);   	\
                    gte_rtps();     	\
                    gte_stsxy(r2); 		\
                    gte_stdp(r3);   	\
                    gte_stflg(r4);		\
					gte_stszotz(r5);	}

#define gte_RotTransPers3(r1,r2,r3,r4,r5,r6,r7,r8,r9)		\
				{	gte_ldv3(r1,r2,r3);	\
					gte_rtpt();		\
					gte_stsxy3(r4,r5,r6);	\
					gte_stdp(r7);		\
					gte_stflg(r8);		\
					gte_stszotz(r9);	}

#define gte_RotTrans(r1,r2,r3)					\
				{	gte_ldv0(r1);   	\
					gte_rt();		\
					gte_stlvnl(r2);		\
					gte_stflg(r3);	}

#define gte_LocalLight(r1,r2)					\
				{	gte_ldv0(r1); 		\
					gte_ll();		\
					gte_stlvl(r2);	}

#define gte_LightColor(r1,r2)					\
				{	gte_ldlvl(r1);		\
					gte_lc();		\
					gte_stlvl(r2);	}

#define gte_DpqColorLight(r1,r2,r3,r4)				\
				{	gte_ldlvl(r1);		\
					gte_ldrgb(r2);		\
					gte_lddp(r3);		\
					gte_dpcl();		\
					gte_strgb(r4);	}

#define gte_DpqColor(r1,r2,r3)					\
				{	gte_ldrgb(r1);		\
					gte_lddp(r2);		\
					gte_dpcs();		\
					gte_strgb(r3);	}

#define gte_DpqColor3(r1,r2,r3,r4,r5,r6,r7)			\
				{	gte_ldrgb3(r1,r2,r3);	\
					gte_lddp(r4);		\
					gte_dpct();		\
					gte_strgb3(r5,r6,r7);	}

#define gte_Intpl(r1,r2,r3)					\
				{	gte_ldlvl(r1);		\
					gte_lddp(r2);		\
					gte_intpl();		\
					gte_strgb(r3);	}

#define gte_Square12(r1,r2)					\
				{	gte_ldlvl(r1);		\
					gte_sqr12();		\
					gte_stlvnl(r2);	}	

#define gte_Square0(r1,r2)					\
				{	gte_ldlvl(r1);		\
					gte_sqr0();		\
					gte_stlvnl(r2);	}	

#define gte_NormalColor(r1,r2)					\
				{	gte_ldv0(r1);		\
					gte_ncs();		\
					gte_strgb(r2);	}

#define gte_NormalColor3(r1,r2,r3,r4,r5,r6)			\
				{	gte_ldv3(r1,r2,r3);	\
					gte_nct();		\
					gte_strgb3(r4,r5,r6);	}

#define gte_NormalColorDpq(r1,r2,r3,r4)				\
				{	gte_ldv0(r1);		\
					gte_ldrgb(r2);		\
					gte_lddp(r3);		\
					gte_ncds();		\
					gte_strgb(r4);	}

#define gte_NormalColorDpq3(r1,r2,r3,r4,r5,r6,r7,r8)		\
				{	gte_ldv3(r1,r2,r3);	\
					gte_ldrgb(r4);		\
					gte_lddp(r5);		\
					gte_ncdt();		\
					gte_strgb3(r6,r7,r8);	}

#define gte_NormalColorCol(r1,r2,r3) 				\
				{	gte_ldv0(r1);		\
					gte_ldrgb(r2);		\
					gte_nccs();		\
					gte_strgb(r3);	}

#define gte_NormalColorCol3(r1,r2,r3,r4,r5,r6,r7)		\
				{	gte_ldv3(r1,r2,r3);	\
					gte_ldrgb(r4);		\
					gte_ncct();		\
					gte_strgb3(r5,r6,r7);	}

#define gte_ColorDpq(r1,r2,r3,r4)				\
				{	gte_ldlvl(r1);		\
					gte_ldrgb(r2);		\
					gte_lddp(r3);		\
					gte_cdp();		\
					gte_strgb(r4);	}

#define gte_ColorCol(r1,r2,r3)					\
				{	gte_ldlvl(r1);		\
					gte_ldrgb(r2);		\
					gte_cc();		\
					gte_strgb(r3);	}

#define gte_NormalClip(r1,r2,r3,r4)				\
				{	gte_ldsxy3(r1,r2,r3);	\
					gte_nclip();		\
					gte_stopz(r4);	}

#define gte_AverageZ3(r1,r2,r3,r4)				\
				{	gte_ldsz3(r1,r2,r3);	\
					gte_avsz3();		\
					gte_stotz(r4);	}

#define gte_AverageZ4(r1,r2,r3,r4,r5)				\
				{	gte_ldsz4(r1,r2,r3,r4);	\
					gte_avsz4();		\
					gte_stotz(r5);	}

#define gte_OuterProduct12(r1,r2,r3)				\
				{	gte_ldopv1(r1);		\
					gte_ldopv2(r2);		\
					gte_op12();		\
					gte_stlvnl(r3); }

#define gte_OuterProduct0(r1,r2,r3)				\
				{	gte_ldopv1(r1);		\
					gte_ldopv2(r2);		\
					gte_op0();		\
					gte_stlvnl(r3); }

#define gte_OuterProduct12SVL(r1,r2,r3)				\
				{	gte_ldopv1SV(r1);	\
					gte_ldopv2SV(r2);	\
					gte_op12();		\
					gte_stlvnl(r3); }

#define gte_OuterProduct0SVL(r1,r2,r3)				\
				{	gte_ldopv1SV(r1);	\
					gte_ldopv2SV(r2);	\
					gte_op0();		\
					gte_stlvnl(r3); }

#define gte_OuterProduct12SV(r1,r2,r3)				\
				{	gte_ldopv1SV(r1);	\
					gte_ldopv2SV(r2);	\
					gte_op12();		\
					gte_stsv(r3); }

#define gte_OuterProduct0SV(r1,r2,r3)				\
				{	gte_ldopv1SV(r1);	\
					gte_ldopv2SV(r2);	\
					gte_op0();		\
					gte_stsv(r3); }

#define gte_Lzc(r1,r2)						\
				{	gte_ldlzc(r1);		\
					gte_nop();		\
					gte_nop();		\
					gte_stlzc(r2);	}

 /*
  * GTE inline functions(Combination)
  *	4 vertices functions can't be replaced by equivalent macros
  *	because they use OR of flags after rtpt & rtps
  *	Please write directry in your program.
  */
#define gte_RotAverage3(r1,r2,r3,r4,r5,r6,r7,r8,r9)		\
				{	gte_ldv3(r1,r2,r3);	\
					gte_rtpt();		\
					gte_stsxy3(r4,r5,r6);	\
                                        gte_stdp(r7);		\
                                        gte_stflg(r8);		\
					gte_avsz3();		\
					gte_stotz(r9);	}

#define gte_RotNclip3(r1,r2,r3,r4,r5,r6,r7,r8,r9,r10)		\
				{	gte_ldv3(r1,r2,r3);	\
					gte_rtpt();		\
                                        gte_stflg(r9);		\
					gte_nclip();		\
					gte_stopz(r10);		\
					gte_stsxy3(r4,r5,r6);	\
					gte_stdp(r7);		\
					gte_stszotz(r8);	}

#define gte_RotAverageNclip3(r1,r2,r3,r4,r5,r6,r7,r8,r9,r10)	\
				{	gte_ldv3(r1,r2,r3);	\
					gte_rtpt();		\
                                        gte_stflg(r9);		\
					gte_nclip();		\
					gte_stopz(r10);		\
					gte_stsxy3(r4,r5,r6);	\
					gte_stdp(r7);		\
					gte_avsz3();		\
					gte_stotz(r8);	}

#define gte_RotColorDpq(r1,r2,r3,r4,r5,r6,r7)			\
				{	gte_ldv0(r1);		\
					gte_rtps();		\
					gte_stsxy(r4);		\
					gte_stflg(r6);		\
					gte_ldv0(r2);		\
					gte_ldrgb(r3);		\
					gte_ncds();		\
					gte_strgb(r5);		\
					gte_stszotz(r7);	}

#define gte_RotColorDpq3(r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15) \
				{	gte_ldv3(r1,r2,r3);	\
					gte_rtpt();		\
					gte_stsxy3(r8,r9,r10);	\
					gte_stflg(r14);		\
					gte_ldv3(r4,r5,r6);	\
					gte_ldrgb(r7);		\
					gte_ncdt();		\
					gte_strgb3(r11,r12,r13);\
					gte_stszotz(r15);	}

#define gte_RotAverageNclipColorDpq3(r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16)	\
				{	gte_ldv3(r1,r2,r3);	\
					gte_rtpt();		\
					gte_stflg(r15);		\
					gte_nclip();		\
					gte_stopz(r16);		\
					gte_ldv3(r4,r5,r6);	\
					gte_ldrgb(r7);		\
					gte_ncdt();		\
					gte_stsxy3(r8,r9,r10);	\
					gte_strgb3(r11,r12,r13);\
					gte_avsz3();		\
					gte_stotz(r14);	}

#define gte_RotAverageNclipColorCol3(r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16)	\
				{	gte_ldv3(r1,r2,r3);	\
					gte_rtpt();		\
					gte_stflg(r15);		\
					gte_nclip();		\
					gte_stopz(r16);		\
					gte_ldv3(r4,r5,r6);	\
					gte_ldrgb(r7);		\
					gte_ncct();		\
					gte_stsxy3(r8,r9,r10);	\
					gte_strgb3(r11,r12,r13);\
					gte_avsz3();		\
					gte_stotz(r14);	}

#define gte_LoadAverage12(r1,r2,r3,r4,r5)			\
				{	gte_lddp(r3);		\
					gte_ldlvl(r1);		\
					gte_gpf12();		\
					gte_lddp(r4);		\
					gte_ldlvl(r2);		\
					gte_gpl12();		\
					gte_stlvl(r5);	}

#define gte_LoadAverage0(r1,r2,r3,r4,r5)			\
				{	gte_lddp(r3);		\
					gte_ldlvl(r1);		\
					gte_gpf0();		\
					gte_lddp(r4);		\
					gte_ldlvl(r2);		\
					gte_gpl0();		\
					gte_stlvl(r5);	}

#define gte_LoadAverageShort12(r1,r2,r3,r4,r5)			\
				{	gte_lddp(r3);		\
					gte_ldsv(r1);		\
					gte_gpf12();		\
					gte_lddp(r4);		\
					gte_ldsv(r2);		\
					gte_gpl12();		\
					gte_stsv(r5);	}

#define gte_LoadAverageShort0(r1,r2,r3,r4,r5)			\
				{	gte_lddp(r3);		\
					gte_ldsv(r1);		\
					gte_gpf0();		\
					gte_lddp(r4);		\
					gte_ldsv(r2);		\
					gte_gpl0();		\
					gte_stsv(r5);	}

#define gte_LoadAverageByte(r1,r2,r3,r4,r5)			\
				{	gte_lddp(r3);		\
					gte_ldbv(r1);		\
					gte_gpf12();		\
					gte_lddp(r4);		\
					gte_ldbv(r2);		\
					gte_gpl12();		\
					gte_stbv(r5);	}

#define gte_LoadAverageCol(r1,r2,r3,r4,r5)			\
				{	gte_lddp(r3);		\
					gte_ldcv(r1);		\
					gte_gpf12();		\
					gte_lddp(r4);		\
					gte_ldcv(r2);		\
					gte_gpl12();		\
					gte_stcv(r5);	}

  /*
   *
   */
#define gte_MulMatrix0(r1,r2,r3)				\
				{	gte_SetRotMatrix(r1);	\
					gte_ldclmv(r2);		\
					gte_rtir();		\
					gte_stclmv(r3);		\
					gte_ldclmv((char*)r2+2);\
					gte_rtir();		\
					gte_stclmv((char*)r3+2);\
					gte_ldclmv((char*)r2+4);\
					gte_rtir();		\
					gte_stclmv((char*)r3+4);	}

#define gte_ApplyMatrix(r1,r2,r3)				\
				{	gte_SetRotMatrix(r1);   \
					gte_ldv0(r2);		\
					gte_rtv0();		\
					gte_stlvnl(r3);	}

#define gte_ApplyMatrixSV(r1,r2,r3)				\
				{	gte_SetRotMatrix(r1);   \
					gte_ldv0(r2);		\
					gte_rtv0();		\
					gte_stsv(r3);	}

#define gte_CompMatrix(r1,r2,r3)				\
				{	gte_MulMatrix0(r1,r2,r3);\
					gte_SetTransMatrix(r1);	\
					gte_ldlv0((char*)r2+20);\
					gte_rt();		\
					gte_stlvnl((char*)r3+20);	}

#define gte_ApplyRotMatrix(r1,r2)				\
				{	gte_ldv0(r1);		\
					gte_rtv0();		\
					gte_stlvnl(r2);		}

#endif