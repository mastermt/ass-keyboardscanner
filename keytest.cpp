/*
 * ASS Keyboard Scanner — eight-key diagnostic extension
 *
 * Prints raw MAKE/BREAK contact states for a configurable block of eight
 * consecutive keys. It does not call any MIDI function.
 *
 * MIDI output is also suppressed while this diagnostic is compiled in;
 * see midi.cpp.
 */

#include "globals.h"
#include "scanner_debug.h"
#include "extensions.h"

#define KEYTEST_ENABLED 1

static uint8_t previous_make[KEYTEST_KEY_COUNT];
static uint8_t previous_break[KEYTEST_KEY_COUNT];
static bool first_report = true;

void keytestSetup()
{
    for (uint8_t i = 0; i < KEYTEST_KEY_COUNT; ++i)
    {
        previous_make[i] = 0xFF;
        previous_break[i] = 0xFF;
    }

    Serial.println(F("KEYTEST: enabled"));
    Serial.print(F("KEYTEST keys "));
    Serial.print(KEYTEST_FIRST_KEY);
    Serial.print(F(".."));
    Serial.println(KEYTEST_FIRST_KEY + KEYTEST_KEY_COUNT - 1);
}

void keytestLoop()
{
    static uint32_t last_print_ms = 0;
    const uint32_t now = millis();

    if (!first_report &&
        (uint32_t)(now - last_print_ms) < KEYTEST_PRINT_INTERVAL)
        return;

    bool changed = first_report;

    for (uint8_t i = 0; i < KEYTEST_KEY_COUNT; ++i)
    {
        const uint8_t key = KEYTEST_FIRST_KEY + i;
        const uint8_t make = scanner_make_state[key] ? 1 : 0;
        const uint8_t brk  = scanner_break_state[key] ? 1 : 0;

        if (make != previous_make[i] || brk != previous_break[i])
            changed = true;
    }

    if (!changed)
        return;

    Serial.print(F("KEYTEST: "));

    for (uint8_t i = 0; i < KEYTEST_KEY_COUNT; ++i)
    {
        const uint8_t key = KEYTEST_FIRST_KEY + i;
        const uint8_t make = scanner_make_state[key] ? 1 : 0;
        const uint8_t brk  = scanner_break_state[key] ? 1 : 0;

        Serial.print(F("K"));
        Serial.print(key);
        Serial.print(F("="));
        Serial.print(make);
        Serial.print(F("/"));
        Serial.print(brk);

        if (i != KEYTEST_KEY_COUNT - 1)
            Serial.print(F(" "));

        previous_make[i] = make;
        previous_break[i] = brk;
    }

    Serial.println();

    first_report = false;
    last_print_ms = now;
}
