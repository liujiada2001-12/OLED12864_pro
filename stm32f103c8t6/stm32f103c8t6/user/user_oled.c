#include "tsl2561.h"
#include "stdint.h"
#include "oled.h"
#include "rtc.h"
#include "user_oled.h"
#include "gpio.h"
#include "bmp.h"
//
uint8_t myBMP[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFC,0xFC,0xF8,
0xF0,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,0xE0,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x3F,0x3F,0x1F,0x1F,0x3F,
0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xFC,0xF8,0xF0,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xC0,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x27,0x60,0x60,0x40,0xC0,0x80,0x00,0x00,0x80,0xC0,0xC0,0x60,0x20,0x20,0x20,
0x20,0x2F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x07,0x1F,0x3F,0x3F,0xFF,0x7F,0x3F,0xFF,0xDF,0x0F,0x07,0x1F,0x1F,0x1D,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFE,0xFE,0x03,0x00,0x1C,0x3C,0x18,0x00,0x00,
0x00,0x00,0x03,0x0F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xF0,0xF8,0xF8,0xF3,0xE6,0xCC,0x08,0x18,0x30,0xF0,0x70,0xB8,0x98,0x18,0x0C,0x0F,0x0D,0x0D,0x0F,0x0C,0x9C,0xB8,0xB0,0xF0,0x30,
0x30,0x30,0x38,0x18,0x8C,0xE6,0xE3,0xF1,0xF1,0xF1,0xF1,0xF3,0xE3,0x83,0x03,0x03,0x07,0x87,0xFF,0x1F,0x1F,0x1F,0x0F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x1F,0x37,0x6F,0xCF,0x8F,0x07,0x01,0x00,0x00,0x01,0x06,0x0C,0x09,0x19,0x19,0x13,0x13,0x13,0x11,0x19,0x09,0x0D,0x04,0x03,0x01,
0x00,0x00,0x00,0x00,0x03,0x0F,0x1F,0x3F,0x3F,0x3F,0x3F,0x1F,0x0F,0x87,0xC0,0xF0,0xFC,0x3F,0x33,0xE2,0x62,0xD2,0x9A,0xCC,0xC4,0xC8,0xD8,0xB0,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x9F,0xFF,0xFE,0xFC,0xF8,0xF0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFC,0xF8,0xF8,0xF8,0xF8,
0xF8,0xF8,0xF8,0xF8,0xF8,0x78,0x78,0xB8,0xB8,0x78,0x3C,0xFC,0xFE,0xF3,0xE1,0xC0,0xF8,0x0E,0x03,0x01,0xFC,0x87,0x01,0x03,0x06,0x18,0xF1,0x81,0x03,0xC7,0x30,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFC,0xFF,0xFF,0xFF,0xFF,0xF8,0x81,0x87,0xFF,0xFF,0xF7,0xCF,0xBF,0xFF,0xFF,0xFF,0xBF,0xFF,0xDF,0xFF,0xEF,0xFF,0xF3,0xFF,
0xFB,0xF9,0xFD,0xFE,0xFE,0xFF,0xFF,0x87,0x81,0xC0,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x80,0x80,0x80,0xFF,0xF8,0x80,0x40,0x40,0x3D,0x1F,0x0C,0x03,0x00,0x00,/*"D:\32_PROJECT\2.bmp",0*/
};
//
 uint8_t  myBMP1[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x80,0x80,0xC0,0xC0,0xE0,0x60,
0x60,0x70,0x30,0x70,0x70,0x60,0x60,0x60,
0x60,0xE0,0x70,0x38,0x1C,0x0C,0x0C,0x0C,
0x0C,0x0C,0x1C,0x18,0x18,0x38,0x30,0x70,
0x60,0xC0,0xC0,0x80,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,
0xE0,0x70,0x38,0x38,0x1C,0x0E,0x06,0x07,
0x03,0x03,0x01,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0xFC,
0xFC,0xEC,0xF0,0xF8,0xFC,0xFC,0xFC,0xF8,
0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,
0x80,0x81,0x83,0x03,0x07,0x0E,0x1C,0x38,
0x70,0xE0,0xC0,0x80,0x00,0x00,0x80,0xC0,
0xF0,0x78,0x3C,0x0E,0x07,0x03,0x01,0x00,
0x00,0x00,0xF0,0xF8,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xF8,0xFF,0xFF,0x33,0x31,
0x31,0x30,0x60,0x60,0xC0,0x80,0x00,0x00,
0x00,0x80,0xC3,0xE7,0x7F,0xFE,0xF8,0x81,
0x03,0x07,0x1E,0x7C,0xF0,0xC0,0x00,0x00,
0x00,0x01,0x0F,0x0F,0x00,0x0F,0x1F,0x31,
0xF8,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,
0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,0x00,
0x00,0xF0,0xF0,0x80,0xC0,0xC0,0xF8,0xF8,
0x70,0x70,0x7F,0x7F,0x7F,0x00,0x00,0x10,
0x78,0x78,0x78,0x78,0x03,0xFF,0xFE,0xFF,
0x03,0x01,0x00,0x00,0x03,0x07,0x07,0x7E,
0x7E,0xFE,0x7E,0x3F,0xCF,0xFF,0xFC,0xF0,
0xC0,0x80,0x00,0x00,0x80,0x80,0xC0,0xC7,
0xDF,0xDC,0xD8,0xFC,0xFC,0xFE,0x0E,0x0F,
0xFF,0xFE,0xF0,0xF0,0xF0,0x70,0x78,0x7F,
0x7F,0x3F,0x3F,0x39,0x01,0x01,0x03,0x07,
0x06,0x0C,0x1C,0x18,0x18,0x98,0xF8,0x78,
0x38,0x1C,0x0E,0x0F,0x0F,0x0D,0x0F,0x0F,
0x0E,0x0C,0x1C,0xB8,0xF8,0xF8,0x18,0x08,
0x0C,0x86,0x63,0x31,0x18,0x18,0x01,0x0F,
0xFF,0xF9,0x00,0x19,0x19,0x39,0x38,0x38,
0x39,0x19,0x18,0x1F,0xBF,0xFC,0xF0,0xE1,
0xC6,0x8C,0x88,0x9C,0x9C,0x94,0x9C,0x98,
0xD8,0xCC,0xC7,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC3,0xC7,0x8F,0x9F,
0x9E,0xB6,0xB6,0xA6,0x26,0x26,0x26,0x36,
0x37,0x13,0x1B,0x0F,0x07,0x00,0x00,0x00,
0x83,0x8E,0xD0,0xE0,0xF0,0xB8,0x1F,0x0F,
0x01,0x00,0x06,0x06,0x0E,0x0E,0x0C,0x1C,
0x1C,0x18,0x18,0xFF,0x7F,0x3F,0x3F,0x3F,
0x3F,0x3F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,0x7F,
0x7F,0x7F,0x3F,0x3F,0x3F,0xFF,0xDF,0x04,
0x00,0x0E,0x0C,0x0C,0x08,0x08,0x00,0x08,
0x08,0x08,0x09,0x0F,0x0F,0x0F,0x0F,0x0E,
0x0E,0x0E,0x0E,0x0C,0x08,0x08,0x00,0x01,
0x07,0x0F,0x0B,0x0B,0x0B,0x07,0x07,0x07,
0x07,0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
0x07,0x07,0x07,0x07,0x07,0x0B,0x0B,0x0B,
0x0B,0x0D,0x07,0x03,0x01,0x08,0x08,0x0C,
0x0C,0x0E,0x0E,0x0F,0x0F,0x09,0x00,0x00,/*"D:\32_PROJECT\1.bmp",0*/
};

//
 uint8_t  xiaohui[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0xC0,0xC0,0x60,0x70,
0x30,0x98,0x98,0xEC,0xCC,0xCE,0x06,0x06,
0x26,0xA3,0xFB,0xB3,0xFF,0xA3,0x83,0x83,
0x03,0x23,0xE3,0xFB,0x6B,0xFB,0x4B,0x06,
0x06,0x06,0xCC,0x8C,0xEC,0x98,0x58,0x30,
0x70,0x60,0xC0,0xC0,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0xC0,0xF0,0x38,
0x1C,0x0E,0x07,0xA3,0xE9,0xD0,0xF8,0x60,
0x60,0x81,0xCD,0xE7,0x6F,0x3E,0x12,0x1A,
0x18,0x0D,0x0F,0x0D,0x07,0x04,0x84,0xE4,
0xC4,0x04,0x04,0x05,0x0C,0x0F,0x08,0x18,
0x18,0x3F,0x37,0x67,0xFF,0xD9,0x81,0x20,
0x20,0xA8,0xF0,0x31,0x7B,0x0F,0x0E,0x1C,
0x38,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,
0x00,0xC0,0xF8,0x3E,0x07,0x01,0x1C,0x5E,
0x78,0x7E,0x7E,0x8C,0xE0,0xFB,0x3D,0x0E,
0x07,0x01,0x00,0x00,0x00,0x00,0xE0,0xF0,
0xD8,0x84,0x00,0x00,0x00,0x3E,0xFF,0xFF,
0xFF,0xFF,0x3C,0x00,0x00,0x00,0x84,0xF8,
0xF0,0xE0,0x00,0x00,0x00,0x01,0x03,0x07,
0x0E,0x3D,0xFB,0xE0,0xB8,0x24,0x3E,0x7E,
0x5C,0x7E,0x3F,0x17,0x3E,0xF8,0xC0,0x00,
0xFE,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0xC0,0xFE,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xF7,
0xCF,0x9F,0x1F,0x3F,0x7E,0xFE,0xFC,0x01,
0x31,0xFC,0xFE,0x3E,0x3F,0x9F,0x8F,0xCF,
0xF7,0xFD,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0xFF,0xFF,0xFC,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFC,
0x7F,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x07,0x7F,0xFF,0xFF,0xE0,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xE1,0xF7,
0xDF,0x9F,0x1F,0x3F,0x7F,0xFD,0xFC,0x30,
0x70,0xFC,0xFF,0x3E,0x3F,0x1F,0x8F,0xFF,
0xF3,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0xF0,0xFF,0xFF,0x7F,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x3F,
0x00,0x03,0x1F,0x7C,0xE0,0x80,0x04,0x1C,
0x7E,0x58,0xF0,0xC3,0x8F,0x1F,0x3F,0x7E,
0xFC,0xF0,0xE0,0xE0,0xC0,0x80,0x83,0x07,
0x0F,0x1F,0x3F,0x3E,0x7F,0xFD,0xF8,0xF0,
0xF0,0xF8,0xFD,0x7E,0x3E,0x3F,0x1F,0x0F,
0x07,0x83,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,
0x7E,0x3F,0x1F,0x87,0xC1,0xF0,0xAA,0x6E,
0x08,0x00,0xC0,0xF0,0x7C,0x0F,0x03,0x00,
0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x1C,
0x38,0x71,0xE3,0xC9,0x8D,0x1B,0x2E,0x1C,
0x78,0xF1,0x63,0xE7,0xCF,0xCF,0x9F,0x9F,
0x1F,0x0E,0x0E,0x06,0x7E,0x53,0x79,0x70,
0x59,0x7B,0x33,0x7E,0x0E,0x0E,0x0E,0x9F,
0x9F,0x9F,0xCF,0xC7,0xE7,0x63,0xF1,0x38,
0x3C,0x3E,0x1E,0x8D,0xC3,0xE3,0x70,0x38,
0x1E,0x07,0x03,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x01,0x03,0x06,0x0E,
0x0C,0x1C,0x19,0x39,0x33,0x33,0x63,0x63,
0x67,0x67,0xC1,0xC0,0xCC,0xC7,0xCE,0xCE,
0xCE,0xCC,0xCF,0xC7,0xC0,0xC0,0x63,0x66,
0x67,0x63,0x33,0x31,0x19,0x19,0x1C,0x0C,
0x06,0x07,0x03,0x01,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"D:\32_PROJECT\校徽.bmp",0*/
};

//
 uint8_t  yuanhui[] =
{
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x7F,0x7F,0x3F,0x3F,0x9F,0x9F,
0xDF,0xDF,0xCF,0xCF,0xCF,0xCF,0xCF,0xEF,
0xEF,0xEF,0xEF,0xEF,0xCF,0x0F,0x0F,0x1F,
0x9F,0x1F,0x9F,0x3F,0x3F,0x7F,0x7F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x7F,0x3F,0x0F,0xC7,0xE7,0xE3,0xF9,
0x68,0x3C,0x38,0x13,0x8F,0xCD,0xC7,0xE3,
0x63,0x63,0x73,0x31,0x31,0x31,0x31,0xB1,
0xF9,0x39,0x31,0xF9,0xFC,0xFE,0xFF,0x63,
0x63,0xE7,0xC7,0xCF,0x8F,0x1F,0x1E,0x34,
0x79,0xF1,0xF3,0xE7,0xCF,0x1F,0x3F,0x7F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x0F,0xC3,
0xC0,0xBC,0xBE,0x3B,0x1F,0x86,0xE1,0xF0,
0x38,0x1C,0x06,0x03,0x03,0x01,0x00,0x80,
0xC0,0xE0,0xF0,0xF8,0x04,0xFE,0xFF,0xFF,
0xFF,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,
0x00,0x00,0x00,0x01,0x03,0x07,0x0E,0x1C,
0x38,0xF1,0xE3,0x83,0x0F,0x1F,0xDE,0xCC,
0x40,0x03,0x0F,0x3F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x01,0x00,0xFC,0xFF,
0xFF,0xCF,0x01,0xE0,0xFE,0x3F,0x03,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC1,
0xFF,0xFF,0xFF,0xFF,0x38,0xFF,0xFF,0xFF,
0xFF,0x1E,0x0E,0xFF,0xFF,0xFF,0xFF,0xEE,
0xFE,0xFE,0x7C,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0x7F,0xFC,0x80,0x00,0x16,
0xFE,0xFE,0xFE,0x00,0x03,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x3F,0xFF,
0xFF,0xFE,0x80,0x0F,0xFF,0xF8,0x80,0x00,
0x00,0x00,0x00,0x38,0x7E,0xFF,0xFF,0xE3,
0xFF,0xFF,0xFF,0xFF,0x86,0xFF,0xFF,0xFF,
0xFF,0xCF,0xC7,0xFF,0xFF,0xFF,0xFF,0xF1,
0xF1,0x70,0x70,0x30,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0xFC,0xFF,0x07,0x00,0x7E,
0xFF,0xFF,0x3F,0x00,0x00,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xC0,0x30,
0x78,0xF8,0xFC,0x7C,0x7C,0x33,0x8F,0xDC,
0x78,0xE0,0xC0,0x80,0x00,0x00,0x01,0xC1,
0xDF,0xDF,0xDF,0xDF,0xC3,0xDF,0xDF,0xDF,
0xDF,0xC1,0xC1,0xDF,0xDF,0xDF,0xDF,0xC0,
0xC0,0x00,0x00,0x00,0x00,0x80,0xC0,0x60,
0xB8,0x9E,0xAF,0x7B,0x7C,0xEE,0xFC,0xF8,
0x70,0xB8,0xC0,0xF8,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFE,0xFD,0xF1,0xEC,0xCF,0xBF,0xBF,0x1F,
0x0E,0x67,0x73,0xFB,0xFF,0xF7,0x36,0x8D,
0xCD,0xD9,0xF9,0xD9,0xD1,0x31,0x31,0x31,
0xB1,0xF0,0xF1,0x31,0xD0,0xD9,0xD9,0xF9,
0x2D,0x0E,0x76,0xFF,0xFF,0x7D,0xF0,0xCF,
0xCF,0x13,0x8F,0x9E,0xDA,0xE0,0xF1,0xFD,
0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFE,0xFC,0xFC,0xFB,0xF9,0xF0,0xF0,0xF3,
0xEF,0xEF,0xEB,0xFF,0xE0,0xE0,0xC2,0xDF,
0xDF,0xC7,0xC3,0xE0,0xE0,0xEC,0xE7,0xE7,
0xF4,0xF6,0xF0,0xF9,0xFB,0xFB,0xFC,0xFC,
0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*"D:\32_PROJECT\院徽.bmp",0*/
};
//
 uint8_t  heikuang[] =
{
0xFF,0xFF,0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,0xFF,0xFF,/*"D:\32_PROJECT\框.bmp",0*/
};









//周换算
char * CalWeek(int y, int m, int d){
	if(m==1||m==2) 
	{
		m+=12;
		y--;
	}
	int week =  (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7+1;
	switch(week)
    {   
        case 0 : return "Sunday"; break;
        case 1 : return "Monday"; break;
        case 2 : return "Tuesday"; break;
        case 3 : return "Wednesday"; break;
        case 4 : return "Thursday"; break;
        case 5 : return "Friday"; break;                                                             
        case 6 : return "Saturday"; break;
        default : return NULL; break;
    }   
}
//  日(0) 期(1) 光(2) 强(3) 你(4) 好(5) 欢(6) 迎(7) 使(8) 用(9)

void User_Time_Show(void)
{
		OLED_Clear();

		RTC_DateTypeDef GetData;  //获取日期结构体
		RTC_TimeTypeDef GetTime;   //获取时间结构体
		HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);//获取时间
      /* Get the RTC current Date */
    HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);//获取日期

    /* Display date Format : yy/mm/dd */
		char time[30];
    sprintf(time,"%02d/%02d/%02d",(2000 + GetData.Year), GetData.Month, GetData.Date);
    /* Display time Format : hh:mm:ss */
		char data[]="00:00:00";
    sprintf(data,"%02d:%02d:%02d",GetTime.Hours, GetTime.Minutes, GetTime.Seconds);

    OLED_ShowString(2,4,time);
		OLED_ShowString(3,6,CalWeek(GetData.Year, GetData.Month, GetData.Date));
		OLED_ShowString(4,5,data);
		OLED_Chinese16(1,4,0);//日
		OLED_Chinese16(1,5,1);//期
}

void User_Init_Show(void)
{
		OLED_Clear();

		OLED_ShowPicture(0,0,64,64,myBMP1,1);
		OLED_Refresh();
		OLED_Chinese16(2,6,6);//欢
		OLED_Chinese16(2,7,7);//迎
		OLED_Chinese16(3,6,8);//使
		OLED_Chinese16(3,7,9);//用
}

void User_huizhang_Show(void)
{
		OLED_Clear();

		OLED_ShowPicture(0,0,64,64,xiaohui,1);
		OLED_ShowPicture(64,0,64,64,yuanhui,0);
		OLED_Refresh();
}
void User_PIC_Show(void)
{
		OLED_Clear();

		OLED_ShowPicture(0,0,64,64,myBMP,1);
		OLED_Refresh();
	
		RTC_DateTypeDef GetData;  //获取日期结构体
		RTC_TimeTypeDef GetTime;   //获取时间结构体
		HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);//获取时间
      /* Get the RTC current Date */
    HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);//获取日期

    /* Display date Format : yy/mm/dd */
		char time[]="2020";
		sprintf(time,"%02d",(2000 + GetData.Year));
		OLED_ShowString(1,11,time);
		char time1[]="07/01";
    sprintf(time1,"%02d/%02d", GetData.Month, GetData.Date);
		OLED_ShowString(2,10,time1);
    /* Display time Format : hh:mm:ss */
		char data[]="00:00:00";
    sprintf(data,"%02d:%02d:%02d",GetTime.Hours, GetTime.Minutes, GetTime.Seconds);
		OLED_ShowString(3,9,CalWeek(GetData.Year, GetData.Month, GetData.Date));
		OLED_ShowString(4,9,data);
}
int data_num=0;
float lightdata[99];
extern float light_ret;
void User_Data_Show(void)
{
		OLED_Clear();
		OLED_Refresh();
		OLED_Chinese16(1,2,2);//光
		OLED_Chinese16(1,3,3);//强
		OLED_ShowString(1,10,"cd/m2");
		lightdata[data_num]=100;
		lightdata[data_num]=light_ret;
		char lightdata2[3][20]={"              ","              ","              "};
		if(data_num>=2)
		{
		sprintf(lightdata2[0],"%2d.  %.2f",data_num-2,lightdata[data_num-2]);
		sprintf(lightdata2[1],"%2d.  %.2f",data_num-1,lightdata[data_num-1]);
		sprintf(lightdata2[2],"%2d.  %.2f",data_num,lightdata[data_num]);
		}
		else if(data_num==1)
		{
			sprintf(lightdata2[0],"%2d.  %.2f",data_num-1,lightdata[data_num-1]);
			sprintf(lightdata2[1],"%2d.  %.2f",data_num,lightdata[data_num]);
		}
		else
		{
			sprintf(lightdata2[0],"%2d.  %.2f",data_num,lightdata[data_num]);
		}
		data_num++;
		OLED_ShowString(2,1,lightdata2[0]);
		OLED_ShowString(3,1,lightdata2[1]);
		OLED_ShowString(4,1,lightdata2[2]);
}
void User_Detect_Show(void)
{
		OLED_Clear();
		OLED_Refresh();
		OLED_Chinese16(2,2,10);//
		OLED_Chinese16(2,3,11);//
		OLED_Chinese16(2,4,21);//	
		OLED_ShowString(2,10,"...");
}


// 日(0) 期(1) 光(2) 强(3) 你(4) 好(5) 欢(6) 迎(7) 使(8) 用(9) 测(10) 量(11)
void User_Time(void)
{
		OLED_Chinese16(1,1,10);//
		OLED_Chinese16(1,2,11);//
	
		OLED_Chinese16(2,2,0);//
		OLED_Chinese16(2,3,1);//
	
		OLED_Chinese(3,1,44);//
		OLED_Chinese(3,2,47);//
		OLED_Chinese(3,3,39);//
	
		OLED_Chinese16(4,1,19);//
		OLED_Chinese16(4,2,20);//
}
void User_Data(void)
{
		OLED_Chinese16(1,2,10);//
		OLED_Chinese16(1,3,11);//
	
		OLED_Chinese16(2,1,0);//
		OLED_Chinese16(2,2,1);//
	
		OLED_Chinese(3,1,44);//
		OLED_Chinese(3,2,47);//
		OLED_Chinese(3,3,39);//
	
		OLED_Chinese16(4,1,19);//
		OLED_Chinese16(4,2,20);//
}

void User_LOG(void)
{
		OLED_Chinese16(1,1,10);//
		OLED_Chinese16(1,2,11);//
	
		OLED_Chinese16(2,1,0);//
		OLED_Chinese16(2,2,1);//
	
		OLED_Chinese(3,4,44);//
		OLED_Chinese(3,5,47);//
		OLED_Chinese(3,6,39);//
	
		OLED_Chinese16(4,1,19);//
		OLED_Chinese16(4,2,20);//
}
void User_Play(void)
{
		OLED_Chinese16(1,1,10);//
		OLED_Chinese16(1,2,11);//
	
		OLED_Chinese16(2,1,0);//光强
		OLED_Chinese16(2,2,1);//
	
		OLED_Chinese(3,1,44);//
		OLED_Chinese(3,2,47);//
		OLED_Chinese(3,3,39);//
	
		OLED_Chinese16(4,2,19);//
		OLED_Chinese16(4,3,20);//
}

void User_Home(void)
{
		OLED_Chinese16(2,3,4);//你好
		OLED_Chinese16(2,6,5);//

}