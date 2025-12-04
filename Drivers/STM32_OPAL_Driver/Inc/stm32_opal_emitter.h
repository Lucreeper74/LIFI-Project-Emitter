#ifndef __STM32_OPAL_EMITTER_H__
#define __STM32_OPAL_EMITTER_H__

#include "stm32_opal_utils.h"
#include "stm32_opal_frame.h"
#include <stdint.h>

OPAL_Status OPAL_Emitter_Encode(const OPAL_Frame* frame, OPAL_PAM4_symbol* frame_symbols);

#endif // __STM32_OPAL_EMITTER_H__