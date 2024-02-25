#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include "targa.h"

#include "hqfont.h"

struct FN2RangeInfo
{
	OUT_FN2RANGE hdr;
	OUT_FN2INFO* chars;
};

static FN2RangeInfo fontRanges[4];
static int fontRangeCount = 0;

void Usage()
{
	printf("example: FontTool -i <file.ttf> -o <name without ext>\n\nAdditional arguments:");
	printf("\t-r <start> <count> : add range of characters");
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		Usage();
		return 0;
	}

	{
		FN2RangeInfo& firstRange = fontRanges[0];

		firstRange.hdr.start = 32;
		firstRange.hdr.count = 224;
		firstRange.chars = new OUT_FN2INFO[firstRange.hdr.count];
		++fontRangeCount;
	}

	const char* inputFilename = nullptr;
	const char* outpitFilename = nullptr;

	for (int i = 0; i < argc; ++i)
	{
		if (!strcmp(argv[i], "-i") && i + 1 < argc)
		{
			inputFilename = argv[i+1];
		}
		else if (!strcmp(argv[i], "-o") && i + 1 < argc)
		{
			outpitFilename = argv[i + 1];
		}
		else if (!strcmp(argv[i], "-r") && i + 2 < argc)
		{
			FN2RangeInfo& newRange = fontRanges[fontRangeCount];

			newRange.hdr.start = atoi(argv[i + 1]);
			newRange.hdr.count = atoi(argv[i + 2]);
			newRange.chars = new OUT_FN2INFO[newRange.hdr.count];
			++fontRangeCount;
		}
	}

	if (!inputFilename)
	{
		Usage();
		return 0;
	}

	if (!outpitFilename)
	{
		Usage();
		return 0;
	}

	FILE* fp = fopen(inputFilename, "rb");
	if (!fp)
	{
		printf("Cannot open %s\n", inputFilename);
		return -1;
	}

	// read whole file
	fseek(fp, 0, SEEK_END);
	const long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	u_char* data = (u_char*)malloc(size);
	fread(data, 1, size, fp);
	fclose(fp);

	// gen font
	u_char* tmpBitmap = (u_char*)malloc(HIRES_FONT_SIZE_W * HIRES_FONT_SIZE_H);
	u_int* bitmapRGBA = (u_int*)malloc(HIRES_FONT_SIZE_W * HIRES_FONT_SIZE_H * 4);

	stbtt_pack_context pc;
	stbtt_PackBegin(&pc, tmpBitmap, HIRES_FONT_SIZE_W, HIRES_FONT_SIZE_H, 0, 2, NULL);
	stbtt_PackSetOversampling(&pc, 1, 1);
	stbtt_PackSetSkipMissingCodepoints(&pc, 1);

	for (int i = 0; i < fontRangeCount; ++i)
	{
		FN2RangeInfo& range = fontRanges[i];
		stbtt_PackFontRange(&pc, data, 0, 65.0f, range.hdr.start, range.hdr.count, (stbtt_packedchar*)range.chars);
	}

	stbtt_PackEnd(&pc);

	for (int x = 0; x < HIRES_FONT_SIZE_W; ++x)
	{
		for (int y = 0; y < HIRES_FONT_SIZE_H; ++y)
		{
			bitmapRGBA[x + y * HIRES_FONT_SIZE_W] = tmpBitmap[x + y * HIRES_FONT_SIZE_W] << 24 | 0xffffff;
		}
	}

	{
		char tgaFileName[256];
		strcpy(tgaFileName, outpitFilename);
		strcat(tgaFileName, ".tga");

		SaveTGAImage(tgaFileName, (u_char*)bitmapRGBA, HIRES_FONT_SIZE_W, HIRES_FONT_SIZE_H, 32);
	}

	{
		char fntFileName[256];
		strcpy(fntFileName, outpitFilename);
		strcat(fntFileName, ".fn2");

		FILE* fntFp = fopen(fntFileName, "wb");
		if (fntFp)
		{
			OUT_FN2HEADER fn2hdr;
			fn2hdr.version = FN2_VERSION;
			fn2hdr.range_count = fontRangeCount;
			fwrite(&fn2hdr, sizeof(fn2hdr), 1, fntFp);

			for (int i = 0; i < fontRangeCount; ++i)
			{
				FN2RangeInfo& range = fontRanges[i];
				fwrite(&range.hdr, sizeof(OUT_FN2RANGE), 1, fntFp);
				fwrite(range.chars, sizeof(OUT_FN2INFO), range.hdr.count, fntFp);

				delete[] range.chars;
			}
		}
	}

	free(bitmapRGBA);
	free(tmpBitmap);
	free(data);
}