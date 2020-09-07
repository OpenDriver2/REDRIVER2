#ifndef CELL_H
#define CELL_H

extern unsigned char cell_object_computed_values[2048];

extern void ClearCopUsage(); // 0x00023DC0

extern struct PACKED_CELL_OBJECT * GetFirstPackedCop(int cellx, int cellz, struct CELL_ITERATOR *pci, int use_computed); // 0x00023BAC

extern struct PACKED_CELL_OBJECT* GetNextPackedCop(struct CELL_ITERATOR* pci); // 0x0003F5F0

extern struct CELL_OBJECT* UnpackCellObject(struct PACKED_CELL_OBJECT* ppco, struct XZPAIR* near); // 0x000418E8

#endif
