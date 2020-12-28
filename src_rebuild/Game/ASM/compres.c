// [D] [T]
char* decomp_asm(char* dest, char* src)
{
	char* ptr = dest + 0x7fff;

	do {
		char pix = *src++;

		if ((pix & 0x80) != 0)
		{
			char p = *src++;

			do (*ptr-- = p);
			while (pix++ <= 0);
		}
		else
		{
			do (*ptr-- = *src++);
			while (pix-- != 0);
		}
	} while (ptr >= dest);

	return src;
}