# ASS Keyboard Scanner

Assembly-oriented AVR implementation of [Moura's Keyboard Scanner](https://github.com/mastermt/keyboardscanner), targeting the **Arduino Mega 2560 / ATmega2560**.

> Status: initial porting foundation. The AVR assembly primitives in this repository are experimental and have not yet been validated on physical keyboard hardware. Do not treat this initial revision as a drop-in replacement for the original firmware until the matrix wiring, timing, MIDI output, and velocity behavior have been tested on the target instrument.

## Goals

- Preserve the original project's model-oriented, modular organization.
- Move carefully selected, timing-critical matrix operations into AVR assembly.
- Keep key-state handling, velocity curves, sustain, MIDI events, and optional UI/extensions modular.
- Document hardware assumptions and provide a repeatable validation process.

## Hardware and toolchain

- Board: Arduino Mega 2560 Rev3
- MCU: ATmega2560, AVR 8-bit, nominal 16 MHz
- Build environment: Arduino IDE or Arduino CLI with the Arduino AVR core
- Assembly syntax: GNU AVR assembler, preprocessed by the AVR-GCC toolchain

The code must be built for **Mega 2560**, not Uno/ATmega328P. Port mappings and register addresses differ between MCUs.

## Repository layout

| Path | Responsibility |
|---|---|
| `keyboardscanner.ino` | Arduino entry point and module lifecycle |
| `globals.h` | Shared declarations and selected model |
| `scanner.cpp` | Scanner setup and high-level matrix scanning |
| `scanner_avr.S` | AVR assembly primitives (experimental) |
| `scanner_avr.h` | C/C++ interface to assembly |
| `states.cpp` | Per-key state machine, velocity timing, sustain |
| `midi.cpp` | MIDI event and velocity conversion |
| `models/` | Instrument-specific pin maps and parameters |
| `extensions.h`, `ui_*` | Optional original extensions/UI modules |

The first revision establishes the assembly interface and porting notes. The original project's remaining modules and instrument model files are being brought across in staged commits so behavior can be checked rather than silently changed.

## Performance strategy

1. Use fixed, compile-time port mappings wherever the selected keyboard's wiring permits it.
2. Keep the scan path free of Arduino `digitalRead()` / `digitalWrite()` calls where direct register access is safe.
3. Minimize per-row overhead and only run key-state transitions for changed matrix bits.
4. Measure scan rate and event latency with a logic analyzer or oscilloscope; do not infer performance solely from instruction counts.
5. Preserve a readable C++ reference path for debugging and unsupported mappings.

### Safety and electrical notes

- Verify the keybed matrix with a multimeter before connecting it.
- Confirm the original keyboard's matrix voltage and current; do not assume all keybeds are 5 V tolerant.
- Use suitable series resistors/level shifting where required. Never connect unknown voltages directly to the Mega.
- Configure only the selected row pins as outputs and never drive opposing matrix lines simultaneously.
- Test with MIDI debug output disabled when measuring scan timing; serial text output materially changes timing.

## Build and validation

This repository's initial assembly primitives are not yet a complete, hardware-validated firmware port. Before using it live:

- [ ] Copy/verify the correct model's `pins.h` and `model.h`.
- [ ] Confirm every row and column against the physical wiring.
- [ ] Compile for Arduino Mega 2560 (ATmega2560).
- [ ] Check generated assembly/listing and SRAM/flash use.
- [ ] Verify Note On/Off, sustain, velocity range, and simultaneous notes.
- [ ] Measure full matrix scan rate and worst-case event latency.
- [ ] Compare output against the original C++ implementation.

## Upstream and license

Original project: https://github.com/mastermt/keyboardscanner

The upstream project is licensed under the GNU General Public License, version 3 or (at your option) any later version. This derivative is distributed under the same terms. See [LICENSE](LICENSE).
