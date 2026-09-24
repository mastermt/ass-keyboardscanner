/*
 * ASS Keyboard Scanner — optional diagnostic extensions
 *
 * Enable/disable extensions by uncommenting the corresponding EXTENSION()
 * line below. This keeps diagnostics out of the hot scanner path when they
 * are not required.
 */

#ifndef ASS_EXTENSIONS_H
#define ASS_EXTENSIONS_H

/* Count complete scanner passes and print scans/second. */
// EXTENSION(counter)

/*
 * Monitor exactly eight consecutive keys through the serial port.
 *
 * KEYTEST_FIRST_KEY is zero-based:
 *   0 = MIDI note 21 / A0 on the pRP8
 */
#define KEYTEST_FIRST_KEY       0
#define KEYTEST_KEY_COUNT       8
#define KEYTEST_PRINT_INTERVAL  100

/* Uncomment to enable the eight-key diagnostic. */
// EXTENSION(keytest)

#endif
