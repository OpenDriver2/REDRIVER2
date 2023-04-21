#ifndef MDL_H
#define MDL_H


enum ModelShapeFlags
{
	SHAPE_FLAG_LITPOLY			= 0x1,
	SHAPE_FLAG_BSPDATA			= 0x2,
	SHAPE_FLAG_TRANS			= 0x8,
	SHAPE_FLAG_NOCOLLIDE		= 0x10,
	SHAPE_FLAG_WATER			= 0x80,		// model is water
	SHAPE_FLAG_AMBIENT2			= 0x100,	// Ambient sound 2 associated - maybe used in D1
	SHAPE_FLAG_AMBIENT1			= 0x200,	// Ambient sound 1 associated - maybe used in D1
	SHAPE_FLAG_TILE				= 0x400,	// treat as road
	SHAPE_FLAG_SHADOW			= 0x800,	// D1 leftover flag
	SHAPE_FLAG_ALPHA			= 0x1000,	// alpha tested object
	SHAPE_FLAG_ROAD				= 0x2000,	// section of road
	SHAPE_FLAG_SPRITE			= 0x4000,
};

enum ModelFlags2
{
	MODEL_FLAG_ANIMOBJ			= 0x1,		// CUSTOM FLAG!

	MODEL_FLAG_MEDIAN			= 0x20,		// Hmmmm...
	MODEL_FLAG_JUNC				= 0x40,
	MODEL_FLAG_ALLEY			= 0x80,		// alley tile
	MODEL_FLAG_INDOORS			= 0x100,
	MODEL_FLAG_CHAIR			= 0x200,
	MODEL_FLAG_BARRIER			= 0x400,
	MODEL_FLAG_SMASHABLE		= 0x800,
	MODEL_FLAG_LAMP				= 0x1000,
	MODEL_FLAG_TREE				= 0x2000,
	MODEL_FLAG_GRASS			= 0x4000,
	MODEL_FLAG_PATH				= 0x8000,
};

#define COLLISION_BOX		0
#define COLLISION_CYLINDER	1
#define COLLISION_CONE		2
#define COLLISION_SPHERE	3
#define	COLLISION_INDOORS	4

struct BOX
{
	float xmin, ymin, zmin, xmax, ymax, zmax;
};

struct BSPHERE
{
	VECTOR bounding_sphere_mid;
	float bounding_sphere;
};

struct COLLISION_PACKET
{
	short type;
	short xpos, ypos, zpos;
	short flags;
	short yang;
	short empty;
	short xsize, ysize, zsize;
};

struct SHADOWHDR
{
	u_int num_common_verts;
	u_short num_verts_total;
	u_short num_polys_total;
	u_short vert_offsets[4];
	u_short nverts[4];
	u_short npolys[4];
	u_int(*poly_block[4]);
	SVECTOR* vertices;
};

struct RGB // almost same as CVECTOR
{
	u_char r;
	u_char g;
	u_char b;
	u_char pad;
};

struct UV_INFO
{
	u_char u, v;
};

struct POLYFT4
{
	u_char id;
	u_char texture_set;
	u_char texture_id;
	u_char spare;
	u_char v0, v1, v2, v3;
	UV_INFO uv0, uv1, uv2, uv3;
	RGB color;
};

struct POLYGT4
{
	u_char id;
	u_char texture_set;
	u_char texture_id;
	u_char spare;
	u_char v0, v1, v2, v3;
	u_char n0, n1, n2, n3;
	UV_INFO uv0, uv1, uv2, uv3;
	RGB color;
};

struct PL_POLYFT4
{
	u_char id;
	u_char texture_set;
	u_char texture_id;
	u_char th;
	u_char v0, v1, v2, v3;
	UV_INFO uv0, uv1, uv2, uv3;
};


struct POLYFT3
{
	u_char id;
	u_char texture_set;
	u_char texture_id;
	u_char spare;
	u_char v0, v1, v2, pad;
	UV_INFO uv0, uv1, uv2, pad2;
	RGB color;
};

struct POLYGT3
{
	u_char id;
	u_char texture_set;
	u_char texture_id;
	u_char spare;
	u_char v0, v1, v2, pad;
	u_char n0, n1, n2, pad2;
	UV_INFO uv0, uv1, uv2, pad3;
	RGB color;
};

struct MODEL
{
	u_short shape_flags;
	u_short flags2;
	short instance_number;
	u_char tri_verts;
	unsigned char zBias;
	short bounding_sphere;
	u_short num_point_normals;
	u_short num_vertices;
	u_short num_polys;
	int vertices;
	int poly_block;
	int normals;
	int point_normals;
	int collision_block;
};


#endif // MDL_H