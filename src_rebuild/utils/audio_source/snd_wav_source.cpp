#include "snd_wav_source.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

//---------------------------------------------------------------------

CSoundSource_Wave::CSoundSource_Wave() : m_loopStart(0), m_loopEnd(0), m_numSamples(0)
{
	m_numSubtitles = 0;
}

CSoundSource_Wave::~CSoundSource_Wave()
{
	for(int i = 0; i < m_numSubtitles; i++)
	{
		free(m_subtitles[i].text);
	}
	
}

void CSoundSource_Wave::ParseChunk(CRIFF_Parser &chunk)
{
	int nameId = chunk.GetName();

	char* name = (char*)&nameId;

	char namestr[5];
	memcpy(namestr, name, 4);
	namestr[4] = 0;

	//printf("chunk ID %s\n", namestr);

    switch ( chunk.GetName() )
    {
		case CHUNK_FMT:
			ParseFormat( chunk );
			break;
		case CHUNK_CUE:
			ParseCue( chunk );
			break;
		case CHUNK_LIST:
			ParseList( chunk );
			break;
		case CHUNK_DATA:
			ParseData( chunk );
			break;
		case CHUNK_SAMPLE:
			ParseSample( chunk );
		default:
			break;
    }
}

void CSoundSource_Wave::ParseFormat(CRIFF_Parser &chunk)
{
    wavfmthdr_t wfx;
    chunk.ReadChunk( (u_char*)&wfx, sizeof(wavfmthdr_t) );

    m_format.format = wfx.Format;
    m_format.channels = wfx.Channels;
    m_format.bitwidth = wfx.BitsPerSample;
    m_format.frequency = wfx.SamplesPerSec;
}

void CSoundSource_Wave::ParseCue(CRIFF_Parser &chunk)
{
	int count;
	chunk.ReadChunk(&count, sizeof(int));

	// now read all CUEs
	for(int i = 0; i < count; i++)
	{
		wavcuehdr_t cue;

		chunk.ReadChunk( (u_char *)&cue, sizeof(wavcuehdr_t) );
		m_loopStart = cue.SampleOffset;

		//printf("CUE %d time: %d ms (%d)\n", i+1, sampleTimeMilliseconds, cue.SampleOffset);

		CUESubtitle_t& sub = m_subtitles[m_numSubtitles];
		sub.sampleStart = float(cue.SampleOffset) / float(m_format.frequency) * 1000.0f;
		sub.sampleLength = 0;
		sub.text = NULL;
		m_numSubtitles++;
	}

    // dont care about the rest
}

struct wavltxthdr_t
{
	uint CueId;
	uint SampleLen;
	uint PurposeId;
	ushort Country;
	ushort Language;
	ushort Dialect;
	ushort CodePage;
};

void CSoundSource_Wave::ParseList(CRIFF_Parser &chunk)
{
	int adtl;
	chunk.ReadChunk(&adtl, sizeof(int));
	
	if(adtl == CHUNK_ADTLLIST)
	{
		int remainingSize = chunk.GetSize() -4;

		while(remainingSize > 0)
		{
			RIFFchunk_t listChunk;

			int read = chunk.ReadChunk(&listChunk, sizeof(listChunk));
			remainingSize -= read;

			char* name = (char*)&listChunk.Id;

			char namestr[5];
			memcpy(namestr, name, 4);
			namestr[4] = 0;

			if(listChunk.Id == CHUNK_LTXT)
			{
				wavltxthdr_t ltxt;
				int read = chunk.ReadChunk(&ltxt, sizeof(wavltxthdr_t));
				remainingSize -= read;

				m_subtitles[ltxt.CueId-1].sampleLength =  float(ltxt.SampleLen) / float(m_format.frequency) * 1000.0f;
			}
			else if(listChunk.Id == CHUNK_LABEL)
			{
				char labelString[128];
				
				int cueId;
				int stringSize = listChunk.Size - 4 + (listChunk.Size & 1);

				int read = chunk.ReadChunk( &cueId, sizeof(int) );
				remainingSize -= read;

				m_subtitles[cueId - 1].text = (char*)malloc(stringSize);
				
				read = chunk.ReadChunk( m_subtitles[cueId - 1].text, stringSize );
				remainingSize -= read;

				
				
				//printf("Label cue = %d, size: %d, '%s'\n", cueId, stringSize, labelString);
			}
		}
	}
}

void CSoundSource_Wave::ParseSample(CRIFF_Parser &chunk)
{
	wavsamplehdr_t wsx;
	chunk.ReadChunk((u_char*)&wsx, sizeof(wavsamplehdr_t));

	if (wsx.Loop[0].Type == 0) // only single loop region supported
	{
		m_loopStart = wsx.Loop[0].Start;
		m_loopEnd = wsx.Loop[0].End;
	}
}

float CSoundSource_Wave::GetLoopPosition(float flPosition)
{
    while ( flPosition > m_numSamples )
        flPosition -= m_numSamples;

    return flPosition;
}
