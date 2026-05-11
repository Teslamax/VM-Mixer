#include <MIDI.h>
#pragma once

// Send a MIDI Control Change (CC) message
void send_midi_cc(uint8_t cc_number, uint8_t value);

// Send a MIDI Note On or Note Off message
void send_midi_note(uint8_t note_number, bool on);

// Handle MIDI IN messages from host
void poll_midi_feedback();

void setup_midi();
