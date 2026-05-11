// VM-Mixer.ino - USB MIDI Volume Controller
// Adapted from Proto-HID
// Hardware: Rotary Encoders + Optional Buttons (e.g., NeoKey)
// Features: USB MIDI, USB CDC CLI

#include "src/cli.h"
#include "src/midi.h"
#include "src/input.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  cli_parser_init();   // Initialize serial CLI
  setup_midi();         // Initialize MIDI over USB
  init_inputs();       // Initialize encoders/buttons (not implemented yet)
}

void loop() {
  update_inputs();     // Poll inputs (stub)
  cli_parser_update(); // Handle CLI commands
  poll_midi_feedback(); // Check for MIDI IN messages
}
