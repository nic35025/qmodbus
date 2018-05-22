/*
 * main.cpp - main file for QModBus
 *
 * Copyright (c) 2009-2014 Tobias Junghans / Electronic Design Chemnitz
 *
 * This file is part of QModBus - http://qmodbus.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */
#include <QDebug>


static const unsigned char aucCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};

static const unsigned char aucCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};

unsigned short usMMCRC16_o( unsigned char * pucData, unsigned short usLen )
{
    unsigned char ucCRCHi = 0xFF;
    unsigned char ucCRCLo = 0xFF;
    unsigned short iIndex;

    while( usLen-- )
    {
        iIndex = ucCRCLo ^ *( pucData++ );
        ucCRCLo = ( unsigned char )( ucCRCHi ^ aucCRCHi[iIndex] );
        ucCRCHi = aucCRCLo[iIndex];
    }
    return ( unsigned short )( ucCRCHi << 8 | ucCRCLo );
}

static const unsigned short aucCRC[] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241, 0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40, 0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40, 0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641, 0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240, 0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41, 0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41, 0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640, 0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240, 0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41, 0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41, 0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640, 0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241, 0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40, 0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40, 0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641, 0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

unsigned short pgm_read_word( const void *ptr )
{
    return *(unsigned short *)ptr;
}

unsigned short usMMCRC16_n( unsigned char *pucData, unsigned short usLen )
{
    unsigned char ucCRCHi = 0xFF;
    unsigned char ucCRCLo = 0xFF;
    unsigned char iIndex;
    unsigned short crc;

    while( usLen-- )
    {
        iIndex = ucCRCLo ^ *( pucData++ );
//        crc = pgm_read_word( &(aucCRC[iIndex]) );
        crc = aucCRC[iIndex];
        ucCRCLo = ( unsigned char )( ucCRCHi ^ (crc & 0xFF) );
        ucCRCHi = crc >> 8;
    }
    return ( unsigned short )( ucCRCHi << 8 | ucCRCLo );
}

void *memchr_P( const void *_Buf, int _Val, size_t _MaxCount )
{
    return memchr(_Buf, _Val, _MaxCount );
}

uint8_t pgm_read_byte( const void *_ptr ) {
    return *(uint8_t *)_ptr;
}

#define g________ 0x00
#define g_______O 0x01
#define g______O_ 0x02
#define g______OO 0x03
#define g_____O__ 0x04
#define g_____O_O 0x05
#define g_____OO_ 0x06
#define g_____OOO 0x07
#define g____O___ 0x08
#define g____O__O 0x09
#define g____O_O_ 0x0A
#define g____O_OO 0x0B
#define g____OO__ 0x0C
#define g____OO_O 0x0D
#define g____OOO_ 0x0E
#define g____OOOO 0x0F
#define g___O____ 0x10
#define g___O___O 0x11
#define g___O__O_ 0x12
#define g___O__OO 0x13
#define g___O_O__ 0x14
#define g___O_O_O 0x15
#define g___O_OO_ 0x16
#define g___O_OOO 0x17
#define g___OO___ 0x18
#define g___OO__O 0x19
#define g___OO_O_ 0x1A
#define g___OO_OO 0x1B
#define g___OOO__ 0x1C
#define g___OOO_O 0x1D
#define g___OOOO_ 0x1E
#define g___OOOOO 0x1F

#define PROGMEM
#define HD44780_LINES    4
#define HD44780_COLS    16
#define LCD_LINES       HD44780_LINES
#define LCD_CHARS       HD44780_COLS

static struct {
    char frame[HD44780_LINES][HD44780_COLS+1];
    int pointer;
} state;

void hd44780_get_frame(char (**frame)[HD44780_COLS+1])
{
    *frame = state.frame;
}

void _delay_ms(int) {}

int hd44780_write_command( uint8_t cmd )
{
    qDebug("HD_cmd=%02X", cmd );
    return 0;
}

int hd44780_write_data( uint8_t data )
{
    qDebug("HD_data=%02X", data );
    return 0;
}

static void encode_lines(void)
{
    // ISO8859-2 - code polish national chars
    static const unsigned char PROGMEM charPL[] = {
            0xA1 /* A, z ogonkiem	*/	, 0xB1 /* a, z ogonkiem */,
            0xC6 /* C' */				, 0xE6 /* c' */,
            0xCA /* E' */				, 0xEA /* e, */,
            0xA3 /* L/ duze L z krecha*/, 0xB3 /* l/ */,
            0xD1 /* N' */				, 0xF1 /* n' */,
            0xD3 /* O' */				, 0xF3 /* o' */,
            0xA6 /* S' */               , 0xB6 /* s' */,
            0xAC /* Z' */               , 0xBC /* z' */,
            0xAF /* Z- */				, 0xBF /* z- */,
    };

    static const unsigned char PROGMEM defPL[] = {
            'A', 'a', 'C', 'c', 'E', 'e', 'L', 'l', 'N', 'n', 'O', 'o', 'S', 's', 'Z', 'z', 'Z', 'z'
    };

    static const unsigned char PROGMEM grafPL[][8] = {
           { // A,
            g____OOO_,
            g___O___O,
            g___O___O,
            g___O___O,
            g___OOOOO,
            g___O___O,
            g___O___O,
            g______O_,
        }, { // a,
            g________,
            g____OOO_,
            g_______O,
            g____OOOO,
            g___O___O,
            g____OOOO,
            g______O_,
            g_______O,
        }, { // C' acute
            g______O_,
            g____OOO_,
            g___O_O_O,
            g___O____,
            g___O____,
            g___O___O,
            g____OOO_,
            g________,
        }, { // c'
            g______O_,
            g_____O__,
            g____OOO_,
            g___O____,
            g___O____,
            g___O___O,
            g____OOO_,
            g________,
        }, { // E ogonek
            g___OOOOO,
            g___O____,
            g___O____,
            g___OOO__,
            g___O____,
            g___O____,
            g___OOOOO,
            g______O_,
        }, { // e,
            g________,
            g____OOO_,
            g___O___O,
            g___OOOOO,
            g___O____,
            g____OOO_,
            g______O_,
            g_______O,
        }, { // L stroke
            g___O____,
            g___O____,
            g___O_O__,
            g___OO___,
            g___O____,
            g___O____,
            g___OOOOO,
            g________,
        }, { // l/
            g____OO__,
            g_____OO_,
            g_____O__,
            g____OO__,
            g___O_O__,
            g_____O__,
            g____OOO_,
            g________,
        }, { // N acute
            g______O_,
            g___O_O_O,
            g___OO__O,
            g___O_O_O,
            g___O__OO,
            g___O___O,
            g___O___O,
            g________,
        }, { // n'
            g______O_,
            g_____O__,
            g___O_OO_,
            g___OO__O,
            g___O___O,
            g___O___O,
            g___O___O,
            g________,
        }, { // O acute
            g_______O,
            g____OOO_,
            g___O_O_O,
            g___O___O,
            g___O___O,
            g___O___O,
            g____OOO_,
            g________,
        }, {
            g______O_,
            g_____O__,
            g____OOO_,
            g___O___O,
            g___O___O,
            g___O___O,
            g____OOO_,
            g________,
        },{ // S acute
            g_______O,
            g____OOO_,
            g___O_O__,
            g____OOO_,
            g_______O,
            g_______O,
            g___OOOO_,
            g________,
        }, {
            g______O_,
            g_____O__,
            g____OOO_,
            g___O____,
            g____OOO_,
            g_______O,
            g___OOOO_,
            g________,
        }, {
            // Z got
            g_____O__,
            g___OOOOO,
            g_______O,
            g______O_,
            g_____O__,
            g____O___,
            g___OOOOO,
            g________,
        }, {
            g________,
            g_____O__,
            g___OOOOO,
            g______O_,
            g_____O__,
            g____O___,
            g___OOOOO,
            g________,
        }, {
            // Z acute
            g_____O__,
            g___OOOOO,
            g____O__O,
            g______O_,
            g_____O__,
            g____O___,
            g___OOOOO,
            g________,
        }, { // z acute
            g______O_,
            g_____O__,
            g___OOOOO,
            g______O_,
            g_____O__,
            g____O___,
            g___OOOOO,
            g________,
        }
    };

    uint8_t cache[8];
    uint8_t cache_no =0;
    uint8_t ch;
    uint8_t chN;

    char *line;
    uint8_t *ptr;

    hd44780_get_frame( (char (**)[17])&line );
    for (uint8_t i =0; i < LCD_LINES*(LCD_CHARS+1); i++, line++) {
        ch = *line;
        ptr =(uint8_t *)memchr_P( charPL, ch, sizeof(charPL));
        if ( ptr == NULL ) continue; // it is no polish character
        chN = ptr -charPL;
        ptr =(uint8_t *)memchr( cache, ch, cache_no );
        if ( ptr != NULL ) {
            // exist in cache
            *line = ptr -cache;
            continue;
        }
        if ( cache_no == sizeof(cache) ) {
            // convert na similar polish character
            *line =  pgm_read_byte( &(defPL[chN]) );
            continue;
        }
        // define char in select place
        _delay_ms(2);
        while( hd44780_write_command( 0x40 | cache_no) );
        for ( uint8_t i =0; i < 8; i++)
            while( hd44780_write_data( pgm_read_byte( &(grafPL[chN][i]) ) ) );
        cache[cache_no] =ch;
        *line = cache_no;
        cache_no++;
    }
}




#include <QDateTime>
void Test(void)
{
#if 1
    strcpy( state.frame[0], "Romek Szyli\xF1ski " );
    encode_lines();
#endif
#if 0
    unsigned short crc[2];
    QDateTime dttm,dttm1;

    qDebug("***START***1");
    dttm = QDateTime::currentDateTime();
    for( int i = 0; i < 1<<20; i++ ) {
        crc[0] = usMMCRC16_o( (unsigned char *)&i, 4 );
    }
    dttm1 = QDateTime::currentDateTime();
    qDebug("***STOP***1 =tm=%d", dttm.msecsTo(dttm1) );

    qDebug("***START***2");
    dttm = QDateTime::currentDateTime();
    for( int i = 0; i < 1<<20; i++ ) {
        crc[1] = usMMCRC16_n( (unsigned char *)&i, 4 );
    }
    dttm1 = QDateTime::currentDateTime();
    qDebug("***STOP***2 =tm=%d", dttm.msecsTo(dttm1) );
#endif
}

#include <QApplication>
#include "mainwindow.h"
MainWindow * globalMainWin = NULL;

int main(int argc, char *argv[])
{
    Test();
	QApplication a(argc, argv);

	QApplication::setOrganizationName( "EDC Electronic Design Chemnitz GmbH" );
	QApplication::setOrganizationDomain( "ed-chemnitz.de" );
	QApplication::setApplicationName( "QModBus" );

	MainWindow w;
	w.show();

	globalMainWin = &w;

	return a.exec();
}
