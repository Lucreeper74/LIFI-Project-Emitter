#ifndef __STM32_OPAL_FRAME_H__
#define __STM32_OPAL_FRAME_H__

#include "stm32_opal_utils.h"

// Definition of known frame Sequences
#define OPAL_FRAME_PREAMBLE     0xCCCC // => 11 00 11 00 11 00 11 00 - 2 Bytes
#define OPAL_FRAME_START_BYTE   0x1B   // => 00 01 10 11 - 1 Byte

#define OPAL_FRAME_PAYLOAD_SIZE 4  // In bytes

/*
*   Represent the frame structure (Packed to ensure contiguous memory layout)
*/
typedef struct __attribute__((packed)) {
    uint16_t Preamble;     /* !< Init the frame (Known sequence) */
    uint8_t  StartFrame;   /* !< Define the start of the frame (Known sequence) */ 
    uint8_t  DataType;     /* !< Define the type of the data transmitted */
    uint8_t  Data[OPAL_FRAME_PAYLOAD_SIZE]; /* !< Define the data transmitted */
    uint16_t crc16;        /* !< Used to verify the frame integrity */
} OPAL_Frame;

/*
*   Represent the interpreted payload data transmitted in a frame
*/
typedef union {
    char    var_str[OPAL_FRAME_PAYLOAD_SIZE / sizeof(char)];
    int     var_int[OPAL_FRAME_PAYLOAD_SIZE / sizeof(int)];
    float   var_float[OPAL_FRAME_PAYLOAD_SIZE / sizeof(float)];
    uint8_t var_bin[OPAL_FRAME_PAYLOAD_SIZE];
} OPAL_Data;

/*
*   Represent the datatype containtend into a frame
*/
typedef enum {
    TYPE_BIN    = 0x00,
    TYPE_STRING = 0x01,
    TYPE_INT    = 0x02,
    TYPE_FLOAT  = 0x03,
} OPAL_DataType;

/*
*   Compute the CRC16 for a specific frame
*/
uint16_t OPAL_Compute_CRC16(const OPAL_Frame* frame);

/*
*   Conversion between OPAL_Frame struct to bytes array (handle little-endians)
*/
void OPAL_Frame_Byte_Conversion(const OPAL_Frame* frame, uint8_t* frame_bytes);

#endif // __STM32_OPAL_FRAME_H__