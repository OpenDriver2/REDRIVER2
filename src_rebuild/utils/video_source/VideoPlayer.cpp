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
#include "C\PAD.H"

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

		for (int s = 0; s < cinfo.output_width * cinfo.num_components; s += cinfo.num_components)
		{
			// flip RGB
			u_char tmp = curr_scanline[s];
			curr_scanline[s] = curr_scanline[s+2];
			curr_scanline[s+2] = tmp;
		}
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	return 0;
}

// emulator window TODO: interface
extern SDL_Window* g_window;

void GetMovieRectangle(SDL_Rect& rect, ReadAVI::stream_format_t& strFmt)
{
	int windowWidth, windowHeight;
	Emulator_GetScreenSize(windowWidth, windowHeight);

	float psxScreenW = 320.0f;
	float psxScreenH = 240.0f;

	rect.x = 0;
	rect.y = (psxScreenH - strFmt.image_height) / 2;
	rect.w = strFmt.image_width;
	rect.h = strFmt.image_height;

	const float video_aspect = float(strFmt.image_width) / float(strFmt.image_height + 48);
	float emuScreenAspect = float(windowHeight) / float(windowWidth);

	{
		// first map to 0..1
		float clipRectX = (float)(rect.x - activeDispEnv.disp.x) / psxScreenW;
		float clipRectY = (float)(rect.y - activeDispEnv.disp.y) / psxScreenH;
		float clipRectW = (float)(rect.w) / psxScreenW;
		float clipRectH = (float)(rect.h) / psxScreenH;

		// then map to screen
		clipRectY -= 0.5f;

		clipRectY /= video_aspect * emuScreenAspect;
		clipRectH /= emuScreenAspect * video_aspect;

		clipRectY += 0.5f;

		rect.x = clipRectX * windowWidth;
		rect.y = clipRectY * windowHeight;
		rect.w = clipRectW * windowWidth;
		rect.h = clipRectH * windowHeight;
	}
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

void DoPlayFMV(RENDER_ARG* arg, int subtitles)
{
	int fd = arg->render - (arg->render % 10);
	if (fd > 0)
		fd /= 10;

	char filename[250];
	sprintf(filename, "DRIVER2\\FMV\\%d\\RENDER%d.STR[0].AVI", fd, arg->render);

	ReadAVI readAVI(filename);

	int indexes = readAVI.GetIndexCnt();
	printf("indexes:%d\n", indexes);

	ReadAVI::avi_header_t avi_header = readAVI.GetAviHeader();

	ReadAVI::stream_format_t stream_format = readAVI.GetVideoFormat();
	ReadAVI::stream_format_auds_t audio_format = readAVI.GetAudioFormat();

	printf("video stream compression: %s\n", stream_format.compression_type);
	printf("audio stream format: %d\n", audio_format.format);
	
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

	int frame_size;
	int queue_counter = 0;

	while (true)
	{
		if (SDL_GetTicks() < nextTime) // wait for frame
		{
			Emulator_EndScene();
			continue;
		}

		frame_entry.type = (ReadAVI::chunk_type_t)(ReadAVI::ctype_video_data | ReadAVI::ctype_audio_data);
		frame_size = readAVI.GetFrameFromIndex(&frame_entry);

		// done, no frames
		if (frame_size < 0)
			break;

		if (frame_size > 0)
		{
			if (frame_entry.type == ReadAVI::ctype_compressed_video_frame)
			{
				// Update video frame
				SDL_Surface* MainSurface = SDL_GetWindowSurface(g_window);

				SDL_LockSurface(BufSurface);

				int ret = UnpackJPEG(frame_entry.buf, frame_size, stream_format.bits_per_pixel, (unsigned char*)BufSurface->pixels);
				SDL_UnlockSurface(BufSurface);

				if (ret == 0)
				{
					SDL_Rect rect;
					GetMovieRectangle(rect, stream_format);

					SDL_UpperBlitScaled(BufSurface, NULL, MainSurface, &rect);
					SDL_UpdateWindowSurface(g_window);
				}

				SDL_FreeSurface(MainSurface);

				// set next step time
				nextTime = SDL_GetTicks() + (avi_header.TimeBetweenFrames - 9000) / 1000;
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
					else if(numProcessed && queue_counter >= 4)
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

		if (Pads[0].mapnew > 0)
			break;

		Emulator_EndScene();
	}

	alDeleteSources(1, &audioStreamSource);
	alDeleteBuffers(4, audioStreamBuffers);
}

// FMV main function
int FMV_main(RENDER_ARGS* args)
{
	for (int i = 0; i < args->nRenders; i++)
	{
		DoPlayFMV(&args->Args[i], args->subtitle);
	}

	return 0;
}

