/*
 * ASS Keyboard Scanner — AVR assembly primitives
 * Target: ATmega2560, GNU AVR assembler (AVR-GCC).
 *
 * AVR-GCC ABI notes:
 * - First 8-bit argument is passed in r24.
 * - A 16-bit data pointer is passed in r25:r24 (low byte in r24).
 * - For (pointer, uint8_t), pointer is in r25:r24 and value in r22.
 * - r18-r27, r30-r31 are call-clobbered; r1 must remain zero in C/C++ code.
 *
 * These small routines intentionally serve as a toolchain/ABI baseline.
 * They are not claimed to outperform compiler-generated direct I/O. The
 * eventual hot scan path should be specialized and benchmarked per model.
 */

#include <avr/io.h>

.section .text

.global scanner_avr_read_io
.type scanner_avr_read_io, @function
scanner_avr_read_io:
    /* Z = pointer argument; load one byte from data space. */
    movw r30, r24
    ld   r24, Z
    ret
.size scanner_avr_read_io, .-scanner_avr_read_io

.global scanner_avr_write_io
.type scanner_avr_write_io, @function
scanner_avr_write_io:
    /* Z = pointer, r22 = value. */
    movw r30, r24
    st   Z, r22
    ret
.size scanner_avr_write_io, .-scanner_avr_write_io

.section .note.GNU-stack,"",@progbits
