#ifndef	_SYS_TYPES_H
#define	_SYS_TYPES_H

#include <stdint.h>
#include <stddef.h>

#if !defined(__APPLE__)
/* major part of a device */
#define	major(x)	((int)(((unsigned)(x)>>8)&0377))

/* minor part of a device */
#define	minor(x)	((int)((x)&0377))

/* make a device number */
#define	makedev(x,y)	((dev_t)(((x)<<8) | (y)))

#endif

#ifndef _UCHAR_T
#define _UCHAR_T
typedef	unsigned char	u_char;
#endif
#ifndef _USHORT_T
#define _USHORT_T
typedef	unsigned short	u_short;
#endif
#ifndef _UINT_T
#define _UINT_T
typedef	unsigned int	u_int;
#endif
#ifndef _ULONG_T
#define _ULONG_T
typedef	unsigned long	u_long;
#endif
#ifndef _SYSIII_USHORT
#define _SYSIII_USHORT
typedef	unsigned short	ushort;		/* sys III compat */
#endif
#ifndef __psx__
#ifndef _SYSV_UINT
#define _SYSV_UINT
typedef	unsigned int	uint;		/* sys V compat */
#endif
#ifndef _SYSV_ULONG
#define _SYSV_ULONG
typedef	unsigned long	ulong;		/* sys V compat */
#endif
#endif /* ! __psx__ */

#if !__APPLE__
typedef	struct	_physadr { int r[1]; } *physadr;
typedef	struct	label_t	{
	int	val[12];
} label_t;

#if !defined(__ANDROID__)
typedef	struct	_quad { long val[2]; } quad;
typedef	long	daddr_t;
typedef	char *	caddr_t;
typedef	long *	qaddr_t;
//typedef	u_long	ino_t;
typedef	long	swblk_t;
#endif

#if !defined(__EMSCRIPTEN__)
#ifndef _SIZE_T
#define _SIZE_T
typedef	unsigned int size_t;
#endif
#endif

//typedef	long	time_t;
//typedef	short	dev_t;
//typedef	long	off_t;
//typedef	u_short	uid_t;
//typedef	u_short	gid_t;

#endif

#define	NBBY	8

#endif
