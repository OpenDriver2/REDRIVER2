/*
 * ReadAVI.cpp
 *
 *
 * Copyright (c) 2004-2013, Michael Kohn <mike@mikekohn.net> http://www.mikekohn.net/
 *
 * Copyright (c) 2018, olegvedi@gmail.com (C++ implementation and adds)
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the author nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include "ReadAVI.h"

#include <iostream>
#include <string.h>

#define ZEROIZE(x) {memset(&x, 0, sizeof(x));}

using namespace std;

#define VERBOSE
#define DBG_LVL_DEF 0

#ifdef VERBOSE
#define MSG_DBG(dl, format, ...) {if(dl <= DBG_LVL_DEF ) fprintf(stdout, format ,##__VA_ARGS__);}
#else
#define MSG_DBG(dl, format, ...)
#endif

ReadAVI::chunk_type_int_t ReadAVI::chunk_types[ChunkTypesCnt] = {
	{"db", ctype_uncompressed_video_frame }, 
	{"dc", ctype_compressed_video_frame },
	{"pc", ctype_palette_change }, 
	{"wb", ctype_audio_data } };

ReadAVI::ReadAVI(const char* filename)
{
	data_buf = NULL;
	stream_format_vid.palette = NULL;
	data_buf_size = 0;
	inFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	inFile.open(filename, ios_base::ate | ios_base::in | ios_base::binary);
	fileSize = inFile.tellg();
	inFile.close();
	inFile.open(filename, ios_base::in | ios_base::binary);

	try {
		parse_riff();
	}
	catch (std::system_error& e) { //file corrupted?
		std::cerr << e.code().message() << "\n";
		if (index_entries.size() == 0) {
			free();
			throw;
		}
	}
}

ReadAVI::~ReadAVI()
{
	free();
}

void ReadAVI::free()
{
	if (inFile.is_open()) {
		inFile.close();
	}

	delete[] stream_format_vid.palette;
	delete[] data_buf;
}

void ReadAVI::check_data_buf(unsigned size)
{
	if (data_buf_size < size) {
		delete[] data_buf;
		data_buf = new unsigned char[size + 1];
		data_buf_size = size;
	}
}

int ReadAVI::GetFrameFromIndex(frame_entry_t* frame_entry)
{
	if (frame_entry->pointer >= index_entries.size()) {
		MSG_DBG(2, "Pointer out of range\n");
		return -5;
	}
	for (unsigned i = frame_entry->pointer; i < index_entries.size(); i++) {
		if (index_entries[i].type & frame_entry->type) {
			check_data_buf(index_entries[i].dwChunkLength);
			try {
				inFile.seekg(index_entries[i].dwChunkOffset, ios_base::beg);
				read_chars_bin(data_buf, index_entries[i].dwChunkLength);
			}
			catch (...) {
				return -1;
			}
			frame_entry->buf = data_buf;
			frame_entry->pointer = i + 1;
			frame_entry->stream_num = index_entries[i].stream_num;
			frame_entry->type = index_entries[i].type;
			return index_entries[i].dwChunkLength;
		}
	}
	MSG_DBG(2, "No more frames\n");
	return -1;
}

#ifdef VERBOSE
int ReadAVI::hex_dump_chunk(int chunk_len)
{
	char chars[17];
	unsigned char c;
	int ch, n;

	chars[16] = 0;

	for (n = 0; n < chunk_len; n++) {
		if ((n % 16) == 0) {
			if (n != 0)
				MSG_DBG(2, "%s\n", chars);
			MSG_DBG(2, "      ");
			memset(chars, ' ', 16);
		}
		read_chars_bin(&c, 1);
		ch = c;
		if (ch == EOF)
			break;
		MSG_DBG(2, "%02x ", ch);
		if (ch >= ' ' && ch <= 126) {
			chars[n % 16] = ch;
		}
		else {
			chars[n % 16] = '.';
		}
	}

	if ((n % 16) != 0) {
		for (ch = n % 16; ch < 16; ch++) {
			MSG_DBG(2, "   ");
		}
	}
	MSG_DBG(2, "%s\n", chars);

	return 0;
}
#endif

int ReadAVI::decodeCkid(char* ckid, chunk_type_t* chunk_type)
{
	int stream = (ckid[0] - '0') * 10 + (ckid[1] - '0');
	for (int i = 0; i < ChunkTypesCnt; i++) {
		if (chunk_types[i].type_id[0] == ckid[2] && chunk_types[i].type_id[1] == ckid[3]) {
			*chunk_type = chunk_types[i].type;
			return stream;
		}
	}
	return -1;
}

int ReadAVI::parse_idx1(int chunk_len)
{
	index_entry_t index_entry;
	index_entry.type = ctype_none;
	int t;

	MSG_DBG(2, "      IDX1\n");
	MSG_DBG(2, "      -------------------------------\n");
	MSG_DBG(2, "      stream  type   dwFlags         dwChunkOffset        dwChunkLength\n");

	for (t = 0; t < chunk_len / 16; t++) {
		char buf[5];
		read_chars(buf, 4);
		index_entry.stream_num = decodeCkid(buf, &index_entry.type);
		index_entry.dwFlags = read_int();
		index_entry.dwChunkOffset = read_int() + movi_offset + 0x10;
		index_entry.dwChunkLength = read_int();

		MSG_DBG(2, "         %d     %d     0x%08x      0x%08x           0x%08x\n", index_entry.stream_num, index_entry.type,
			index_entry.dwFlags, index_entry.dwChunkOffset, index_entry.dwChunkLength);
		index_entries.push_back(index_entry);
	}

	MSG_DBG(2, "\n");

	return 0;
}

int ReadAVI::read_avi_header()
{
#ifdef VERBOSE
	long offset = inFile.tellg();
#endif
	avi_header.TimeBetweenFrames = read_int();
	avi_header.MaximumDataRate = read_int();
	avi_header.PaddingGranularity = read_int();
	avi_header.Flags = read_int();
	avi_header.TotalNumberOfFrames = read_int();
	avi_header.NumberOfInitialFrames = read_int();
	avi_header.NumberOfStreams = read_int();
	avi_header.SuggestedBufferSize = read_int();
	avi_header.Width = read_int();
	avi_header.Height = read_int();
	avi_header.TimeScale = read_int();
	avi_header.DataRate = read_int();
	avi_header.StartTime = read_int();
	avi_header.DataLength = read_int();

	MSG_DBG(2, "         offset=0x%lx\n", offset);
	MSG_DBG(2, "             TimeBetweenFrames: %d\n", avi_header.TimeBetweenFrames);
	MSG_DBG(2, "               MaximumDataRate: %d\n", avi_header.MaximumDataRate);
	MSG_DBG(2, "            PaddingGranularity: %d\n", avi_header.PaddingGranularity);
	MSG_DBG(2, "                         Flags: %d\n", avi_header.Flags);
	MSG_DBG(2, "           TotalNumberOfFrames: %d\n", avi_header.TotalNumberOfFrames);
	MSG_DBG(2, "         NumberOfInitialFrames: %d\n", avi_header.NumberOfInitialFrames);
	MSG_DBG(2, "               NumberOfStreams: %d\n", avi_header.NumberOfStreams);
	MSG_DBG(2, "           SuggestedBufferSize: %d\n", avi_header.SuggestedBufferSize);
	MSG_DBG(2, "                         Width: %d\n", avi_header.Width);
	MSG_DBG(2, "                        Height: %d\n", avi_header.Height);
	MSG_DBG(2, "                     TimeScale: %d\n", avi_header.TimeScale);
	MSG_DBG(2, "                      DataRate: %d\n", avi_header.DataRate);
	MSG_DBG(2, "                     StartTime: %d\n", avi_header.StartTime);
	MSG_DBG(2, "                    DataLength: %d\n", avi_header.DataLength);

	return 0;
}

static void print_data_handler(unsigned char* handler)
{
	int t;

	for (t = 0; t < 4; t++) {
		if ((handler[t] >= 'a' && handler[t] <= 'z') || (handler[t] >= 'A' && handler[t] <= 'Z')
			|| (handler[t] >= '0' && handler[t] <= '9'))
		{
			MSG_DBG(2, "%c", handler[t]);
		}
		else {
			MSG_DBG(2, "[0x%02x]", handler[t]);
		}
	}
}

int ReadAVI::read_stream_header(stream_header_t* sheader)
{
#ifdef VERBOSE
	long offset = inFile.tellg();
#endif
	read_chars(sheader->DataType, 4);
	read_chars(sheader->DataHandler, 4);
	sheader->Flags = read_int();
	sheader->Priority = read_int();
	sheader->InitialFrames = read_int();
	sheader->TimeScale = read_int();
	sheader->DataRate = read_int();
	sheader->StartTime = read_int();
	sheader->DataLength = read_int();
	sheader->SuggestedBufferSize = read_int();
	sheader->Quality = read_int();
	sheader->SampleSize = read_int();

	MSG_DBG(2, "            offset=0x%lx\n", offset);
	MSG_DBG(2, "                      DataType: %s\n", sheader->DataType);
	MSG_DBG(2, "                   DataHandler: ");
	print_data_handler((unsigned char*)sheader->DataHandler);
	MSG_DBG(2, "\n");
	MSG_DBG(2, "                         Flags: %d\n", sheader->Flags);
	MSG_DBG(2, "                      Priority: %d\n", sheader->Priority);
	MSG_DBG(2, "                 InitialFrames: %d\n", sheader->InitialFrames);
	MSG_DBG(2, "                     TimeScale: %d\n", sheader->TimeScale);
	MSG_DBG(2, "                      DataRate: %d\n", sheader->DataRate);
	MSG_DBG(2, "                     StartTime: %d\n", sheader->StartTime);
	MSG_DBG(2, "                    DataLength: %d\n", sheader->DataLength);
	MSG_DBG(2, "           SuggestedBufferSize: %d\n", sheader->SuggestedBufferSize);
	MSG_DBG(2, "                       Quality: %d\n", sheader->Quality);
	MSG_DBG(2, "                    SampleSize: %d\n", sheader->SampleSize);

	return 0;
}

int ReadAVI::read_stream_format()
{
	int t, r, g, b;
#ifdef VERBOSE
	long offset = inFile.tellg();
#endif
	stream_format_vid.header_size = read_int();
	stream_format_vid.image_width = read_int();
	stream_format_vid.image_height = read_int();
	stream_format_vid.number_of_planes = read_word();
	stream_format_vid.bits_per_pixel = read_word();
	read_chars(stream_format_vid.compression_type, 4);
	//stream_format_vid.compression_type = read_int();
	stream_format_vid.image_size_in_bytes = read_int();
	stream_format_vid.x_pels_per_meter = read_int();
	stream_format_vid.y_pels_per_meter = read_int();
	stream_format_vid.colors_used = read_int();
	stream_format_vid.colors_important = read_int();
	stream_format_vid.palette = 0;

	if (stream_format_vid.colors_important != 0) {
		stream_format_vid.palette = new int[stream_format_vid.colors_important];
		for (t = 0; t < stream_format_vid.colors_important; t++) {
			unsigned char buf[3];
			read_chars_bin(buf, 3);
			b = buf[0];
			g = buf[1];
			r = buf[2];
			stream_format_vid.palette[t] = (r << 16) + (g << 8) + b;
		}
	}

	MSG_DBG(2, "            offset=0x%lx\n", offset);
	MSG_DBG(2, "                   header_size: %d\n", stream_format_vid.header_size);
	MSG_DBG(2, "                   image_width: %d\n", stream_format_vid.image_width);
	MSG_DBG(2, "                  image_height: %d\n", stream_format_vid.image_height);
	MSG_DBG(2, "              number_of_planes: %d\n", stream_format_vid.number_of_planes);
	MSG_DBG(2, "                bits_per_pixel: %d\n", stream_format_vid.bits_per_pixel);
	MSG_DBG(2, "              compression_type: %s\n", stream_format_vid.compression_type);
	/*    MSG_DBG(2, "              compression_type: %04x (%c%c%c%c)\n", stream_format_vid.compression_type,
	 ((stream_format_vid.compression_type) & 255), ((stream_format_vid.compression_type >> 8) & 255),
	 ((stream_format_vid.compression_type >> 16) & 255), ((stream_format_vid.compression_type >> 24) & 255));
	 */
	MSG_DBG(2, "           image_size_in_bytes: %d\n", stream_format_vid.image_size_in_bytes);
	MSG_DBG(2, "              x_pels_per_meter: %d\n", stream_format_vid.x_pels_per_meter);
	MSG_DBG(2, "              y_pels_per_meter: %d\n", stream_format_vid.y_pels_per_meter);
	MSG_DBG(2, "                   colors_used: %d\n", stream_format_vid.colors_used);
	MSG_DBG(2, "              colors_important: %d\n", stream_format_vid.colors_important);

	return 0;
}

int ReadAVI::read_stream_format_auds()
{
#ifdef VERBOSE
	long offset = inFile.tellg();
#endif
	stream_format_auds.format = read_word();
	stream_format_auds.channels = read_word();
	stream_format_auds.samples_per_second = read_int();
	stream_format_auds.bytes_per_second = read_int();
	int block_align = read_word();
	stream_format_auds.block_size_of_data = read_word();
	stream_format_auds.bits_per_sample = read_word();
	//stream_format_auds.extended_size=read_word();

	MSG_DBG(2, "            offset=0x%lx\n", offset);
	MSG_DBG(2, "                        format: %d\n", stream_format_auds.format);
	MSG_DBG(2, "                      channels: %d\n", stream_format_auds.channels);
	MSG_DBG(2, "            samples_per_second: %d\n", stream_format_auds.samples_per_second);
	MSG_DBG(2, "              bytes_per_second: %d\n", stream_format_auds.bytes_per_second);
	MSG_DBG(2, "                   block_align: %d\n", block_align);
	MSG_DBG(2, "            block_size_of_data: %d\n", stream_format_auds.block_size_of_data);
	MSG_DBG(2, "               bits_per_sample: %d\n", stream_format_auds.bits_per_sample);

	return 0;
}

int ReadAVI::parse_hdrl_list()
{
	char chunk_id[5];
	int chunk_size;
	char chunk_type[5];
	int end_of_chunk;
	int next_chunk;
#ifdef VERBOSE
	long offset = inFile.tellg();
#endif
	int stream_type = 0;     // 0=video 1=sound

	read_chars(chunk_id, 4);
	chunk_size = read_int();
	read_chars(chunk_type, 4);

	MSG_DBG(2, "      AVI Header LIST (id=%s size=%d type=%s offset=0x%lx)\n", chunk_id, chunk_size, chunk_type, offset);
	MSG_DBG(2, "      {\n");

	end_of_chunk = chunk_size - 4 + inFile.tellg();
	if ((end_of_chunk % 4) != 0) {
		//MSG_DBG(2, "Adjusting end of chunk %d\n", end_of_chunk);
			//end_of_chunk=end_of_chunk+(4-(end_of_chunk%4));
		//MSG_DBG(2, "Adjusting end of chunk %d\n", end_of_chunk);
	}

	if (strcmp(chunk_id, "JUNK") == 0) {
		inFile.seekg(end_of_chunk, ios_base::beg);
		MSG_DBG(2, "      }\n");
		return 0;
	}

	while (inFile.tellg() < end_of_chunk) {
#ifdef VERBOSE
		long offset = inFile.tellg();
#endif
		read_chars(chunk_type, 4);
		chunk_size = read_int();
		next_chunk = chunk_size + inFile.tellg();
		if ((chunk_size % 4) != 0) {
			//MSG_DBG(2, "Chunk size not a multiple of 4?\n");
					//chunk_size=chunk_size+(4-(chunk_size%4));
		}

		MSG_DBG(2, "         %.4s (size=%d offset=0x%lx)\n", chunk_type, chunk_size, offset);
		MSG_DBG(2, "         {\n");

		if (strcmp("strh", chunk_type) == 0)
		{
			long marker = inFile.tellg();
			char buffer[5];
			read_chars(buffer, 4);
			inFile.seekg(marker, ios_base::beg);

			if (strcmp(buffer, "vids") == 0)
			{
				stream_type = 0;
				read_stream_header(&stream_header_vid);
			}
			else if (strcmp(buffer, "auds") == 0)
			{
				stream_type = 1;
				read_stream_header(&stream_header_auds);
			}
			else
			{
				MSG_DBG(2, "Unknown stream type %s\n", buffer);
				return -1;
			}
		}
		else if (strcmp("strf", chunk_type) == 0)
		{
			if (stream_type == 0) {
				read_stream_format();
			}
			else {
				read_stream_format_auds();
			}
		}
		else if (strcmp("strd", chunk_type) == 0)
		{

		}
		else
		{
			MSG_DBG(2, "            Unknown chunk type: %s\n", chunk_type);
			// skip_chunk();
		}

		MSG_DBG(2, "         }\n");

		inFile.seekg(next_chunk, ios_base::beg);
	}

	MSG_DBG(2, "      }\n");
	inFile.seekg(end_of_chunk, ios_base::beg);

	return 0;
}

int ReadAVI::parse_movi(int size)
{
	char chunk_id[5];
	long end_of_chunk;
	index_entry_t index_entry;
	int blk_size;

	do {
		long offset = inFile.tellg();
		/*
		 if (fileSize - offset < 8)
		 break;
		 */
		read_chars(chunk_id, 4);
		index_entry.stream_num = decodeCkid(chunk_id, &index_entry.type);

		if (index_entry.stream_num < 0) {
			inFile.seekg(offset - 4, ios_base::beg);
			break;
		}

		index_entry.dwChunkLength = read_int();

		if (!(avi_header.Flags & AVIF_HASINDEX)) {
			index_entry.dwChunkOffset = offset + 8;
			index_entries.push_back(index_entry);
		}

		MSG_DBG(3, "      AVI Movi Chunk ( id=%s(%d-%d) chunk_size=%d offset=0x%lx)\n", chunk_id, index_entry.type,
			index_entry.stream_num, index_entry.dwChunkLength, offset);
		MSG_DBG(3, "      {\n");

		end_of_chunk = index_entry.dwChunkLength + inFile.tellg();
		end_of_chunk = (end_of_chunk + 1) & ~1;
		/*    if ((end_of_chunk % 4) != 0) {
		 end_of_chunk = end_of_chunk + (4 - (end_of_chunk % 4));
		 }
		 */
		 //    MSG_DBG(2, "end_of_chunk:%d  %X\n", end_of_chunk, end_of_chunk);
		inFile.seekg(end_of_chunk, ios_base::beg);
		MSG_DBG(3, "      }\n");

		blk_size = end_of_chunk - offset;
		size -= blk_size;
		MSG_DBG(3, "size:%d \n", size);

	} while (size > 7);

	return 0;
}

int ReadAVI::parse_hdrl(unsigned int size)
{
	char chunk_id[5];
	int chunk_size;
	int end_of_chunk;
	long offset = inFile.tellg();

	read_chars(chunk_id, 4);
	chunk_size = read_int();

	MSG_DBG(2, "      AVI Header Chunk (id=%s size=%d offset=0x%lx)\n", chunk_id, chunk_size, offset);
	MSG_DBG(2, "      {\n");

	end_of_chunk = chunk_size + inFile.tellg();
	if ((end_of_chunk % 4) != 0) {
		end_of_chunk = end_of_chunk + (4 - (end_of_chunk % 4));
	}

	read_avi_header();
	MSG_DBG(2, "      }\n");

	while (inFile.tellg() < offset + size - 4) {
		//MSG_DBG(2, "Should end at 0x%lx  0x%lx\n",offset+size,inFile.tellg());
		parse_hdrl_list();
	}

	return 0;
}

int ReadAVI::parse_riff()
{
	char chunk_id[5];
	int chunk_size;
	char chunk_type[5];
	int end_of_chunk, end_of_subchunk;

	ZEROIZE(avi_header);
	ZEROIZE(stream_header_vid);
	ZEROIZE(stream_format_vid);
	ZEROIZE(stream_header_auds);
	ZEROIZE(stream_format_auds);
#ifdef VERBOSE
	long offset = inFile.tellg();
#endif
	read_chars(chunk_id, 4);
	chunk_size = read_int();
	read_chars(chunk_type, 4);

	MSG_DBG(2, "RIFF Chunk (id=%s size=%d type=%s offset=0x%lx)\n", chunk_id, chunk_size, chunk_type, offset);
	MSG_DBG(2, "{\n");

	if (strcmp("RIFF", chunk_id) != 0)
	{
		MSG_DBG(2, "Not a RIFF file.\n");
		return 1;
	}
	else if (strcmp("AVI ", chunk_type) != 0)
	{
		MSG_DBG(2, "Not an AVI file.\n");
		return 1;
	}

	end_of_chunk = chunk_size - 4 + inFile.tellg();

	while (inFile.tellg() < end_of_chunk) {
		long offset = inFile.tellg();
		read_chars(chunk_id, 4);
		chunk_size = read_int();
		end_of_subchunk = chunk_size + inFile.tellg();

		if (strcmp("JUNK", chunk_id) == 0 || strcmp("PAD ", chunk_id) == 0) {
			chunk_type[0] = 0;
		}
		else {
			read_chars(chunk_type, 4);
		}

		MSG_DBG(2, "   New Chunk (id=%s size=%d type=%s offset=0x%lx)\n", chunk_id, chunk_size, chunk_type, offset);
		MSG_DBG(2, "   {\n");

		fflush(stdout);

		if (strcmp("JUNK", chunk_id) == 0 || strcmp("PAD ", chunk_id) == 0) {
			if ((chunk_size % 4) != 0) {
				chunk_size = chunk_size + (4 - (chunk_size % 4));
			}
#ifdef VERBOSE
			hex_dump_chunk(chunk_size);
#endif
		}
		else if (strcmp("INFO", chunk_type) == 0) {
			if ((chunk_size % 4) != 0) {
				chunk_size = chunk_size + (4 - (chunk_size % 4));
			}
#ifdef VERBOSE
			hex_dump_chunk(chunk_size);
#endif
		}
		else if (strcmp("hdrl", chunk_type) == 0) {
			parse_hdrl(chunk_size);
			/* skip_chunk(); */
		}
		else if (strcmp("movi", chunk_type) == 0) {
			movi_offset = offset;
			parse_movi(chunk_size);
		}
		else if (strcmp("idx1", chunk_id) == 0) {
			inFile.seekg(inFile.tellg() - std::streamoff(4), ios_base::beg);
			parse_idx1(chunk_size);
		}/* else if (strcmp("indx", chunk_id) == 0) {
		 inFile.seekg(inFile.tellg() - 4L, ios_base::beg);
		 parse_indx(chunk_size);
		 }*/else {
			MSG_DBG(2, "      Unknown chunk at %d (%4s)\n", (int)inFile.tellg() - 8, chunk_type);
			if (chunk_size == 0)
				break;
		}

		inFile.seekg(end_of_subchunk, ios_base::beg);
		MSG_DBG(2, "   }\n");

	}

	if (stream_format_vid.palette) {
		delete[] stream_format_vid.palette;
		stream_format_vid.palette = NULL;
	}

	MSG_DBG(2, "}\n");

	return 0;
}

int ReadAVI::read_int()
{
	int c;
	unsigned char buf[4];

	inFile.read((char*)buf, 4);
	c = buf[0];
	c = c + (buf[1] << 8);
	c = c + (buf[2] << 16);
	c = c + (buf[3] << 24);

	return c;
}

int ReadAVI::read_word()
{
	int c;
	unsigned char buf[2];

	inFile.read((char*)buf, 2);
	c = buf[0];
	c = c + (buf[1] << 8);

	return c;
}

void ReadAVI::read_chars(char* s, int count)
{
	inFile.read(s, count);
	s[count] = 0;
}

void ReadAVI::read_chars_bin(unsigned char* s, int count)
{
	inFile.read((char*)s, count);
}
