/*
 * ASS Keyboard Scanner — MIDI output integration
 *
 * During the optional eight-key diagnostic extension, MIDI transmission is
 * disabled so contact testing cannot produce Note On/Off or controller data.
 */
#include "globals.h"
#include "diagnostics.h"

void sendKeyEvent(byte status_byte, byte key_index, unsigned long time)
{
    (void)status_byte;
    (void)key_index;
    (void)time;

    if (diagnostic_midi_suppressed)
        return;

    // TODO: restore upstream velocity conversion and model velocity curve.
}

void sendSustainPedalEvent(boolean pressed)
{
    if (diagnostic_midi_suppressed)
        return;

    sendMidiEvent(0xB0, 0x40, pressed ? 0x7F : 0x00);
}

void sendMidiEvent(byte status_byte, byte data1, byte data2)
{
    if (diagnostic_midi_suppressed)
        return;

    Serial.write(status_byte);
    Serial.write(data1);
    Serial.write(data2);
}
