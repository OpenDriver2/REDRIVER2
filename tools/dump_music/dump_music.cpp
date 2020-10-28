#include <iostream>
#include <Windows.h>

// WAV file header and smpl-chunk template - Quick and dirty solution because I'm lazy
int wavHeader[11] = {
	0x46464952, 0, 0x45564157, 0x20746D66,
	0x10, 0x10001, 0, 0,
	0x100002, 0x61746164, 0
};

int smplChunk[17] = {
	0x6C706D73, 0x3C, 0, 0,
	0x1D316, 0x3C, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,
	0
};

// PSX ADPCM coefficients
const double K0[5] = { 0, 0.9375, 1.796875, 1.53125, 1.90625 };
const double K1[5] = { 0, 0, -0.8125, -0.859375, -0.9375 };

// PSX ADPCM decoding routine - decodes a single sample
short vagToPcm(unsigned char soundParameter, int soundData, double* vagPrev1, double* vagPrev2)
{
	int resultInt = 0;

	double dTmp1 = 0.0;
	double dTmp2 = 0.0;
	double dTmp3 = 0.0;

	if (soundData > 7)
		soundData -= 16;

	dTmp1 = (double)soundData * pow(2, (double)(12 - (soundParameter & 0x0F)));

	dTmp2 = (*vagPrev1) * K0[(soundParameter >> 4) & 0x0F];
	dTmp3 = (*vagPrev2) * K1[(soundParameter >> 4) & 0x0F];

	(*vagPrev2) = (*vagPrev1);
	(*vagPrev1) = dTmp1 + dTmp2 + dTmp3;

	resultInt = (int)round((*vagPrev1));

	if (resultInt > 32767)
		resultInt = 32767;

	if (resultInt < -32768)
		resultInt = -32768;

	return (short)resultInt;
}

// Main decoding routine - Takes PSX ADPCM formatted audio data and converts it to PCM. It also extracts the looping information if used.
void decodeSound(unsigned char* iData, short* oData, int soundSize, int* loopStart, int* loopLength)
{
	unsigned char sp = 0;
	int sd = 0;
	double vagPrev1 = 0.0;
	double vagPrev2 = 0.0;
	int k = 0;

	for (int i = 0; i < soundSize; i++)
	{
		if (i % 16 == 0)
		{
			sp = iData[i];

			if ((iData[i + 1] & 0x0E) == 6) 
				(*loopStart) = k;

			if ((iData[i + 1] & 0x0F) == 3 || (iData[i + 1] & 0x0F) == 7)
				(*loopLength) = (k + 28) - (*loopStart);

			i += 2;
		}

		sd = (int)iData[i] & 0x0F;
		oData[k++] = vagToPcm(sp, sd, &vagPrev1, &vagPrev2);
		sd = ((int)iData[i] >> 4) & 0x0F;
		oData[k++] = vagToPcm(sp, sd, &vagPrev1, &vagPrev2);
	}
}

void XM_Sample2Delta(short *p, int len)
{
	short news, olds;

	news = 0;
	for (int i = 0; i < len; ++i)
	{
		olds = p[i];
		p[i] -= news;
		news = olds;
	}
}

//------------------------------------------------------------------------------------

#define XM_SONGS 8

#define XM_INSTR_HEADER_SIZE 263
#define XM_MAX_CHANNELS 32

struct song_t
{
	int xm_offset;
	int bank_offset;
};

struct SAMPLE_DATA 
{
	unsigned long address;
	unsigned long length;
	unsigned long loop;
	unsigned long samplerate;
};

struct PCMSample
{
	short* data;
	int length;
	int loopStart;
	int loopLength;
};

struct XM_Note
{
	unsigned char note;
	unsigned char inst;
	unsigned char volc;
	unsigned char efft;
	unsigned char effp;
};

#pragma pack(push,1)

struct XM_SampleHeader
{
	int32_t len, repS, repL;
	uint8_t vol;
	int8_t fine;
	uint8_t typ, pan;
	int8_t relTon;
	uint8_t reserved;
	char name[22];
};

struct XM_InstHeaeder
{
	uint32_t instrSize;
	char name[22];
	uint8_t typ;
	int16_t antSamp;
	int32_t sampleSize;
	uint8_t ta[96];
	int16_t envVP[12][2], envPP[12][2];
	uint8_t envVPAnt, envPPAnt;
	uint8_t envVSust, envVRepS, envVRepE;
	uint8_t envPSust, envPRepS, envPRepE;
	uint8_t envVTyp, envPTyp;
	uint8_t vibTyp, vibSweep, vibDepth, vibRate;
	uint16_t fadeOut;
	uint8_t midiOn, midiChannel;
	int16_t midiProgram, midiBend;
	int8_t mute;
	uint8_t reserved[15];
	XM_SampleHeader samp[16];
};

#pragma pack(pop)

int DecompressAndRestoreXM(char* destXM, char* xmData, int srcSize, PCMSample* samples)
{
	char* destOrig = destXM;
	char* srcOrig = xmData;

	memcpy(destXM, xmData, 336);

	unsigned short* version = (unsigned short*)(&destXM[58]);

	// check if it's an XMPlay version (superpacked)
	if (*version != 0xDDBA)
	{
		memcpy(destXM, xmData, srcSize);
		return srcSize;
	}

	printf("Decompressing XM...\n");

	// convert XM to standard version
	*version = 0x104;

	destXM += 336;		// go to patterns
	xmData += 68;

	short numChannels = *(short*)xmData;		xmData += 2;
	short numPatterns = *(short*)xmData;		xmData += 2;
	short numInstruments = *(short*)xmData;		xmData += 264;	// skip other header data since it's not changed

	printf("channel count: %d\n", numChannels);

	printf("Unpacking %d patterns\n", numPatterns);

	XM_Note rowNotes[XM_MAX_CHANNELS];	// more for safety

	for (int i = 0; i < numPatterns; i++)
	{
		xmData += 5;
		int pattLen = *(short*)xmData;
		xmData -= 5;

		memcpy(destXM, xmData, 7);	// copy pattern header properties
		destXM += 7;
		xmData += 7;

		short patternSize = *(short*)xmData;
		xmData += sizeof(short);	// now pattern data itself

		short* unpackedPatternSize = (short*)destXM;
		destXM += sizeof(short);

		// no empty reads
		if (patternSize == 0)
			continue;

		char* pattStartSrc = xmData;
		char* pattStart = destXM;

		for (int r = 0; r < pattLen; r++)
		{
			// zero full channel size double from current position
			memset(rowNotes, 0, sizeof(rowNotes));

			while (1)
			{
				// don't overflow reading
				if ((xmData - pattStartSrc) >= patternSize)
					break;

				unsigned char patdat = *xmData++;

				if (patdat == 0xFF)	// channel end
					break;

				unsigned char data = 0;

				XM_Note& xmnote = rowNotes[patdat];

				// unpack it fully
				unsigned char note = *xmData++;
				if (note & 0x80)
				{
					data = 0; if (note & 0x01) data = *xmData++; xmnote.note = data;
					data = 0; if (note & 0x02) data = *xmData++; xmnote.inst = data;
					data = 0; if (note & 0x04) data = *xmData++; xmnote.volc = data;
					data = 0; if (note & 0x08) data = *xmData++; xmnote.efft = data;
					data = 0; if (note & 0x10) data = *xmData++; xmnote.effp = data;
				}
				else
				{
					xmnote.note = note;
					xmnote.inst = *xmData++;
					xmnote.volc = *xmData++;
					xmnote.efft = *xmData++;
					xmnote.effp = *xmData++;
				}
			}

			// pack notes again
			for (int c = 0; c < numChannels; c++)
			{
				XM_Note& xmnote = rowNotes[c];

				if (xmnote.note > 0 &&
					xmnote.inst > 0 &&
					xmnote.volc > 0 &&
					xmnote.efft > 0 &&
					xmnote.effp > 0)
				{
					// write full note
					memcpy(destXM, &xmnote, sizeof(XM_Note));
					destXM += sizeof(XM_Note);
				}
				else
				{
					char* packedFlag = destXM++;

					*packedFlag = 0x80;

					if (xmnote.note > 0) { *destXM++ = xmnote.note; *packedFlag |= 0x01; }
					if (xmnote.inst > 0) { *destXM++ = xmnote.inst; *packedFlag |= 0x02; }
					if (xmnote.volc > 0) { *destXM++ = xmnote.volc; *packedFlag |= 0x04; }
					if (xmnote.efft > 0) { *destXM++ = xmnote.efft; *packedFlag |= 0x08; }
					if (xmnote.effp > 0) { *destXM++ = xmnote.effp; *packedFlag |= 0x10; }
				}
			}
		}

		*unpackedPatternSize = destXM - pattStart;
	}

	printf("instrument count: %d\n", numInstruments);

	for (int i = 0; i < numInstruments; i++)
	{
		char* instStart = xmData;

		XM_InstHeaeder* instr = (XM_InstHeaeder*)xmData;

		{
			int readSize = instr->instrSize;
			if ((readSize < 4) || (readSize > XM_INSTR_HEADER_SIZE))
				readSize = XM_INSTR_HEADER_SIZE;

			if (instr->instrSize > XM_INSTR_HEADER_SIZE)
				readSize += instr->instrSize - XM_INSTR_HEADER_SIZE;

			printf("instr %d size: %d readSize: %d\n", i, instr->instrSize, readSize);

			memcpy(destXM, xmData, readSize);

			xmData += readSize;
			destXM += readSize;
		}

		printf("instr name: %s\n", instr->name);
		printf("sample count: %d\n", instr->antSamp);

		// since the XMPlay for PSX does not 
		// support more than one samples, we don't bother...
		if (instr->antSamp > 0)
		{
			//if (i == 17)
			//	printf("flash!\n");

			printf("sample: %s typ %d\n", instr->samp[0].name, instr->samp[0].typ);

			// samples are direct to the instrument number,
			// so we don't bother here too...
			PCMSample& sample = samples[i];

			if ((instr->samp[0].typ & 0x16))
			{
				instr->samp[0].len = sample.length * sizeof(short);
				instr->samp[0].repS = sample.loopStart * sizeof(short);
				instr->samp[0].repL = sample.loopLength * sizeof(short);
			}

			// write headers
			int readSize = instr->antSamp * sizeof(XM_SampleHeader);

			memcpy(destXM, xmData, readSize);
			xmData += readSize;
			destXM += readSize;

			if ((instr->samp[0].typ & 0x16))
			{
				// right after the instrument data comes the sample data
				// there is nothing to read, but there is something to write...
				XM_Sample2Delta(sample.data, sample.length);

				memcpy(destXM, sample.data, sample.length * sizeof(short));
				destXM += sample.length * sizeof(short);
			}
		}
	}

	int remainingStart = (xmData - srcOrig);
	int remaining = srcSize - remainingStart;

	// copy remaining data
	memcpy(destXM, xmData, remaining);
	destXM += remaining;

	return destXM-destOrig;
}

//-----------------------------------------------------------------------------

int LoadSoundBank(SAMPLE_DATA* out_sample_info, PCMSample* out_samples, FILE* fp)
{
	int numBankSamples = 0;
	fread(&numBankSamples, sizeof(int), 1, fp);

	printf("bank sounds: %d\n", numBankSamples);

	fread(out_sample_info, sizeof(SAMPLE_DATA), numBankSamples, fp);

	int bankSamplesOffset = ftell(fp);

	printf("bank sounds: %d\n", numBankSamples);

	for (int j = 0; j < numBankSamples; j++)
	{
		SAMPLE_DATA& sample = out_sample_info[j];
		PCMSample& pcmSample = out_samples[j];

		if (sample.loop == 0)
			sample.length -= 16;

		if (sample.length == 0)
			continue;

		// read VAG and convert to ADPCM
		{
			unsigned char* iData = (unsigned char*)malloc(sample.length);

			pcmSample.length = (sample.length >> 4) * 28;
			pcmSample.data = new short[pcmSample.length];

			fseek(fp, bankSamplesOffset + sample.address, SEEK_SET);
			fread(iData, sizeof(char), sample.length, fp);  // Read the audio data

			decodeSound(iData, pcmSample.data, sample.length, &pcmSample.loopStart, &pcmSample.loopLength);

			free(iData);

			printf("sample %d rate=%d loop=%d size=%d\n", j, sample.samplerate, sample.loop, pcmSample.length);
		}
	}

	return numBankSamples;
}

int DoConvertSBK(const char* sbkFileName)
{
	char tmpString[_MAX_PATH];
	snprintf(tmpString, _MAX_PATH, "%s_dec", sbkFileName);

	printf("Loading '%s'...\n", sbkFileName);

	FILE* sbkFp = fopen(sbkFileName, "rb");

	if (!sbkFp)
	{
		printf("No such file '%s'!", sbkFileName);
		return -1;
	}

	CreateDirectoryA(tmpString, NULL);

	PCMSample pcmSamples[80];
	SAMPLE_DATA sampleDescs[80];
	memset(pcmSamples, 0, sizeof(PCMSample) * 80);
	memset(sampleDescs, 0, sizeof(SAMPLE_DATA) * 80);

	int numBankSamples = LoadSoundBank(sampleDescs, pcmSamples, sbkFp);

	for (int i = 0; i < numBankSamples; i++)
	{
		PCMSample& sample = pcmSamples[i];
		SAMPLE_DATA& sampleDesc = sampleDescs[i];

		snprintf(tmpString, _MAX_PATH, "%s_dec\\%d.wav", sbkFileName, i);

		FILE* wavfp = fopen(tmpString, "wb");

		if (wavfp)
		{
			// Prepare the WAV file header
			wavHeader[1] = sample.length * sizeof(short) + 36;  // Size of the "RIFF" chunk

			if (sample.loopLength > 0)
				wavHeader[1] += 68;

			wavHeader[6] = sampleDesc.samplerate;  // Sampling rate
			wavHeader[7] = wavHeader[6] * sizeof(short);  // Average bytes per second
			wavHeader[10] = sample.length * sizeof(short);  // Size of the "data" chunk

			// Write WAV file header, the converted audio data, and the loop positions if used
			fwrite(&wavHeader, sizeof(int), 11, wavfp);
			fwrite(sample.data, sizeof(short), sample.length, wavfp);
			if (sample.loopLength > 0)
			{
				smplChunk[13] = sample.loopStart * sizeof(short);
				smplChunk[14] = sample.loopStart * sizeof(short) + sample.loopLength * sizeof(short);
				fwrite(&smplChunk, sizeof(int), 17, wavfp);
			}

			fclose(wavfp);
		}
		else
			printf("Unable to create file %s\n", tmpString);

	}

	return 0;
}

int DoConvertXMAndSBK(const char* xmFilename)
{
	char tmpString[_MAX_PATH];
	char sbkFileName[_MAX_PATH];
	strcpy_s(sbkFileName, xmFilename);

	char* extStr = strchr(sbkFileName, '.');
	if (extStr)
		strcpy(extStr, ".sbk");

	FILE* psxXmFp = fopen(xmFilename, "rb");

	if (!psxXmFp)
	{
		printf("No such file '%s'!", xmFilename);
		return -1;
	}

	FILE* sbkFp = fopen(sbkFileName, "rb");

	if (!sbkFp)
	{
		printf("No such file '%s'!", sbkFileName);
		return -1;
	}

	printf("Loading '%s' & '%s'...\n", xmFilename, sbkFileName);

	PCMSample pcmSamples[80];
	SAMPLE_DATA sampleDescs[80];
	memset(pcmSamples, 0, sizeof(PCMSample) * 80);
	memset(sampleDescs, 0, sizeof(SAMPLE_DATA) * 80);

	int numBankSamples = LoadSoundBank(sampleDescs, pcmSamples, sbkFp);

	// restore XM and save to disk
	{
		*extStr = 0;

		printf("--- XM song '%s' ---\n", sbkFileName);
		sprintf_s(tmpString, "%s_orig.xm", sbkFileName);

		FILE* xmFp = fopen(tmpString, "wb");

		if (xmFp)
		{
			fseek(psxXmFp, 0, SEEK_END);
			int songSize = ftell(psxXmFp);
			fseek(psxXmFp, 0, SEEK_SET);

			// read the PSX XM
			char* xmData = (char*)malloc(songSize);
			fread(xmData, songSize, 1, psxXmFp);

			fclose(psxXmFp);

			// calculate new XM size according to samples
			int addSize = 0;

			for (int j = 0; j < numBankSamples; j++)
			{
				//printf("sample %d rate=%d loop=%d size=%d\n", j, sample.samplerate, sample.loop, sample.length);
				addSize += pcmSamples[j].length * sizeof(short);
			}

			int calculatedXMSize = songSize * 4 + addSize;

			// decompress
			char* newXMData = (char*)malloc(calculatedXMSize);	// the new size is pretty hardcoded setting

			songSize = DecompressAndRestoreXM(newXMData, xmData, songSize, pcmSamples);

			free(xmData);
			xmData = newXMData;

			fwrite(xmData, 1, songSize, xmFp);
			fclose(xmFp);

			free(xmData);
		}
		else
			printf("ERROR: can't open '%s' for write!", tmpString);
	}

	// free samples
	for (int j = 0; j < numBankSamples; j++)
	{
		delete[] pcmSamples[j].data;
		pcmSamples[j].data = nullptr;
	}

	// close handles
	fclose(sbkFp);

	return 0;
}

int DoExtractMusicFile(const char* fileName)
{
	FILE* fp = fopen(fileName, "rb");

	if (!fp)
	{
		printf("No such file '%s'!", fileName);
		return -1;
	}

	printf("Loading '%s'...\n", fileName);

	//char songPath[_MAX_PATH];
	char tmpString[_MAX_PATH];

	// max 80 samples per bank
	PCMSample pcmSamples[80];
	SAMPLE_DATA sampleDescs[80];
	song_t songs[XM_SONGS];
	int numBankSamples = 0;

	// read song offsets
	fread(songs, sizeof(song_t), XM_SONGS, fp);

	for (int i = 0; i < XM_SONGS; i++)
	{
		const song_t& offsets = songs[i];

		int songSize = offsets.bank_offset - offsets.xm_offset;

		printf("--- XM song %d at %d (size %d) ---\n", i, offsets.xm_offset, songSize);

		// create folder for song
		//sprintf_s(songPath, "%s_song_%d", fileName, i);
		//CreateDirectoryA(songPath, NULL);  // Create the sound bank directory

		// Read XM and store to separate file
		fseek(fp, offsets.xm_offset, SEEK_SET);

		char* xmData = (char*)malloc(songSize);
		fread(xmData, songSize, 1, fp);

		// Read sound bank and then convert it using vabdecode
		fseek(fp, offsets.bank_offset, SEEK_SET);

		memset(pcmSamples, 0, sizeof(PCMSample) * 80);
		memset(sampleDescs, 0, sizeof(SAMPLE_DATA) * 80);

		numBankSamples = LoadSoundBank(sampleDescs, pcmSamples, fp);

		// restore XM and save to disk
		{
			printf("--- XM song %d ---\n", i);
			sprintf_s(tmpString, "%s_song%d.xm", fileName, i);

			FILE* xmFp = fopen(tmpString, "wb");

			if (xmFp)
			{

				// calculate new XM size according to samples
				int addSize = 0;

				for (int j = 0; j < numBankSamples; j++)
				{
					//printf("sample %d rate=%d loop=%d size=%d\n", j, sample.samplerate, sample.loop, sample.length);
					addSize += pcmSamples[j].length * sizeof(short);
				}

				int calculatedXMSize = songSize * 4 + addSize;

				// decompress
				char* newXMData = (char*)malloc(calculatedXMSize);	// the new size is pretty hardcoded setting

				songSize = DecompressAndRestoreXM(newXMData, xmData, songSize, pcmSamples);

				free(xmData);
				xmData = newXMData;

				fwrite(xmData, 1, songSize, xmFp);
				fclose(xmFp);
			}
			else
				printf("ERROR: can't open '%s' for write!", tmpString);

			free(xmData);
		}

		// free samples
		for (int j = 0; j < numBankSamples; j++)
		{
			delete[] pcmSamples[j].data;
			pcmSamples[j].data = nullptr;
		}
	}

	fclose(fp);

	return 0;
}

int DoAssembleMusicFile(const char* folder)
{


	return 0;
}

//-----------------------------------------------------

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		printf("usage:\n");
		printf("\tdump_music -bin2xm MUSIC.BIN\n");
		printf("\tdump_music -psx2xm FETUNE.XM\n");
		printf("\tdump_music -sbk2wav SOUNDS.SBK\n");

		return -1;
	}

	for (int i = 0; i < argc; i++)
	{
		if (!_stricmp(argv[i], "-bin2xm"))
		{
			if (i + 1 <= argc)
				DoExtractMusicFile(argv[i + 1]);
			else
				printf("-extract must have an argument!");
		}
		else if (!_stricmp(argv[i], "-psx2xm"))
		{
			if (i + 1 <= argc)
				DoConvertXMAndSBK(argv[i + 1]);
			else
				printf("-psx2xm must have an argument!");
		}
		else if (!_stricmp(argv[i], "-sbk2wav"))
		{
			if (i + 1 <= argc)
				DoConvertSBK(argv[i + 1]);
			else
				printf("-sbk2wav must have an argument!");
		}
		else if (!_stricmp(argv[i], "-a") || !_stricmp(argv[i], "-assemble"))
		{

		}
	}

	return 0;
}