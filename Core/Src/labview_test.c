#include "labview_test.h"

LabVIEW_Test_Handle h_labview = {
    .test_id = LABVIEW_NONE,
    .test_status = LABVIEW_CONFIGURING,
}; // Initialization of global LabVIEW test handle

LabVIEW_Test_ID LabVIEW_Task(OPAL_UART_RX_Handle* huart_rx, OPAL_Emitter_Handle* htx) {

    // Listen UART Commands
    if (huart_rx->cmd_ready) {
      OPAL_UART_Command cmd = OPAL_UART_RX_ParseCmd(huart_rx);
      LabVIEW_Process_Command(cmd.command, cmd.param);
    }

    // Process LabVIEW Tests
    LabVIEW_Process_Test(htx);
    
    return h_labview.test_id;
}

void LabVIEW_Process_Command(const char *command_str, const char *param_str) {
    CommandType cmdType = UNKNOWN_COMMAND;

    // Find command type from string
    for (int i = 0; i < (sizeof(cmdType_map)/sizeof(CommandType_Map)); i++) {
        if (strcmp((const char*) command_str, cmdType_map[i].name) == 0) {
            cmdType = cmdType_map[i].type;
            break;
        }
    }
    
    // Process command based on type
    switch (cmdType) {
        case START_TEST: {
            // Handle START_TEST command
            int test_num = atoi(param_str);
            switch (test_num) {
            case 1:
                printf("Executing Test 1 BER vs Distance...\r\n");
                h_labview.test_id = LABVIEW_TEST_1;
                break;

            case 2:
                printf("Executing Test 2 logic...\r\n");
                h_labview.test_id = LABVIEW_TEST_2;
                break;

            case 3:
                printf("Executing Test 3 logic...\r\n");
                h_labview.test_id = LABVIEW_TEST_3;
                break;

            default:
                printf("[!] INVALID TEST SELECTION!\r\n");
                break;
            }
            break;
        }

        case CONFIRM_NEXT_STEP:
            // Handle CONFIRM_NEXT_STEP command
            if (h_labview.test_status == LABVIEW_WAITING) {
                printf("Confirmation received, sending next frame...\r\n");
                h_labview.test_status = LABVIEW_RUNNING;
            }
            break;

        case ABORT_CURRENT_TEST:
            // Handle ABORT_CURRENT_TEST command
            printf("Aborting current LabVIEW test...\r\n");
            // Add logic to abort the current test            
            break;

        default:
            printf("[!] UNKNOWN COMMAND ERROR!\r\n");
            break;
    }
}

void LabVIEW_Process_Test(OPAL_Emitter_Handle* htx) {
    switch (h_labview.test_status) {
        case LABVIEW_CONFIGURING: {
            switch (h_labview.test_id) {
                case LABVIEW_TEST_1: {
                    OPAL_Frame test_frame = OPAL_TestFrame;
                    if (OPAL_Emitter_Encode(htx, &test_frame) != OPAL_SUCCESS) {
                        printf("[!] ERROR ENCODING TEST FRAME!\r\n");
                    } else
                        h_labview.test_status = LABVIEW_WAITING; // Frame ready, wait for confirmation
                    break;
                }

                case LABVIEW_TEST_2:
                    break;

                case LABVIEW_TEST_3:
                    break;

                default:
                    break;
            
            }
        break;
        }

        case LABVIEW_WAITING: {
            switch (h_labview.test_id) {
                case LABVIEW_TEST_1:
                    // Waiting for confirmation to send frame
                    LabVIEW_Process_Command(const char *command_str, const char *param_str)
                    break;

                case LABVIEW_TEST_2:
                    break;

                case LABVIEW_TEST_3:
                    break;

                default:
                    break;
            
            }
        break;
        }

        case LABVIEW_RUNNING: {
            switch (h_labview.test_id) {
                case LABVIEW_TEST_1:
                    if (htx->Status == OPAL_EMITTER_IDLE)
                        h_labview.test_status = LABVIEW_WAITING; // Frame sent, wait for next one
                    break;

                case LABVIEW_TEST_2:
                    break;

                case LABVIEW_TEST_3:
                    break;

                default:
                    break;
            
            }
        break;
        }

        case LABVIEW_COMPLETED: {
            switch (h_labview.test_id) {
                case LABVIEW_TEST_1:
                    break;

                case LABVIEW_TEST_2:
                    break;

                case LABVIEW_TEST_3:
                    break;

                default:
                    break;
            
            }
        break;
        }
    }
}