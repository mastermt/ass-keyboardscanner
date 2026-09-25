/*
Moura's Keyboard Scanner: turn you broken (or unused) keyboard in a MIDI controller
Copyright (C) 2017 Daniel Moura <oxesoft@gmail.com>

This code is originally hosted at https://github.com/oxesoft/keyboardscanner

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


Pedro Tomaz Alves
2026-03-10
Cuiabá-MT, Brazil
*/

// GeneralMusic pRP8 model definition
// Based on the structure of the other models in models/

// Number of keys and first MIDI note.
// GeneralMusic pRP8 is an 88‑key piano starting at A0 (MIDI 21).
#define KEYS_NUMBER       88
#define FIRST_KEY         21

// Sustain pedal pin (PORTB, keeping A0–A8 free)
#define SUSTAIN_PEDAL_PIN A15 // As indicated in the original pRP8 wiring SVG

// Time range in microseconds used for velocity calculation
// Tweak these if you need to refine the velocity response
#define MIN_TIME_US       3000
#define MAX_TIME_US       25000

// Matrix pin assignments are centralized in scanner.cpp for the AVR
// assembly scanner. The assignments follow the original wiring SVG:
// KD0..KD7 = D2..D9; MK0..MK10 = D22,D24,...,D42;
// BR0..BR10 = D23,D25,...,D43. KD8/D10 is not used by the 88-key
// 8-by-11 matrix described in the model pins.h.
