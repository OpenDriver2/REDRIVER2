#include "riff.h"
#include "driver2.h"
#include "STRINGS.H"

CRIFF_Parser::CRIFF_Parser(const char* szFilename)
{
	m_pos = 0;

	m_riff = fopen(szFilename, "rb" );
	m_riffData = NULL;

	if ( !m_riff )
	{
		m_curChunk.Id = 0;
		m_curChunk.Size = 0;
		return;
	}

	RIFFhdr_t header;
	ReadData(&header, sizeof(header));

	if ( header.Id != RIFF_ID )
	{
		printError("LoadRIFF: '%s' not valid RIFF file\n", szFilename);

		header.Id = 0;
		header.Size = 0;
		return;
	}
	else
	{
		if ( header.Type != WAVE_ID )
		{
			printError("LoadRIFF: '%s' not valid WAVE file\n", szFilename);

			header.Id = 0;
			header.Size = 0;
		}
	}

	ChunkSet();
}

CRIFF_Parser::CRIFF_Parser(u_char* pChunkData, int nChunkSize)
{
	m_pos = 0;

	m_riff = NULL;
	m_riffData = pChunkData;

	if ( !m_riffData )
	{
		m_curChunk.Id = 0;
		m_curChunk.Size = 0;
		return;
	}

	RIFFhdr_t header;
	ReadData(&header, sizeof(header));

	if ( header.Id != RIFF_ID )
	{
		header.Id = 0;
		header.Size = 0;
		return;
	}
	else
	{
		if ( header.Type != WAVE_ID )
		{
			header.Id = 0;
			header.Size = 0;
		}
	}

	ChunkSet();
}

void CRIFF_Parser::ChunkClose ()
{
	if( m_riff )
	{
		fclose( m_riff );
		m_riff = NULL;
	}
}

int CRIFF_Parser::ReadChunk( void* pOutput, int maxLen )
{
	int numToRead = m_curChunk.Size;

	if (maxLen != -1)
		numToRead = maxLen;

	int readCount = ReadData( pOutput, numToRead);

	numToRead -= readCount;
	/*
	if (numToRead < m_curChunk.Size)
	{
		m_pos += m_curChunk.Size - numToRead;

		if (m_riff)
			fseek(m_riff, m_curChunk.Size - numToRead, SEEK_CUR);
	}*/

	return readCount;
}

int CRIFF_Parser::ReadData(void* dest, int len)
{
	if( m_riff )
	{
		int read = fread(dest, 1, len, m_riff);

		m_pos += read;
		return read;
	}
	else if( m_riffData )
	{
		memcpy( dest, m_riffData + m_pos, len );
		m_pos += len;
		return len;
	}
	else
		return 0;
}

int CRIFF_Parser::ReadInt()
{
	int i;
	ReadData( &i, sizeof(i) );
	return i;
}

int CRIFF_Parser::GetPos()
{
	return m_pos;
}

int CRIFF_Parser::SetPos(int pos)
{
	m_pos = pos;

	if ( m_riff )
		fseek(m_riff, pos, SEEK_SET );

	return m_pos;
}

uint CRIFF_Parser::GetName()
{
	return m_curChunk.Id;
}

int CRIFF_Parser::GetSize()
{
	return m_curChunk.Size;
}

// goes to the next chunk
bool CRIFF_Parser::ChunkNext()
{
	bool result = ChunkSet();
	
	if(!result)
	{
		m_curChunk.Id = 0;
		m_curChunk.Size = 0;
	}

	return result;
}

//-----------------------------------------

bool CRIFF_Parser::ChunkSet()
{
	int n = ReadData(&m_curChunk, sizeof(m_curChunk));
	return n > 0;
}