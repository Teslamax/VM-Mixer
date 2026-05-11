# VM-Mixer

Distributed VoiceMeeter + VBAN control infrastructure using:
- ANAVI Knobs 3
- SinLoon macropad
- CircuitPython
- Python orchestration
- VoiceMeeter Remote API
- SSH-based service orchestration

## Core Concepts

- Centralized mixer authority on `Haruna`
- Distributed physical control devices
- VBAN audio routing
- Semantic event transport
- Hardware abstraction

## Major Components

- `haruna-bridge/`
  - VoiceMeeter + SSH orchestration service

- `devices/anavi-knobs3/`
  - Primary long-term control surface

- `devices/sinloon/`
  - Prototype operator panel

- `docs/`
  - Architecture and deployment documentation
