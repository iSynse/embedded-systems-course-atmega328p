# 🏎️ F1 Steering Wheel — Bare-Metal Embedded C on ATmega328p

> A fully custom Formula 1-inspired steering wheel controller built with pure Embedded C, featuring real-time RPM/speed simulation, LED rev lights, paddle shifters, and a 7-segment gear display — all running on an Arduino Nano (ATmega328p) without any abstraction layers.

---

## 📖 About The Project

This project is a hardware/software deep-dive into bare-metal embedded systems engineering. Inspired by the telemetry interfaces found in real Formula 1 cars, we designed and built a functional steering wheel controller that simulates vehicle speed and RPM data, visualizes the rev range through a WS2812 NeoPixel LED strip, and allows the driver to shift gears via physical paddle shifters — all displayed live on a MAX7219-driven 7-segment display.

The entire firmware is written in **pure Embedded C**, compiled with `avr-gcc`, and targets the **ATmega328p** microcontroller (as found on the Arduino Nano). There is no Arduino IDE, no `digitalWrite()`, no HAL — just registers, timers, and tight control over every hardware peripheral. This approach was chosen to maximize performance, minimize overhead, and demonstrate a professional-grade embedded software architecture.

---

## ✨ Key Features

- **RPM & Speed Simulation** — A dedicated logic module calculates simulated vehicle speed and engine RPM based on current gear and a throttle model, cycling through realistic F1-style rev ranges.
- **LED RPM Gauge (WS2812 NeoPixels)** — A custom bit-banging WS2812 driver illuminates an LED strip in real time, color-coded to reflect RPM zones (green → yellow → red), mimicking the shift lights on an F1 car.
- **Paddle Shifters** — Physical up/down paddle inputs are read through a debounced switch driver, triggering gear-change events in a dedicated state machine.
- **7-Segment Gear Display (MAX7219)** — The current gear is shown on a MAX7219-driven display via a custom SPI driver, providing instant visual feedback to the driver.
- **Modular Driver Architecture** — Hardware drivers (WS2812, MAX7219, switches, encoder) are fully decoupled from application logic, making the codebase easy to extend and port.
- **Rotary Encoder Support** — A rotary encoder driver allows navigation through on-wheel menus or parameter adjustment.
- **Zero Arduino Overhead** — All I/O, SPI, and timing are handled by directly manipulating ATmega328p registers for maximum responsiveness.

---

## 🔧 Hardware Requirements

| Component | Description |
|---|---|
| Arduino Nano (ATmega328p) | Main microcontroller |
| WS2812B LED Strip | RPM shift lights (NeoPixel, configurable count) |
| MAX7219 Module | 7-segment display for gear indication |
| Paddle Shifters (×2) | Momentary push-buttons for up/down gear changes |
| Rotary Encoder | Menu navigation / parameter input |
| Tactile Switches | Additional function buttons |
| 5V Power Supply | Stable supply for LED strip and logic |
| Decoupling Capacitors | 100nF on VCC/GND near IC power pins |
| 300–500 Ω Resistor | On WS2812 data line (signal integrity) |
| 1000 µF Capacitor | Bulk cap across WS2812 power rail |

---

## 🗂️ Software Architecture

The codebase follows a layered embedded software architecture, with a strict separation between hardware drivers, application logic, and system configuration.

```
F1_SteeringWheel_Project/
│
├── F1_SteeringWheel.sln          (Visual Studio Solution)
│
├── src/
│   ├── main.c                    (Main entry point & state machine)
│   ├── config.h                  (Pin definitions & system config)
│   ├── types.h                   (Custom data types & enums)
│   └── system_init.c             (System initialization)
│
├── drivers/
│   ├── ws2812/
│   │   ├── ws2812.h               (NeoPixel driver header)
│   │   └── ws2812.c               (NeoPixel bit-banging implementation)
│   │
│   ├── max7219/
│   │   ├── max7219.h              (7-Segment display driver header)
│   │   └── max7219.c              (SPI interface to MAX7219)
│   │
│   └── input/
│       ├── switches.h             (Switch debouncing & reading)
│       ├── switches.c
│       ├── encoder.h              (Rotary encoder driver)
│       └── encoder.c
│
├── logic/
│   ├── gear_control.h             (Gear state machine)
│   ├── gear_control.c
│   ├── speed_simulation.h         (Speed/RPM calculation logic)
│   └── speed_simulation.c
│
├── lib/                           (Third-party lightweight libraries)
│   └── (Optional: minimal FastLED or custom timing libs)
│
└── docs/
    └── wiring_diagram.png         (Hardware wiring reference)
```

**Layer overview:**

- **`src/`** — Core system files. `main.c` hosts the top-level state machine and main loop. `config.h` is the single source of truth for all pin assignments and compile-time constants. `system_init.c` configures clocks, timers, and peripheral registers at startup.
- **`drivers/`** — Hardware Abstraction. Each peripheral (WS2812, MAX7219, switches, encoder) has its own isolated driver module. The WS2812 driver uses cycle-accurate bit-banging (timing-critical, interrupt-disabled). The MAX7219 driver communicates over a software or hardware SPI implementation.
- **`logic/`** — Application Logic. `gear_control` implements the gear state machine (1–8, neutral, limits). `speed_simulation` computes RPM and speed values fed to the display and LED drivers.
- **`lib/`** — Optional third-party or utility code kept separate from project sources.

---

## ⚡ Wiring & Schematics

The full wiring diagram is available in the `/docs` folder:

```
docs/wiring_diagram.png
```

The diagram covers all connections between the Arduino Nano and the WS2812 LED strip, MAX7219 display module, paddle shifter inputs, rotary encoder, and auxiliary switches — including recommended decoupling capacitor placement and resistor values.

> **Note:** Always power the WS2812 LED strip from a dedicated 5V rail with adequate current capacity (60 mA per LED at full brightness). Do not rely solely on the Arduino's onboard regulator for strips longer than ~8 LEDs.

---

## 🚀 Getting Started / Compilation

### Prerequisites

- [`avr-gcc`](https://gcc.gnu.org/wiki/avr-gcc) and `avr-libc` (AVR toolchain)
- [`avrdude`](https://github.com/avrdudes/avrdude) (flashing utility)
- **OR** Visual Studio with the Visual Micro or similar AVR extension (`.sln` provided)

### Build with avr-gcc (command line)

```bash
# Compile all source files
avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -Wall \
  -Isrc -Idrivers/ws2812 -Idrivers/max7219 -Idrivers/input -Ilogic \
  src/main.c src/system_init.c \
  drivers/ws2812/ws2812.c \
  drivers/max7219/max7219.c \
  drivers/input/switches.c \
  drivers/input/encoder.c \
  logic/gear_control.c \
  logic/speed_simulation.c \
  -o F1_SteeringWheel.elf

# Generate HEX file
avr-objcopy -O ihex -R .eeprom F1_SteeringWheel.elf F1_SteeringWheel.hex

# Flash to Arduino Nano (adjust port as needed)
avrdude -carduino -patmega328p -P/dev/ttyUSB0 -b115200 \
  -U flash:w:F1_SteeringWheel.hex:i
```

### Build with Visual Studio

Open `F1_SteeringWheel.sln` in Visual Studio with the appropriate AVR/embedded extension installed, select the target configuration, and build. Refer to your extension's documentation for flashing options.

---

## 📄 License

This project is released for educational and personal use. See `LICENSE` for details.

---

<p align="center">
  Built with ❤️ and bare-metal C — no Arduino.h was harmed in the making of this project.
</p>
