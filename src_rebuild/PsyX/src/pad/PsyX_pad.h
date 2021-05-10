#ifndef PSYX_PAD_H
#define PSYX_PAD_H

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern void		PsyX_Pad_InitPad(int slot, u_char* padData);
extern void		PsyX_Pad_Vibrate(int mtap, int slot, unsigned char* table, int len);
extern int		PsyX_Pad_GetStatus(int mtap, int slot);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif // PSYX_PAD_H