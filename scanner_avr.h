/*
 * ASS Keyboard Scanner — AVR assembly interface
 * Target: ATmega2560 / Arduino Mega 2560.
 */
#ifndef SCANNER_AVR_H
#define SCANNER_AVR_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Assembly scan of one matrix contact.
 * Returns 1 when the selected input is LOW while its KD output is active.
 */
uint8_t scanner_avr_read_contact(volatile uint8_t *out_port,
                                 uint8_t out_mask,
                                 volatile uint8_t *in_pin,
                                 uint8_t in_mask);

#ifdef __cplusplus
}
#endif
#endif
