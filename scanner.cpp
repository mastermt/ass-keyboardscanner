/*
 * ASS Keyboard Scanner — matrix scanner integration point
 * Target: Arduino Mega 2560 / ATmega2560
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * IMPORTANT:
 * This initial scaffold deliberately does not energize matrix pins until
 * a complete model pin map is present. The upstream project uses model
 * headers that expand PINS(output_pin, input_pin) entries. Import and verify
 * the selected model before enabling physical scanning.
 */

#include "globals.h"
#include "scanner_avr.h"

void scannerSetup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void scannerLoop()
{
    /*
     * Model-specific optimized scanner will be implemented here.
     *
     * ATmega2560 direct-register scan routines must be generated from the
     * exact model matrix map. A generic hard-coded PORTA/B/C/etc sequence
     * could short or misread a keybed wired differently, so no arbitrary
     * port sequence is driven in this baseline.
     */
}
