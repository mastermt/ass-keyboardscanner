/*
 * ASS Keyboard Scanner — diagnostic scanner interface
 *
 * The scanner writes raw MAKE/BREAK state for every key. Diagnostic
 * extensions can inspect this data without becoming part of the MIDI path.
 */

#ifndef ASS_SCANNER_DEBUG_H
#define ASS_SCANNER_DEBUG_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint8_t scanner_make_state[KEYS_NUMBER];
extern volatile uint8_t scanner_break_state[KEYS_NUMBER];

uint32_t scannerGetScanCount(void);

#ifdef __cplusplus
}
#endif

#endif
