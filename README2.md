# 🎛️ VM-Mixer: USB MIDI Controller for VoiceMeeter

**VM-Mixer** is a compact, open-source USB MIDI controller for [VoiceMeeter](https://vb-audio.com/Voicemeeter/) (Windows virtual audio mixer).  
It uses the **ANAVI Knobs 3** hardware (3 clickable rotary encoders + RGB LEDs) powered by the **Seeed Studio XIAO RP2040** microcontroller, running **CircuitPython** + **KMK** firmware.

Primary use: precise control of up to 3 VoiceMeeter strips (e.g., two hardware inputs like mic/hardware + one virtual input for Windows system audio) via gain faders and mute toggles.

## 🔧 Hardware

- **ANAVI Knobs 3**  
  - 3× rotary encoders (incremental/relative, with push-buttons)  
  - RGB LEDs per encoder (for potential visual feedback)  
  - Microcontroller: Seeed Studio XIAO RP2040 (RP2040-based, USB-C)  
- Optional expansions:  
  - I²C OLED display (SSD1306, 128×32 or 128×64) for per-strip status  
  - External GPIO button for manual save/load

**Resources**  
- ANAVI Knobs 3 product page: https://www.anavi.technology/anavi-knobs/  
- Hardware schematics & docs: https://github.com/AnaviTechnology/anavi-knobs-3  
- Seeed XIAO RP2040 wiki: https://wiki.seeedstudio.com/XIAO-RP2040/

## 🎹 Features

- **USB MIDI bidirectional**  
  - Out: MIDI CC (absolute synthetic 0–127) for gain control  
  - Out: MIDI Note On/Off for mute toggle  
  - In: MIDI feedback from VoiceMeeter to sync virtual absolute values (avoids drift)  
- **Encoder button logic**  
  - Short press (< ~600 ms): toggle mute on assigned strip  
  - Long press: reset gain to 0 dB (send fixed CC value, e.g. ~95–105; test exact value)  
- **Relative vs Absolute modes**  
  - Absolute (primary): synthetic tracking + feedback overwrite  
  - Relative (optional): Note triggers (+1/-1 per detent) mapped via Macro Buttons or script for incremental dB steps  
- **Flash storage** (EEPROM-style)  
  - Save/load current gain + mute states (manual trigger or external button)  
- **USB CDC CLI**  
  - Serial console commands: `/help`, `/status`, `/save`, `/load`, `/reset`, etc.  
  - Consistent CLI style for reuse across MCU projects  
- **Future ideas**  
  - OLED for real-time gain/mute display  
  - LED ring animations driven by MIDI feedback  
  - Multi-profile/layer switching

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
--

## ⚙️ MIDI Configuration (VoiceMeeter Side)

- **Mapping dialog**: Menu → M.I.D.I. Mapping → select your device → Learn mode  
- **Recommended assignments** (absolute mode, Channel 1):  
  - Knob 1 Gain → CC#21  
  - Knob 2 Gain → CC#22  
  - Knob 3 Gain → CC#23  
  - Mute toggles → Notes 40–42 (or separate CCs)  
- **Feedback**: Enable 'F' (basic) or 'FF' (advanced) per mapping for bidirectional sync  
- **0 dB reset**: Test by resetting a fader in GUI → observe incoming CC value on feedback (typically ~95–105; depends on "Limit Remote Gain to 0 dBFS" setting)  
- **Resolution**: 7-bit (0–127 steps) via MIDI CC; VoiceMeeter internal gain is floating-point dB (higher precision, quantized on MIDI)  
- **Drift handling**: Feedback overwrites virtual value; long-press reset snaps to tested 0 dB CC  

**Note**: VoiceMeeter prefers absolute CC for gain; relative CC often ignored/jumpy. Use Note triggers + Macro Buttons script (`Strip(x).Gain +=1.5;`) for true relative if desired.

## 🛠️ Setup & Development Notes

1. **Firmware**  
   - Mount CIRCUITPY drive (REPL: `import storage; storage.enable_usb_drive()`)  
   - Install CircuitPython UF2 for XIAO RP2040: https://circuitpython.org/board/seeeduino_xiao_rp2040/  
   - Copy KMK + libraries; edit keymap for MIDI logic  

2. **VoiceMeeter**  
   - Latest version recommended (Dec 2025 manual)  
   - Enable feedback ('F'/'FF') per control  
   - Test with MIDI-OX to verify send/receive  

3. **Style notes**  
   - Modular structure for future Arduino/PlatformIO migration  
   - Shared CLI + settings modules reusable across projects  

## 🔗 Related Resources

- VoiceMeeter: https://vb-audio.com/Voicemeeter/  
- User Manual (Dec 2025): https://vb-audio.com/Voicemeeter/Voicemeeter_UserManual.pdf  
- ANAVI Technology: https://www.anavi.technology/  
- KMK Firmware: https://kmkfw.io/ & https://github.com/KMKfw/kmk_firmware  
- CircuitPython MIDI: https://docs.circuitpython.org/en/latest/shared-bindings/usb_midi  

Happy mixing! 🎧