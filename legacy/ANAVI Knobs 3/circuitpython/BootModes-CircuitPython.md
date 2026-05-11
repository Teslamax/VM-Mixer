# 🛡️ CircuitPython Boot Modes & Drive Protection

This file documents how to safely configure the `boot.py` script on a CircuitPython-compatible board (such as the Seeed XIAO RP2040) to **control access to the `CIRCUITPY` USB mass storage drive**. This is useful for:

- Preventing accidental deletion/modification
- Reducing filesystem corruption risk
- Providing a "safe mode" or development toggle behavior

---

## 🔧 Option 1: Disable USB Drive (Mass Storage)

This prevents `CIRCUITPY` from showing up as a USB drive.

```python
# boot.py
import storage

storage.disable_usb_drive()
```

`CIRCUITPY` will still run `code.py`, and USB CDC/MIDI/HID features will work.

⸻

🧰 Option 2: Conditional Drive Mount (e.g., with Button Press)

You can make `CIRCUITPY` mount only when a physical button is pressed during boot.

```python
# boot.py
import board
import digitalio
import storage

# Define input pin (example: Encoder Button 1 on D0)
button = digitalio.DigitalInOut(board.D0)
button.switch_to_input(pull=digitalio.Pull.UP)

if not button.value:
    storage.enable_usb_drive()   # Mount if button held LOW
else:
    storage.disable_usb_drive()  # Disable otherwise
```

Replace `board.D0` with any usable GPIO pin tied to a button or jumper.

⸻

♻️ Re-Enabling `CIRCUITPY` Access

To remount the USB drive:
	•	Double-press the reset button to enter UF2 Bootloader mode
	•	Update or comment out `boot.py`
	•	Or reboot the board while holding the designated button (if using Option 2)

⸻

📁 Notes
	•	`boot.py` runs before `code.py`, during board startup.
	•	Changes to boot.py require a power cycle or reset to take effect.
	•	If `CIRCUITPY` becomes corrupted, connect in UF2 mode and re-flash CircuitPython.

⸻

✅ Recommended Use

| Mode |	Use Case |
|------|-----------|
| Always Disabled	|  Permanent installation or embedded use  |
| Conditional Mount  |	Developer mode toggle via button press |
| Always Enabled  |	Default behavior (safe for development) |

> Let me know if you'd like it tailored for your VM-Mixer project specifically or paired with a `boot.py` generator.
