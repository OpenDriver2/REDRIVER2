#ifndef TARGA_H
#define TARGA_H

#include <types.h>

#pragma pack (push, 1)

struct TGAHeader
{
	u_char  descriptionlen;
	u_char  cmaptype;
	u_char  imagetype;
	u_short cmapstart;
	u_short cmapentries;
	u_char  cmapbits;
	u_short xoffset;
	u_short yoffset;
	u_short width;
	u_short height;
	u_char  bpp;
	u_char  attrib;
};

#pragma pack (pop)

bool LoadTGAImage(const char* filename, u_char** data, int& width, int& height, int& bpp);

#endif // TARGA_H