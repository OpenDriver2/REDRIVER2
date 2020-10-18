#ifndef SND_AL_SOURCE_H
#define SND_AL_SOURCE_H

#include "snd_source.h"
#include <AL/al.h>

class CSoundSource_WaveCache;

class CSoundSource_OpenALCache : public ISoundSource
{
	friend class CEqAudioSystemAL;
public:
	CSoundSource_OpenALCache(ISoundSource* source);

	virtual int             GetSamples(u_char*pOutput, int nSamples, int nOffset, bool bLooping) { return 0; };
	virtual u_char*			GetDataPtr(int& dataSize) const { return 0; };

	virtual soundFormat_t*	GetFormat() { return &m_format; };
	virtual int				GetSampleCount() const { return 0; };

	virtual float           GetLoopPosition(float flPosition) { return 0; };

	virtual bool			IsStreaming() { return false; }

	ALuint					m_alBuffer;
	soundFormat_t			m_format;

private:
	void					InitWav(CSoundSource_WaveCache* wav);

	virtual bool			Load(const char *szFilename) { return false; };
	virtual void			Unload();
};

#endif // SND_AL_SOURCE_H