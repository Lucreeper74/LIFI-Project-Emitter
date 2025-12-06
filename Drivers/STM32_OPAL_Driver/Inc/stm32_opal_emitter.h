#ifndef __STM32_OPAL_EMITTER_H__
#define __STM32_OPAL_EMITTER_H__

#include "stm32_opal_utils.h"
#include "stm32_opal_frame.h"

/*
*   Encoding Frame (binary) to PAM4 Symbols
*/
OPAL_Status OPAL_Emitter_Encode(const OPAL_Frame* frame, OPAL_PAM4_symbol* frame_symbols);

/*
*   Preparation of the frame transmission (Reset buffers and such)
*/
OPAL_Status OPAL_Emitter_Prepare_Frame(const OPAL_Frame *frame);

/*
*   Send the frame by enabling the timer
*/
OPAL_Status OPAL_Emitter_Send_Frame(TIM_HandleTypeDef* htim);

/*
*   Drive the DAC to send PAM4 symbol levels
*/
OPAL_Status OPAL_Emitter_Send_Symbol(DAC_HandleTypeDef* hdac, OPAL_PAM4_symbol symbol);

/*
*   Callback to handle interruption from TIMER for frame transmission
*/
void OPAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim, DAC_HandleTypeDef* hdac);

#endif // __STM32_OPAL_EMITTER_H__