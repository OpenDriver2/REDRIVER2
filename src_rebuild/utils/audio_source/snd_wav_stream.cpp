//////////////////////////////////////////////////////////////////////////////////
// Copyright © Inspiration Byte
// 2009-2020
//////////////////////////////////////////////////////////////////////////////////
// Description: Streamed WAVe source
//////////////////////////////////////////////////////////////////////////////////

#include "snd_wav_stream.h"

//--------------------------------------------------------

bool CSoundSource_WaveStream::Load(const char *szFilename)
{
	m_filename = szFilename;
	m_reader = new CRIFF_Parser( szFilename );

	while ( m_reader->GetName( ) )
	{
		ParseChunk( *m_reader );
		m_reader->ChunkNext();
	}

	return m_numSamples > 0;
}

void CSoundSource_WaveStream::Unload()
{
	m_reader->ChunkClose();
	delete m_reader;
	m_numSamples = 0;
}

void CSoundSource_WaveStream::ParseData(CRIFF_Parser &chunk)
{
	m_dataOffset = chunk.GetPos();
	m_dataSize = chunk.GetSize();

	m_numSamples = m_dataSize / (m_format.channels * m_format.bitwidth / 8);
}

int CSoundSource_WaveStream::GetSamples(ubyte *pOutput, int nSamples, int nOffset, bool bLooping)
{
	int     nRemaining;
	int     nBytes, nStart;

	int     nSampleSize = m_format.channels * m_format.bitwidth / 8;

	nBytes = nSamples * nSampleSize;
	nStart = nOffset * nSampleSize;

	nRemaining = nBytes;

	if ( nBytes + nStart > m_dataSize )
		nBytes = m_dataSize - nStart;

	ReadData( pOutput, nStart, nBytes );
	nRemaining -= nBytes;

	if ( nRemaining && bLooping )
	{
		if ( m_loopStart )
		{
			int loopBytes = m_loopStart * nSampleSize;
			ReadData( pOutput+nBytes, loopBytes, nRemaining );
		}
		else
			ReadData( pOutput+nBytes, 0, nRemaining );

		return (nBytes + nRemaining) / nSampleSize;
	}

	return nBytes / nSampleSize;
}

int CSoundSource_WaveStream::ReadData(ubyte *pOutput, int nStart, int nBytes)
{
	int sample;

	m_reader->SetPos( m_dataOffset + nStart );
	m_reader->ReadData( pOutput, nBytes );

	/*
	int fin = nBytes / (m_format.bitwidth / 8);

	for ( int i = 0; i < fin; i++ )
	{
		if ( m_format.bitwidth == 16 )
		{
			sample = ((short *)pOutput)[i];
			((short *)pOutput)[i] = sample;
		}
		else
		{
			sample = (int)((unsigned char)(pOutput[i]) - 128);
			((signed char *)pOutput)[i] = sample;
		}
	}
	*/

	return 0;
}
