// midi_manager.cpp - Handles sending MIDI messages for Proto-HID
#include <Arduino.h>
#include "MIDIUSB.h"
#include "midi_manager.h"
#include "cli.h"

void send_midi_cc(uint8_t cc_number, uint8_t value) {
  midiEventPacket_t event = {0x0B, 0xB0, cc_number, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
  logInfo("MIDI CC Sent: CC%d -> %d", cc_number, value);
}

void send_midi_note(uint8_t note_number, bool on) {
  if (on) {
    midiEventPacket_t noteOn = {0x09, 0x90, note_number, 127};
    MidiUSB.sendMIDI(noteOn);
    logInfo("MIDI Note On Sent: Note %d", note_number);
  } else {
    midiEventPacket_t noteOff = {0x08, 0x80, note_number, 0};
    MidiUSB.sendMIDI(noteOff);
    logInfo("MIDI Note Off Sent: Note %d", note_number);
  }
  MidiUSB.flush();
}
