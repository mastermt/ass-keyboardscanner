/*
 * ASS Keyboard Scanner — analog MIDI controls
 * Target: Arduino Mega 2560 / ATmega2560
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * A0 = joystick X / Pitch Bend (14-bit)
 * A1 = joystick Y / Modulation Wheel (CC1)
 * A2 = slider / Channel Volume (CC7)
 *
 * Analog controls are polled on a low-rate schedule, independently of the
 * keyboard matrix scan. No delay() is used. A control sends MIDI only when
 * its quantized output changes by at least the configured threshold.
 */
#ifndef ANALOG_CONTROLS_H
#define ANALOG_CONTROLS_H

#include <Arduino.h>

#ifndef ANALOG_POLL_INTERVAL_MS
#define ANALOG_POLL_INTERVAL_MS 5
#endif

#ifndef ANALOG_CC_CHANGE_THRESHOLD
#define ANALOG_CC_CHANGE_THRESHOLD 1
#endif

#ifndef ANALOG_PITCH_CHANGE_THRESHOLD
#define ANALOG_PITCH_CHANGE_THRESHOLD 32
#endif

void analogControlsSetup();
void analogControlsLoop();

#endif
