#ifndef SPOOL_H
#define SPOOL_H

extern int cell_objects_add[5];
extern int cell_slots_add[5];

extern char* specmallocptr;
extern char *specLoadBuffer;

extern int allowSpecSpooling;
extern int startSpecSpool;

extern int doSpooling;

extern short loading_region[4];;
extern int regions_unpacked[4];

extern unsigned short *spoolinfo_offsets;
extern char* RegionSpoolInfo;

extern char* packed_cell_pointers;

typedef void(*spooledFuncPtr)();

extern void test_changemode(); // 0x0007B228

extern void changemode(SPOOLQ *current); // 0x0007E1A8

extern int check_regions_present(); // 0x0007B3C4

extern void stopgame(); // 0x0007E958

extern void startgame(); // 0x0007E9A0

extern void DrawCDicon(); // 0x0007E24C

extern void CheckValidSpoolData(); // 0x0007E2CC

extern void UpdateSpool(); // 0x0007B6C4

extern void RequestSpool(int type, int data, int offset, int loadsize, char *address, spooledFuncPtr func); // 0x0007E36C

extern void InitSpooling(); // 0x0007E494

extern void SendTPage(); // 0x0007B88C

extern void SpoolSYNC(); // 0x0007E528

extern void LoadInAreaTSets(int area); // 0x0007BB14

extern void SendSBK(); // 0x0007BD84

extern void init_spooled_models(); // 0x0007BEBC

extern void SetupModels(); // 0x0007E540

extern void LoadInAreaModels(int area); // 0x0007E580

extern void CheckLoadAreaData(int cellx, int cellz); // 0x0007C08C

extern void ClearRegion(int target_region); // 0x0007E3E4

extern int LoadRegionData(int region, int target_region); // 0x0007C28C

extern void UnpackRegion(int region_to_unpack, int target_barrel_region); // 0x0007E5DC

extern void ProcessSpoolInfoLump(char *lump_ptr, int lump_size); // 0x0007C464

extern void WaitCloseLid(); // 0x0007E66C

extern void FoundError(char *name, unsigned char intr, unsigned char *result); // 0x0007E6D8

extern void GotRegion(); // 0x0007D9CC

extern void data_cb_textures(); // 0x0007DF64

extern void ready_cb_textures(unsigned char intr, unsigned char *result); // 0x0007E078

extern void ready_cb_regions(unsigned char intr, unsigned char *result); // 0x0007DE90

extern void data_cb_regions(); // 0x0007DDA8

extern void data_cb_soundbank(); // 0x0007DBCC

extern void ready_cb_soundbank(unsigned char intr, unsigned char *result); // 0x0007DCA4

extern void data_cb_misc(); // 0x0007DA60

extern void ready_cb_misc(unsigned char intr, unsigned char *result); // 0x0007DB38

extern void StartSpooling(); // 0x0007E724

extern void unpack_cellpointers(); // 0x0007C5C0

extern void Unpack_CellPtrs(); // 0x0007D978

extern void SpecClutsSpooled(); // 0x0007C74C

extern void CleanModelSpooled(); // 0x0007C9B8

extern void DamagedModelSpooled(); // 0x0007CAFC

extern void LowModelSpooled(); // 0x0007CC24

extern void CleanSpooled(); // 0x0007CD64

extern void LowSpooled(); // 0x0007E7C0

extern void Tada(); // 0x0007CF0C

extern void SpecialStartNextBlock(); // 0x0007D144

extern void CheckSpecialSpool(); // 0x0007D4E0

extern void QuickSpoolSpecial(); // 0x0007E84C

extern void PrepareSecretCar(); // 0x0007E8DC

extern void InitSpecSpool(); // 0x0007D6D8




#endif
