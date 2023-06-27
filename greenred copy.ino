#include <SoftwareSerial.h>
SoftwareSerial bluetooth(9, 10); // 블루투스 모듈 Rx, Tx 핀
#define GREEN_LED_PIN  5
#define RED_LED_PIN    6
#define SWITCH_PIN     7
#define AMP_PIN 3
#include "talkie.h"
Talkie voice;

const uint8_t spONE[]       PROGMEM = {0xCC,0x67,0x75,0x42,0x59,0x5D,0x3A,0x4F,0x9D,0x36,0x63,0xB7,0x59,0xDC,0x30,0x5B,0x5C,0x23,0x61,0xF3,0xE2,0x1C,0xF1,0xF0,0x98,0xC3,0x4B,0x7D,0x39,0xCA,0x1D,0x2C,0x2F,0xB7,0x15,0xEF,0x70,0x79,0xBC,0xD2,0x46,0x7C,0x52,0xE5,0xF1,0x4A,0x6A,0xB3,0x71,0x47,0xC3,0x2D,0x39,0x34,0x4B,0x23,0x35,0xB7,0x7A,0x55,0x33,0x8F,0x59,0xDC,0xA2,0x44,0xB5,0xBC,0x66,0x72,0x8B,0x64,0xF5,0xF6,0x98,0xC1,0x4D,0x42,0xD4,0x27,0x62,0x38,0x2F,0x4A,0xB6,0x9C,0x88,0x68,0xBC,0xA6,0x95,0xF8,0x5C,0xA1,0x09,0x86,0x77,0x91,0x11,0x5B,0xFF,0x0F};
const uint8_t spTWO[]       PROGMEM = {0x0E,0x38,0x6E,0x25,0x00,0xA3,0x0D,0x3A,0xA0,0x37,0xC5,0xA0,0x05,0x9E,0x56,0x35,0x86,0xAA,0x5E,0x8C,0xA4,0x82,0xB2,0xD7,0x74,0x31,0x22,0x69,0xAD,0x1C,0xD3,0xC1,0xD0,0xFA,0x28,0x2B,0x2D,0x47,0xC3,0x1B,0xC2,0xC4,0xAE,0xC6,0xCD,0x9C,0x48,0x53,0x9A,0xFF,0x0F};
const uint8_t spTHREE[]     PROGMEM = {0x02,0xD8,0x2E,0x9C,0x01,0xDB,0xA6,0x33,0x60,0xFB,0x30,0x01,0xEC,0x20,0x12,0x8C,0xE4,0xD8,0xCA,0x32,0x96,0x73,0x63,0x41,0x39,0x89,0x98,0xC1,0x4D,0x0D,0xED,0xB0,0x2A,0x05,0x37,0x0F,0xB4,0xA5,0xAE,0x5C,0xDC,0x36,0xD0,0x83,0x2F,0x4A,0x71,0x7B,0x03,0xF7,0x38,0x59,0xCD,0xED,0x1E,0xB4,0x6B,0x14,0x35,0xB7,0x6B,0x94,0x99,0x91,0xD5,0xDC,0x26,0x48,0x77,0x4B,0x66,0x71,0x1B,0x21,0xDB,0x2D,0x8A,0xC9,0x6D,0x88,0xFC,0x26,0x28,0x3A,0xB7,0x21,0xF4,0x1F,0xA3,0x65,0xBC,0x02,0x38,0xBB,0x3D,0x8E,0xF0,0x2B,0xE2,0x08,0xB7,0x34,0xFF,0x0F};
const uint8_t spFOUR[]      PROGMEM = {0x0C,0x18,0xB6,0x9A,0x01,0xC3,0x75,0x09,0x60,0xD8,0x0E,0x09,0x30,0xA0,0x9B,0xB6,0xA0,0xBB,0xB0,0xAA,0x16,0x4E,0x82,0xEB,0xEA,0xA9,0xFA,0x59,0x49,0x9E,0x59,0x23,0x9A,0x27,0x3B,0x78,0x66,0xAE,0x4A,0x9C,0x9C,0xE0,0x99,0xD3,0x2A,0xBD,0x72,0x92,0xEF,0xE6,0x88,0xE4,0x45,0x4D,0x7E,0x98,0x2D,0x62,0x67,0x37,0xF9,0xA1,0x37,0xA7,0x6C,0x94,0xE4,0xC7,0x1E,0xDC,0x3C,0xA5,0x83,0x1F,0x8B,0xEB,0x52,0x0E,0x0E,0x7E,0x2E,0x4E,0xC7,0x31,0xD2,0x79,0xA5,0x3A,0x0D,0xD9,0xC4,0xFF,0x07};
const uint8_t spFIVE[]      PROGMEM = {0x02,0xE8,0x3E,0x8C,0x01,0xDD,0x65,0x08,0x60,0x98,0x4C,0x06,0x34,0x93,0xCE,0x80,0xE6,0xDA,0x9A,0x14,0x6B,0xAA,0x47,0xD1,0x5E,0x56,0xAA,0x6D,0x56,0xCD,0x78,0xD9,0xA9,0x1C,0x67,0x05,0x83,0xE1,0xA4,0xBA,0x38,0xEE,0x16,0x86,0x9B,0xFA,0x60,0x87,0x5B,0x18,0x6E,0xEE,0x8B,0x1D,0x6E,0x61,0xB9,0x69,0x36,0x65,0xBA,0x8D,0xE5,0xE5,0x3E,0x1C,0xE9,0x0E,0x96,0x9B,0x5B,0xAB,0x95,0x2B,0x58,0x6E,0xCE,0xE5,0x3A,0x6A,0xF3,0xB8,0x35,0x84,0x7B,0x05,0xA3,0xE3,0x36,0xEF,0x92,0x19,0xB4,0x86,0xDB,0xB4,0x69,0xB4,0xD1,0x2A,0x4E,0x65,0x9A,0x99,0xCE,0x28,0xD9,0x85,0x71,0x4C,0x18,0x6D,0x67,0x47,0xC6,0x5E,0x53,0x4A,0x9C,0xB5,0xE2,0x85,0x45,0x26,0xFE,0x7F};
const uint8_t spSIX[]       PROGMEM = {0x0E,0xD8,0xAE,0xDD,0x03,0x0E,0x38,0xA6,0xD2,0x01,0xD3,0xB4,0x2C,0xAD,0x6A,0x35,0x9D,0xB1,0x7D,0xDC,0xEE,0xC4,0x65,0xD7,0xF1,0x72,0x47,0x24,0xB3,0x19,0xD9,0xD9,0x05,0x70,0x40,0x49,0xEA,0x02,0x98,0xBE,0x42,0x01,0xDF,0xA4,0x69,0x40,0x00,0xDF,0x95,0xFC,0x3F};
const uint8_t spSEVEN[]     PROGMEM = {0x02,0xB8,0x3A,0x8C,0x01,0xDF,0xA4,0x73,0x40,0x01,0x47,0xB9,0x2F,0x33,0x3B,0x73,0x5F,0x53,0x7C,0xEC,0x9A,0xC5,0x63,0xD5,0xD1,0x75,0xAE,0x5B,0xFC,0x64,0x5C,0x35,0x87,0x91,0xF1,0x83,0x36,0xB5,0x68,0x55,0xC5,0x6F,0xDA,0x45,0x2D,0x1C,0x2D,0xB7,0x38,0x37,0x9F,0x60,0x3C,0xBC,0x9A,0x85,0xA3,0x25,0x66,0xF7,0x8A,0x57,0x1C,0xA9,0x67,0x56,0xCA,0x5E,0xF0,0xB2,0x16,0xB2,0xF1,0x89,0xCE,0x8B,0x92,0x25,0xC7,0x2B,0x33,0xCF,0x48,0xB1,0x99,0xB4,0xF3,0xFF};
const uint8_t spEIGHT[]     PROGMEM = {0xC3,0x6C,0x86,0xB3,0x27,0x6D,0x0F,0xA7,0x48,0x99,0x4E,0x55,0x3C,0xBC,0x22,0x65,0x36,0x4D,0xD1,0xF0,0x32,0xD3,0xBE,0x34,0xDA,0xC3,0xEB,0x82,0xE2,0xDA,0x65,0x35,0xAF,0x31,0xF2,0x6B,0x97,0x95,0xBC,0x86,0xD8,0x6F,0x82,0xA6,0x73,0x0B,0xC6,0x9E,0x72,0x99,0xCC,0xCB,0x02,0xAD,0x3C,0x9A,0x10,0x60,0xAB,0x62,0x05,0x2C,0x37,0x84,0x00,0xA9,0x73,0x00,0x00,0xFE,0x1F};
const uint8_t spNINE[]      PROGMEM = {0xCC,0xA1,0x26,0xBB,0x83,0x93,0x18,0xCF,0x4A,0xAD,0x2E,0x31,0xED,0x3C,0xA7,0x24,0x26,0xC3,0x54,0xF1,0x92,0x64,0x8B,0x8A,0x98,0xCB,0x2B,0x2E,0x34,0x53,0x2D,0x0E,0x2F,0x57,0xB3,0x0C,0x0D,0x3C,0xBC,0x3C,0x4C,0x4B,0xCA,0xF4,0xF0,0x72,0x0F,0x6E,0x49,0x53,0xCD,0xCB,0x53,0x2D,0x35,0x4D,0x0F,0x2F,0x0F,0xD7,0x0C,0x0D,0x3D,0xBC,0xDC,0x4D,0xD3,0xDD,0xC2,0xF0,0x72,0x52,0x4F,0x57,0x9B,0xC3,0xAB,0x89,0xBD,0x42,0x2D,0x0F,0xAF,0x5A,0xD1,0x71,0x91,0x55,0xBC,0x2C,0xC5,0x3B,0xD8,0x65,0xF2,0x82,0x94,0x18,0x4E,0x3B,0xC1,0x73,0x42,0x32,0x33,0x15,0x45,0x4F,0x79,0x52,0x6A,0x55,0xA6,0xA3,0xFF,0x07};
const uint8_t spTEN[]       PROGMEM = {0x0E,0xD8,0xB1,0xDD,0x01,0x3D,0xA8,0x24,0x7B,0x04,0x27,0x76,0x77,0xDC,0xEC,0xC2,0xC5,0x23,0x84,0xCD,0x72,0x9A,0x51,0xF7,0x62,0x45,0xC7,0xEB,0x4E,0x35,0x4A,0x14,0x2D,0xBF,0x45,0xB6,0x0A,0x75,0xB8,0xFC,0x16,0xD9,0x2A,0xD9,0xD6,0x0A,0x5A,0x10,0xCD,0xA2,0x48,0x23,0xA8,0x81,0x35,0x4B,0x2C,0xA7,0x20,0x69,0x0A,0xAF,0xB6,0x15,0x82,0xA4,0x29,0x3C,0xC7,0x52,0x08,0xA2,0x22,0xCF,0x68,0x4B,0x2E,0xF0,0x8A,0xBD,0xA3,0x2C,0xAB,0x40,0x1B,0xCE,0xAA,0xB2,0x6C,0x82,0x40,0x4D,0x7D,0xC2,0x89,0x88,0x8A,0x61,0xCC,0x74,0xD5,0xFF,0x0F};
const uint8_t spELEVEN[]    PROGMEM = {0xC3,0xCD,0x76,0x5C,0xAE,0x14,0x0F,0x37,0x9B,0x71,0xDE,0x92,0x55,0xBC,0x2C,0x27,0x70,0xD3,0x76,0xF0,0x83,0x5E,0xA3,0x5E,0x5A,0xC1,0xF7,0x61,0x58,0xA7,0x19,0x35,0x3F,0x99,0x31,0xDE,0x52,0x74,0xFC,0xA2,0x26,0x64,0x4B,0xD1,0xF1,0xAB,0xAE,0xD0,0x2D,0xC5,0xC7,0x2F,0x36,0xDD,0x27,0x15,0x0F,0x3F,0xD9,0x08,0x9F,0x62,0xE4,0xC2,0x2C,0xD4,0xD8,0xD3,0x89,0x0B,0x1B,0x57,0x11,0x0B,0x3B,0xC5,0xCF,0xD6,0xCC,0xC6,0x64,0x35,0xAF,0x18,0x73,0x1F,0xA1,0x5D,0xBC,0x62,0x45,0xB3,0x45,0x51,0xF0,0xA2,0x62,0xAB,0x4A,0x5B,0xC9,0x4B,0x8A,0x2D,0xB3,0x6C,0x06,0x2F,0x29,0xB2,0xAC,0x8A,0x18,0xBC,0x28,0xD9,0xAA,0xD2,0x92,0xF1,0xBC,0xE0,0x98,0x8C,0x48,0xCC,0x17,0x52,0xA3,0x27,0x6D,0x93,0xD0,0x4B,0x8E,0x0E,0x77,0x02,0x00,0xFF,0x0F};
const uint8_t spTWELVE[]    PROGMEM = {0x06,0x28,0x46,0xD3,0x01,0x25,0x06,0x13,0x20,0xBA,0x70,0x70,0xB6,0x79,0xCA,0x36,0xAE,0x28,0x38,0xE1,0x29,0xC5,0x35,0xA3,0xE6,0xC4,0x16,0x6A,0x53,0x8C,0x97,0x9B,0x72,0x86,0x4F,0x28,0x1A,0x6E,0x0A,0x59,0x36,0xAE,0x68,0xF8,0x29,0x67,0xFA,0x06,0xA3,0x16,0xC4,0x96,0xE6,0x53,0xAC,0x5A,0x9C,0x56,0x72,0x77,0x31,0x4E,0x49,0x5C,0x8D,0x5B,0x29,0x3B,0x24,0x61,0x1E,0x6C,0x9B,0x6C,0x97,0xF8,0xA7,0x34,0x19,0x92,0x4C,0x62,0x9E,0x72,0x65,0x58,0x12,0xB1,0x7E,0x09,0xD5,0x2E,0x53,0xC5,0xBA,0x36,0x6B,0xB9,0x2D,0x17,0x05,0xEE,0x9A,0x6E,0x8E,0x05,0x50,0x6C,0x19,0x07,0x18,0x50,0xBD,0x3B,0x01,0x92,0x08,0x41,0x40,0x10,0xA6,0xFF,0x0F};
const uint8_t spTHIRTEEN[]  PROGMEM = {0x08,0xE8,0x2C,0x15,0x01,0x43,0x07,0x13,0xE0,0x98,0xB4,0xA6,0x35,0xA9,0x1E,0xDE,0x56,0x8E,0x53,0x9C,0x7A,0xE7,0xCA,0x5E,0x76,0x8D,0x94,0xE5,0x2B,0xAB,0xD9,0xB5,0x62,0xA4,0x9C,0xE4,0xE6,0xB4,0x41,0x1E,0x7C,0xB6,0x93,0xD7,0x16,0x99,0x5A,0xCD,0x61,0x76,0x55,0xC2,0x91,0x61,0x1B,0xC0,0x01,0x5D,0x85,0x05,0xE0,0x68,0x51,0x07,0x1C,0xA9,0x64,0x80,0x1D,0x4C,0x9C,0x95,0x88,0xD4,0x04,0x3B,0x4D,0x4E,0x21,0x5C,0x93,0xA8,0x26,0xB9,0x05,0x4B,0x6E,0xA0,0xE2,0xE4,0x57,0xC2,0xB9,0xC1,0xB2,0x93,0x5F,0x09,0xD7,0x24,0xCB,0x4E,0x41,0x25,0x54,0x1D,0x62,0x3B,0x05,0x8D,0x52,0x57,0xAA,0xAD,0x10,0x24,0x26,0xE3,0xE1,0x36,0x5D,0x10,0x85,0xB4,0x97,0x85,0x72,0x41,0x14,0x52,0x5E,0x1A,0xCA,0xF9,0x91,0x6B,0x7A,0x5B,0xC4,0xE0,0x17,0x2D,0x54,0x1D,0x92,0x8C,0x1F,0x25,0x4B,0x8F,0xB2,0x16,0x41,0xA1,0x4A,0x3E,0xE6,0xFA,0xFF,0x01};
const uint8_t spFOURTEEN[]  PROGMEM = {0x0C,0x58,0xAE,0x5C,0x01,0xD9,0x87,0x07,0x51,0xB7,0x25,0xB3,0x8A,0x15,0x2C,0xF7,0x1C,0x35,0x87,0x4D,0xB2,0xDD,0x53,0xCE,0x28,0x2B,0xC9,0x0E,0x97,0x2D,0xBD,0x2A,0x17,0x27,0x76,0x8E,0xD2,0x9A,0x6C,0x80,0x94,0x71,0x00,0x00,0x02,0xB0,0x58,0x58,0x00,0x9E,0x0B,0x0A,0xC0,0xB2,0xCE,0xC1,0xC8,0x98,0x7A,0x52,0x95,0x24,0x2B,0x11,0xED,0x36,0xD4,0x92,0xDC,0x4C,0xB5,0xC7,0xC8,0x53,0xF1,0x2A,0xE5,0x1A,0x17,0x55,0xC5,0xAF,0x94,0xBB,0xCD,0x1C,0x26,0xBF,0x52,0x9A,0x72,0x53,0x98,0xFC,0xC2,0x68,0xD2,0x4D,0x61,0xF0,0xA3,0x90,0xB6,0xD6,0x50,0xC1,0x8F,0x42,0xDA,0x4A,0x43,0x39,0x3F,0x48,0x2D,0x6B,0x33,0xF9,0xFF};
const uint8_t spFIFTEEN[]   PROGMEM = {0x08,0xE8,0x2A,0x0D,0x01,0xDD,0xBA,0x31,0x60,0x6A,0xF7,0xA0,0xAE,0x54,0xAA,0x5A,0x76,0x97,0xD9,0x34,0x69,0xEF,0x32,0x1E,0x66,0xE1,0xE2,0xB3,0x43,0xA9,0x18,0x55,0x92,0x4E,0x37,0x2D,0x67,0x6F,0xDF,0xA2,0x5A,0xB6,0x04,0x30,0x55,0xA8,0x00,0x86,0x09,0xE7,0x00,0x01,0x16,0x17,0x05,0x70,0x40,0x57,0xE5,0x01,0xF8,0x21,0x34,0x00,0xD3,0x19,0x33,0x80,0x89,0x9A,0x62,0x34,0x4C,0xD5,0x49,0xAE,0x8B,0x53,0x09,0xF7,0x26,0xD9,0x6A,0x7E,0x23,0x5C,0x13,0x12,0xB3,0x04,0x9D,0x50,0x4F,0xB1,0xAD,0x14,0x15,0xC2,0xD3,0xA1,0xB6,0x42,0x94,0xA8,0x8C,0x87,0xDB,0x74,0xB1,0x70,0x59,0xE1,0x2E,0xC9,0xC5,0x81,0x5B,0x55,0xA4,0x4C,0x17,0x47,0xC1,0x6D,0xE3,0x81,0x53,0x9C,0x84,0x6A,0x46,0xD9,0x4C,0x51,0x31,0x42,0xD9,0x66,0xC9,0x44,0x85,0x29,0x6A,0x9B,0xAD,0xFF,0x07};
const uint8_t spSIXTEEN[]   PROGMEM = {0x0A,0x58,0x5A,0x5D,0x00,0x93,0x97,0x0B,0x60,0xA9,0x48,0x05,0x0C,0x15,0xAE,0x80,0xAD,0x3D,0x14,0x30,0x7D,0xD9,0x50,0x92,0x92,0xAC,0x0D,0xC5,0xCD,0x2A,0x82,0xAA,0x3B,0x98,0x04,0xB3,0x4A,0xC8,0x9A,0x90,0x05,0x09,0x68,0x51,0xD4,0x01,0x23,0x9F,0x1A,0x60,0xA9,0x12,0x03,0xDC,0x50,0x81,0x80,0x22,0xDC,0x20,0x00,0xCB,0x06,0x3A,0x60,0x16,0xE3,0x64,0x64,0x42,0xDD,0xCD,0x6A,0x8A,0x5D,0x28,0x75,0x07,0xA9,0x2A,0x5E,0x65,0x34,0xED,0x64,0xBB,0xF8,0x85,0xF2,0x94,0x8B,0xAD,0xE4,0x37,0x4A,0x5B,0x21,0xB6,0x52,0x50,0x19,0xAD,0xA7,0xD8,0x4A,0x41,0x14,0xDA,0x5E,0x12,0x3A,0x04,0x91,0x4B,0x7B,0x69,0xA8,0x10,0x24,0x2E,0xE5,0xA3,0x81,0x52,0x90,0x94,0x5A,0x55,0x98,0x32,0x41,0x50,0xCC,0x93,0x2E,0x47,0x85,0x89,0x1B,0x5B,0x5A,0x62,0x04,0x44,0xE3,0x02,0x80,0x80,0x64,0xDD,0xFF,0x1F};
const uint8_t spSEVENTEEN[] PROGMEM = {0x02,0x98,0x3A,0x42,0x00,0x5B,0xA6,0x09,0x60,0xDB,0x52,0x06,0x1C,0x93,0x29,0x80,0xA9,0x52,0x87,0x9A,0xB5,0x99,0x4F,0xC8,0x3E,0x46,0xD6,0x5E,0x7E,0x66,0xFB,0x98,0xC5,0x5A,0xC6,0x9A,0x9C,0x63,0x15,0x6B,0x11,0x13,0x8A,0x9C,0x97,0xB9,0x9A,0x5A,0x39,0x71,0xEE,0xD2,0x29,0xC2,0xA6,0xB8,0x58,0x59,0x99,0x56,0x14,0xA3,0xE1,0x26,0x19,0x19,0xE3,0x8C,0x93,0x17,0xB4,0x46,0xB5,0x88,0x71,0x9E,0x97,0x9E,0xB1,0x2C,0xC5,0xF8,0x56,0xC4,0x58,0xA3,0x1C,0xE1,0x33,0x9D,0x13,0x41,0x8A,0x43,0x58,0xAD,0x95,0xA9,0xDB,0x36,0xC0,0xD1,0xC9,0x0E,0x58,0x4E,0x45,0x01,0x23,0xA9,0x04,0x37,0x13,0xAE,0x4D,0x65,0x52,0x82,0xCA,0xA9,0x37,0x99,0x4D,0x89,0xBA,0xC0,0xBC,0x14,0x36,0x25,0xEA,0x1C,0x73,0x52,0x1D,0x97,0xB8,0x33,0xAC,0x0E,0x75,0x9C,0xE2,0xCE,0xB0,0xDA,0xC3,0x51,0x4A,0x1A,0xA5,0xCA,0x70,0x5B,0x21,0xCE,0x4C,0x26,0xD2,0x6C,0xBA,0x38,0x71,0x2E,0x1F,0x2D,0xED,0xE2,0x24,0xB8,0xBC,0x3D,0x52,0x88,0xAB,0x50,0x8E,0xA8,0x48,0x22,0x4E,0x42,0xA0,0x26,0x55,0xFD,0x3F};
const uint8_t spEIGHTEEN[]  PROGMEM = {0x2E,0x9C,0xD1,0x4D,0x54,0xEC,0x2C,0xBF,0x1B,0x8A,0x99,0x70,0x7C,0xFC,0x2E,0x29,0x6F,0x52,0xF6,0xF1,0xBA,0x20,0xBF,0x36,0xD9,0xCD,0xED,0x0C,0xF3,0x27,0x64,0x17,0x73,0x2B,0xA2,0x99,0x90,0x65,0xEC,0xED,0x40,0x73,0x32,0x12,0xB1,0xAF,0x30,0x35,0x0B,0xC7,0x00,0xE0,0x80,0xAE,0xDD,0x1C,0x70,0x43,0xAA,0x03,0x86,0x51,0x36,0xC0,0x30,0x64,0xCE,0x4C,0x98,0xFB,0x5C,0x65,0x07,0xAF,0x10,0xEA,0x0B,0x66,0x1B,0xFC,0x46,0xA8,0x3E,0x09,0x4D,0x08,0x2A,0xA6,0x3E,0x67,0x36,0x21,0x2A,0x98,0x67,0x9D,0x15,0xA7,0xA8,0x60,0xEE,0xB6,0x94,0x99,0xA2,0x4A,0x78,0x22,0xC2,0xA6,0x8B,0x8C,0x8E,0xCC,0x4C,0x8A,0x2E,0x8A,0x4C,0xD3,0x57,0x03,0x87,0x28,0x71,0x09,0x1F,0x2B,0xE4,0xA2,0xC4,0xC5,0x6D,0xAD,0x54,0x88,0xB2,0x63,0xC9,0xF2,0x50,0x2E,0x8A,0x4A,0x38,0x4A,0xEC,0x88,0x28,0x08,0xE3,0x28,0x49,0xF3,0xFF};
const uint8_t spNINETEEN[]  PROGMEM = {0xC2,0xEA,0x8A,0x95,0x2B,0x6A,0x05,0x3F,0x71,0x71,0x5F,0x0D,0x12,0xFC,0x28,0x25,0x62,0x35,0xF0,0xF0,0xB3,0x48,0x1E,0x0F,0xC9,0xCB,0x2F,0x45,0x7C,0x2C,0x25,0x1F,0xBF,0x14,0xB3,0x2C,0xB5,0x75,0xFC,0x5A,0x5C,0xA3,0x5D,0xE1,0xF1,0x7A,0x76,0xB3,0x4E,0x45,0xC7,0xED,0x96,0x23,0x3B,0x18,0x37,0x7B,0x18,0xCC,0x09,0x51,0x13,0x4C,0xAB,0x6C,0x4C,0x4B,0x96,0xD2,0x49,0xAA,0x36,0x0B,0xC5,0xC2,0x20,0x26,0x27,0x35,0x63,0x09,0x3D,0x30,0x8B,0xF0,0x48,0x5C,0xCA,0x61,0xDD,0xCB,0xCD,0x91,0x03,0x8E,0x4B,0x76,0xC0,0xCC,0x4D,0x06,0x98,0x31,0x31,0x98,0x99,0x70,0x6D,0x2A,0xA3,0xE4,0x16,0xCA,0xBD,0xCE,0x5C,0x92,0x57,0x28,0xCF,0x09,0x69,0x2E,0x7E,0xA5,0x3C,0x63,0xA2,0x30,0x05,0x95,0xD2,0x74,0x98,0xCD,0x14,0x54,0xCA,0x53,0xA9,0x96,0x52,0x50,0x28,0x6F,0xBA,0xCB,0x0C,0x41,0x50,0xDE,0x65,0x2E,0xD3,0x05,0x89,0x4B,0x7B,0x6B,0x20,0x17,0x44,0xAE,0xED,0x23,0x81,0x52,0x90,0x85,0x73,0x57,0xD0,0x72,0x41,0xB1,0x02,0xDE,0x2E,0xDB,0x04,0x89,0x05,0x79,0xBB,0x62,0xE5,0x76,0x11,0xCA,0x61,0x0E,0xFF,0x1F};
const uint8_t spTWENTY[]    PROGMEM = {0x01,0x98,0xD1,0xC2,0x00,0xCD,0xA4,0x32,0x20,0x79,0x13,0x04,0x28,0xE7,0x92,0xDC,0x70,0xCC,0x5D,0xDB,0x76,0xF3,0xD2,0x32,0x0B,0x0B,0x5B,0xC3,0x2B,0xCD,0xD4,0xDD,0x23,0x35,0xAF,0x44,0xE1,0xF0,0xB0,0x6D,0x3C,0xA9,0xAD,0x3D,0x35,0x0E,0xF1,0x0C,0x8B,0x28,0xF7,0x34,0x01,0x68,0x22,0xCD,0x00,0xC7,0xA4,0x04,0xBB,0x32,0xD6,0xAC,0x56,0x9C,0xDC,0xCA,0x28,0x66,0x53,0x51,0x70,0x2B,0xA5,0xBC,0x0D,0x9A,0xC1,0xEB,0x14,0x73,0x37,0x29,0x19,0xAF,0x33,0x8C,0x3B,0xA7,0x24,0xBC,0x42,0xB0,0xB7,0x59,0x09,0x09,0x3C,0x96,0xE9,0xF4,0x58,0xFF,0x0F};


int redTime = 3;
int greenTime = 10;

bool green = false; //
bool start = true;
bool redStart = true;
bool blu = false;
bool bluetoothConnected = false;
bool bluetoothOn = false;
int n = 0;
char sound;
unsigned long running;
unsigned long bluetoothTimming;

void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  
  Serial.begin(9600);
  bluetooth.begin(38400);
}

void loop() {
  sound = "";

  // 1. 초록불 if문
  if (green) {
    digitalWrite(GREEN_LED_PIN,HIGH);
    if (start) {
      running = millis(); // 초록불 켜진지 몇초인지
      start = false;
      n = greenTime - 1;
      Serial.println("green start");
    }
    //Serial.println((millis() - running) / 1000 );

    if (n + 1 == greenTime - (millis() - running) / 1000) {
      Serial.print(n + 1);
      Serial.println("초 남았습니다.");
      
      if(n+1==1)voice.say(spONE);
      if(n+1==2)voice.say(spTWO);
      if(n+1==3)voice.say(spTHREE);
      if(n+1==4)voice.say(spFOUR);
      if(n+1==5)voice.say(spFIVE);
      if(n+1==6)voice.say(spSIX);
      if(n+1==7)voice.say(spSEVEN);
      if(n+1==8)voice.say(spEIGHT);
      if(n+1==9)voice.say(spNINE);
      if(n+1==10)voice.say(spTEN);
      if(n+1==11)voice.say(spELEVEN);
      if(n+1==12)voice.say(spTWELVE);
      if(n+1==13)voice.say(spTHIRTEEN);
      if(n+1==14)voice.say(spFOURTEEN);
      if(n+1==15)voice.say(spFIFTEEN);
      if(n+1==16)voice.say(spSIXTEEN);
      if(n+1==17)voice.say(spSEVENTEEN);
      if(n+1==18)voice.say(spEIGHTEEN);
      if(n+1==19)voice.say(spNINETEEN);
      if(n+1==20)voice.say(spTWENTY);
      n-=1;

    }
     if (bluetooth.available()){

      if(!blu){ //초록불이 된후 알림을 보낸적이 없다면
          if(greenTime - (millis() - running) / 1000>=greenTime-3){
          bluetooth.write(greenTime - (millis() - running) / 1000); //남은시간 보내줌
          }
          blu= true;
        }
     }
      

    //Serial.println(n+1);

    if ((millis() - running) / 1000 >= greenTime) { // 초록불로 변한지 7초 이상이라면, led off/ green false /start true
      Serial.println("green time");
      green = false;
      start = true;
      digitalWrite(GREEN_LED_PIN, LOW);
      running = 0;
      blu = false;
    }
  }

  // 2. 빨간불 if문
  if (!green) {
    digitalWrite(RED_LED_PIN, HIGH);

    if (redStart) {
      running = millis(); // 현재 시간 확인
      redStart = false;
      Serial.println("red start");
    }
    //Serial.println((millis() - running) / 1000 );
    if ((millis() - running) / 1000 >= redTime) {
      green = true;
      redStart = true;
      running = 0;
      digitalWrite(RED_LED_PIN,LOW);
      Serial.println("red off");
    }
  }
  
  if (digitalRead(SWITCH_PIN) == HIGH) { // 신호등 스위치가 눌렸을 때

    Serial.println("Switch is pressed");
    bluetooth.begin(38400); // 블루투스 모듈 1 켜기 (=초기화)
    bluetoothOn = true;
    bluetoothConnected = false;
    blu = false;


  }

  if(bluetoothOn){
    if(!bluetoothConnected){ //처음 연결 된거라면
      if (bluetooth.available()) { // 블루투스 모듈 1이 연결되었다면
      Serial.println("Bluetooth module 1 is connected");
      bluetooth.write("connected"); // 지팡이에서는 이 메세지를 받으면 진동 울리기
      bluetoothConnected = true; //이거는 뒤에 일정 시간이 지나면 false로 바꾸는거 추가해야함!!!!!!!!!!!!!!!!!!!!!!
      bluetoothTimming = millis(); }//이거가지고 블투 시간 체크해서 할듯
      
    
    }
    if (green) {
      //Serial.println("green");
      //bluetooth.write("testone");
      if(!blu){ //초록불이 된후 알림을 보낸적이 없다면
          if(greenTime - (millis() - running) / 1000>=greenTime-1){
            bluetooth.write("testone");
           //남은시간 보내줌
            Serial.println("111");
            blu= true;
          }else if(greenTime - (millis() - running) / 1000>=greenTime-2){
          bluetooth.write("testo");
          Serial.println("111");
          blu= true;
          
          
          }else if(greenTime - (millis() - running) / 1000>=greenTime-3){
          bluetooth.write("test");
          Serial.println("111");
          blu= true;
          }
          
        }
      }
    
  }
  

}//블루투스 확인