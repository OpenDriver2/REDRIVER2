#ifndef MODELS_H
#define MODELS_H

extern char* modelname_buffer;
extern char *car_models_lump;

extern void ProcessMDSLump(char *lump_file, int lump_size); // 0x00064CFC

extern int ProcessCarModelLump(char *lump_ptr, int lump_size); // 0x00064E6C

extern struct MODEL * GetCarModel(char *src, char **dest, int KeepNormals); // 0x00065134


#endif
