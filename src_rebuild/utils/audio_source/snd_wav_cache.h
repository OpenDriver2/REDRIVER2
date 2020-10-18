#ifndef SND_WAV_CACHE_H
#define SND_WAV_CACHE_H

#include "snd_wav_source.h"

class CSoundSource_WaveCache : public CSoundSource_Wave
{
	friend class CSoundSource_OpenALCache;
public:
	virtual int     GetSamples(u_char*pOutput, int nSamples, int nOffset, bool bLooping);
	u_char*			GetDataPtr(int& dataSize) const { dataSize = m_cacheSize; return m_dataCache; }

	virtual bool	Load(const char *szFilename);
	virtual void	Unload();

	bool			IsStreaming() { return false; }

protected:
	virtual void    ParseData(CRIFF_Parser &chunk);

	u_char*			m_dataCache;   // data chunk
	int				m_cacheSize;    // in bytes
};

#endif // SND_WAV_CACHE_H