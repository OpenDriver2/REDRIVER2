#ifndef SND_SOURCE_H
#define SND_SOURCE_H

#include <types.h>

typedef struct soundFormat_s
{
	int format;
	int channels;
	int bitwidth;
	int frequency;
} soundFormat_t;

class ISoundSource
{
public:
	virtual int             GetSamples(u_char* pOutput, int nSamples, int nOffset, bool bLooping) = 0;
	virtual u_char*			GetDataPtr(int& dataSize) const = 0;

	virtual soundFormat_t*	GetFormat() = 0;
	virtual int				GetSampleCount() const = 0;

	virtual float           GetLoopPosition(float flPosition) = 0;

	virtual bool			IsStreaming() = 0;
private:
	virtual bool			Load(const char *szFilename) = 0;
	virtual void			Unload () = 0;
};

#endif // SND_SOURCE_H