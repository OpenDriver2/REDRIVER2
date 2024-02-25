#ifndef HQFONT_H
#define HQFONT_H

#define FN2_VERSION 1
#define HIRES_FONT_SIZE_W	768
#define HIRES_FONT_SIZE_H	768

struct OUT_FN2INFO
{
	u_short x0, y0, x1, y1;
	float xoff, yoff, xadvance;
	float xoff2, yoff2;
};

struct OUT_FN2RANGE
{
	u_short start;
	u_short count;
};

struct OUT_FN2HEADER
{
	u_short version;
	u_short range_count;
};

#endif // HQFONT_H