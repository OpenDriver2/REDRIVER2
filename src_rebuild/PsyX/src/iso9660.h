#ifndef ISO9660_H
#define ISO9660_H

/*
 * Sub-header info
 *
 +----------------------+--------------------------------------------------+
 |            | Interleaved file (1 byte)
 |            |   1 if this file is interleaved, or 0 if not
 | byte 1     |
 +--        --+------------------------------------------------------------+
 |            | Channel number (1 byte)
 |            |   The sub-channel in this 'file'. Video, audio and data
 |            |   sectors can be mixed into the same channel or can be
 |            |   on separate channels. Usually used for multiple audio
 |            |   tracks (e.g. 5 different songs in the same 'file', on
 |            |   channels 0, 1, 2, 3 and 4)
 | byte 2     |
 +--        --+------------------------------------------------------------+
 |            | Submode (1 byte)
 |            |   bit 7: eof_marker -- set if this sector is the end
 |            |                        of the 'file'
 |            |   bit 6: real_time  -- always set in PSX STR streams
 |            |   bit 5: form       -- 0 = Form 1 (2048 user data bytes)
 |            |                        1 = Form 2 (2324 user data bytes)
 |            |   bit 4: trigger    -- for use by reader application
 |            |                        (unimportant)
 |            |   bit 3: DATA       -- set to indicate DATA  sector
 |            |   bit 2: AUDIO      -- set to indicate AUDIO sector
 |            |   bit 1: VIDEO      -- set to indicate VIDEO sector
 |            |   bit 0: end_audio  -- end of audio frame
 |            |                        (rarely set in PSX STR streams)
 |            |
 |            |   bits 1, 2 and 3 are mutually exclusive
 | byte 3     |
 +--        --+------------------------------------------------------------+
 |            | Coding info (1 byte)
 |            | If Submode.AUDIO bit is set:
 |            |   bit 7: reserved -- should always be 0
 |            |   bit 6: emphasis -- boost audio volume (ignored by us)
 |            |   bit 5: bitssamp -- must always be 0
 |            |   bit 4: bitssamp -- 0 for mode B/C
 |            |                        (4 bits/sample, 8 sound sectors)
 |            |                      1 for mode A
 |            |                        (8 bits/sample, 4 sound sectors)
 |            |   bit 3: samprate -- must always be 0
 |            |   bit 2: samprate -- 0 for 37.8kHz playback
 |            |                      1 for 18.9kHz playback
 |            |   bit 1: stereo   -- must always be 0
 |            |   bit 0: stereo   -- 0 for mono sound, 1 for stereo sound
 |            |
 |            | If Submode.AUDIO bit is NOT set, this byte can be ignored
 | byte 4     |
 +--        --+------------------------------------------------------------+
 | byte 5-8   | Duplicated
*/

#define CD_ROOT_DIRECTORY_SECTOR	22
#define CD_SECTOR_SIZE				2048
#define CD_SECTOR_SIZE_MODE2		2352		// MODE2/2352

#pragma pack(push, 1)
typedef struct
{
	u_char tocEntryLength;
	u_char extEntryLength;
	u_int sectorPosition[2];
	u_int fileSize[2];
	u_char date[7];
	u_char flags;
	u_char fileUnitSize;
	u_char interleaveGapSize;
	u_short volSeqNum[2];
	u_char nameLength;
} TOC;

typedef struct
{
	u_char	sync[12];	/// Sync pattern (usually 00 FF FF FF FF FF FF FF FF FF FF 00)
	u_char	addr[3];	/// Sector address (see below for encoding details)
	u_char	mode;		/// Mode (usually 2 for Mode 2 Form 1/2 sectors)
	u_char	subHead[8];	/// Sub-header (00 00 08 00 00 00 08 00 for Form 1 data sectors). See below for more
	u_char	data[2048];	/// Data (form 1)
	u_char	edc[4];		/// Error-detection code (CRC32 of data area)
	u_char	ecc[276];	/// Error-correction code (uses Reed-Solomon ECC algorithm)
} Sector;

typedef struct
{
	u_char	sync[12];	/// Sync pattern (usually 00 FF FF FF FF FF FF FF FF FF FF 00)
	u_char	addr[3];	/// Sector address (a 24-bit big-endian integer. starts at 200, 201 an onwards)
	u_char	mode;		/// Mode (usually 2 for Mode 2 Form 1/2 sectors)
	u_char	data[2336];	/// 8 bytes Subheader, 2324 bytes Data (form 2), and 4 bytes ECC
} AudioSector;
#pragma pack(pop)

#endif