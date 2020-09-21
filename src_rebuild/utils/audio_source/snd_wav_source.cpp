#include "snd_wav_source.h"
#include <stdio.h>
#include <string.h>

//---------------------------------------------------------------------

CSoundSource_Wave::CSoundSource_Wave() : m_loopStart(0), m_loopEnd(0), m_numSamples(0)
{

}

void CSoundSource_Wave::ParseChunk(CRIFF_Parser &chunk)
{
	int nameId = chunk.GetName();

	char* name = (char*)&nameId;

	char namestr[5];
	memcpy(namestr, name, 4);
	namestr[4] = 0;

    switch ( chunk.GetName() )
    {
		case CHUNK_FMT:
			ParseFormat( chunk );
			break;
		case CHUNK_CUE:
			ParseCue( chunk );
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
	wavcuehdr_t cue;

    chunk.ReadChunk( (u_char *)&cue, sizeof(wavcuehdr_t) );
    m_loopStart = cue.SampleOffset;

    // dont care about the rest
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
