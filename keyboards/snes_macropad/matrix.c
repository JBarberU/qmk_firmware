#include "matrix.h"
#include "gpio.h"
#include "wait.h"
#include "string.h"
#include "print.h"

#define KEYPAD_DATA_PIN D4
#define CONTROLLER1_DATA_PIN 7
#define CONTROLLER2_DATA_PIN 8
#define CONTROLLER3_DATA_PIN 9
#define CONTROLLER4_DATA_PIN 10

#define CLOCK_PIN C6
#define LATCH_PIN D7

void matrix_init_custom(void)
{
    setPinInput(KEYPAD_DATA_PIN);
    setPinOutput(CLOCK_PIN);
    setPinOutput(LATCH_PIN);
    writePinLow(CLOCK_PIN);
    writePinLow(LATCH_PIN);
}

void readShiftRegisters(matrix_row_t current_matrix[])
{
    writePinHigh(LATCH_PIN);
    matrix_row_t kbd = 1;
    matrix_row_t ct1 = 0;
    matrix_row_t ct2 = 0;
    matrix_row_t ct3 = 0;
    matrix_row_t ct4 = 0;
    const unsigned int delay_us = 10;
    for (size_t i = 0; i < 16; ++i)
    {
        wait_us(delay_us);

        kbd = (kbd << 1) | readPin(KEYPAD_DATA_PIN);
        /*ct1 = (ct1 << 1) | readPin(CONTROLLER1_DATA_PIN);*/
        /*ct2 = (ct2 << 1) | readPin(CONTROLLER2_DATA_PIN);*/
        /*ct3 = (ct3 << 1) | readPin(CONTROLLER3_DATA_PIN);*/
        /*ct4 = (ct4 << 1) | readPin(CONTROLLER4_DATA_PIN);*/

        writePinHigh(CLOCK_PIN);
        wait_us(delay_us);
        writePinLow(CLOCK_PIN);
    }

    writePinLow(LATCH_PIN);
#ifdef CONSOLE_ENABLE
    /*uprintf("kbd value: %u\n", 0b0000111100000000 & ~kbd);*/
#endif
    current_matrix[0] = 0b0000111100000000 & ~kbd;
    current_matrix[1] = ~ct1;
    current_matrix[2] = ~ct2;
    current_matrix[3] = ~ct3;
    current_matrix[4] = ~ct4;
}

#define str(x) #x
#define xstr(x) str(x)

bool matrix_scan_custom(matrix_row_t current_matrix[])
{
#if 1    
    matrix_row_t last_value[MATRIX_ROWS];
    const size_t MATRIX_ARRAY_SIZE = MATRIX_ROWS * sizeof(matrix_row_t);
    memcpy(last_value, current_matrix, MATRIX_ARRAY_SIZE);
    readShiftRegisters(current_matrix);
    for (size_t row = 0; row < MATRIX_ROWS; ++row)
    {
        volatile __attribute__((unused)) uint16_t v1 = last_value[row];
        volatile __attribute__((unused)) uint16_t v2 = current_matrix[row];
        if (v1 != v2)
        {
            print("Keys changed\n");
            return true;
        }
    }
    return false;
#else
    matrix_row_t last_value[MATRIX_ROWS];
    const size_t MATRIX_ARRAY_SIZE = MATRIX_ROWS * sizeof(matrix_row_t);
    memcpy(last_value, current_matrix, MATRIX_ARRAY_SIZE);
    readShiftRegisters(current_matrix);
    return memcmp(last_value, current_matrix, MATRIX_ARRAY_SIZE) != 0;
#endif
}
