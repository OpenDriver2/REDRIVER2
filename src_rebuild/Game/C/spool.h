#ifndef SPOOL_H
#define SPOOL_H

extern int cell_objects_add[5];
extern int cell_slots_add[5];

extern char* specmallocptr;
extern char *specLoadBuffer;

extern char specModelValid;
extern int allowSpecSpooling;
extern int startSpecSpool;

extern int doSpooling;
extern int LoadingArea;

extern short loading_region[4];
extern int regions_unpacked[4];

extern unsigned short *spoolinfo_offsets;
extern char* RegionSpoolInfo;

extern char* packed_cell_pointers;

extern int RoadMapRegions[4];

extern volatile int spoolactive;
extern int spoolpos_reading;
extern int chunk_complete;
extern volatile int spoolactive;

extern void ProcessSpoolInfoLump(char *lump_ptr, int lump_size); // 0x0007C464

extern void InitSpooling(); // 0x0007E494
extern void UpdateSpool(); // 0x0007B6C4
extern void CheckValidSpoolData(); // 0x0007E2CC

extern void LoadInAreaTSets(int area); // 0x0007BB14
extern void LoadInAreaModels(int area); // 0x0007E580

extern void CheckLoadAreaData(int cellx, int cellz); // 0x0007C08C

extern void ClearRegion(int target_region); // 0x0007E3E4
extern void UnpackRegion(int region_to_unpack, int target_barrel_region); // 0x0007E5DC

extern void StartSpooling(); // 0x0007E724
extern void SpoolSYNC(void);

extern void InitSpecSpool(); // 0x0007D6D8

extern void CheckSpecialSpool(); // 0x0007D4E0
extern void QuickSpoolSpecial(); // 0x0007E84C

extern void PrepareSecretCar(); // 0x0007E8DC

#endif
