Project Reference: ANAVI Knobs 3 + Voicemeeter USB MIDI Controller
Project Overview
Custom USB MIDI controller using ANAVI Knobs 3 hardware (3 clickable rotary encoders powered by Seeed Studio XIAO RP2040) running CircuitPython + KMK firmware. Configured to control Voicemeeter virtual audio mixer strips (gain faders, mutes, etc.) for real-time sound mixing (e.g., mic, game, music channels).
Hardware
•  Device: ANAVI Knobs 3
	•  3 rotary encoders (relative/incremental, clickable buttons)
	•  RGB LEDs per encoder
	•  Microcontroller: Seeed Studio XIAO RP2040 (Raspberry Pi RP2040-based)
	•  Connection: USB-C (emulates USB MIDI device)
•  Open-source hardware designs: GitHub - AnaviTechnology/anavi-knobs-3
•  Documentation & build guide: ANAVI Docs - Macro Pad 10 / Knobs 3 / Knob 1
Firmware
•  Base: CircuitPython (preloaded on device)
•  Keyboard framework: KMK (open-source, Python-based firmware for mechanical keyboards)
	•  GitHub: KMKfw/kmk_firmware (ANAVI-specific board support in /boards/anavi/knobs3)
•  Key libraries: usb_midi, adafruit_midi, rotaryio / KMK EncoderHandler, adafruit_debouncer (for button press detection)
•  Custom behaviors:
	•  Rotation → MIDI Control Change (CC) absolute (synthetic 0–127 tracking) or Note triggers (relative +1/-1)
	•  Button short press → mute/unmute (Note On/Off or CC toggle)
	•  Button long press → reset to 0 dB (send fixed CC value for unity gain)
	•  Bidirectional sync: Receive MIDI feedback from Voicemeeter to update virtual absolute values
Software Integration: Voicemeeter
•  Application: Voicemeeter (Standard/Banana/Potato versions; tested concepts apply across)
•  Official site & downloads: vb-audio.com/Voicemeeter
•  User Manual (latest Dec 2025): Voicemeeter User Manual PDF (covers M.I.D.I. Mapping on pp. 82–84)
•  MIDI features used:
	•  M.I.D.I. Mapping dialog (Menu > M.I.D.I. Mapping) with Learn mode
	•  Assign incoming CC (absolute) or Note (relative triggers) to parameters: Gain Slider (Strip #), Mute, Solo, Bus A/B sends
	•  Bidirectional feedback: Enable ‘F’ (basic) or ‘FF’ (double) per mapping → Voicemeeter sends updated CC back on parameter change (mouse, script, or incoming MIDI)
	•  MIDI output device selection for feedback (often same as input for bidirectional USB MIDI)
MIDI Configuration Details
•  Protocol: USB MIDI Class Compliant (no drivers needed on Windows)
•  Channel: Typically Channel 1 (0 in 0-based code) for all controls
•  Suggested CC assignments (absolute mode):
	•  Knob 1 Gain → CC#21
	•  Knob 2 Gain → CC#22
	•  Knob 3 Gain → CC#23
	•  Avoid reserved: CC#7 (standard volume), CC#1 (modulation), etc.
•  Relative mode alternative: Note On triggers (e.g., Note 61 = +1/CW, Note 62 = -1/CCW per knob)
	•  Map to same Gain parameter (if Learn supports multi) or bridge via Macro Buttons script (Strip(x).Gain += 1.5;)
•  0 dB reset value: ~95–105 (test: reset fader in Voicemeeter → observe feedback CC value)
•  Resolution: 7-bit (0–127 steps) for MIDI CC; internal Voicemeeter gain is floating-point dB (higher precision, but quantized on MIDI)
•  Drift mitigation:
	•  Feedback overwrites virtual value on receive
	•  Long-press reset forces to tested 0 dB CC value
Setup Steps Summary
1.  Mount CIRCUITPY drive (if hidden: REPL import storage; storage.enable_usb_drive())
2.  Edit KMK keymap/code.py: Add MIDI send/receive, encoder handlers, button debounce/long-press logic
3.  In Voicemeeter: Menu > M.I.D.I. Mapping → select input device → Learn mappings → enable ‘F’/‘FF’ for feedback
4.  Test: Use MIDI-OX for message verification; monitor gain sliders on rotation/mouse adjust
5.  Optional: Macro Buttons for advanced scripting (e.g., relative += via Notes)
References & Sources
•  ANAVI Knobs 3 GitHub: https://github.com/AnaviTechnology/anavi-knobs-3
•  KMK Firmware Docs: https://kmkfw.io/
•  Voicemeeter User Manual (Dec 2025): https://vb-audio.com/Voicemeeter/Voicemeeter_UserManual.pdf
•  Voicemeeter MIDI Feedback Discussion: VB-Audio Forum threads (e.g., 2021 updates on bidirectional control)
•  CircuitPython MIDI Libs: https://circuitpython.org/libraries (adafruit_midi, usb_midi)
This reference is tailored to your specific goals (relative encoders → Voicemeeter mixer control with bidirectional sync and reset). Feel free to copy-paste into a README.md or notes file—let me know if you want expansions (e.g., full code template, diagram, or version-specific tweaks)!