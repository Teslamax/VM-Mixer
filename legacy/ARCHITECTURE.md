# VM-Mixer / Distributed VoiceMeeter Control Surface Reference

## Overview

This document describes the current architecture and design goals for two related control-surface projects:

1. SinLoon 3-key + rotary encoder USB macropad
2. ANAVI Knobs 3 distributed mixer/control interface

The overall goal is to create a distributed audio-control and service-management system for the homelab/media environment centered around:

- `Haruna` (Windows 11 gaming PC running VoiceMeeter)
- `tovan` (Pi 3B SPDIF → VBAN source for Fire Cube / Samsung TV)
- `zuban` (Pi Zero 2W USB audio → VBAN source for Iona)
- `Iona` (Mac system potentially routed through VBAN)

The architecture intentionally separates:

- physical control devices
- audio transport
- control transport
- VoiceMeeter API orchestration

---

# High-Level Architecture

```text
Physical controls
    ↓
USB / CDC / HID
    ↓
Haruna Python control bridge
    ├─ VoiceMeeter Remote API
    ├─ SSH orchestration
    └─ future status/state management
            ↓
Distributed audio/VBAN systems
```

The Python control service on `Haruna` becomes the central authority for:

- VoiceMeeter strip gain
- mute state
- reset-to-0dB operations
- VBAN source recovery/restart
- future status monitoring
- future LED/status synchronization

---

# VoiceMeeter Integration Philosophy

VoiceMeeter does not expose a native network API.

Therefore:

- physical controls do NOT directly control VoiceMeeter
- a Haruna-side Python bridge is required
- all mixer state/control logic is centralized on Haruna

The Haruna Python bridge will:

- receive semantic control events
- map events to configured audio sources
- issue VoiceMeeter API calls
- optionally issue SSH commands to remote source hosts

---

# Source Model

## Planned Sources

| Logical Source | Audio Path | VoiceMeeter Target | Restart Action |
|---|---|---|---|
| `tovan_tv` | Fire Cube / Samsung TV SPDIF → `tovan` → VBAN | VoiceMeeter VBAN strip | SSH restart `vban_emitter` on `tovan` |
| `haruna_local` | Haruna local/default virtual audio | VoiceMeeter local strip | none |
| `zuban_iona` | Iona USB audio → `zuban` → VBAN | VoiceMeeter VBAN strip | SSH restart `vban_emitter` on `zuban` |

Future sources may be added later.

---

# SinLoon Macropad

## Hardware

Product:

```text
SinLoon Mini Programmable Mechanical Keyboard
3 keys + 1 rotary encoder
```

Observed hardware details:

- Acrylic sandwich construction
- Mechanical switches
- Hot-swappable switches
- CH552G MCU
- Composite USB HID device
- Vendor/config HID interfaces present
- Encoder + keyboard interfaces separated

Identified MCU:

```text
CH552G
```

USB behavior:

- Multiple HID interfaces
- Keyboard interface
- Mouse/encoder interface
- Vendor configuration interface

Linux device mapping observed:

```text
/dev/input/event1
    encoder/media functions

/dev/input/event2
    keypad functions
```

---

# SinLoon Intended Role

The SinLoon device is intended as:

- a first-generation prototype operator panel
- a near-TV control appliance
- a quick-access VBAN/service recovery tool
- a simple VoiceMeeter control frontend

The device is NOT intended to directly implement:

- VoiceMeeter API logic
- SSH orchestration
- source-state management

Instead, Linux/Python layers handle the actual control semantics.

---

# SinLoon Current Key Mapping

## Current Verified Linux Events

### Keypad Buttons

| Physical | Event |
|---|---|
| Key 1 | `KEY_KP1` |
| Key 2 | `KEY_KP2` |
| Key 3 | `KEY_KP3` |

### Encoder

| Physical | Event |
|---|---|
| Rotate Left | `KEY_VOLUMEDOWN` |
| Rotate Right | `KEY_VOLUMEUP` |
| Press | `KEY_MUTE` |

---

# SinLoon Intended Actions

| Physical Control | Intended Action |
|---|---|
| Key 1 | Restart `vban_emitter` on `tovan` |
| Key 2 | Restart WookieBot on `kaiho` |
| Key 3 | Toggle/start-stop WookieBot |
| Encoder Left | VoiceMeeter gain down |
| Encoder Right | VoiceMeeter gain up |
| Encoder Press | VoiceMeeter mute toggle |

---

# SinLoon Linux Handling

Linux will:

- intercept HID events
- optionally exclusively grab the device
- reinterpret events semantically
- prevent accidental desktop/media interaction

Likely implementation:

```text
Python + evdev
```

Expected architecture:

```text
SinLoon HID events
    ↓
Linux evdev daemon
    ↓
Haruna bridge API / SSH / VoiceMeeter
```

---

# ANAVI Knobs 3

## Intended Role

The ANAVI Knobs 3 is intended to become the primary long-term distributed audio-control surface.

Primary functions:

- VoiceMeeter gain control
- mute control
- reset-to-0dB control
- remote VBAN service recovery
- future status indication
- future LED synchronization

The Knobs 3 is expected to supersede the SinLoon device for most mixer functions.

---

# Knobs 3 Interaction Philosophy

The Knobs 3 firmware SHOULD:

- interpret physical gestures locally
- debounce locally
- classify button interactions locally
- emit semantic events

The Haruna bridge SHOULD:

- own all source mappings
- own VoiceMeeter logic
- own SSH orchestration
- own mixer state

This cleanly separates:

```text
Knobs 3:
    "what did the human do?"

Haruna bridge:
    "what does that mean for the audio system?"
```

---

# Knobs 3 Gesture Model

## Per-Knob Interactions

| Gesture | Meaning |
|---|---|
| Rotate | Adjust gain |
| Single press | Mute/unmute |
| Double press | Reset gain to 0.0 dB |
| Long hold | Restart source-side `vban_emitter` |

Suggested timing:

| Action | Timing |
|---|---|
| Debounce | 20–50 ms |
| Double-press window | 250–400 ms |
| Hold threshold | 1.5–2.0 sec |

---

# Knobs 3 Source Assignment

## Knob 1

```text
tovan_tv
```

Controls:

- Fire Cube / Samsung TV VBAN source
- mute
- gain
- reset gain
- restart `vban_emitter` on `tovan`

---

## Knob 2

```text
haruna_local
```

Controls:

- Haruna local/default virtual audio
- mute
- gain
- reset gain

Potential future long-hold behavior:

- restart local audio subsystem
- restart local VoiceMeeter components

---

## Knob 3

```text
zuban_iona
```

Controls:

- Iona USB audio → zuban → VBAN
- mute
- gain
- reset gain
- restart `vban_emitter` on `zuban`

---

# Knobs 3 USB Interface Philosophy

Preferred interface:

```text
USB CDC serial
```

Optional secondary interfaces:

- HID keyboard
- HID media keys
- HID mouse
- HID gamepad

CDC is preferred because:

- semantic events can be transmitted directly
- easy debugging/logging
- structured messages possible
- avoids fake keyboard semantics

---

# Proposed CDC Event Format

Potential JSON-lines style:

```json
{"control":"knob1","event":"rotate","delta":1}
```

```json
{"control":"knob1","event":"press"}
```

```json
{"control":"knob1","event":"double_press"}
```

```json
{"control":"knob1","event":"hold"}
```

---

# Haruna Python Bridge Responsibilities

The Haruna-side Python service becomes the central orchestration layer.

Responsibilities:

## VoiceMeeter API

- gain adjustment
- mute toggling
- reset-to-0dB
- future strip/bus routing
- future state query/reporting

## SSH Orchestration

- restart `vban_emitter` on `tovan`
- restart `vban_emitter` on `zuban`
- future remote actions

## Input Mapping

- map controls to logical sources
- map gestures to semantic actions

## Future Features

- LED state synchronization
- source status monitoring
- reconnect detection
- on-screen status UI
- MQTT/HTTP API expansion
- centralized logging

---

# Example Haruna Bridge Flow

```text
Knob 1 rotated clockwise
    ↓
Knobs 3 sends CDC JSON event
    ↓
Haruna bridge receives event
    ↓
Source map resolves:
    knob1 → tovan_tv
    ↓
VoiceMeeter API:
    strip gain += 0.5 dB
```

---

# Example Remote Restart Flow

```text
Knob 1 long-hold
    ↓
Knobs 3 emits "hold"
    ↓
Haruna bridge resolves:
    tovan_tv
    ↓
SSH command:
    ssh tovan sudo systemctl restart vban_emitter
```

---

# Recommended Linux/Python Technologies

## Linux Side

- `evdev`
- `systemd`
- `ssh`
- optional `udev`

## Haruna Side

- Python 3
- VoiceMeeter Remote API wrapper
- optional Flask/FastAPI
- optional pyserial
- optional asyncio

## Potential Future Additions

- MQTT
- OSC
- WebSocket API
- LED synchronization protocol

---

# Design Philosophy Summary

## Core Principles

- centralized mixer authority
- distributed physical controls
- semantic event transport
- Linux/Python orchestration
- avoid dependency on proprietary HID semantics
- avoid coupling hardware directly to VoiceMeeter
- keep physical devices as relatively dumb frontends

## Overall Goal

Create a modular distributed control-surface architecture for:

- VoiceMeeter
- VBAN infrastructure
- homelab audio routing
- service recovery/orchestration

using inexpensive programmable hardware and lightweight Python orchestration.

