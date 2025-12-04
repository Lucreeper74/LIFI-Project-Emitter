#include "stm32_opal_emitter.h"

OPAL_Status OPAL_Emitter_Encode(const OPAL_Frame* frame, OPAL_PAM4_symbol* frame_symbols) {
    if (frame == NULL)
        return OPAL_ERROR_NULL_PTR;

    const uint8_t* frameBytes = (const uint8_t*) frame;
    size_t frameSize = sizeof(OPAL_Frame);
    size_t symbol_index = 0;

    for (size_t i = 0; i < frameSize; i++) {
        OPAL_byte_to_pam4(frameBytes[i], &frame_symbols[symbol_index]);
        symbol_index += OPAL_SYMBOLS_PER_BYTE;
    }
    
    return OPAL_SUCCESS;
}