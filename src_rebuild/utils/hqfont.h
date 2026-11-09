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

static int DecodeUTF8Character(const char* text, int* characterSize)
{
	const u_char* bytes = (const u_char*)text;

	*characterSize = 1;

	if (bytes[0] < 0x80)
		return bytes[0];

	if (bytes[0] >= 0xC2 && bytes[0] <= 0xDF &&
		(bytes[1] & 0xC0) == 0x80)
	{
		*characterSize = 2;
		return ((bytes[0] & 0x1F) << 6) | (bytes[1] & 0x3F);
	}

	if (bytes[0] >= 0xE0 && bytes[0] <= 0xEF &&
		(bytes[1] & 0xC0) == 0x80 && (bytes[2] & 0xC0) == 0x80)
	{
		*characterSize = 3;
		return ((bytes[0] & 0x0F) << 12) | ((bytes[1] & 0x3F) << 6) | (bytes[2] & 0x3F);
	}

	// Preserve legacy single-byte text and controller button codes.
	return bytes[0];
}

#endif // HQFONT_H