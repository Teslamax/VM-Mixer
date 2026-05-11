import board
import time
import supervisor

# KMK Core
from kmk.kmk_keyboard import KMKKeyboard
from kmk.scanners.keypad import KeysScanner
from kmk.keys import KC
from kmk.modules.encoder import EncoderHandler
from kmk.extensions.media_keys import MediaKeys
from kmk.extensions.RGB import RGB, AnimationModes

# OLED
import displayio
import terminalio
from adafruit_display_text import label
import adafruit_ssd1306

# ─────────────────────────────────────────────
# 🧠 INIT: Keyboard
# ─────────────────────────────────────────────
keyboard = KMKKeyboard()
keyboard.matrix = KeysScanner([])

# ─────────────────────────────────────────────
# 🔁 ENCODERS (A, B, BTN)
# ─────────────────────────────────────────────
encoder = EncoderHandler()
encoder.divisor = 2
encoder.pins = (
    (board.D1, board.D2, board.D0),   # Encoder 1
    (board.D9, board.D10, board.D3),  # Encoder 2
    (board.D7, board.D8, board.D6),   # Encoder 3
)
encoder.map = (
    (KC.VOLD, KC.VOLU, KC.MUTE),  # Encoder 1
    (KC.UP, KC.DOWN, KC.A),       # Encoder 2
    (KC.RIGHT, KC.LEFT, KC.B),    # Encoder 3
)
keyboard.modules.append(encoder)

# ─────────────────────────────────────────────
# 🔊 MEDIA KEYS
# ─────────────────────────────────────────────
keyboard.extensions.append(MediaKeys())

# ─────────────────────────────────────────────
# 🌈 RGB LED on XIAO-RP2040 (NeoPixel)
# ─────────────────────────────────────────────
rgb = RGB(
    pixel_pin=board.NEOPIXEL,
    num_pixels=1,
    val_limit=100,
    val_default=25,
    animation_mode=AnimationModes.RAINBOW,
)
keyboard.extensions.append(rgb)

# ─────────────────────────────────────────────
# ⌨️ Fallback keymap
# ─────────────────────────────────────────────
keyboard.keymap = [[KC.MUTE]]

# ─────────────────────────────────────────────
# 🖥️ OLED DISPLAY SETUP
# ─────────────────────────────────────────────
WIDTH, HEIGHT = 128, 64
i2c = board.I2C()
display_bus = displayio.I2CDisplay(i2c, device_address=0x3C)
oled = adafruit_ssd1306.SSD1306(display_bus, width=WIDTH, height=HEIGHT)

oled_group = displayio.Group()
oled_label = label.Label(terminalio.FONT, text="", x=0, y=10)
oled_group.append(oled_label)
oled.show(oled_group)

def oled_print(text, clear=True):
    if clear:
        oled_label.text = ""
    oled_label.text = text[:40]  # limit display width

# ─────────────────────────────────────────────
# 🖧 USB CDC CLI
# ─────────────────────────────────────────────
print("ANAVI Knobs 3 VM-Mixer ready. Type /help")
oled_print("VM-Mixer Ready")

def handle_cli_command(cmd):
    cmd = cmd.strip().lower()
    if cmd == "/help":
        print("Available: /help, /status, /rgb <on|off>")
        oled_print("Help: /status /rgb on|off")
    elif cmd == "/status":
        print("Encoders OK. RGB On.")
        oled_print("Status: RGB On")
    elif cmd.startswith("/rgb"):
        parts = cmd.split()
        if len(parts) == 2:
            if parts[1] == "off":
                rgb.disable()
                print("RGB disabled")
                oled_print("RGB Off")
            elif parts[1] == "on":
                rgb.enable()
                print("RGB enabled")
                oled_print("RGB On")
            else:
                print("Use /rgb on or /rgb off")
                oled_print("Usage: /rgb on|off")
        else:
            print("Missing arg: /rgb on|off")
            oled_print("Usage: /rgb on|off")
    else:
        print(f"Unknown: {cmd}")
        oled_print("Unknown cmd")

# CDC command processor
def cli_loop():
    if supervisor.runtime.serial_bytes_available:
        try:
            cmd = input().strip()
            handle_cli_command(cmd)
        except Exception as e:
            print("Error:", e)
            oled_print("Input Error")

# ─────────────────────────────────────────────
# 🚀 MAIN
# ─────────────────────────────────────────────
if __name__ == '__main__':
    keyboard.go(before_matrix_scan=lambda: cli_loop())
