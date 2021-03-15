#include "targa.h"
#include <stdio.h>
#include <string.h>

bool LoadTGAImage(const char* filename, u_char** data, int& width, int& height, int& bpp)
{
	FILE* fp;
	TGAHeader header;

	int size, x, y, pixelSize, palLength;
	u_char* tempBuffer, * fBuffer, * dest, * src;
	uint tempPixel;
	u_char palette[768];

	fp = fopen(filename, "rb");
	if (!fp)
		return false;

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// Read the header
	fread(&header, sizeof(header), 1, fp);

	width = header.width;
	height = header.height;

	pixelSize = header.bpp / 8;

	if ((palLength = header.descriptionlen + header.cmapentries * header.cmapbits / 8) > 0)
		fread(palette, sizeof(palette), 1, fp);

	// Read the file data
	fBuffer = new u_char[size - sizeof(header) - palLength];
	fread(fBuffer, size - sizeof(header) - palLength, 1, fp);
	fclose(fp);

	size = width * height * pixelSize;

	// Decode if rle compressed. Bit 3 of .imagetype tells if the file is compressed
	if (header.imagetype & 0x08)
	{
		uint c, count;

		tempBuffer = new u_char[size];

		dest = tempBuffer;
		src = fBuffer;

		while (size > 0)
		{
			// Get packet header
			c = *src++;

			count = (c & 0x7f) + 1;
			size -= count * pixelSize;

			if (c & 0x80)
			{
				// Rle packet
				do
				{
					memcpy(dest, src, pixelSize);
					dest += pixelSize;
				} while (--count);

				src += pixelSize;
			}
			else
			{
				// Raw packet
				count *= pixelSize;
				memcpy(dest, src, count);
				src += count;
				dest += count;
			}
		}

		src = tempBuffer;
	}
	else
	{
		tempBuffer = NULL;
		src = fBuffer;
	}

	src += (header.bpp / 8) * width * (height - 1);

	bpp = header.bpp;

	switch (header.bpp)
	{
		case 8:
			if (palLength > 0)
			{
				bpp = 24;
				dest = *data = new u_char[width * height * 3];
				for (y = 0; y < height; y++)
				{
					for (x = 0; x < width; x++)
					{
						tempPixel = 3 * (*src++);
						*dest++ = palette[tempPixel + 2];
						*dest++ = palette[tempPixel + 1];
						*dest++ = palette[tempPixel];
					}
					src -= 2 * width;
				}
			}
			else
			{
				bpp = 8;
				dest = *data = new u_char[width * height];
				for (y = 0; y < height; y++)
				{
					memcpy(dest, src, width);
					dest += width;
					src -= width;
				}
			}
			break;
		case 16:
			bpp = 32;
			dest = *data = new u_char[width * height * 4];
			for (y = 0; y < height; y++)
			{
				for (x = 0; x < width; x++)
				{
					tempPixel = *((unsigned short*)src);

					dest[0] = ((tempPixel >> 10) & 0x1F) << 3;
					dest[1] = ((tempPixel >> 5) & 0x1F) << 3;
					dest[2] = ((tempPixel) & 0x1F) << 3;
					dest[3] = ((tempPixel >> 15) ? 0xFF : 0);
					dest += 4;
					src += 2;
				}
				src -= 4 * width;
			}
			break;
		case 24:
			bpp = 24;
			dest = *data = new u_char[width * height * 3];

			for (y = 0; y < height; y++)
			{
				for (x = 0; x < width; x++)
				{
					*dest++ = src[2];
					*dest++ = src[1];
					*dest++ = src[0];
					src += 3;
				}
				src -= 6 * width;
			}
			break;
		case 32:
			bpp = 32;
			dest = *data = new u_char[width * height * 4];
			for (y = 0; y < height; y++)
			{
				for (x = 0; x < width; x++)
				{
					*dest++ = src[2];
					*dest++ = src[1];
					*dest++ = src[0];
					*dest++ = src[3];
					src += 4;
				}
				src -= 8 * width;
			}
			break;
	}

	delete[] tempBuffer;
	delete[] fBuffer;

	return true;
}