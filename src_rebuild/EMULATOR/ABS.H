#ifndef ABS_H
#define ABS_H

#ifndef ABS
#define ABS(x)		fst_abs(x)
#endif

#ifndef MIN
#define MIN(a,b)	fst_min(a,b)
#endif

#ifndef MAX
#define MAX(a,b)	fst_max(a,b)
#endif

extern int fst_abs(int x);
extern int fst_min(int a, int b);
extern int fst_max(int a, int b);

// TODO: MINMAX.H

#endif