#ifndef TEXTURE_H
#define TEXTURE_H

extern char carTpages[4][8];
extern char* texturename_buffer;
extern char* palette_lump;

extern SXYPAIR tpagepos[20];

extern short texture_pages[128];
extern short texture_cluts[128][32];
extern int tpage_texamts[128];

extern RECT16 clutpos;
extern RECT16 fontclutpos;

extern unsigned char tpageloaded[128];
extern unsigned char tpageslots[19];

extern DVECTOR slot_clutpos[19];
extern DVECTOR slot_tpagepos[19];

extern RECT16 tpage;

extern short specialSlot;
extern int slotsused;

extern char specTpages[4][12];

extern void IncrementClutNum(RECT16 *clut); // 0x00080DDC

extern void IncrementTPageNum(RECT16 *tpage); // 0x00080528

extern int LoadTPageAndCluts(RECT16 *tpage, RECT16 *cluts, int tpage2send, char *tpageaddress); // 0x00080E14

extern int Find_TexID(MODEL *model, int t_id); // 0x000805EC

extern TEXINF * GetTEXINFName(char *name, int *tpagenum, int *texturenum); // 0x00080F3C

extern TEXINF * GetTextureInfoName(char *name, TPAN *result); // 0x00080DA0

extern void update_slotinfo(int tpage, int slot, RECT16 *pos); // 0x00081038

extern void ProcessTextureInfo(char *lump_ptr); // 0x00081080

extern void LoadPermanentTPages(int *sector); // 0x00080688

extern void ReloadIcons(); // 0x00081118

extern void GetTextureDetails(char *name, TEXTURE_DETAILS *info); // 0x00080BB0


#endif
