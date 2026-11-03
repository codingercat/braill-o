# Braill-o

**A playful way to explore and learn Braille, one dot at a time.**

Braill-o is a hands-on Braille learning device built around the idea of learning through play. The initial concept came from **Braille Wordle** taking inspiration from word-guessing games like Wordle and applying the same element of challenge and discovery to Braille learning.

The device uses six tactile switches to represent the six dots of a Braille cell. Users can enter dot combinations, view the corresponding characters on an OLED display, and receive audio feedback.

![Braill-o need assesment](assets/images/need_assesment.png)

## The Device

<!-- Add prototype photograph here -->
![Braill-o prototype](assets/images/prototype.png)

## How it works

- **Braille input:** Six tactile switches represent the six dots of a Braille cell.
- **Visual feedback:** An OLED display shows the decoded character.
- **Audio feedback:** A DFPlayer Mini and speaker provide audio output.
- **Game concept:** The longer-term idea is to build word-based learning activities inspired by Wordle.

## Hardware

- Raspberry Pi Pico (RP2040)
- 6 tactile switches
- OLED display (I2C)
- DFPlayer Mini and speaker
- 3D-printed enclosure

## Firmware

The repository contains the different stages of firmware development:

| Folder | Description |
|---|---|
| `braille_decoder` | Initial Braille character decoder |
| `braille_decoder_oled` | Decoder with OLED display |
| `braille_decoder_oled_dfplayer` | Version integrating audio feedback |

**Platform:** Arduino IDE with the Earle Philhower RP2040 Arduino core.

## Repository Structure

```text
Braill-o/
├── firmware/
│   ├── braille_decoder/
│   ├── braille_decoder_oled/
│   └── braille_decoder_oled_dfplayer/
├── assets/
│   ├── images/
│   └── videos/
├── docs/
└── README.md
```

---

*An ongoing exploration of making Braille learning more interactive, accessible, and engaging.*