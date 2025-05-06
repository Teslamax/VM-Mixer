#include "config.h"
#include "input.h"
#include "midi.h"
#include "cli.h"
#include <Arduino.h>

// --- Configuration ---
const int NUM_CHANNELS = 3;
const uint8_t encoderPinsA[NUM_CHANNELS] = {ENC1_A, ENC2_A, ENC3_A};
const uint8_t encoderPinsB[NUM_CHANNELS] = {ENC1_B, ENC2_B, ENC3_B};
const uint8_t buttonPins[NUM_CHANNELS]   = {ENC1_BTN, ENC2_BTN, ENC3_BTN};

const uint8_t ccVolume[NUM_CHANNELS] = {20, 21, 22};
const uint8_t ccMute[NUM_CHANNELS]   = {64, 65, 66};

const uint8_t volumeResetLevel = 100; // ~0dB in many systems
const uint16_t holdThresholdMs = 500;

// --- State ---
int volumeLevel[NUM_CHANNELS] = {100, 100, 100};
bool muteState[NUM_CHANNELS] = {false, false, false};

volatile int lastEncoderState[NUM_CHANNELS] = {0, 0, 0};
unsigned long buttonPressTime[NUM_CHANNELS] = {0, 0, 0};
bool buttonPressed[NUM_CHANNELS] = {false, false, false};
unsigned long saveloadPressTime = 0;
bool saveloadPressed = false;

void sendVolume(uint8_t ch) {
  MIDI.sendControlChange(ccVolume[ch], volumeLevel[ch]);
  logInfo("🎚️ CH%d Volume: %d\n", ch + 1, volumeLevel[ch]);
}

void sendMute(uint8_t ch) {
  MIDI.sendControlChange(ccMute[ch], muteState[ch] ? 127 : 0);
  logInfo("🔇 CH%d Mute %s\n", ch + 1, muteState[ch] ? "ON" : "OFF");
}

void init_inputs() {
  for (int i = 0; i < NUM_CHANNELS; i++) {
    pinMode(encoderPinsA[i], INPUT_PULLUP);
    pinMode(encoderPinsB[i], INPUT_PULLUP);
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastEncoderState[i] = (digitalRead(encoderPinsA[i]) << 1) | digitalRead(encoderPinsB[i]);
  }
}

void update_inputs() {
  for (int i = 0; i < NUM_CHANNELS; i++) {
    // --- Encoder Rotation ---
    int a = digitalRead(encoderPinsA[i]);
    int b = digitalRead(encoderPinsB[i]);
    int state = (a << 1) | b;

    if (state != lastEncoderState[i]) {
      if ((lastEncoderState[i] == 0b00 && state == 0b01) ||
          (lastEncoderState[i] == 0b01 && state == 0b11) ||
          (lastEncoderState[i] == 0b11 && state == 0b10) ||
          (lastEncoderState[i] == 0b10 && state == 0b00)) {
        // Clockwise
        volumeLevel[i] = min(127, volumeLevel[i] + 1);
        sendVolume(i);
      } else {


  // --- Save/Load Button Logic ---
  bool btnDown = (digitalRead(SAVELOAD_BTN) == LOW);

  if (btnDown && !saveloadPressed) {
    saveloadPressed = true;
    saveloadPressTime = millis();
  }

  if (!btnDown && saveloadPressed) {
    unsigned long dur = millis() - saveloadPressTime;
    saveloadPressed = false;

    if (dur >= SAVELOAD_HOLD_MS) {
      logInfo("💾 Saved current state\n");
      // TODO: save_state();
    } else {
      logInfo("📥 Loaded saved state\n");
      // TODO: load_state();
    }
  }
        // Counter-clockwise
        volumeLevel[i] = max(0, volumeLevel[i] - 1);
        sendVolume(i);
      }
      lastEncoderState[i] = state;
    }

    // --- Button Press Detection ---
    bool currentPressed = (digitalRead(buttonPins[i]) == LOW);

    if (currentPressed && !buttonPressed[i]) {
      // Press started
      buttonPressed[i] = true;
      buttonPressTime[i] = millis();
    }

    if (!currentPressed && buttonPressed[i]) {
      // Released
      unsigned long pressDuration = millis() - buttonPressTime[i];
      buttonPressed[i] = false;

      if (pressDuration >= holdThresholdMs) {
        // Long press: reset volume
        volumeLevel[i] = volumeResetLevel;
        sendVolume(i);
        logInfo("🔄 CH%d Reset to 0dB (%d)\n", i + 1, volumeResetLevel);
      } else {
        // Short press: toggle mute
        muteState[i] = !muteState[i];
        sendMute(i);
      }
    }
  }
}
