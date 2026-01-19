#include "labview_test.h"

void LabVIEW_Process_Command(const OPAL_UART_Command *cmd, OPAL_Emitter_Handle* htx) {
    CommandType cmdType = UNKNOWN_COMMAND;

    // Find command type from string
    for (int i = 0; i < (sizeof(cmdType_map)/sizeof(CommandType_Map)); i++) {
        if (strcmp((const char*) cmd->command, cmdType_map[i].name) == 0) {
            cmdType = cmdType_map[i].type;
            break;
        }
    }
    
    // Process command based on type
    switch (cmdType) {
        case START_TEST: {
            // Handle START_TEST command
            int test_num = atoi(cmd);
            switch (test_num) {
            case 1:
                printf("Executing Test 1 BER vs Distance...\r\n");
                break;

            case 2:
                printf("Executing Test 2 logic...\r\n");
                break;

            case 3:
                printf("Executing Test 3 logic...\r\n");
                break;

            default:
                printf("[!] INVALID TEST SELECTION!\r\n");
                break;
            }
            break;
        }

        case CONFIRM_NEXT_STEP:
            // Handle CONFIRM_NEXT_STEP command
            printf("Confirmation received, sending next frame...\r\n");
            break;

        case ABORT_CURRENT_TEST:
            // Handle ABORT_CURRENT_TEST command
            printf("Aborting current LabVIEW test...\r\n");
            // Add logic to abort the current test            
            break;

        default:
            printf("[!] UNKNOWN LABVIEW COMMAND ERROR!\r\n");
            break;
    }
}