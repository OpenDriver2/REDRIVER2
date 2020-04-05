#ifndef TEXTURE_H
#define TEXTURE_H

extern char* texturename_buffer;

extern void IncrementClutNum(struct RECT *clut); // 0x00080DDC

extern void IncrementTPageNum(struct RECT *tpage); // 0x00080528

extern int LoadTPageAndCluts(struct RECT *tpage, struct RECT *cluts, int tpage2send, char *tpageaddress); // 0x00080E14

extern int Find_TexID(struct MODEL *model, int t_id); // 0x000805EC

extern struct TEXINF * GetTEXINFName(char *name, int *tpagenum, int *texturenum); // 0x00080F3C

extern struct TEXINF * GetTextureInfoName(char *name, struct TPAN *result); // 0x00080DA0

extern void update_slotinfo(int tpage, int slot, struct RECT *pos); // 0x00081038

extern void ProcessTextureInfo(char *lump_ptr); // 0x00081080

extern void LoadPermanentTPages(int *sector); // 0x00080688

extern void ReloadIcons(); // 0x00081118

extern void GetTextureDetails(char *name, struct TEXTURE_DETAILS *info); // 0x00080BB0


#endif
