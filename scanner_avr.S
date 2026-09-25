/*
 * ASS Keyboard Scanner — ATmega2560 contact-scan primitive
 *
 * scanner_avr_read_contact(out_port, out_mask, in_pin, in_mask)
 *
 * AVR-GCC ABI (5 arguments/register slots):
 *   out_port: r25:r24 (data-space address of PORTx)
 *   out_mask: r22
 *   in_pin:   r21:r20 (data-space address of PINx)
 *   in_mask:  r18
 *
 * Drives exactly one KD output LOW, samples one input, then restores the
 * output HIGH. All other KD lines remain inactive. Input pull-ups are
 * configured by scannerSetup().
 *
 * Return r24 = 1 when the active-low input is LOW, otherwise 0.
 */

#include <avr/io.h>

.section .text

.global scanner_avr_read_contact
.type scanner_avr_read_contact, @function
scanner_avr_read_contact:
    /* Save pointer/masks in call-clobbered registers. */
    movw r30, r24           /* Z = PORTx address */
    mov  r19, r22           /* output mask */
    movw r26, r20           /* X = PINx address */
    mov  r22, r18           /* input mask */

    /* Assert selected KD low: PORTx &= ~out_mask. */
    ld   r18, Z
    mov  r20, r19
    com  r20
    and  r18, r20
    st   Z, r18

    /* A few CPU cycles for signal propagation through keybed/diodes. */
    nop
    nop
    nop

    /* Read input register and normalize the selected bit to 0 or 1. */
    ld   r24, X
    and  r24, r22
    breq 1f
    clr  r24                /* high = inactive */
    rjmp 2f
1:
    ldi  r24, 1             /* low = contact closed */
2:
    /* Restore selected KD output HIGH: PORTx |= out_mask. */
    ld   r18, Z
    or   r18, r19
    st   Z, r18

    ret
.size scanner_avr_read_contact, .-scanner_avr_read_contact

.section .note.GNU-stack,"",@progbits
