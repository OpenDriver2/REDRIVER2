#ifndef LIBPRESS_H
#define LIBPRESS_H

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern void DecDCTReset(int mode);
extern int DecDCTBufSize(u_long *bs);
extern void DecDCTvlc(u_long *bs, u_long *buf);
extern void DecDCTin(u_long *buf, int mode);
extern void DecDCTout(u_long *buf, int size);
extern int DecDCTinSync( int mode) ;
extern int DecDCToutSync( int mode) ;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

	
#endif
