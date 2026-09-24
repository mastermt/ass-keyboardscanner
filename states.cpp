/*
 * ASS Keyboard Scanner — key-state engine integration point
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * The upstream state machine is retained as the behavioral reference.
 * Import the complete upstream model definitions and velocity settings
 * before enabling Note On/Off processing in this module.
 */
#include "globals.h"

void statesLoop()
{
    /*
     * TODO: port upstream key state transitions:
     * KEY_OFF -> KEY_START -> KEY_ON -> KEY_RELEASED -> KEY_OFF.
     *
     * Keep transition semantics and unsigned micros() subtraction so timer
     * wraparound remains well-defined. Optimize only after equivalence tests.
     */
}
