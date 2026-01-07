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
    { START_TEST,           "START_TEST" },
    { CONFIRM_NEXT_STEP,    "CONF_NEXT_STEP" },
    { ABORT_CURRENT_TEST,   "ABORT_CURR_TEST" },
};

/*
*  Definition of LabVIEW Test ID enumeration
*/
typedef enum {
    LABVIEW_NONE = 0x0,
    LABVIEW_TEST_1,
    LABVIEW_TEST_2,
    LABVIEW_TEST_3,
} LabVIEW_Test_ID;

/*
*   Definition of LabVIEW Test Status enumeration
*/
typedef enum {
    LABVIEW_CONFIGURING = 0x0,
    LABVIEW_WAITING,
    LABVIEW_RUNNING,
    LABVIEW_COMPLETED,
} LabVIEW_Test_Status;

/*
*   Structure to hold LabVIEW test information
*/
typedef struct {
    LabVIEW_Test_ID     test_id;     /* < Test ID */
    LabVIEW_Test_Status test_status; /* < Test Status */
} LabVIEW_Test_Handle;

extern LabVIEW_Test_Handle h_labview; // Global LabVIEW test handle


/*
*   Main LabVIEW Task to be called in the main loop
*/
LabVIEW_Test_ID LabVIEW_Task(OPAL_UART_RX_Handle* huart_rx, OPAL_Emitter_Handle* htx);

/*
*  Process a LabVIEW command received via UART
*/
void LabVIEW_Process_Command(const char *command_str, const char *param_str);

/*
*   Process LabVIEW tests
*/
void LabVIEW_Process_Test(OPAL_Emitter_Handle* htx);

#endif // __LABVIEW_TEST_H__