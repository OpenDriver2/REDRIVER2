#include "ReadAVI.h"	// WTF, ostream/fstream

#include <PSYX_RENDER.H>
#include "COMMON/glad.h"

#include "driver2.h"

#include "C/pad.h"
#include "C/system.h"
#include "C/E3stuff.h"
#include "C/fmv_font.h"

#include "STRINGS.H"

#include <AL/al.h>
#include <jpeglib.h>
#include "platform.h"

#include <UTIL/TIMER.H>

// Partially decompiled function from FMV EXE
void InitFMVFont()
{
	int i;
	RECT16 fontRect;

	DrawSync(0);
	LoadClut((u_long *)(fmvFont + 20),960,72);
	DrawSync(0);

	fontRect.x = 960;
	fontRect.y = 0;
	fontRect.w = 64;
	fontRect.h = 72;

	LoadImage2(&fontRect,(u_long *)(fmvFont + 64));
	DrawSync(0);
}

POLY_FT4 fmvTextPolys[512];

// partially decompiled
void PrintFMVText(char *str, int x, short y, int brightness)
{
	u_char chr;
	char *ptr;
	int x_ofs;
	int i;
	int str_w;
	int drawnChars;
	OTTYPE ot;
	POLY_FT4* poly;

	ClearOTagR((ulong*)&ot, 1);
	poly = fmvTextPolys;

	str_w = 0;

	if (brightness > 128) 
		brightness = 128;

	i = 0;
	while (chr = str[i], chr != 0) 
	{
		if (chr == 32)
			str_w += 4;
		else
			str_w += fmvFontUV[chr].w;
		i++;
	}

	x_ofs = x - str_w / 2;

	drawnChars = 0;

	ptr = (char *)str;
	while( true )
	{
		chr = *ptr;
		ptr++;
	
		if (chr == 0 || drawnChars > 511) 
			break;
		
		if (chr == 32)	// space
		{
			x_ofs += 4;
		}
		else
		{
			setPolyFT4(poly);
			
			poly->x0 = x_ofs;
			poly->y0 = y;
			poly->x1 = x_ofs + fmvFontUV[chr].w;
			poly->y1 = y;
			poly->x2 = x_ofs;
			poly->y2 = y + fmvFontUV[chr].h;
			poly->x3 = x_ofs + fmvFontUV[chr].w;
			poly->y3 = y + fmvFontUV[chr].h;
			poly->u0 = fmvFontUV[chr].u;
			poly->v0 = fmvFontUV[chr].v;
			poly->u1 = fmvFontUV[chr].u + fmvFontUV[chr].w;
			poly->v1 = fmvFontUV[chr].v;
			poly->u2 = fmvFontUV[chr].u;
			poly->v2 = fmvFontUV[chr].v + fmvFontUV[chr].h;
			poly->u3 = fmvFontUV[chr].u + fmvFontUV[chr].w;
			poly->v3 = fmvFontUV[chr].v + fmvFontUV[chr].h;
			poly->tpage = getTPage(0,0, 960, 0);
			poly->clut = getClut(960, 72);

			poly->r0 = brightness;
			poly->g0 = brightness;
			poly->b0 = brightness;

			addPrim(&ot, poly);
			
			x_ofs += fmvFontUV[chr].w;
			drawnChars++;
			poly++;
		}
	}

	DrawOTag((ulong*)&ot);
}

int UnpackJPEG(unsigned char* src_buf, unsigned src_length, unsigned bpp, unsigned char* dst_buf, int& width, int& height)
{
	// it's rough but it works...
	jpeg_decompress_struct cinfo;
	jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	jpeg_mem_src(&cinfo, src_buf, src_length);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);

	width = cinfo.image_width;
	height = cinfo.image_height;

	for (u_char* curr_scanline = dst_buf; 
		cinfo.output_scanline < cinfo.output_height; 
		curr_scanline += cinfo.output_width * cinfo.num_components)
	{
		jpeg_read_scanlines(&cinfo, &curr_scanline, 1);
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	return 0;
}

// emulator window TODO: interface
extern int g_swapInterval;

void SetupMovieRectangle(int image_w, int image_h)
{
	int windowWidth, windowHeight;
	PsyX_GetScreenSize(windowWidth, windowHeight);

	float psxScreenW = 320.0f;
	float psxScreenH = 200.0f;	// FIXME: NTSC scaling

	const float video_aspect = float(image_w) / float(image_h);
	const float psx_aspect = (psxScreenH / psxScreenW);
	
	const float image_to_screen_w = float(psxScreenW) / float(windowWidth);// * psx_aspect;
	const float image_to_screen_h = float(psxScreenH) / float(windowHeight);// * psx_aspect;

	const float image_scale = float(windowHeight) / psxScreenH * video_aspect;
	
	float clipRectX = 0;
	float clipRectY = 0;
	float clipRectW = image_to_screen_w * image_scale;
	float clipRectH = image_to_screen_h * image_scale;

	clipRectX -= clipRectW * 0.5f;
	clipRectY -= clipRectH * 0.5f;
	
	u_char l = 0;
	u_char t = 0;
	u_char r = 1;
	u_char b = 1;

#ifdef USE_PGXP
	GR_SetViewPort(0, 0, windowWidth, windowHeight);

	GrVertex blit_vertices[] =
	{
		{ clipRectX+ clipRectW,  clipRectY + clipRectH,		0, 0,    0, 0, 0, 0,	r, t, 0, 0, },
		{ clipRectX, clipRectY,    							0, 0,    0, 0, 0, 0,	l, b, 0, 0, },
		{ clipRectX, clipRectY + clipRectH,    				0, 0,    0, 0, 0, 0,	l, t, 0, 0, },
		
		{ clipRectX + clipRectW, clipRectY,    				0, 0,    0, 0, 0, 0,	r, b, 0, 0, },
		{ clipRectX, clipRectY,    							0, 0,    0, 0, 0, 0,	l, b, 0, 0, },
		{ clipRectX + clipRectW,  clipRectY + clipRectH,    0, 0,    0, 0, 0, 0,	r, t, 0, 0, },
	};
#else
	GR_SetViewPort(0, 0, windowWidth, windowHeight);

	clipRectX *= 2;
	clipRectY *= 2;
	clipRectW *= 2;
	clipRectH *= 2;

	GrVertex blit_vertices[] =
	{
		{ clipRectX+ clipRectW,  clipRectY + clipRectH,		0, 0,    r, t,    0, 0,		0, 0, 		0, 0 },
		{ clipRectX, clipRectY,    							0, 0,    l, b,    0, 0,		0, 0, 		0, 0 },
		{ clipRectX, clipRectY + clipRectH,    				0, 0,    l, t,    0, 0,		0, 0, 		0, 0 },

		{ clipRectX + clipRectW, clipRectY,    				0, 0,    r, b,    0, 0,     0, 0, 		0, 0 },
		{ clipRectX, clipRectY,    							0, 0,    l, b,    0, 0,		0, 0, 		0, 0 },
		{ clipRectX + clipRectW,  clipRectY + clipRectH,    0, 0,    r, t,    0, 0,		0, 0, 		0, 0 },
	};
#endif

	GR_UpdateVertexBuffer(blit_vertices, 6);
}

// send audio buffer
void QueueAudioBuffer(ALuint buffer, ALuint source, ReadAVI::frame_entry_t& frame_entry, ReadAVI::stream_format_auds_t& audio_format, int frame_offset, int frame_size)
{
	ALenum alFormat;

	if (audio_format.block_size_of_data == 8)
		alFormat = audio_format.channels == 2 ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
	else if (audio_format.block_size_of_data == 16)
		alFormat = audio_format.channels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
	else
		alFormat = AL_FORMAT_MONO16;

	// upload to specific buffer
	alBufferData(buffer, alFormat, frame_entry.buf + frame_offset, frame_size, audio_format.samples_per_second);

	// queue after uploading
	alSourceQueueBuffers(source, 1, &buffer);
}

const char* fmv_shader =
	"varying vec4 v_texcoord;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord;\n"
	"	void main() {\n"
	"		v_texcoord = a_texcoord;\n"
	"		gl_Position = vec4(a_position.xy, 0.0, 1.0);\n"
	"	}\n"
	"#else\n"
	"	uniform sampler2D s_texture;\n"
	"	void main() {\n"
	"		fragColor = texture2D(s_texture, v_texcoord.xy);\n"
	"	}\n"
	"#endif\n";

TextureID g_FMVTexture = 0;
ShaderID g_FMVShader = 0;

extern int GR_Shader_CheckShaderStatus(GLuint shader);
extern int GR_Shader_CheckProgramStatus(GLuint program);

extern ShaderID GR_Shader_Compile(const char* source);
extern void GR_SetShader(const ShaderID& shader);

#define DECODE_BUFFER_ALLOC (3840 * 2160 * 3)	// RGB in 4K frame

u_char* g_FMVDecodedImageBuffer = NULL;

void FMVPlayerInitGL()
{
	g_FMVDecodedImageBuffer = (u_char*)malloc(DECODE_BUFFER_ALLOC);	
	memset(g_FMVDecodedImageBuffer, 0, DECODE_BUFFER_ALLOC);
	// FIXME: double buffering?
	
#if defined(RENDERER_OGL) || defined(OGLES)
	glGenTextures(1, &g_FMVTexture);

	glBindTexture(GL_TEXTURE_2D, g_FMVTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 4096, 4096, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	if(!g_FMVShader)
	{
		g_FMVShader = GR_Shader_Compile(fmv_shader);
	}
#endif
}

void FMVPlayerShutdownGL()
{
	RECT16 rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 512;
	rect.h = 256;

	free(g_FMVDecodedImageBuffer);
	g_FMVDecodedImageBuffer = NULL;
	
	ClearImage(&rect, 0, 0, 0);
	GR_SwapWindow();

	GR_DestroyTexture(g_FMVTexture);
}

struct SUBTITLE
{
	ushort startframe;
	ushort endframe;
	ushort x;
	ushort y;
	ushort unk3;
	ushort unk4;
	char text[32];
};

SUBTITLE g_Subtitles[128];
int g_NumSubtitles = 0;

void InitSubtitles(const char* filename)
{
	g_NumSubtitles = 0;
	FILE* subFile = fopen(filename, "rb");
	if (subFile)
	{
		fread(&g_NumSubtitles, sizeof(int), 1, subFile);

		fread(g_Subtitles, sizeof(SUBTITLE), g_NumSubtitles, subFile);

		fclose(subFile);
	}
}

char* g_CreditsBuffer = NULL;
char* g_CreditsLines[512];

void InitCredits(const char* filename)
{
	memset(g_CreditsLines, 0, sizeof(g_CreditsLines));
	
	FILE* credFile = fopen(filename, "rb");
	if (credFile)
	{
		fseek(credFile, 0, SEEK_END);
		int credits_buffer_size = ftell(credFile);
		fseek(credFile, 0, SEEK_SET);

		g_CreditsBuffer = (char*)malloc(credits_buffer_size + 1);

		fread(g_CreditsBuffer, 1, credits_buffer_size, credFile);
		g_CreditsBuffer[credits_buffer_size] = 0;

		fclose(credFile);
	}

	if(g_CreditsBuffer)
	{
		// make credits into lines
		char* str = g_CreditsBuffer;
		int numCreditsLines = 0;

		while(*str)
		{
			if(!g_CreditsLines[numCreditsLines])
				g_CreditsLines[numCreditsLines] = str;
			
			if(*str == '\r')
			{
				*str = '\0';
				
				if (*++str == '\n')
					numCreditsLines++;
			}
			else if(*str == '\n')
			{
				*str = '\0';
				numCreditsLines++;
			}
			
			str++;
		}
	}
}

void PrintSubtitleText(SUBTITLE* sub)
{
	char* str = sub->text;

	// skip some trailing spaces
	while (isspace(*str)) {
		str++;
	}

	PrintFMVText(str, 256, sub->y - 25, 128);
}

void DisplaySubtitles(int frame_number)
{
	// draw subtitie text
	for (int i = 0; i < g_NumSubtitles; i++)
	{
		if(frame_number >= g_Subtitles[i].startframe && frame_number <= g_Subtitles[i].endframe)
			PrintSubtitleText(&g_Subtitles[i]);
	}
}

#define CREDITS_START_FRAME				700
#define CREDITS_STOP_FRAME				5450
#define CREDITS_FADE_START_FRAME		5900

void DisplayCredits(int frame_number)
{
	int i;

	int frame = frame_number;

	if (frame > CREDITS_STOP_FRAME)
		frame = CREDITS_STOP_FRAME;
	
	int height = (frame - CREDITS_START_FRAME) * 30 >> 5;

	int fade = 0;
	if (frame_number > CREDITS_FADE_START_FRAME)
	{
		fade = (frame_number - CREDITS_FADE_START_FRAME) * 2;
		if (fade > 128)
			fade = 128;
	}

	for(i = 0; i < 512; i++)
	{
		int text_h = 250 - height + i * 16;
		
		if (text_h < -20 || text_h > 260)
			continue;
		
		char* str = g_CreditsLines[i];

		if(str)
			PrintFMVText(str, 256, text_h, 128 - fade);
	}
}

extern void GR_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar);

void DrawFrame(ReadAVI::stream_format_t& stream_format, int frame_number, int credits, int image_w, int image_h)
{
	int windowWidth, windowHeight;
	PsyX_GetScreenSize(windowWidth, windowHeight);

	PsyX_BeginScene();

	GR_Clear(0, 0, windowWidth, windowHeight, 0, 0, 0);
	
	glBindTexture(GL_TEXTURE_2D, g_FMVTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, image_w, image_h, 0, GL_RGB, GL_UNSIGNED_BYTE, g_FMVDecodedImageBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	GR_SetShader(g_FMVShader);
	GR_SetTexture(g_FMVTexture, (TexFormat)-1);

	GR_SetScissorState(0);
	GR_EnableDepth(0);
	GR_SetStencilMode(0);
	GR_SetBlendMode(BM_NONE);
	
	SetupMovieRectangle(stream_format.image_width, stream_format.image_height);

	GR_DrawTriangles(0, 2);

	DisplaySubtitles(frame_number);

	if(credits && frame_number >= CREDITS_START_FRAME)
	{
		DisplayCredits(frame_number);
	}
	
	PsyX_EndScene();
}

void DoPlayFMV(RENDER_ARG* arg, int subtitles)
{
	int fd = arg->render - (arg->render % 10);
	if (fd > 0)
		fd /= 10;

	char filename[250];
	sprintf(filename, "%sFMV\\%d\\RENDER%d.STR[0].avi", gDataFolder, fd, arg->render);
	FS_FixPathSlashes(filename);

	ReadAVI readAVI(filename);
	
	// also load subtitle file
	if (subtitles)
	{
		sprintf(filename, "%sFMV\\%d\\RENDER%d.SBN", gDataFolder, fd, arg->render);
		FS_FixPathSlashes(filename);
	
		InitSubtitles(filename);
	}
	else
	{
		g_NumSubtitles = 0;
	}

	if(arg->credits)
	{
		sprintf(filename, "%sDATA\\CREDITS.ENG", gDataFolder);
		FS_FixPathSlashes(filename);
	
		InitCredits(filename);
	}

	ReadAVI::avi_header_t avi_header = readAVI.GetAviHeader();

	ReadAVI::stream_format_t stream_format = readAVI.GetVideoFormat();
	ReadAVI::stream_format_auds_t audio_format = readAVI.GetAudioFormat();

	if (strcmp(stream_format.compression_type, "MJPG")) 
	{
		printf("Only MJPG supported\n");
		return;
	}

	ReadAVI::frame_entry_t frame_entry;
	frame_entry.type = (ReadAVI::chunk_type_t)(ReadAVI::ctype_video_data | ReadAVI::ctype_audio_data);
	frame_entry.pointer = 0;

	ALuint audioStreamSource;
	ALuint audioStreamBuffers[4];

	alGenSources(1, &audioStreamSource);
	alGenBuffers(4, audioStreamBuffers);
	alSourcei(audioStreamSource, AL_LOOPING, AL_FALSE);

	timerCtx_t fmvTimer;

	Util_InitHPCTimer(&fmvTimer);

	double nextFrameDelay = 0.0;

	int frame_size;
	int queue_counter = 0;

	int fade_out = 0;
	int done_frames = 0;

	Util_GetHPCTime(&fmvTimer, 1);
	
	// main loop
	while (true)
	{
		double delta = Util_GetHPCTime(&fmvTimer, 1);

		if (delta > 1.0)
			delta = 0.0;

		nextFrameDelay -= delta;

		if (nextFrameDelay > 0) // wait for frame
		{
			PsyX_EndScene();
			continue;
		}

		frame_entry.type = (ReadAVI::chunk_type_t)(ReadAVI::ctype_video_data | ReadAVI::ctype_audio_data);
		frame_size = readAVI.GetFrameFromIndex(&frame_entry);

		// done, no frames
		if (frame_size < 0)
			break;

		// handle recap
		if(arg->recap && done_frames > arg->recap)
			break;

		// fade out sound and stop playback
		if (fade_out > 0)
		{
			fade_out -= 18;
			if (fade_out < 0)
				break;

			alSourcef(audioStreamSource, AL_GAIN, float(fade_out) / 255.0);
		}

		if (frame_size > 0)
		{
			if (frame_entry.type == ReadAVI::ctype_compressed_video_frame)
			{
				int real_frame_width;
				int real_frame_height;
				
				// Do video frame
				int ret = UnpackJPEG(frame_entry.buf, frame_size, stream_format.bits_per_pixel, g_FMVDecodedImageBuffer, real_frame_width, real_frame_height);

				if (ret == 0)
				{
					DrawFrame(stream_format, done_frames, arg->credits, real_frame_width, real_frame_height);
				}

				// set next step time
				if (g_swapInterval == 1)
					nextFrameDelay += double(avi_header.TimeBetweenFrames) / 1000000.0;
				else
					nextFrameDelay = 0.0;
				
				done_frames++;
			}
			else if (frame_entry.type == ReadAVI::ctype_audio_data)
			{
				// Update audio buffer
				ALint state;
				alGetSourcei(audioStreamSource, AL_SOURCE_STATE, &state);

				int numProcessed = 0;
				alGetSourcei(audioStreamSource, AL_BUFFERS_PROCESSED, &numProcessed);

				if (state == AL_STOPPED || numProcessed > 0)
				{
					ALuint qbuffer;

					// stop queued
					if (state == AL_STOPPED)
					{
						alGetSourcei(audioStreamSource, AL_BUFFERS_QUEUED, &numProcessed);

						// dequeue all buffers for restarting
						while (numProcessed--)
							alSourceUnqueueBuffers(audioStreamSource, 1, &qbuffer);

						// restart
						queue_counter = 0;
					}
					else if(numProcessed && queue_counter > 3)
					{
						// dequeue one buffer
						alSourceUnqueueBuffers(audioStreamSource, 1, &qbuffer);
						QueueAudioBuffer(qbuffer, audioStreamSource, frame_entry, audio_format, 0, frame_size);
					}
				}

				// for starting only
				if (queue_counter < 4)
					QueueAudioBuffer(audioStreamBuffers[queue_counter++], audioStreamSource, frame_entry, audio_format, 0, frame_size);

				if((queue_counter > 1 || numProcessed == -1) && state != AL_PLAYING)
					alSourcePlay(audioStreamSource);
			}
		}

		ReadControllers();

		// exit
		if (fade_out == 0 && Pads[0].mapnew > 0)
			fade_out = 255;
	}

	alDeleteSources(1, &audioStreamSource);
	alDeleteBuffers(4, audioStreamBuffers);
}

// FMV main function
int FMV_main(RENDER_ARGS* args)
{
	DISPENV disp;
	DRAWENV draw;

	FMVPlayerInitGL();

	InitFMVFont();

	SetupDefDrawEnv(&draw, 0, 0, 512, 256);
	SetupDefDispEnv(&disp, 0, 0, 512, 256);

	draw.dfe = 1;

	draw.clip.x = -512;
	draw.clip.w = 1200;
	draw.clip.y = -1;
	draw.clip.h = 512;
	
	disp.isinter = 0;

	PutDrawEnv(&draw);
	PutDispEnv(&disp);

	GR_SetupClipMode(draw.clip, draw.dfe);

	for (int i = 0; i < args->nRenders; i++)
	{
		DoPlayFMV(&args->Args[i], args->subtitle);
	}

	FMVPlayerShutdownGL();

	if (g_CreditsBuffer)
		free(g_CreditsBuffer);
	g_CreditsBuffer = NULL;

	return 0;
}

