#ifndef ENGINE_CELL_H
#define ENGINE_CELL_H

struct CELL_OBJECT
{
	VECTOR_NOPAD pos;
	u_char pad;
	u_char yang;
	u_short type;
};

struct CELL_DATA
{
	u_short num;
};

struct PACKED_CELL_OBJECT
{
	USVECTOR_NOPAD pos;
	u_short value;
};

struct CELL_ITERATOR
{
	CELL_DATA* pcd;
	PACKED_CELL_OBJECT* ppco;
	XZPAIR nearCell;
	int use_computed;
};

struct OUT_CELL_FILE_HEADER
{
	int cells_across;
	int cells_down;
	int cell_size;
	int num_regions;
	int region_size;
	int num_cell_objects;
	int num_cell_data;
	int ambient_light_level;
	VECTOR_NOPAD light_source;
};


#endif // ENGINE_CELL_H