#ifndef SND_RIFF_H
#define SND_RIFF_H

#include "TYPES.H"
#include <stdio.h>

#define RIFF_ID				(('F' << 24) | ('F' << 16) | ('I' << 8) | 'R' )
#define WAVE_ID				(('E' << 24) | ('V' << 16) | ('A' << 8) | 'W' )
#define CDXA_ID				(('A' << 24) | ('X' << 16) | ('D' << 8) | 'C' )


#define CHUNK_FMT			((' ' << 24) | ('t' << 16) | ('m' << 8) | 'f' )
#define CHUNK_CUE			((' ' << 24) | ('e' << 16) | ('u' << 8) | 'c' )
#define CHUNK_DATA			(('a' << 24) | ('t' << 16) | ('a' << 8) | 'd' )
#define CHUNK_SAMPLE		(('l' << 24) | ('p' << 16) | ('m' << 8) | 's' )
#define CHUNK_LTXT			(('t' << 24) | ('x' << 16) | ('t' << 8) | 'l' )
#define CHUNK_LABEL			(('l' << 24) | ('b' << 16) | ('a' << 8) | 'l' )
#define CHUNK_LIST			(('T' << 24) | ('S' << 16) | ('I' << 8) | 'L' )
#define CHUNK_ADTLLIST		(('l' << 24) | ('t' << 16) | ('d' << 8) | 'a' )

// RIFF WAVE FILE HEADERS
typedef struct
{
	int		Id;
	int		Size;
	int		Type;
} RIFFhdr_t;

typedef struct
{
	int		Id;
	int		Size;
} RIFFchunk_t;

typedef struct // CHUNK_FMT
{
	ushort Format;
	ushort Channels;
	uint   SamplesPerSec;
	uint   BytesPerSec;
	ushort BlockAlign;
	ushort BitsPerSample;
} wavfmthdr_t;

typedef struct // CHUNK_SAMPLE
{
	uint   Manufacturer;
	uint   Product;
	uint   SamplePeriod;
	uint   Note;
	uint   FineTune;
	uint   SMPTEFormat;
	uint   SMPTEOffest;
	uint   Loops;
	uint   SamplerData;

	struct
	{
		uint Identifier;
		uint Type;
		uint Start;
		uint End;
		uint Fraction;
		uint Count;
	}Loop[1];
}wavsamplehdr_t;

typedef struct // CHUNK_CUE
{
	uint Name;
	uint Position;
	uint fccChunk;
	uint ChunkStart;
	uint BlockStart;
	uint SampleOffset;
} wavcuehdr_t;

//-----------------------------------------------------------

class CRIFF_Parser
{
public:
	CRIFF_Parser(const char *szFilename);
	CRIFF_Parser(u_char* pChunkData, int nChunkSize);

	void			ChunkClose();
	bool			ChunkNext();

	uint			GetName();
	int             GetSize();

	int             GetPos();
	int             SetPos(int pos);

	int				ReadChunk(void* dest, int maxLen = -1);
	int				ReadData(void* dest, int len);
	int				ReadInt();

private:
	bool			ChunkSet();
	int				m_pos;

	RIFFchunk_t		m_curChunk;

	FILE*			m_riff;
	u_char*			m_riffData;
};

#endif // SND_RIFF_H