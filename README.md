# 🎛️ VM-Mixer: Distributed VoiceMeeter + VBAN Control Infrastructure

**VM-Mixer** is a distributed VoiceMeeter + VBAN control infrastructure project built around physical control devices, Python orchestration, and the VoiceMeeter Remote API.

It uses:

- **ANAVI Knobs 3**
- **SinLoon macropad**
- **CircuitPython**
- **Python orchestration**
- **VoiceMeeter Remote API**
- **SSH-based service orchestration**

---

## 🎚️ Core Concepts

- **Centralized mixer authority** on `Haruna`
- **Distributed physical control devices**
- **VBAN audio routing**
- **Semantic event transport**
- **Hardware abstraction**

---

## 📦 Major Components

- `haruna-bridge/`
  - VoiceMeeter + SSH orchestration service

- `devices/anavi-knobs3/`
  - Primary long-term control surface

- `devices/sinloon/`
  - Prototype operator panel

- `docs/`
  - Architecture and deployment documentation

---

## 🔗 Related Projects & References

- [VoiceMeeter by VB-Audio](https://vb-audio.com/Voicemeeter/)
- [VBAN by VB-Audio](https://vb-audio.com/Voicemeeter/vban.htm)
- [VoiceMeeter Remote API / VBVMR](https://forum.vb-audio.com/viewtopic.php?t=346)
- [voicemeeter-api Python package](https://pypi.org/project/voicemeeter-api/)
- [ANAVI Knobs 3](https://lectronz.com/products/anavi-knobs-3)
- [ANAVI Knobs 3 hardware docs](https://github.com/AnaviTechnology/anavi-knobs-3)
- [CircuitPython](https://circuitpython.org/)
- [CircuitPython documentation](https://docs.circuitpython.org/en/latest/README.html)
- [Python](https://www.python.org/)
- [CH552G macropad firmware references](https://github.com/topics/ch552g)
