#include "snd_al_source.h"
#include <AL/alext.h>

#include "snd_wav_cache.h"

CSoundSource_OpenALCache::CSoundSource_OpenALCache(ISoundSource* source)
{
	CSoundSource_WaveCache* wav = (CSoundSource_WaveCache*)source;
	InitWav(wav);
}

void CSoundSource_OpenALCache::InitWav(CSoundSource_WaveCache* wav)
{
	alGenBuffers(1, &m_alBuffer);

	m_format = *wav->GetFormat();
	ALenum alFormat;

	if (m_format.bitwidth == 8)
		alFormat = m_format.channels == 2 ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
	else if (m_format.bitwidth == 16)
		alFormat = m_format.channels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
	else
		alFormat = AL_FORMAT_MONO16;

	alBufferData(m_alBuffer, alFormat, wav->m_dataCache, wav->m_cacheSize, m_format.frequency );

	int loopStart = wav->m_loopStart;
	int loopEnd = wav->m_loopEnd;

	// setup additional loop points
	if (loopStart > 0)
	{
		int loopEnd = wav->m_loopEnd;

		if (loopEnd == -1)
			alGetBufferi(m_alBuffer, AL_SAMPLE_LENGTH_SOFT, &loopEnd); // loop to the end

		int sampleOffs[] = { loopStart, loopEnd };
		alBufferiv(m_alBuffer, AL_LOOP_POINTS_SOFT, sampleOffs);
	}
}

void CSoundSource_OpenALCache::Unload()
{
	alDeleteBuffers(1, &m_alBuffer);
}