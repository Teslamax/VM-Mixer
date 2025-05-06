#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
#include <Arduino.h>
#include "midi.h"
#include "cli.h"

void send_midi_cc(uint8_t cc_number, uint8_t value) {
  MIDI.sendControlChange(cc_number, value, 1);  // channel 1
  logInfo("MIDI CC Sent: CC%d -> %d", cc_number, value);
}

void send_midi_note(uint8_t note_number, bool on) {
  if (on) {
    MIDI.sendNoteOn(note_number, 127, 1);  // velocity 127 on channel 1
    logInfo("MIDI Note On Sent: Note %d", note_number);
  } else {
    MIDI.sendNoteOff(note_number, 0, 1);   // velocity 0 on channel 1
    logInfo("MIDI Note Off Sent: Note %d", note_number);
  }
}

void poll_midi_feedback() {
  if (MIDI.read()) {
    // Handle incoming MIDI if needed
    auto type = MIDI.getType();
    if (type == midi::ControlChange) {
      uint8_t cc = MIDI.getData1();
      uint8_t value = MIDI.getData2();
      logInfo("MIDI IN: CC%d -> %d", cc, value);
    } else if (type == midi::NoteOn || type == midi::NoteOff) {
      uint8_t note = MIDI.getData1();
      uint8_t velocity = MIDI.getData2();
      logInfo("MIDI IN: %s Note %d Vel %d", (type == midi::NoteOn ? "On" : "Off"), note, velocity);
    }
  }
}

void setup_midi() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
}
