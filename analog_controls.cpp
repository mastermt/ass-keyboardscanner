/*
 * ASS Keyboard Scanner — analog MIDI controls
 * Target: Arduino Mega 2560 / ATmega2560
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "globals.h"
#include "analog_controls.h"

// Hardware allocation requested for the GeneralMusic pRP8 controller.
static const uint8_t PIN_PITCH_X = A0;
static const uint8_t PIN_MOD_Y   = A1;
static const uint8_t PIN_VOLUME  = A2;

// Keep the remaining analog inputs available for future controls.
static const uint8_t MIDI_CHANNEL = 0; // MIDI channel 1, zero-based status nibble.

static uint32_t last_poll_ms = 0;
static uint16_t last_pitch = 0xFFFF;
static int16_t last_mod = -1;
static int16_t last_volume = -1;

static uint16_t readPitchBend()
{
    // ADC returns 0..1023. Split at the nominal center (512) so the
    // center maps exactly to MIDI 8192 and both endpoints are preserved.
    const uint16_t raw = analogRead(PIN_PITCH_X);
    if (raw <= 512) {
        return (uint32_t)raw * 8192UL / 512UL;
    }
    return 8192U + (uint32_t)(raw - 512U) * 8191UL / 511UL;
}

static uint8_t readControlChange(uint8_t pin)
{
    // Scale 10-bit ADC range to the 7-bit MIDI data range.
    return (uint32_t)analogRead(pin) * 127UL / 1023UL;
}

void analogControlsSetup()
{
    pinMode(PIN_PITCH_X, INPUT);
    pinMode(PIN_MOD_Y, INPUT);
    pinMode(PIN_VOLUME, INPUT);

    // Do not emit startup controller values: the host/synth keeps its
    // current state until the user moves a control.
    last_poll_ms = millis();
}

void analogControlsLoop()
{
    const uint32_t now = millis();
    if ((uint32_t)(now - last_poll_ms) < ANALOG_POLL_INTERVAL_MS) {
        return;
    }
    last_poll_ms = now;

    const uint16_t pitch = readPitchBend();
    if (last_pitch == 0xFFFF ||
        (pitch > last_pitch ? pitch - last_pitch : last_pitch - pitch) >= ANALOG_PITCH_CHANGE_THRESHOLD) {
        // Pitch Bend is a 14-bit value, least-significant 7 bits first.
        sendMidiEvent(0xE0 | MIDI_CHANNEL, pitch & 0x7F, (pitch >> 7) & 0x7F);
        last_pitch = pitch;
    }

    const uint8_t modulation = readControlChange(PIN_MOD_Y);
    if (last_mod < 0 ||
        (modulation > last_mod ? modulation - last_mod : last_mod - modulation) >= ANALOG_CC_CHANGE_THRESHOLD) {
        sendMidiEvent(0xB0 | MIDI_CHANNEL, 1, modulation); // CC1: Modulation Wheel
        last_mod = modulation;
    }

    const uint8_t volume = readControlChange(PIN_VOLUME);
    if (last_volume < 0 ||
        (volume > last_volume ? volume - last_volume : last_volume - volume) >= ANALOG_CC_CHANGE_THRESHOLD) {
        sendMidiEvent(0xB0 | MIDI_CHANNEL, 7, volume); // CC7: Channel Volume
        last_volume = volume;
    }
}
