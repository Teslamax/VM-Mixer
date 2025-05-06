#pragma once

// MIDI CC Mappings
#define CC_VOL_INPUT_1 20
#define CC_VOL_INPUT_2 21
#define CC_VOL_VIRTUAL 22

#define CC_MUTE_INPUT_1 64
#define CC_MUTE_INPUT_2 65
#define CC_MUTE_VIRTUAL 66

// Volume Level Constants
#define VOLUME_MIN     0
#define VOLUME_MAX     127
#define VOLUME_RESET   100  // 0 dB default reset level

// Timing Constants
#define HOLD_THRESHOLD_MS 500  // Press duration threshold for reset


// GPIO Assignments for ANAVI Knobs 3 (Seeed XIAO RP2040)
#define ENC1_A 0  // D0
#define ENC1_B 1  // D1
#define ENC1_BTN 2  // D2

#define ENC2_A 3  // D3
#define ENC2_B 4  // D4
#define ENC2_BTN 5  // D5

#define ENC3_A 6  // D6
#define ENC3_B 7  // D7
#define ENC3_BTN 8  // D8


// === Optional External Save/Load Button ===
#define ENABLE_SAVELOAD_BUTTON   1   // Set to 0 to disable this feature
#define PIN_SAVELOAD_BUTTON      9   // GPIO pin for external button
