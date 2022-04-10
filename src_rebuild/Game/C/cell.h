#ifndef CELL_H
#define CELL_H

extern unsigned char cell_object_computed_values[2048];

extern void ClearCopUsage(); // 0x00023DC0

extern PACKED_CELL_OBJECT * GetFirstPackedCop(int cellx, int cellz, CELL_ITERATOR *pci, int use_computed, int level = -1); // 0x00023BAC
extern PACKED_CELL_OBJECT* GetNextPackedCop(CELL_ITERATOR* pci); // 0x0003F5F0

inline void QuickUnpackCellObject(PACKED_CELL_OBJECT* ppco, XZPAIR* near, CELL_OBJECT* pco)
{
	pco->pos.vx = near->x + (short)(ppco->pos.vx - near->x);
	pco->pos.vz = near->z + (short)(ppco->pos.vz - near->z);

	pco->pos.vy = (short)ppco->pos.vy >> 1;

	pco->yang = ppco->value & 63;
	pco->type = (ppco->value >> 6) | ((ppco->pos.vy & 1) << 10);
}

#endif
