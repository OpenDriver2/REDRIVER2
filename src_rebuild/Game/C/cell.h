#ifndef CELL_H
#define CELL_H

extern unsigned char cell_object_computed_values[2048];

extern void ClearCopUsage(); // 0x00023DC0

extern PACKED_CELL_OBJECT * GetFirstPackedCop(int cellx, int cellz, CELL_ITERATOR *pci, int use_computed, int level = -1); // 0x00023BAC
extern PACKED_CELL_OBJECT* GetNextPackedCop(CELL_ITERATOR* pci); // 0x0003F5F0
extern CELL_OBJECT* UnpackCellObject(PACKED_CELL_OBJECT* ppco, XZPAIR* near); // 0x000418E8

#endif
