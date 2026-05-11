# VM-Mixer Architecture

## Philosophy

Physical controls are separated from mixer logic.

The Haruna bridge acts as:
- VoiceMeeter authority
- SSH orchestrator
- source mapper
- semantic event processor

## Audio Paths

- Fire Cube / TV -> tovan -> VBAN -> Haruna
- Iona USB audio -> zuban -> VBAN -> Haruna
- Haruna local virtual audio

## Control Paths

Control devices emit semantic events:
- rotate
- press
- double_press
- hold

These are interpreted by the Haruna bridge.
