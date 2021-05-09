#ifndef LIBPRESS_H
#define LIBPRESS_H

extern void DecDCTReset(int mode);
extern int DecDCTBufSize(u_long *bs);
extern void DecDCTvlc(u_long *bs, u_long *buf);
extern void DecDCTin(u_long *buf, int mode);
extern void DecDCTout(u_long *buf, int size);
extern int DecDCTinSync( int mode) ;
extern int DecDCToutSync( int mode) ;

#endif
