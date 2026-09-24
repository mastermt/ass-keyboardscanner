/*
 * ASS Keyboard Scanner — scan-rate counter extension
 *
 * Reports the number of complete scanner passes observed during the last
 * one-second interval. The count is maintained by scannerLoop(), so this
 * measures complete matrix scans.
 */

#include "globals.h"
#include "scanner_debug.h"

void counterSetup()
{
}

void counterLoop()
{
    static uint32_t last_report_us = 0;
    static uint32_t last_scan_count = 0;

    const uint32_t now = micros();

    if ((uint32_t)(now - last_report_us) < 1000000UL)
        return;

    const uint32_t scans = scannerGetScanCount();
    const uint32_t delta = scans - last_scan_count;

    Serial.print(F("SCAN/s: "));
    Serial.println(delta);

    last_scan_count = scans;
    last_report_us = now;
}
