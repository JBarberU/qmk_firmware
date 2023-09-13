#include "matrix.h"
#include "gpio.h"
#include "wait.h"
#include "string.h"
#include "print.h"
#include "debug.h"

#define SNES_CLOCK GP0
#define SNES_LATCH GP1
#define SNES_D0 GP2
#define SNES_D1 GP3
#define SNES_IO GP4

#define KBD_ROW0 GP24
#define KBD_ROW1 GP23
#define KBD_ROW2 GP22
#define KBD_NUM_ROWS 3

#define KBD_COL0 GP18
#define KBD_COL1 GP19
#define KBD_COL2 GP20
#define KBD_COL3 GP21
#define KBD_ROW_SETUP_DELAY_US 1

// The real snes will clock 16 bits out of the controller, but only really has 12 bits of data
#define SNES_DATA_BITS 12
#define SNES_DATA_SETUP_DELAY_US 10
#define SNES_CLOCK_PULSE_DURATION 10

static inline int get_pin(size_t row)
{
    switch (row)
    {
        case 0: return KBD_ROW0;
        case 1: return KBD_ROW1;
        case 2: return KBD_ROW2;
        default: return -1;
    }
}

static void deselect_all_rows(void)
{
    setPinOutput(KBD_ROW0);
    writePinHigh(KBD_ROW0);

    setPinOutput(KBD_ROW1);
    writePinHigh(KBD_ROW1);

    setPinOutput(KBD_ROW2);
    writePinHigh(KBD_ROW2);
}

static void deselect_row(size_t row)
{
    const int pin = get_pin(row);
    if (pin >= 0)
    {
        setPinOutput(pin);
        writePinHigh(pin);
    }
}

static void select_row(size_t row)
{
    const int pin = get_pin(row);
    if (pin >= 0)
    {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static void init_cols(void)
{
    setPinInputHigh(KBD_COL0);
    setPinInputHigh(KBD_COL1);
    setPinInputHigh(KBD_COL2);
    setPinInputHigh(KBD_COL3);
}

void matrix_init_custom(void)
{
    setPinInputHigh(SNES_D0);
    // todo: look into protocol for other strange snes controllers that use D1 and IO
    // setPinInputHigh(SNES_D1);
    // setPinInputHigh(SNES_IO);
    setPinOutput(SNES_CLOCK);
    setPinOutput(SNES_LATCH);

    deselect_all_rows();
    init_cols();

    writePinLow(SNES_CLOCK);
    writePinLow(SNES_LATCH);
}

static matrix_row_t read_row(size_t row)
{
    select_row(row);
    wait_us(KBD_ROW_SETUP_DELAY_US);
    const matrix_row_t ret = 
        (readPin(KBD_COL0) ? 0 : 1 << 0) |
        (readPin(KBD_COL1) ? 0 : 1 << 1) |
        (readPin(KBD_COL2) ? 0 : 1 << 2) |
        (readPin(KBD_COL3) ? 0 : 1 << 3);
    deselect_row(row);
    return ret;
}

static uint16_t readShiftRegister(void)
{
    uint16_t ret = 0;

    writePinHigh(SNES_LATCH);

    for (size_t bit = 0; bit < SNES_DATA_BITS; ++bit)
    {
        // Wait for shift register to setup the data line
        wait_us(SNES_DATA_SETUP_DELAY_US);

        // Shift accumulated data and read data pin
        ret <<= 1;
        ret |= readPin(SNES_D0);
        // todo: maybe read D1 and IO here too

        // Shift next bit in
        writePinHigh(SNES_CLOCK);
        wait_us(SNES_CLOCK_PULSE_DURATION);
        writePinLow(SNES_CLOCK);
    }
    
    writePinLow(SNES_LATCH);

    return ret;
}

static void readKeyboard(matrix_row_t current_matrix[])
{
    for (size_t row = 0; row < KBD_NUM_ROWS; ++row)
    {
        current_matrix[row] = read_row(row);
    }
}

static void readSnesController(matrix_row_t current_matrix[])
{
  const uint16_t controller = ~readShiftRegister();
  current_matrix[3] = 0b1111 & (controller >> (0 * MATRIX_COLS));
  current_matrix[4] = 0b1111 & (controller >> (1 * MATRIX_COLS));
  current_matrix[5] = 0b1111 & (controller >> (2 * MATRIX_COLS));
}

bool matrix_scan_custom(matrix_row_t current_matrix[])
{
  matrix_row_t last_value[MATRIX_ROWS];
  const size_t MATRIX_ARRAY_SIZE = MATRIX_ROWS * sizeof(matrix_row_t);
  memcpy(last_value, current_matrix, MATRIX_ARRAY_SIZE);
  readKeyboard(current_matrix);
  readSnesController(current_matrix);
  return memcmp(last_value, current_matrix, MATRIX_ARRAY_SIZE) != 0;
}
