# 🎛️ VM-Mixer: USB MIDI Controller for VoiceMeeter

**VM-Mixer** is a modular, USB MIDI-based controller designed for use with [VoiceMeeter](https://vb-audio.com/Voicemeeter/) on Windows. It is built around the **Seeed XIAO RP2040** microcontroller and designed to work with the **ANAVI Knobs 3** board (3 rotary encoders with push-buttons).

This controller enables precise volume (gain) control and mute toggling for up to three VoiceMeeter strips: two hardware inputs and one virtual input (Windows system audio).

---

## 🔧 Hardware

- [ANAVI Knobs 3](https://www.anavi.technology/anavi-knobs/)
  - [Seeed XIAO RP2040](https://wiki.seeedstudio.com/XIAO-RP2040/)
  - 3x Rotary encoders (w/ push-buttons)
- Optional:
  - OLED display via I²C (SSD1306, 128x32 or 128x64)
  - External button for manual save/load

---

## 🎹 Features

- **USB MIDI IN/OUT**
  - MIDI CC messages for volume control (CC 20–22)
  - MIDI NoteOn messages for mute toggle (Note 40–42)
  - Receives MIDI IN to synchronize state with VoiceMeeter
- **Push button logic**
  - Short press = mute toggle
  - Long press = reset volume to 0 dB (CC value 64)
- **EEPROM-style flash storage**
  - Save/load volume and mute state manually
  - Storage triggered only by command or external button
- **USB CDC CLI interface**
  - `/help`, `/status`, `/save`, `/load`, `/reset`, and more
  - Shared CLI structure across MCU projects

---

## 📦 Project Structure

```
VM-Mixer/
├── firmware/
│   └── VM-Mixer/
│       ├── VM-Mixer.ino            # Arduino main sketch
│       ├── src/
│       │   ├── cli.cpp/.h          # CDC CLI command handling
│       │   ├── midi.cpp/.h         # USB MIDI IN/OUT logic
│       │   ├── encoders.cpp/.h     # Encoder handling
│       │   ├── buttons.cpp/.h      # External GPIO buttons
│       │   ├── settings.cpp/.h     # Flash storage
│       │   ├── display.cpp/.h      # OLED display logic (stubbed)
│       │   └── config.h            # Global config/constants
│       └── platformio.ini          # Optional PlatformIO support
```

---

## 🚀 Future Expansion Ideas

- OLED screen for per-strip status (gain level, mute indicator)
- Rotary encoder LED rings
- MIDI feedback-driven light or display animations
- Multi-profile support (HID mode, gamepad, etc.)

---

## 🛠️ Development Notes

This project uses Arduino IDE structure but follows a modular layout to simplify future PlatformIO migration. All MCU behavior (MIDI, CLI, settings) is reusable in other projects via shared code style and common modules.

---

## 🔗 Related Projects

- [VoiceMeeter by VB-Audio](https://vb-audio.com/Voicemeeter/)
- [ANAVI Technology](https://www.anavi.technology/)
- [Seeed XIAO RP2040 Wiki](https://wiki.seeedstudio.com/XIAO-RP2040/)
