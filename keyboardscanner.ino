/*
 * ASS Keyboard Scanner — Arduino entry point
 * Target: Arduino Mega 2560 / ATmega2560
 *
 * Derived from Moura's Keyboard Scanner:
 * https://github.com/mastermt/keyboardscanner
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "globals.h"

void setup()
{
    Serial.begin(SERIAL_SPEED);
    scannerSetup();
}

void loop()
{
    scannerLoop();
    statesLoop();
}
