/*
 * ASS Keyboard Scanner — MIDI output integration point
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * MIDI DIN serial uses 31,250 baud, 8-N-1. Keep debug text disabled during
 * timing measurements because formatted output changes execution latency.
 */
#include "globals.h"

void sendKeyEvent(byte status_byte, byte key_index, unsigned long time)
{
    (void)status_byte;
    (void)key_index;
    (void)time;
    // TODO: restore upstream velocity conversion and model velocity curve.
}

void sendSustainPedalEvent(boolean pressed)
{
    sendMidiEvent(0xB0, 0x40, pressed ? 0x7F : 0x00);
}

void sendMidiEvent(byte status_byte, byte data1, byte data2)
{
    Serial.write(status_byte);
    Serial.write(data1);
    Serial.write(data2);
}
