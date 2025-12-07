#include "stm32_opal_frame.h"
#include <stddef.h>
#include <stdint.h>

uint16_t OPAL_Compute_CRC16(const OPAL_Frame* frame) {
    const uint8_t* frame_bytes = (const uint8_t*) frame;

    uint8_t gen_MSB_index = OPAL_msb_index(OPAL_CRC16_GENERATOR);
    uint16_t CRC16_result = OPAL_CRC16_DEFAULT;

    for (size_t i = 0; i < offsetof(OPAL_Frame, crc16); i++) { // Parse each bytes in frame (except CRC16 field obviously)
        uint8_t byte = frame_bytes[i];

        CRC16_result ^= (byte << (gen_MSB_index-7)); // Align data byte (x0 to x7) with GEN MSB
        // XOR operation used here to avoid erasing data during each bytes of the frame

        /* Start polynomial division in a Finite Field [0, 1] :
        *   0+0=0   0-0=0
        *   0+1=1   0-1=1   Which is equal to XOR truth table
        *   1+0=1   1-0=1
        *   1+1=0   1-1=0
        */
        for (uint8_t j = 0; j < 8; j++) { // Parse each bits in the Byte
            if (CRC16_result & (1 << gen_MSB_index)) // Check if the bit is set at the MSB index of the GEN
                CRC16_result = (CRC16_result << 1) ^ OPAL_CRC16_GENERATOR; // Bit is set -> proceed substraction (XOR)
            else
                CRC16_result <<= 1;
        }
    }
    return CRC16_result;
}

void OPAL_Frame_Byte_Conversion(const OPAL_Frame* frame, uint8_t* frame_bytes) {
    uint8_t* frame_bytes_buffer = (const uint8_t*) frame;
    
    for (size_t i = 0; i < sizeof(OPAL_Frame); i++) {

    }
}