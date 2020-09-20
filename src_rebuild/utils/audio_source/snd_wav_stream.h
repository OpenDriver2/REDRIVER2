//////////////////////////////////////////////////////////////////////////////////
// Copyright © Inspiration Byte
// 2009-2020
//////////////////////////////////////////////////////////////////////////////////
// Description: Streamed WAVe source
//////////////////////////////////////////////////////////////////////////////////

#include "snd_wav_source.h"

class CSoundSource_WaveStream : public CSoundSource_Wave
{
public:
	int				GetSamples (u_char* pOutput, int nSamples, int nOffset, bool bLooping);
	u_char*			GetDataPtr(int& dataSize) const { dataSize = 0; return nullptr; }

	bool			Load(const char *szFilename);
	void			Unload();

	bool			IsStreaming() { return true; }

private:
	virtual void    ParseData(CRIFF_Parser &chunk);

	int             ReadData (u_char* pOutput, int nStart, int nBytes);

	int				m_dataOffset;   // data chunk
	int				m_dataSize;     // in bytes

	CRIFF_Parser*	m_reader;
};
