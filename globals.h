/*
 * ASS Keyboard Scanner — shared configuration
 * Target: ATmega2560
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#ifndef ASS_GLOBALS_H
#define ASS_GLOBALS_H

#include <Arduino.h>

/*
 * Select an instrument model by supplying MODEL_NAME in the build flags
 * or changing the default below once its model directory is imported.
 *
 * Example: -DMODEL_NAME=general_music_prp8
 */
#ifndef MODEL_NAME
#define MODEL_NAME general_music_prp8
#endif

#ifndef SERIAL_SPEED
#define SERIAL_SPEED 31250UL
#endif

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define MODEL_HEADER_PATH models/MODEL_NAME/model.h

/*
 * Model header is intentionally included only after the model files have
 * been added. This keeps the source tree's model-based configuration pattern.
 */
#if __has_include(STR(MODEL_HEADER_PATH))
#include STR(MODEL_HEADER_PATH)
#else
#warning "Selected model header is missing; import the model directory before building."
#ifndef KEYS_NUMBER
#define KEYS_NUMBER 0
#endif
#endif

void scannerSetup();
void scannerLoop();
void statesLoop();
void sendKeyEvent(byte status_byte, byte key_index, unsigned long time);
void sendSustainPedalEvent(boolean pressed);
void sendMidiEvent(byte status_byte, byte data1, byte data2);

#endif
