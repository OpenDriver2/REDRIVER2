/*
    RNC2 source
    Tyler Gorton, 2011
    Adapted from copywritten Intel Assembler Source

    Not for commercial use
*/

#include "../THISDUST.H"
#include "../C/SYSTEM.H"
#include "STRINGS.H"

struct RNCheader
{
    unsigned long identifier;    //must contain 'R', 'N', 'C', method
    unsigned long unpackSize;     //unpacked data size
    unsigned long packSize;      //packed data size (excludes this header)
    unsigned short unpackChecksum;  //unpacked data checksum
    unsigned short packChecksum;   //packed data checksum
    unsigned char leeway;         //not used
    unsigned char blocks;    //number of sections
    //unsigned char start;		//first byte of data
};

#define RNC_HEADER_LENGTH	18

//encryption key
/*
    byte ^= key; key = _rotr(key, 1);
*/

/*____________________________________________________________________________*/
short testRNC(unsigned long firstLong)
{
    int method = 0;
    method = (firstLong & 0xFF000000) >> 24;      //get low byte
    firstLong &= 0x00FFFFFF;        //mask off low byte
    if (firstLong != 0x00434E52)    //test for 'R','N','C'
        method = -1;				//error return value
    return method;
}

/*____________________________________________________________________________*/
unsigned char get_byte(unsigned char** byteStreamPtr) //modifies data source ptr
{
    return *(*byteStreamPtr)++;
}

unsigned short get_word(unsigned char** byteStreamPtr) //modifies data source ptr
{
    return get_byte(byteStreamPtr) | get_byte(byteStreamPtr) << 8;
}

//modifies only data destination ptr
void mem_move(unsigned char** put, unsigned char* start, int count)
{
    unsigned char* get = start;
    while (count--) 
        *(*put)++ = *get++;
}

/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
// RNC 2 huffman code tools

/* 8 bit left going stream
 * count is zero to initialze
 */
unsigned short get_bits2(unsigned char** byteStreamPtr, unsigned short count)
{
    static unsigned char bitStream = 0;
    unsigned short nextBit = 0;
    unsigned short theBits = 0;

    if (!count)
        bitStream = 0;	//flush stream on zero

    while (count--) {
        if (bitStream & 0x80)
            nextBit = 1;
        else
            nextBit = 0;

        bitStream <<= 1;//shift
        if (!bitStream) {
            bitStream = get_byte(byteStreamPtr);//fetch new byte
            if (bitStream & 0x80)//get first bit
                nextBit = 1;
            else
                nextBit = 0;
            bitStream <<= 1;//shift
            bitStream |= 1;//set sentinel
        }
        theBits = (theBits << 1) + nextBit;
    }
    return theBits;
}

unsigned short get_offset(unsigned char** byteStreamPtr)
{
    unsigned short value = 0;
    if (get_bits2(byteStreamPtr, 1)) {
        value = get_bits2(byteStreamPtr, 1);
        if (get_bits2(byteStreamPtr, 1)) {
            value = value * 2 + 4 + get_bits2(byteStreamPtr, 1);
            if (!get_bits2(byteStreamPtr, 1))
                value = value * 2 + get_bits2(byteStreamPtr, 1);
        }
        else if (value == 0)
            value = get_bits2(byteStreamPtr, 1) + 2;
    }
    return (value << 8) + get_byte(byteStreamPtr) + 1;
}

/*____________________________________________________________________________*/
//RNC2 unpack

int RNCunpack2(unsigned char* packed, unsigned long srcSize,
    unsigned char* unpacked, unsigned long dstSize)
{
    unsigned char* src = packed;
    unsigned char* dst = unpacked;
    unsigned char* srcEnd = src + srcSize;
    unsigned char* dstEnd = dst + dstSize;
    unsigned short length, offset, index;
    unsigned short end = 0;

    get_bits2(&src, 0); //resets bit stream
    get_bits2(&src, 2); //toss first two bits

    while (!end && dst < dstEnd && src < srcEnd) {
        if (!get_bits2(&src, 1)) {
            *dst++ = get_byte(&src); //pack bits
        }
        else {
            length = 2;
            if (!get_bits2(&src, 1)) {
                length = 4 + get_bits2(&src, 1); //pack length
                if (get_bits2(&src, 1)) {
                    length = (length - 1) * 2 + get_bits2(&src, 1);
                    if (length == 9) {
                        length = (get_bits2(&src, 4) + 3) * 4;
                        for (index = 0; index < length; index++)
                            *dst++ = get_byte(&src);
                        continue;
                    }
                }
                offset = get_offset(&src);
            }
            else {
                if (get_bits2(&src, 1)) {
                    if (get_bits2(&src, 1)) {
                        length = get_byte(&src) + 8;
                        if (length == 8) {
                            if (!get_bits2(&src, 1))
                                end = 1;
                            continue; //restart if length was zero
                        }
                    }
                    else {
                        length = 3;
                    }
                    offset = get_offset(&src);
                }
                else {
                    offset = get_byte(&src) + 1;
                }
            }//end secondary else

            mem_move(&dst, dst - offset, length);

        }//end primary else
    }//end while

    if (src > srcEnd || dst > dstEnd)
        return 1;
    else
        return 0;
}//end unpack2

//--------------------------------------------------

// RNC decoding routine
void UnpackRNC(char* src, char* dest)
{
    RNCheader* hdr = (RNCheader*)src;

    int method = testRNC(hdr->identifier);

    if (method == 2)
        RNCunpack2((unsigned char*)src + RNC_HEADER_LENGTH, hdr->packSize, (unsigned char*)dest, hdr->unpackSize);
    else
        printError("UnpackRNC error - unsupported method %d\n", method);
}