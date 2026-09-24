/*
 * ASS Keyboard Scanner — AVR assembly interface
 * Target: ATmega2560 (Arduino Mega 2560), GNU AVR toolchain.
 *
 * Copyright (C) 2026 contributors to ASS Keyboard Scanner.
 * Distributed under GPL-3.0-or-later; see LICENSE.
 */

#ifndef SCANNER_AVR_H
#define SCANNER_AVR_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Read one memory-mapped I/O register through its data-space address.
 * The argument is the data-space address of the PINx register (not a
 * bit number and not a pointer to a C++ object).
 *
 * This helper is primarily an ABI/toolchain smoke test. Calling a function
 * for every matrix row may cost more cycles than an inlined C register read.
 * Production scan loops should inline the operations or use a specialized
 * model-specific assembly routine after measuring the generated code.
 */
uint8_t scanner_avr_read_io(volatile uint8_t *io_address);

/*
 * Write an 8-bit value to a memory-mapped I/O register.
 * Use only with the selected model's documented PORTx register address.
 * This function is not atomic with respect to other code modifying that port.
 */
void scanner_avr_write_io(volatile uint8_t *io_address, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif
