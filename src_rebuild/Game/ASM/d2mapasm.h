#ifndef D2MAPASM_H
#define D2MAPASM_H

extern uint region_buffer_xor;
extern uint sdSelfModifyingCode; // 0x00012D18

extern sdPlane*	sdGetCell_asm(int param_2, short** roadMapData, int pos_x, int pos_z, int pos_y, int _sdLevel);

extern sdPlane* sdGetCell_alpha16(VECTOR* pos);
extern int		RoadInCell_alpha16(VECTOR* pos);

#endif
