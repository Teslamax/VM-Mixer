# 🎛️ VM-Mixer (CircuitPython + KMK Firmware)

A USB MIDI + CDC mixer controller built on the **ANAVI Knobs 3** with a **Seeed XIAO RP2040**, supporting rotary encoder volume control, mute toggling, 0dB resets, RGB feedback, OLED status, and USB serial CLI.

---

## 📦 Hardware Components

| Component                     | Description                                              |
|-------------------------------|----------------------------------------------------------|
| 🧠 MCU                        | Seeed Studio XIAO RP2040                                 |
| 🎚️ Rotary Encoders (x3)      | Mechanical encoders with pushbutton (20 detents/turn)   |
| 💡 RGB LED                   | Onboard NeoPixel (XIAO RP2040)                          |
| 🖥️ OLED Display              | SSD1306 128x64 I2C (monochrome)                         |
| 🛠️ Custom PCB                | ANAVI Knobs 3 (preassembled and prewired)               |

---

## 🔌 GPIO Pin Usage (Seeed XIAO RP2040)

| Function           | GPIO Pin | KMK / CircuitPython Name                | Notes                                 |
| ------------------ | -------- | --------------------------------------- | ------------------------------------- |
| Encoder 1 A        | D1       | `board.D1`                              |                                       |
| Encoder 1 B        | D2       | `board.D2`                              |                                       |
| Encoder 1 Button   | D0       | `board.D0`                              |                                       |
| Encoder 2 A        | D10      | `board.D10`                             |                                       |
| Encoder 2 B        | D9       | `board.D9`                              |                                       |
| Encoder 2 Button   | D3       | `board.D3`                              |                                       |
| Encoder 3 A        | D8       | `board.D8`                              |                                       |
| Encoder 3 B        | D7       | `board.D7`                              |                                       |
| Encoder 3 Button   | D6       | `board.D6`                              |                                       |
| I2C SDA (OLED)     | D4       | `board.SDA`                             | Shared I2C                            |
| I2C SCL (OLED)     | D5       | `board.SCL`                             | Shared I2C                            |
| NeoPixel (onboard) | D12      | `board.NEOPIXEL`                        | Built-in RGB                          |
| Discrete Red LED   | D13      | `board.D13` or `board.LED_RED` (custom) | Often used as status LED              |
| Discrete Green LED | D11      | `board.D11` or custom                   | Not officially named in CircuitPython |
| Discrete Blue LED  | D14\*    | Not exposed by default                  | Check if routed via PCB/schematic     |

> \*GPIO D14 on the RP2040 chip may not be exposed directly on the Seeed XIAO RP2040. Verify via schematic if wired.

---

## ⚙️ Features

### 🔁 Encoders
- Rotate CW/CCW to increase/decrease volume (MIDI CC)
- Short press: mute toggle (MIDI CC)
- Long press (TBD): reset volume to 0 dB (MIDI CC)

### 🎵 USB MIDI
- Sends MIDI Control Change (CC) messages for:
  - Volume Up/Down (per input)
  - Mute On/Off
  - 0 dB Reset (future)

### 🖧 USB CDC Serial
- Receives commands like `/help`, `/status`, `/rgb on`
- Prints events and debug messages

### 🖥️ OLED Display (SSD1306)
- Displays status feedback, recent commands
- Mirrors USB CLI responses

### 🌈 RGB Feedback
- Onboard NeoPixel shows animation or status color
- Can be enabled/disabled via `/rgb` command

---

## 🖥️ CLI Commands (USB CDC Serial)

Type these into the Arduino Serial Monitor or another terminal:

| Command     | Description                 |
|-------------|-----------------------------|
| `/help`     | Show available commands     |
| `/status`   | Print current state         |
| `/rgb on`   | Enable RGB animation        |
| `/rgb off`  | Disable RGB                 |

---

## 🛠️ Setup

1. Format your board as **CIRCUITPY**
2. Install [KMK Firmware](https://github.com/KMKfw/kmk_firmware)
3. Place `code.py` at the root of `CIRCUITPY/`
4. Create `/lib` and add:
   - `kmk/` core firmware folder
   - Required libraries:
     - `adafruit_display_text`
     - `adafruit_ssd1306`
     - `adafruit_bus_device`

You can download the `lib/` bundle from [Adafruit CircuitPython Library Bundle](https://circuitpython.org/libraries).

---

## 🚧 Roadmap

- [ ] Add long-press detection for 0 dB reset
- [ ] Support save/load volume levels
- [ ] Optional display of active volume per channel
- [ ] USB HID fallback for basic use

---

## 📸 Photos / Diagrams

*(Add photos of your physical build or pin diagram here)*

---

## 💬 Credits

Built using:
- [KMK Firmware](https://github.com/KMKfw/kmk_firmware)
- [Adafruit CircuitPython](https://circuitpython.org/)
- [ANAVI Knobs 3](https://www.crowdsupply.com/anavi-technology/anavi-macro-pad-10)

---

## 🧠 Author

**Ryan Rasmussen**  
_Mixer controller project for VoiceMeeter + MIDI + custom hardware._

