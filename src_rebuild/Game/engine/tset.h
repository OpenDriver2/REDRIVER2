#ifndef TSET_H
#define TSET_H

// Texture Set definitions

struct UV
{
	u_char u0, v0;
	u_char u1, v1;
	u_char u2, v2;
	u_char u3, v3;
};

struct TEXTURE_DETAILS
{
	UV coords;
	u_short tpageid;
	u_short clutid;
	char texture_number;
	char texture_page;
};

struct TP
{
	u_int flags;
	u_int offset;
};

struct TEXINF
{
	u_short id;
	u_short nameoffset;
	u_char x, y, width, height;
};

struct TPAN
{
	u_char texture_page;
	u_char texture_number;
};

#endif // TSET_H