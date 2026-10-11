# Brink PCB

**English** · [Nederlands](README.nl.md)

An ESP32 controller for the switch inputs of a **Brink Renovent Excellent 300/400** and two **Brink Elan E** zones. The PCB brings together three device connections, nine relay control signals, and circuitry intended for filter indication. ESPHome can connect the controls to Home Assistant.

> **Project status — 11 October 2026**  
> The existing ESPHome and relay setup is the practical starting point. The PCB design and additional functions shared here have not been validated as a complete assembled board. Verify the schematic, parts, wiring, filter inputs, and power-on behaviour before connecting equipment.

## Repository map

| Path | Contents |
| --- | --- |
| [`hardware/rev-2026-10-11/`](hardware/rev-2026-10-11/) | Schematic, bill of materials, Gerbers, and PCB layer images for the supplied revision |
| [`docs/artikelen/`](docs/artikelen/) | Three Dutch articles about the Renovent, RJ12/ESPHome, and the PCB |
| [`docs/hardware.md`](docs/hardware.md) | Connections, project status, and checks before assembly (Dutch) |
| [`docs/firmware.md`](docs/firmware.md) | Notes on the supplied ESPHome configuration (Dutch) |
| [`firmware/esphome-web-d0df24.example.yaml`](firmware/esphome-web-d0df24.example.yaml) | Sanitised example of the newly supplied configuration |
| [`Wtw.yaml`](https://github.com/dkwolf1/Brink-PCB/blob/main/Wtw.yaml), [`arduino/`](https://github.com/dkwolf1/Brink-PCB/tree/main/arduino), [`web/`](https://github.com/dkwolf1/Brink-PCB/tree/main/web) | Firmware and web interface already present in this repository |
| [`Pcb/`](https://github.com/dkwolf1/Brink-PCB/tree/main/Pcb) | PCB files already present in this repository |

## How it works

Each device connection uses three normally open, dry relay contacts. At most one contact should be closed per device; all contacts open form a fourth logical state. The actual meaning of each state depends on the connected Brink model and its settings. The ESP32 selects relay contacts; Brink's internal control and protection systems remain in charge of the appliance.

| Channel | PCB connector | GPIOs for the three contacts |
| --- | --- | --- |
| Renovent WTW | CN3 | 26, 27, 19 |
| Elan E upper zone | CN2 | 32, 23, 22 |
| Elan E lower zone | CN1 | 33, 25, 14 |

This mapping comes from the **project schematic**. It is not a universal Brink RJ12 pinout. The ESPHome labels `position 1` through `position 4` describe four contact combinations; they do not automatically match every appliance's speed numbering.

## Getting started

1. Review the [schematic](hardware/rev-2026-10-11/schema.pdf), [BOM](hardware/rev-2026-10-11/onderdelenlijst.tsv), and [hardware notes](docs/hardware.md).
2. Check the actual RJ12 cable with a multimeter. Identify pin numbers and continuity; wire colours are not reliable.
3. Test the relay module, signal polarity, supply, contact order, and cold-boot behaviour on the bench before connecting a Brink appliance.
4. Choose a firmware starting point. The existing [`Wtw.yaml`](https://github.com/dkwolf1/Brink-PCB/blob/main/Wtw.yaml) remains in the repository root; the newly supplied [ESPHome example](firmware/esphome-web-d0df24.example.yaml) is separate. Read the [firmware notes](docs/firmware.md).
5. Measure the X2 connection on your own appliance and test one channel at a time. The [Dutch articles](docs/artikelen/) provide additional background.

### Firmware already in this repository

The existing [`arduino/`](https://github.com/dkwolf1/Brink-PCB/tree/main/arduino) sketch and [`web/`](https://github.com/dkwolf1/Brink-PCB/tree/main/web) interface remain available alongside ESPHome. Follow the instructions in those files for their respective build and upload steps. The new YAML example has not been compiled or tested on the new PCB.

## Manufacturing files

[`hardware/rev-2026-10-11/`](hardware/rev-2026-10-11/) is a snapshot of one revision. `gerber.zip` contains the manufacturing layers and drill files. `pcb-lagen-png.zip` contains preview images only. The BOM is tab-separated and lacks manufacturer or supplier identifiers for several parts. Check footprints, values, and availability before ordering.

No native EasyEDA source file for this revision was included with the supplied files. The PDF schematic and Gerbers can be reviewed and used for fabrication, but they do not replace an editable schematic and PCB project.

## Safety

- X2 is a **low-voltage interface**. Never connect mains voltage to the RJ12 lines.
- Do not assume the Brink relay-contact reference is the same as ESP ground.
- A filter line that may carry approximately 24 V must not be connected directly to an ESP32 GPIO. Measure its voltage and polarity on the actual appliance before using the filter circuit.
- Software interlocks alone do not guarantee safe relay behaviour during reset, boot, or incorrect wiring.
- This is a self-build project, not a Brink-approved modification. Verify the appliance revision, wiring, and operation in your own installation.

## License

The existing repository is published under the [MIT license](https://github.com/dkwolf1/Brink-PCB/blob/main/LICENSE). The license file lives in the GitHub repository; this update package does not replace it. If you want separate licenses for the new material, define their scope and copyright holders first. CERN-OHL-P-2.0 is a permissive option tailored to hardware designs; CC BY 4.0 is an option for articles you own.
