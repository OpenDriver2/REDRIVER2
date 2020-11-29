#ifndef MODELS_H
#define MODELS_H

extern MODEL dummyModel;

extern char* modelname_buffer;
extern char *car_models_lump;

extern MODEL* modelpointers[MAX_MODEL_SLOTS];
extern MODEL* pLodModels[MAX_MODEL_SLOTS];

extern unsigned short *Low2HighDetailTable;
extern unsigned short *Low2LowerDetailTable;

extern int num_models_in_pack;

extern int CleanSpooledModelSlots();

extern void ProcessMDSLump(char *lump_file, int lump_size); // 0x00064CFC

extern int ProcessCarModelLump(char *lump_ptr, int lump_size); // 0x00064E6C

extern MODEL * GetCarModel(char *src, char **dest, int KeepNormals, int modelNumber, int type); // 0x00065134

extern MODEL * FindModelPtrWithName(char *name); // 0x0005D40C

extern int FindModelIdxWithName(char *name); // 0x0005D4C4

#endif
