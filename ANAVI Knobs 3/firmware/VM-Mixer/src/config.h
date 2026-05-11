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

// Save/Load Button
#define SAVELOAD_BTN 9
#define SAVELOAD_HOLD_MS 500

// CLI defines
#define FIRMWARE_NAME "VM-Mixer"
#define FIRMWARE_VERSION "0-b1 (dev)"
#define FIRMWARE_DESCRIPTION "USB MIDI/CDC Mixer Control"
#define FIRMWARE_BOOT_MSG "VM-Mixer ready. Type /help for commands."

// ———————————————————————————————
// User‑echo compile‑time defaults
#define ECHO_USER_INITIAL  true
#define ECHO_USER_PREFIX   "➡️ "
//#define PI_ECHO_PREFIX     "🐧 "

// ————— CDC Log‑Level Prefixes —————
#define CDC_INFO_PREFIX    "ℹ️  "   // informational
#define CDC_WARN_PREFIX    "⚠️  "   // warnings
#define CDC_ERROR_PREFIX   "❌ "    // errors
#define CDC_VERBOSE_PREFIX "🔍 "   // verbose/debug

// more stuff
#define LED_PIN 13
#define LED_BLINK_ENABLED true


