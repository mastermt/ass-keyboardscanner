/*
 * ASS Keyboard Scanner — GeneralMusic pRP8 matrix scanner
 * Target: Arduino Mega 2560 / ATmega2560
 *
 * Physical matrix, following the pRP8 wiring diagram:
 *   KD0..KD7: Arduino D2..D9 (active-low scan outputs)
 *   MK0..MK10: D22,D24,...,D42 (MAKE contact inputs)
 *   BR0..BR10: D23,D25,...,D43 (BREAK contact inputs)
 *
 * The original schematic also labels KD8 on D10. The 88-key matrix
 * definition in pins.h is eight KD lines by eleven groups, so KD8 is not
 * part of the 88-key scan and is intentionally left untouched.
 *
 * Each completed scan updates 88 MAKE and 88 BREAK states, then increments
 * scanner_scan_count once. MIDI/state handling remains outside this module.
 */

#include "globals.h"
#include "scanner_avr.h"
#include "scanner_debug.h"

volatile uint8_t scanner_make_state[KEYS_NUMBER] = {0};
volatile uint8_t scanner_break_state[KEYS_NUMBER] = {0};

static volatile uint32_t scanner_scan_count = 0;

static const uint8_t kd_pins[8] = {
    2, 3, 4, 5, 6, 7, 8, 9
};

/* MK0..MK10 are on the even-numbered pins 22..42. */
static const uint8_t mk_pins[11] = {
    22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42
};

/* BR0..BR10 are on the odd-numbered pins 23..43. */
static const uint8_t br_pins[11] = {
    23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43
};

static volatile uint8_t *kd_port[8];
static uint8_t kd_mask[8];
static volatile uint8_t *mk_input[11];
static uint8_t mk_mask[11];
static volatile uint8_t *br_input[11];
static uint8_t br_mask[11];

static void cachePin(uint8_t pin,
                     volatile uint8_t **input_register,
                     uint8_t *mask)
{
    const uint8_t port = digitalPinToPort(pin);
    *input_register = portInputRegister(port);
    *mask = digitalPinToBitMask(pin);
}

uint32_t scannerGetScanCount(void)
{
    noInterrupts();
    const uint32_t count = scanner_scan_count;
    interrupts();
    return count;
}

void scannerSetup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    /* Initialize KD scan outputs inactive (HIGH) before scanning. */
    for (uint8_t i = 0; i < 8; ++i)
    {
        const uint8_t pin = kd_pins[i];
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);

        const uint8_t port = digitalPinToPort(pin);
        kd_port[i] = portOutputRegister(port);
        kd_mask[i] = digitalPinToBitMask(pin);
    }

    /* All 22 contact lines use internal pull-ups; closed = LOW. */
    for (uint8_t i = 0; i < 11; ++i)
    {
        pinMode(mk_pins[i], INPUT_PULLUP);
        pinMode(br_pins[i], INPUT_PULLUP);

        cachePin(mk_pins[i], &mk_input[i], &mk_mask[i]);
        cachePin(br_pins[i], &br_input[i], &br_mask[i]);
    }

    pinMode(SUSTAIN_PEDAL_PIN, INPUT_PULLUP);
}

void scannerLoop()
{
    /*
     * Matrix organization is group-major: 11 groups × 8 KD lines.
     * The key index is group*8 + KD index, matching the model's pins.h.
     */
    for (uint8_t group = 0; group < 11; ++group)
    {
        const uint8_t make_pin = group;
        const uint8_t break_pin = group;

        for (uint8_t kd = 0; kd < 8; ++kd)
        {
            const uint8_t key = (uint8_t)(group * 8 + kd);

            scanner_make_state[key] =
                scanner_avr_read_contact(kd_port[kd], kd_mask[kd],
                                         mk_input[make_pin], mk_mask[make_pin]);

            scanner_break_state[key] =
                scanner_avr_read_contact(kd_port[kd], kd_mask[kd],
                                         br_input[break_pin], br_mask[break_pin]);
        }
    }

    ++scanner_scan_count;
}
