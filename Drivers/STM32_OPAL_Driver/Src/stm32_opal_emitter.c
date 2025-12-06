#include "stm32_opal_emitter.h"
#include "stm32_opal_utils.h"
#include "stm32l0xx_hal_tim.h"

static volatile uint8_t symbol_index = 0; // Volatile because can be modified by an ITR
static volatile bool tx_active = false;   // Default state inactive
static OPAL_PAM4_symbol frame_buffer[sizeof(OPAL_PAM4_symbol) * OPAL_SYMBOLS_PER_BYTE];

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

OPAL_Status OPAL_Emitter_Prepare_Frame(const OPAL_Frame *frame) {
    OPAL_Status status = OPAL_Emitter_Encode(frame, frame_buffer);

    if (status == OPAL_ERROR_INVALID_FRAME)
        return OPAL_ERROR_INVALID_FRAME;

    tx_active = false;
    symbol_index = 0;

    return OPAL_SUCCESS;
}

OPAL_Status OPAL_Emitter_Send_Frame(TIM_HandleTypeDef* htim) {
    tx_active = true;
    symbol_index = 0;
    HAL_TIM_Base_Start_IT(htim);

    return OPAL_SUCCESS;
}

OPAL_Status OPAL_Emitter_Send_Symbol(DAC_HandleTypeDef* hdac, OPAL_PAM4_symbol symbol) {
    HAL_StatusTypeDef dac_status = HAL_DAC_SetValue(hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, OPAL_symbol_to_voltage(symbol));

    if (dac_status == HAL_ERROR)
        return OPAL_DAC_ERROR;

    return OPAL_SUCCESS;
}

void OPAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim, DAC_HandleTypeDef* hdac) {
    if (tx_active) {
        if (symbol_index < (sizeof(OPAL_Frame) * OPAL_SYMBOLS_PER_BYTE)) {
            OPAL_Emitter_Send_Symbol(hdac, frame_buffer[symbol_index++]);
        } else {
            tx_active = false; // End of transmission
            HAL_TIM_Base_Stop_IT(htim);
        }
    }
}