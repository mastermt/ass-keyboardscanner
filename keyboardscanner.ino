/*
 * ASS Keyboard Scanner — Arduino entry point
 * Target: Arduino Mega 2560 / ATmega2560
 *
 * Derived from Moura's Keyboard Scanner:
 * https://github.com/mastermt/keyboardscanner
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "globals.h"
#include "analog_controls.h"

#define EXTENSION(name) void name##Setup(); void name##Loop();
#include "extensions.h"
#undef EXTENSION

void setup()
{
    Serial.begin(SERIAL_SPEED);

    scannerSetup();

    analogControlsSetup();

    #define EXTENSION(name) name##Setup();
    #include "extensions.h"
    #undef EXTENSION
}

void loop()
{
    /*
     * Keep the real-time path in this order:
     *  1. complete matrix scan
     *  2. state transitions / MIDI generation
     *  3. optional diagnostics
     *  4. analog controls
     *
     * The counter extension observes the scanner count maintained by
     * scannerLoop(). The key-test extension reads the raw scanner snapshot.
     */
    scannerLoop();
    statesLoop();

    #define EXTENSION(name) name##Loop();
    #include "extensions.h"
    #undef EXTENSION

    analogControlsLoop();
}
