/*
 * player.h
 *
 *  Created on: 8 мая 2018 г.
 *      Author: olegvedi@gmail.com
 */

#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <AL/al.h>

extern "C"
{
#include <jpeglib.h>
}


#include "EMULATOR_PRIVATE.H"

#include "ReadAVI.h"

#include "DRIVER2.H"
#include "C/PAD.H"
#include "C/SYSTEM.H"
#include "C/E3STUFF.H"
#include "C/PRES.H"
#include "C/PAUSE.H"

int UnpackJPEG(unsigned char* src_buf, unsigned src_length, unsigned bpp, unsigned char* dst_buf)
{
	// it's rough but it works...
	jpeg_decompress_struct cinfo;
	jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	jpeg_mem_src(&cinfo, src_buf, src_length);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);

	for (u_char* curr_scanline = dst_buf; cinfo.output_scanline < cinfo.output_height; curr_scanline += cinfo.output_width * cinfo.num_components)
	{
		jpeg_read_scanlines(&cinfo, &curr_scanline, 1);
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	return 0;
}

// emulator window TODO: interface
extern SDL_Window* g_window;
extern int g_swapInterval;

void SetupMovieRectangle(ReadAVI::stream_format_t& strFmt)
{
	int windowWidth, windowHeight;
	Emulator_GetScreenSize(windowWidth, windowHeight);

	float psxScreenW = 320.0f;
	float psxScreenH = 240.0f;

	int ideal_image_height = strFmt.image_height; // strFmt.image_height;

	if (ideal_image_height < 220)
		ideal_image_height = 220;

	RECT16 rect;
	rect.x = 0;
	rect.y = (psxScreenH - ideal_image_height);// / 2;
	rect.w = strFmt.image_width;
	rect.h = ideal_image_height;

	const float video_aspect = float(strFmt.image_width) / float(ideal_image_height);
	float emuScreenAspect = float(windowHeight) / float(windowWidth);

	// first map to 0..1
	float clipRectX = (float)(rect.x) / psxScreenW;
	float clipRectY = (float)(rect.y) / psxScreenH;
	float clipRectW = (float)(rect.w) / psxScreenW;
	float clipRectH = (float)(rect.h) / psxScreenH;

	// then map to screen
	clipRectY -= 1.0f;
	clipRectX -= 1.0f;

	clipRectY /= video_aspect * emuScreenAspect;
	clipRectH /= emuScreenAspect * video_aspect;

	clipRectW *= 2.0f;
	clipRectH *= 2.0f;

	u_char l = 0;
	u_char t = 0;
	u_char r = 1;
	u_char b = 1;

	Vertex blit_vertices[] =
	{
		{ clipRectX+ clipRectW,  clipRectY + clipRectH,    0, 0,    r, t,    0, 0,    0, 0, 0, 0 },
		{ clipRectX, clipRectY,    0, 0,    l, b,    0, 0,    0, 0, 0, 0 },
		{ clipRectX, clipRectY + clipRectH,    0, 0,    l, t,    0, 0,    0, 0, 0, 0 },

		{ clipRectX + clipRectW, clipRectY,    0, 0,    r, b,    0, 0,    0, 0, 0, 0 },
		{ clipRectX, clipRectY,    0, 0,    l, b,    0, 0,    0, 0, 0, 0 },
		{ clipRectX + clipRectW,  clipRectY + clipRectH,    0, 0,    r, t,    0, 0,    0, 0, 0, 0 },
	};

	Emulator_UpdateVertexBuffer(blit_vertices, 6);
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

extern void Shader_CheckShaderStatus(GLuint shader);
extern void Shader_CheckProgramStatus(GLuint program);
extern ShaderID Shader_Compile(const char* source);
extern void Emulator_SetShader(const ShaderID& shader);

void FMVPlayerInitGL()
{
#if defined(OGL) || defined(OGLES)
	glGenTextures(1, &g_FMVTexture);

	glBindTexture(GL_TEXTURE_2D, g_FMVTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 320, 240, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	if(!g_FMVShader)
		g_FMVShader = Shader_Compile(fmv_shader);
#endif
}

void FMVPlayerShutdownGL()
{
	Emulator_DestroyTexture(g_FMVTexture);
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

SUBTITLE g_Subtitles[512];
int g_NumSubtitles = 0;

void InitSubtitles(const char* filename)
{
	g_NumSubtitles = 0;
	FILE* subFile = fopen(filename, "rb");
	if (subFile)
	{
		fread(&g_NumSubtitles, sizeof(int), 1, subFile);
		printInfo("Subtitle text count: %d\n", g_NumSubtitles);

		fread(g_Subtitles, sizeof(g_Subtitles), g_NumSubtitles, subFile);

		fclose(subFile);
	}
}

void PrintSubtitleText(SUBTITLE* sub)
{
	gShowMap = 1;

	char* str = sub->text;

	// skip some trailing spaces
	while (isspace(*str)) {
		str++;
	}

	SetTextColour(128, 128, 128);
	PrintString(str, (600 - StringWidth(str)) * 0x8000 >> 0x10, sub->y - 25);

	gShowMap = 0;
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

extern void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar);

void DrawFrame(ReadAVI::stream_format_t& stream_format, int frame_number)
{
	int windowWidth, windowHeight;
	Emulator_GetScreenSize(windowWidth, windowHeight);

	Emulator_BeginScene();

	Emulator_Clear(0, 0, windowWidth, windowHeight, 0, 0, 0);

	glBindTexture(GL_TEXTURE_2D, g_FMVTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, stream_format.image_width, stream_format.image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _frontend_buffer);
	
	Emulator_SetViewPort(0, 0, windowWidth, windowHeight);
	Emulator_SetTexture(g_FMVTexture, (TexFormat)-1);
	Emulator_SetShader(g_FMVShader);

	SetupMovieRectangle(stream_format);

	Emulator_SetBlendMode(BM_NONE);
	Emulator_DrawTriangles(0, 2);

	DisplaySubtitles(frame_number);

	Emulator_EndScene();
}

void DoPlayFMV(RENDER_ARG* arg, int subtitles)
{
	int fd = arg->render - (arg->render % 10);
	if (fd > 0)
		fd /= 10;

	char filename[250];
	sprintf(filename, "%sFMV\\%d\\RENDER%d.STR[0].AVI", gDataFolder, fd, arg->render);

	ReadAVI readAVI(filename);

	// also load subtitle file
	if (subtitles)
	{
		sprintf(filename, "%sFMV\\%d\\RENDER%d.SBN", gDataFolder, fd, arg->render);
		InitSubtitles(filename);
	}
	else
	{
		g_NumSubtitles = 0;
	}

	ReadAVI::avi_header_t avi_header = readAVI.GetAviHeader();

	ReadAVI::stream_format_t stream_format = readAVI.GetVideoFormat();
	ReadAVI::stream_format_auds_t audio_format = readAVI.GetAudioFormat();

	if (strcmp(stream_format.compression_type, "MJPG")) {
		printf("Only MJPG supported\n");
		return;
	}

	SDL_Surface* BufSurface = SDL_CreateRGBSurface(0, stream_format.image_width, stream_format.image_height, stream_format.bits_per_pixel, 0, 0, 0, 0);

	ReadAVI::frame_entry_t frame_entry;
	frame_entry.type = (ReadAVI::chunk_type_t)(ReadAVI::ctype_video_data | ReadAVI::ctype_audio_data);
	frame_entry.pointer = 0;

	ALuint audioStreamSource;
	ALuint audioStreamBuffers[4];

	alGenSources(1, &audioStreamSource);
	alGenBuffers(4, audioStreamBuffers);
	alSourcei(audioStreamSource, AL_LOOPING, AL_FALSE);

	int nextTime = SDL_GetTicks();
	int oldTime = nextTime;

	int frame_size;
	int queue_counter = 0;

	int fade_out = 0;
	int done_frames = 0;

	// main loop
	while (true)
	{
		int curTime = SDL_GetTicks();
		int deltaTime = curTime - oldTime;

		if (deltaTime > 1000)
		{
			nextTime += deltaTime;
			oldTime = curTime;
		}


		if (curTime <= nextTime) // wait for frame
		{
			Emulator_EndScene();
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
				// Do video frame
				int ret = UnpackJPEG(frame_entry.buf, frame_size, stream_format.bits_per_pixel, (unsigned char*)_frontend_buffer);

				if (ret == 0)
					DrawFrame(stream_format, done_frames);

				// set next step time
				if (g_swapInterval == 0)
					nextTime = curTime;
				else
					nextTime += avi_header.TimeBetweenFrames / 1000;

				oldTime = curTime;

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

				if(queue_counter > 0 && state != AL_PLAYING)
					alSourcePlay(audioStreamSource);
			}
		}

		ReadControllers();

		// exit
		if (fade_out == 0 && Pads[0].mapnew > 0)
			fade_out = 255;
	}

	alDeleteSources(1, &audioStreamSource);
	alDeleteBuffers(2, audioStreamBuffers);
}

// FMV main function
int FMV_main(RENDER_ARGS* args)
{
	DISPENV disp;
	DRAWENV draw;

	FMVPlayerInitGL();
	LoadFont(NULL);

	SetupDefDrawEnv(&draw, 0, 0, 600, 250);
	SetupDefDispEnv(&disp, 0, 0, 600, 250);
	draw.dfe = 1;
	PutDrawEnv(&draw);
	PutDispEnv(&disp);

	for (int i = 0; i < args->nRenders; i++)
	{
		DoPlayFMV(&args->Args[i], args->subtitle);
	}

	FMVPlayerShutdownGL();

	return 0;
}

