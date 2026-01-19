#ifndef __LABVIEW_TEST_H__
#define __LABVIEW_TEST_H__

#include "stm32_opal_frame.h"
#include "stm32_opal_emitter.h"
#include "stm32_opal_uart.h"

#include <stdlib.h>
#include <stdio.h>

/*
*   Definition of LabVIEW UART Commands enumeration
*/
typedef enum {
    START_TEST = 0x0,
    CONFIRM_NEXT_STEP,
    ABORT_CURRENT_TEST,
    UNKNOWN_COMMAND,
} CommandType;

/*
*   Pair mapping command types to their string representations
*/
typedef struct {
    CommandType type; /* !< Command type */
    const char* name; /* !< Command name string */
} CommandType_Map;

/*
*   Array to get the string representation of a command type
*/
static const CommandType_Map cmdType_map[] = {
    { START_TEST,           "LV_START_TST" },
    { CONFIRM_NEXT_STEP,    "LV_CONFIRM" },
    { ABORT_CURRENT_TEST,   "LV_ABORT" },
};

/*
*  Process a LabVIEW command received via UART
*/
void LabVIEW_Process_Command(const OPAL_UART_Command *cmd, OPAL_Emitter_Handle* htx);

#endif // __LABVIEW_TEST_H__