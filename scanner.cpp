/*
 * ASS Keyboard Scanner — matrix scanner integration point
 * Target: Arduino Mega 2560 / ATmega2560
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * The diagnostic data below is kept separate from MIDI/state handling:
 * scanner_make_state[] and scanner_break_state[] are the raw contact
 * snapshots that the future optimized AVR scan routine will fill.
 */

#include "globals.h"
#include "scanner_avr.h"
#include "scanner_debug.h"

volatile uint8_t scanner_make_state[KEYS_NUMBER] = {0};
volatile uint8_t scanner_break_state[KEYS_NUMBER] = {0};

static volatile uint32_t scanner_scan_count = 0;

uint32_t scannerGetScanCount(void)
{
    noInterrupts();
    const uint32_t count = scanner_scan_count;
    interrupts();
    return count;
}

void scannerSetup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void scannerLoop()
{
    /*
     * The model-specific AVR scan routine will update the raw MAKE/BREAK
     * arrays here. Keep the scan counter at the end of this function:
     * one increment represents one complete matrix scan.
     */

    ++scanner_scan_count;
}
