#ifndef CELL_H
#define CELL_H


extern void ClearCopUsage(); // 0x00023DC0

extern struct PACKED_CELL_OBJECT * GetFirstPackedCop(int cellx, int cellz, struct CELL_ITERATOR *pci, int use_computed); // 0x00023BAC


#endif
